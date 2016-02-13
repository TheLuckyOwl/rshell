#!/bin/sh
./bin/rshell << EOF

echo pwd && ls -l && date
echo
pwd && ls -l && date

echo ls -a || ls -l && date
echo
ls -a || ls -l && date

echo pwd ; ls ; date
echo
pwd ; ls ; date

echo ls -a || ls -l || pwd
echo
ls -a || ls -l || pwd

echo pwd || ls -l && ls -a
echo
pwd || ls -l && ls -a

echo date ; pwd && ls -l
echo
date ; pwd && ls -l

echo date ; pwd || ls -al
echo
date ; pwd || ls -al

echo date || pwd ; ls -al
echo
date || pwd ; ls -al

echo date && pwd ; ls -al
echo
date && pwd ; ls -al

exit
EOF
echo
