#if [ ! -d lib/freetype-gl ]; then
if [ ! -d lib/freetype ]; then
  ./getlibs.sh
elif [ ! -d lib/glew ]; then
  ./getlibs.sh
elif [ ! -d lib/glm ]; then
  ./getlibs.sh
  elif [ ! -d lib/glfw ]; then
  ./getlibs.sh
fi

mkdir -p build
cd build
cmake ..
make