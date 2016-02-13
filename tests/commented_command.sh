#!/bin/sh
./bin/rshell <<EOF

echo pwd #This is a comment
echo
pwd #This is a comment

echo ls #This is a comment
echo 
ls #This is a comment

echo ls -l #This wont run &&
echo
ls -l #This wont run &&

echo ls -a #This is a comment ||
echo
ls -a #This is a comment ||

echo ls -la #This is a comment ;
echo
ls -la #This is a comment ;

echo mkdir madeDir #test comment ;&
echo
mkdir madeDir #test comment ;&

echo rmdir madeDir #test comment ;&
echo
rmdir madeDir #test comment ;&

echo date && ls -a && pwd #This comment won't be read
echo
date && ls -a && pwd #This comment won't be read

echo date ; ls -a || pwd #This won't be read
echo
date ; ls -a || pwd #This won't be read

echo date || ls -a ; pwd #Test comment
echo
date || ls -a ; pwd #Test comment

exit

EOF
echo
