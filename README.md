# C-python-loader
C code for wraping python scripts in an executable (bootleg pyinstaller)


how to use (on linux):

step 1:

    git clone https://github.com/9-s3c/C-python-loader

step 2:

    cd C-python-loader/

step 3:

    nano main.c
    #define IN "your base64 encoded python script"

step 4:

    sudo apt install mingw-w64-i686-dev -y
    
step 5:

    i686-w64-mingw32-gcc -o main.exe main.c -lurlmon -w

