@echo off

set XPJ="xpj4.exe"

%XPJ% -v 1 -t VC14 -p WIN64 -x obj2usda.xpj

cd ..
cd vc14win64

goto cleanExit

:pauseExit
pause

:cleanExit

