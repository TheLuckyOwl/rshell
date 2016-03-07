#!/bin/sh
./bin/rshell << EOF

echo
( [ src ] && [ src/Analyze.cpp ] )

echo
( echo A ) || ( echo B )

echo
( test -d src ) || ( test -f src/Expansion.h )

echo
( echo A && echo B ) || ( echo C && echo D )

echo
((( [ tests ] )) & test src )

echo
(echo A && echo B || echo C) || echo D

echo
(echo "A") && (echo "B" && sdfhlsdjfl || ls -a)

echo
(ls -a || ls -l || echo "B") && cal

echo
((echo A || echo B) && (echo C || echo D))

echo
(test -e src)

echo
sdkfjsdkldjs || (([tests] || echo A) && echo B)

exit
EOF
echo
