@set CRT_INCLUDE_DIR=C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt
@set VS_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133
@set SDL_DIR=F:\SDL2-2.32.8
set INCLUDE=%SDL_DIR%\include;%CRT_INCLUDE_DIR%;%VS_DIR%\include
cl.exe /MD /c main.c
cl.exe /MD /c render.c
set LINK=%SDL_DIR%\lib\x64\SDL2.lib %SDL_DIR%\lib\x64\SDL2main.lib
link.exe /out:main.exe main.obj render.obj /subsystem:windows kernel32.lib shell32.lib ucrt.lib