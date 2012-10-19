mkdir ndll/iPhone 2> /dev/null
pushd project
haxelib run hxcpp Build.xml -Diphonesim
haxelib run hxcpp Build.xml -Diphoneos
popd