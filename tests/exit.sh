#!/bin/sh
./bin/rshell << EOF

echo ls -l && exit
echo
ls -l && exit

EOF

./bin/rshell << EOF

echo date && exit
echo
date && exit

EOF

./bin/rshell << EOF

echo pwd ; exit
echo
pwd ; exit

EOF

./bin/rshell << EOF

echo ls -al ; exit
echo
ls -al ; exit

EOF

./bin/rshell << EOF

echo ls -al && pwd ; exit
echo
ls -al && pwd ; exit

EOF

./bin/rshell << EOF

echo pwd ; ls -a && exit
echo
pwd ; ls -a && exit

EOF
