#! /bin/bash
set -o errexit
set -o nounset
shopt -s extglob
#set -o verbose

snake_it() {
    for it in "${@}"; do
	local basename="${it%.*}"
	local extension="${it##*.}"
	local replaced_with_underscore="${basename//+([[:space:]]|[[:punct:]])/_}"
	local different_cases_with_underscore=$( echo "${replaced_with_underscore}" | sed -e "s/\([a-z]\)\([A-Z]\)/\1_\2/g" )
	local all_lower_case="${different_cases_with_underscore,,}"
	echo "${all_lower_case}.${extension}"
    done
}

check_snake_it() {
    local check_text="${1}"
    local expected="${2}"
    shift 2
    local actual=$( snake_it "${@}" )
    if [ "${expected}" != "${actual}" ]; then
	{
	    printf "FAILURE in \"%s\"\n" "${check_text}"
	    printf "input    = %s\n" "${@}"
	    printf "expected = %s\n" "${expected}"
	    printf "actual   = %s\n" "${actual}"
	} >&2
	exit 1
    fi
}

check() {
    eval '$@'
}

check_snake_it "replace space with _" "a_b_c_d.txt" "a b c d.txt"
check_snake_it "collapse multiple spaces to one _" "a_b_c_d.txt" "a b  c   d.txt"
check_snake_it "convert upper to lower" "a_b_c_d.txt" "A B C D.txt"
check_snake_it "insert _ between camel cased letters" "a_b_c_d.txt" "aB cD.txt"
check_snake_it "seperator . is replaced with _" "1_12_123_1234.txt" "1.12.123.1234.txt"
check_snake_it "seperator - is replaced with _" "1_12_123_1234.txt" "1-12-123-1234.txt"
check_snake_it "multiple texts are snaked with \\n as seperator" "a_b_c_d.txt
a_b_c_d.txt
a_b_c_d.txt
a_b_c_d.txt
1_12_123_1234.txt
1_12_123_1234.txt" "a b c d.txt" "a b  c   d.txt" "A B C D.txt" "aB cD.txt" "1.12.123.1234.txt" "1-12-123-1234.txt"

for it in *; do
    snaked=$( snake_it "${it}" )
    if [ "${snaked}" != "${it}" ]; then
	printf "before = %s\nafter  = %s\n" "${it}" "${snaked}"
    fi
done


check 'echo "1 2 3\n" " 4 5 6\n" " 7 8 9 10\n"'
#check "printf" "%s\n %s\n %s\n" "1 2 3" "4 5 6" "7 8 9 10"

#check check_snake_it "convert upper to lower" "a_b_c_d.txt" "A B C D.txt"
