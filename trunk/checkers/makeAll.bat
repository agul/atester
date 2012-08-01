@echo off

set CHECKER_NAME=acmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=dcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=fcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=hcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=icmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=lcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=ncmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=rcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=rcmp4
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=rcmp6
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=rcmp9
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=rncmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=wcmp
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"

set CHECKER_NAME=yesno
echo Compiling %CHECKER_NAME%.cpp...
"C:\MinGW\bin\g++.exe" -c src\%CHECKER_NAME%.cpp -o src\temp\%CHECKER_NAME%.o -I"C:\MinGW/include"
"C:\MinGW\bin\g++.exe" src\temp\%CHECKER_NAME%.o -o exe\%CHECKER_NAME%.exe -L"C:\MinGW/lib"