#!/bin/sh
./bin/rshell << EOF

echo test -e bin
echo
test -e bin

echo test -f bin
echo
test -f bin

echo test -d bin
echo
test -d bin

echo test -e src/Analyze.cpp
echo
test -e src/Analyze.cpp

echo test -f src/Analyze.cpp
echo
test -f src/Analyze.cpp

echo test -d src/Analyze.cpp
echo
test -d src/Analyze.cpp

echo test src
echo
test src

echo test src/Analyze.cpp
echo
test src/Analyze.cpp

echo [ src ]
echo
[ src ]

echo [ -d src ]
echo
[ -d src ]

echo [ -f src ]
echo
[ -f src ]

echo test -d src && [ src/Parse.cpp ]
echo
test -d src && [ src/Parse.cpp ]

echo test -f src || [ -d src ]
echo
test -f src || [ -d src ]

echo [ src ] ; [ src/Main.cpp ]
echo
[ src ] ; [ src/Main.cpp ]

echo ( test -d src ) && ( [ -f src/Analyze.cpp] )
echo
( test -d src ) && ( [ -f src/Analyze.cpp] )

exit
EOF
echo
