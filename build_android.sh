mkdir ndll/Android 2> /dev/null
pushd project
haxelib run hxcpp Build.xml -Dandroid
haxelib run hxcpp Build.xml -Dandroid -DHXCPP_ARMV7
haxelib run hxcpp Build.xml -Dandroid -DHXCPP_X86
popd
