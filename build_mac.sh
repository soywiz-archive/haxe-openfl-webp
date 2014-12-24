mkdir ndll/Mac 2> /dev/null
mkdir ndll/Mac64 2> /dev/null
pushd project
haxelib run hxcpp Build.xml -Dmac
haxelib run hxcpp Build.xml -Dmac -DHXCPP_M64
popd
