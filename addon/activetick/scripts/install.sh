if ! type wget > /dev/null; then
  echo 'Run "sudo apt-get install wget" and try again.'
  exit 1
fi

if ! type protoc > /dev/null; then
  echo 'Run "sudo apt-get install protobuf" and try again'
  exit 1
fi

mkdir import
cd import
sysname=$(uname -s)
arch=$(uname -m)

case $( uname -s ) in
Linux)
  if [ "$arch" == "x86_64" ]
  then
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-ubuntu.x86_64.tar.gz | tar x
  else
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-ubuntu.i386.tar.gz | tar x
  fi
  cp atfeed-cppsdk/bin/libActiveTickServerAPI.so ..
  ;;
Darwin)
  if [ "$arch" == "x86_64" ]
  then
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-osx.i386.tar.gz | tar x
  else
    curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-osx.i386.tar.gz | tar x
  fi
  cp atfeed-cppsdk/bin/libActiveTickServerAPI.dylib ..
  ;;
esac

exit 0

