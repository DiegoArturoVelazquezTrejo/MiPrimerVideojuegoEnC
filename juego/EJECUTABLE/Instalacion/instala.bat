@echo off
rem Este archivo permite la instalación de la carpeta con documentos del juego. 
cls
@echo Inicio de instalación
pause 
md c:\cartas
xcopy /s cartas\*.* c:\cartas