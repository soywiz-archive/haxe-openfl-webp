@echo off
pushd %~dp0
del deploy.zip 2> NUL
"%~dp0\tools\7z" a deploy.zip -r -xr!.git -xr!obj -xr!*.pdb -xr!all_objs
haxelib submit deploy.zip
del deploy.zip 2> NUL
popd