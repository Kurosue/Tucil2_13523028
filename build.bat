@echo off
echo [INFO] Compiling the program...

gcc -o bin\program.exe src\main.c src\image.c src\quadtree.c src\errorcalculations.c -lm -ljpeg -lz

if %errorlevel% neq 0 (
    echo [ERROR] Compilation failed.
    exit /b %errorlevel%
)

echo [SUCCESS] Compilation finished.
echo [INFO] Running the program...
bin\program.exe
