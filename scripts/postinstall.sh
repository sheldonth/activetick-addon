current_dir=$(pwd)
script_dir=$(dirname $0)
dylib='/import/atfeed-cppsdk/bin/libActiveTickServerAPI.dylib'
r=$current_dir$dylib

case $( uname -s ) in
Darwin)
  if [ -f build/Release/NodeActiveTickAddon.node ]; then
    install_name_tool -change "libActiveTickServerAPI.dylib" $r build/Release/NodeActiveTickAddon.node
  fi
  if [ -f build/Debug/NodeActiveTickAddon.node ]; then
    install_name_tool -change "libActiveTickServerAPI.dylib" $r build/Debug/NodeActiveTickAddon.node 
  fi
  ;;
esac
