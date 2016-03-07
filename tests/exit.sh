#!/bin/sh
./bin/rshell << EOF

echo ls -l && exit
echo
ls -l && exit
exit
EOF

./bin/rshell << EOF

echo date && exit
echo
date && exit
exit
EOF

./bin/rshell << EOF

echo pwd ; exit
echo
pwd ; exit
exit
EOF

./bin/rshell << EOF

echo ls -al ; exit
echo
ls -al ; exit
exit
EOF

./bin/rshell << EOF

echo ls -al && pwd ; exit
echo
ls -al && pwd ; exit
exit
EOF

./bin/rshell << EOF

echo pwd ; ls -a && exit
echo
pwd ; ls -a && exit
exit
EOF

./bin/rshell << EOF

echo
[ src ] ; exit
exit
EOF

./bin/rshell << EOF
  
echo
( echo "A" || exit ) && exit
exit
EOF

./bin/rshell << EOF

echo
( (exit) || echo "A" ) && sdkfjdskjfldsj
exit
EOF

./bin/rshell << EOF

echo
[ src/guineafowl ] ; exit
exit
EOF

./bin/rshell << EOF

echo
test -d tests && (fakeCommand || exit)
exit
EOF

./bin/rshell << EOF

echo
( echo "A" || exit ) && (( exit ))
exit
EOF

./bin/rshell << EOF

echo
(\t (echo "A" || echo "B" || echo "C") && (echo "D" || exit ) && exit )
exit
EOF
