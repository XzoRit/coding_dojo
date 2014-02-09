#!/bin/bash

set -o errexit
set -o nounset
shopt -s extglob
#set -x
#set -o verbose

# usage: xzr_snake_it txt1 txt2 txt3 ...
# result is stored in XZR_SNAKED
xzr_snake_it() {
    XZR_SNAKED=
    for it in "${@}"; do
	local replaced_with_underscore="${it//+([[:space:]]|[[:punct:]])/_}"
	local different_cases_with_underscore=$( echo "${replaced_with_underscore}" |\
                                                 sed -e "s/\([a-z]\)\([A-Z]\)/\1_\2/g" )
	XZR_SNAKED="${XZR_SNAKED:+"${XZR_SNAKED}" }${different_cases_with_underscore,,}"
#	echo "${XZR_SNAKED}"
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

xzr_check xzr_snake_it XZR_SNAKED "replace space with _" "a_b_c_d" "a b c d"
xzr_check xzr_snake_it XZR_SNAKED "collapse multiple spaces to one _" "a_b_c_d" "a b  c   d"
xzr_check xzr_snake_it XZR_SNAKED "convert upper to lower" "a_b_c_d" "A B C D"
xzr_check xzr_snake_it XZR_SNAKED "insert _ between camel cased letters" "a_b_c_d" "aB cD"
xzr_check xzr_snake_it XZR_SNAKED "seperator . is replaced with _" "1_12_123_1234" "1.12.123.1234"
xzr_check xzr_snake_it XZR_SNAKED "seperator - is replaced with _" "1_12_123_1234" "1-12-123-1234"
xzr_check xzr_snake_it XZR_SNAKED "multiple texts are snaked with a space as seperator" "a_b_c_d a_b_c_d a_b_c_d a_b_c_d 1_12_123_1234 1_12_123_1234" "a b c d" "a b  c   d" "A B C D" "aB cD" "1.12.123.1234" "1-12-123-1234"

# test renaming files/directories
touch "a b c d.xzr"
touch "a b  c   d e.xzr"
touch "A B C Df.xzr"
touch "aB cDg.xzr"
touch "1.12.123.1234.xzr"
touch "1-12-123-1234-12345.xzr"
touch "1_12_123_1234_12345.xzr"
mkdir "test 1 12 aGoodTest Xzr"
for it in *; do
    extension=
    basename="${it}"
    if [ -f "${it}" ]; then
	basename="${it%.*}"
	extension=".${it##*.}"
    fi
    xzr_snake_it "${basename}"
    snaked="${XZR_SNAKED}${extension}"
    if [ "${snaked}" != "${it}" ]; then
	if [ \( -f "${it}" -o -d "${it}" \) -a ! \( -e "${snaked}" \) ]; then
	    mv "${it}" "${snaked}"
	fi
	echo "${snaked}"
    fi
done
rm -d *xzr
