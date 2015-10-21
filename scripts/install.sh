sysname=$(uname -s)
arch=$(uname -m)

cd protobuf
./build.sh
cd ..

mkdir import
cd import

case $( uname -s ) in
Linux)
  if [ "$arch" == "x86_64" ]
  then
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-ubuntu.x86_64.tar.gz | tar xz
  else
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-ubuntu.i386.tar.gz | tar xz
  fi
  cp atfeed-cppsdk/bin/libActiveTickServerAPI.so ..
  ;;
Darwin)
  curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-osx.i386.tar.gz | tar x
  cp atfeed-cppsdk/bin/libActiveTickServerAPI.dylib ..
  ;;
esac

exit 0

