set -o errexit
set -o nounset

. /Users/Tobi/projects/programming/coding_dojo/case_it/bash/snake_it.sh

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
	    echo "renamed " "${it}" " to " "${snaked}"
	fi
    fi
done
rm -d *xzr
