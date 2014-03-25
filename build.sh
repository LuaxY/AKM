DIR="$( cd "$( dirname "$0" )" && pwd )"

rm -rf $DIR/build
mkdir $DIR/build
cd $DIR/build
cmake ..
make