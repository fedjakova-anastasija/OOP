set PROGRAM="%~1"

REM запуск программы без параметров          
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM 256 
%PROGRAM% 256                                 
IF NOT ERRORLEVEL 1 GOTO err

REM 7654312345678987654 
%PROGRAM% 7654312345678987654                                 
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с отрицательным числом
%PROGRAM% -1                               
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с нечисловымы входными данными  
%PROGRAM% a                                
IF NOT ERRORLEVEL 1 GOTO err

REM 6 96 
%PROGRAM% 6 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output1.txt 
IF ERRORLEVEL 1 GOTO err  

REM 200 19 
%PROGRAM% 200 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output2.txt 
IF ERRORLEVEL 1 GOTO err      

                     
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT