#!/bin/sh
./bin/rshell <<EOF

echo pwd
pwd

echo ls
echo
ls

echo ls -l
echo
ls -l

echo ls -a
echo
ls -a

echo ls -la
echo
ls -la

echo mkdir madeDir
echo
mkdir madeDir

echo rmdir madeDir
echo
rmdir madeDir

echo touch madeFile
echo
touch madeFile

echo rm madeFile
echo
rm madeFile

echo date
echo
date

exit

EOF
echo
