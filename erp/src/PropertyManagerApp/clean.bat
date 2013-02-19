cd FVector
rd /q /s Debug
rd /q /s Release
del /q *.ncb
attrib -s -h *.suo
del /q *.suo
del /q *.user
del /q *.aps
rd /q /s Debug

rd /q /s ReleaseLib
rd /q /s DebugLib
 
cd ../PropertyManagerApp
rd /q /s Debug
rd /q /s Release
del /q /s *.aps
del /q /s *.aps
del /q /s *.user

cd ../Debug
del /q *.pdb
del /q *.ilk
del /q *.exe
del /q *.lib

cd ../Release
del /q *.pdb
del /q *.ilk
del /q *.exe
del /q *.lib

cd ..
del /q *.ncb
attrib -s -h *.suo
del /q *.suo
del /q *.user
del /q *.aps

