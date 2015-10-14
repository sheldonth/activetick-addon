if [! type protoc > /dev/null]
  then
    case $( uname -s ) in
    Linux)
      echo 'Run "sudo apt-get install protobuf" and try again'
      exit 1
      ;;
    Darwin)
      echo echo 'Run "brew install protoc" and try again.'
      exit 1
      ;;
    esac
fi

sysname=$(uname -s)
arch=$(uname -m)

mkdir import
cd import

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
  curl https://www.activetick.com/activetick/contents/binaries/atfeedapi/atfeed-cppsdk-osx.i386.tar.gz | tar x
  cp atfeed-cppsdk/bin/libActiveTickServerAPI.dylib ..
  ;;
esac

cd ..
./protobuf/build.sh

exit 0

