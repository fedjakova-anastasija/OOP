set PROGRAM="%~1"

REM запуск программы без параметров
%PROGRAM%
IF ERRORLEVEL 1 GOTO err

REM запуск программы с одним нечисловым параметром
%PROGRAM% notANumber
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустой строкой в качестве одного из параметров
%PROGRAM% ""
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним числовым параметром (и проверяем результат)
%PROGRAM% -123 > output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt test\-123.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с двумя числовыми параметрами
%PROGRAM% 15 2 > output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt test\15+2=17.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с тремя числовыми параметрами
%PROGRAM% 15 2 -8 > output.txt
IF ERRORLEVEL 1 GOTO err
FC output.txt test\15+2+-8=9.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT