REM показать список каталогов диска C:
FOR %%A IN (c) DO dir %%A:*.*
REM вывести на экран содержимое всех текстовых файлов текущей директории
FOR %%f IN (*.txt) DO type %%f 
