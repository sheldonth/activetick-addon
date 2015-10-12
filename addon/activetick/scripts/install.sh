if ! type wget > /dev/null; then
  echo 'Please install wget'
  exit 1
fi

# cd ..
# mkdir import
sysname=$(uname -s)
arch=$(uname -m)

case $( uname -s ) in
Linux)
  if [ "$arch" == "x86_64" ]
  then
    echo Linux64bit
  else
    echo Linux32bit
  fi
  ;;
Darwin)
  if [ "$arch" == "x86_64" ]
  then
    echo Mac64
  else
    echo Mac32
  fi
  ;;
esac

# echo $uname -s

