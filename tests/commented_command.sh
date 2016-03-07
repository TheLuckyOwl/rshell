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

echo [ src ] ; pwd #&& This is a Test || ( ls -l ) && ls -a.
echo
[ src ] ; pwd #&& This is a Test || ( ls -l ) && ls -a.

echo test -f src/Analyze.cpp #&& (test -d src) || skgjflskjs
echo
test -f src/Analyze.cpp #&& (test -d src) || skgjflskjs

echo "( echo 'A' ) && ls -a" #; exit
echo
( echo 'A' ) && ls -a #; exit

echo [ src ] && test -f src/Analyze.cpp #\t && ((test -d tests) && (echo "A"))
echo
[ src ] && test -f src/Analyze.cpp #\t &&  ((test -d tests) && (echo "A"))

echo "( echo "A" && ( echo "B" || echo "C" ) ) #&& cal ; (ls -a || ls -l)
echo 
( echo "A" && ( echo "B" || echo "C" ) ) #&& cal ; (ls -a || ls -l)

echo test -d tests #&& echo "A"
echo
test -d tests #&& echo "A"

echo [ -f src/Main.cpp ] #; test -e sdkfkjsdfsdkfj
echo
[ -f src/Main.cpp ] #; test -e sdkfkjsdfsdkfj

echo "((echo "A" && echo "B"))" #&& echo "C"
echo
((echo "A" && echo "B")) #&& echo "C"

echo "(echo A)||(echo B)" #&& [ src ]
echo
(echo A)||(echo B) #&& [ src ]

echo test -e src/Expansion.h #&& [ -d src ]
echo
test -e src/Expansion.h #&& [ -d src ]

echo test -d src/Main.cpp #|| echo "B"
echo
test -d src/Main.cpp #|| echo "B"

exit
EOF
echo
