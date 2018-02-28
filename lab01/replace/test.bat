set PROGRAM="%~1"

REM запуск программы без параметров           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с несуществующим файлом
%PROGRAM% input1.txt output.txt "ma" "*"
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с несуществующей в тексте строкой 
REM %PROGRAM% test\input.txt output.txt "nastya" "*"                                  
REM IF ERRORLEVEL 1 GOTO err 
REM FC output.txt test\outputExistString.txt 
REM IF ERRORLEVEL 1 GOTO err  

REM запуск программы с нулевой искомой строкой
%PROGRAM% test\input.txt output.txt "" "*"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputEmptyString.txt 
IF ERRORLEVEL 1 GOTO err  

REM запуск программы с заменой искомой строки на большую строку 
%PROGRAM% test\input.txt output.txt "ma" "***"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputLongString.txt 
IF ERRORLEVEL 1 GOTO err  

REM запуск программы с заменой искомой строки на меньшую строку
%PROGRAM% test\input.txt output.txt "ma" "*"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputShortString.txt 
IF ERRORLEVEL 1 GOTO err 

REM запуск программы с заменой искомой строки на нулевую строку 
%PROGRAM% test\input.txt output.txt "ma" ""                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputEmptyString.txt 
IF ERRORLEVEL 1 GOTO err 

REM запуск программы с заменой искомой строки 1231234 на любую строку 
%PROGRAM% test\input.txt output.txt "1231234" "*"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output1231234String.txt 
IF ERRORLEVEL 1 GOTO err 
                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT