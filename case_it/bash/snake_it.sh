#!/bin/bash

set -o errexit
set -o nounset
set -x
shopt -s extglob
#set -o verbose

snake_it() {
    for it in "${@}"; do
	local replaced_with_underscore="${it//+([[:space:]]|[[:punct:]])/_}"
	local different_cases_with_underscore=$( echo "${replaced_with_underscore}" | sed -e "s/\([a-z]\)\([A-Z]\)/\1_\2/g" )
	echo "${different_cases_with_underscore,,}"
    done
}

check() {
    local command="${1}"
    local check_name="${2}"
    local expected="${3}"
    shift 3
    local actual=$( "${command}" "${@}" )
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

check_snake_it() {
    check snake_it "${@}"
}

check_snake_it "replace space with _" "a_b_c_d" "a b c d"
check_snake_it "collapse multiple spaces to one _" "a_b_c_d" "a b  c   d"
check_snake_it "convert upper to lower" "a_b_c_d" "A B C D"
check_snake_it "insert _ between camel cased letters" "a_b_c_d" "aB cD"
check_snake_it "seperator . is replaced with _" "1_12_123_1234" "1.12.123.1234"
check_snake_it "seperator - is replaced with _" "1_12_123_1234" "1-12-123-1234"
check_snake_it "multiple texts are snaked with \\n as seperator" "a_b_c_d
a_b_c_d
a_b_c_d
a_b_c_d
1_12_123_1234
1_12_123_1234" "a b c d" "a b  c   d" "A B C D" "aB cD" "1.12.123.1234" "1-12-123-1234"

touch "a b c d.txt"
touch "a b  c   d.txt"
touch "A B C D.txt"
touch "aB cD.txt"
touch "1.12.123.1234.txt"
touch "1-12-123-1234.txt"
for it in *; do
    extension=
    basename="${it}"
    if [ -f "${it}" ]; then
	basename="${it%.*}"
	extension=".${it##*.}"
    fi
    snaked=$( snake_it "${basename}" )
    snaked="${snaked}${extension}"
    if [ "${snaked}" != "${it}" ]; then
	printf "before = %s\nafter  = %s\n" "${it}" "${snaked}"
    fi
done
rm "a b c d.txt"
rm "a b  c   d.txt"
rm "A B C D.txt"
rm "aB cD.txt"
rm "1.12.123.1234.txt"
rm "1-12-123-1234.txt"
