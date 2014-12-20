set -o errexit
set -o nounset
shopt -s extglob
#set -x
#set -o verbose

# usage: xzr_snake_it txt1 txt2 txt3 ...
# result is stored in XZR_SNAKED
xzr_snake_it() {
    XZR_SNAKED=
    until [ -z "${1}" ]; do
	set -o nounset
	local replaced_with_underscore="${1//+([[:space:]]|[[:punct:]])/_}"
	local different_cases_with_underscore=$( echo "${replaced_with_underscore}" |\
                                                 gsed -e "s/\([a-z]\)\([A-Z]\)/\1_\2/g" )
	XZR_SNAKED="${XZR_SNAKED:+"${XZR_SNAKED}" }${different_cases_with_underscore,,}"
	shift
	set +o nounset
    done
}

# usage: xzr_camel_it txt1 txt2 txt3 ...
# result is stored in XZR_CAMELED
xzr_camel_it() {
    XZR_CAMELED=
    until [ -z "${1}" ]; do
	set -o nounset
	xzr_snake_it "${1}"
	local cameled=$( echo "${XZR_SNAKED}" |\
                       gsed -e "s/_\([a-z0-9]\)/\U\1\E/g"  )
	XZR_CAMELED="${XZR_CAMELED:+"${XZR_CAMELED}" }${cameled}"
	shift
	set +o nounset
    done
}

# usage: xzr_pascal_it txt1 txt2 txt3 ...
# result is stored in XZR_PASCALED
xzr_pascal_it() {
    XZR_PASCALED=
    until [ -z "${1}" ]; do
	set -o nounset
	xzr_camel_it "${1}"
	local pascaled="${XZR_CAMELED^?}"
	XZR_PASCALED="${XZR_PASCALED:+"${XZR_PASCALED} "}${pascaled}"
	shift
	set +o nounset
    done
}

xzr_check() {
    local command="${1}"
    local return_value="${2}"
    local check_name="${3}"
    local expected="${4}"
    shift 4
    "${command}" "${@}"
    local actual="${!return_value}"
    if [ "${expected}" != "${actual}" ]; then
	{
	    printf "FAILURE in \"%s\"\n" "${check_name}"
	    printf "input    = %s\n" "${@}"
	    printf "expected = %s\n" "${expected}"
	    printf "actual   = %s\n" "${actual}"
	} >&2
	exit 1
    fi
}

# execute_tests=
# while getopts "t" OPTION; do
# case $OPTION in
# a)
# execute_tests=1
# ;;
# esac
# done

xzr_check xzr_snake_it XZR_SNAKED "replace space with _" "a_b_c_d" "a b c d"
xzr_check xzr_snake_it XZR_SNAKED "collapse multiple spaces to one _" "a_b_c_d" "a b  c   d"
xzr_check xzr_snake_it XZR_SNAKED "convert upper to lower" "a_b_c_d" "A B C D"
xzr_check xzr_snake_it XZR_SNAKED "insert _ between camel cased letters" "a_b_c_d" "aB cD"
xzr_check xzr_snake_it XZR_SNAKED "seperator . is replaced with _" "1_12_123_1234" "1.12.123.1234"
xzr_check xzr_snake_it XZR_SNAKED "seperator - is replaced with _" "1_12_123_1234" "1-12-123-1234"
xzr_check xzr_snake_it XZR_SNAKED "multiple texts are snaked with a space as seperator" "a_b_c_d a_b_c_d a_b_c_d a_b_c_d 1_12_123_1234 1_12_123_1234" "a b c d" "a b  c   d" "A B C D" "aB cD" "1.12.123.1234" "1-12-123-1234"

xzr_check xzr_camel_it XZR_CAMELED "test xzr_camel_it" "thisShouldBeCamelCased asWellAsThis" "This should be camel cased" "as well as this"
xzr_check xzr_pascal_it XZR_PASCALED "test xzr_pascal_it" "ThisShouldBePascalCased AsWellAsThis" "This should be pascal cased" "as well as this"
