mkdir ndll/Linux 2> /dev/null
mkdir ndll/Linux64 2> /dev/null
pushd project
haxelib run hxcpp Build.xml -Dlinux
haxelib run hxcpp Build.xml -Dlinux -DHXCPP_M64
popd
