set PROGRAM="%~1"

REM запуск программы без параметров          
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с несуществующим файлом
%PROGRAM% inputExist.txt
IF NOT ERRORLEVEL 1 GOTO err 

REM заполнение области внутри границ 
%PROGRAM% test\input1.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output1.txt 
IF ERRORLEVEL 1 GOTO err   
    
REM заполнение области внутри границ и все границ до стенки
%PROGRAM% test\input2.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output2.txt 
IF ERRORLEVEL 1 GOTO err 

REM отсутствие заполнения области внутри границ безначальной точки О
%PROGRAM% test\input3.txt > output.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output3.txt 
IF ERRORLEVEL 1 GOTO err  

REM заполнение области внутри и вне границ 
%PROGRAM% test\input4.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output4.txt 
IF ERRORLEVEL 1 GOTO err

REM заполнение области внутри и вне границ одной области и отсутствие заполнения в другой области
%PROGRAM% test\input5.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output5.txt 
IF ERRORLEVEL 1 GOTO err
                     
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT