# C-python-loader
C code for wraping python scripts in an executable (bootleg pyinstaller)


how to use (on linux):

step 1:
    edit line 1 of main.c
    #define IN "your base64 encoded python script"

step 2:
    sudo apt install mingw-w64-i686-dev -y
    
step 3:
    i686-w64-mingw32-gcc -o main.exe main.c -lurlmon -w
