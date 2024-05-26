mkdir -p lib
cd lib

# Get freetype
rm -f freetype-master.tar.gz
rm -rf freetype
wget https://gitlab.freedesktop.org/freetype/freetype/-/archive/master/freetype-master.tar.gz
tar -xf freetype-master.tar.gz
rm freetype-master.tar.gz
mv freetype-master freetype # rename
cd freetype
mkdir build
cd build
cmake ..
make

cd ../..

# Get freetype-gl
# Requires doxygen
#echo "------------ WARNING ------------"
#echo "freetype-gl requires doxygen, libglfw3, imagemagick (Debian-Based Package-Names)"
#echo "Check if you have these installed on your system before pressing Enter..."
#read -n 1 -p "------------ WARNING ------------"
#rm -rf freetype-gl
#git clone https://github.com/rougier/freetype-gl.git
#cd freetype-gl
#mkdir build
#cd build
#cmake .. -DOpenGL_GL_PREFERENCE="GLVND" -DFREETYPE_INCLUDE_DIRS="../../freetype/include" -DFREETYPE_LIBRARY="../../freetype/build/libfreetype2.a" -DGLEW_LIBRARY="../../glew/lib/libglew.a" -DGLEW_INCLUDE_PATH="../../glew/include"
#make

#cd ../..

# Get glew (KEEP VERSION UP TO DATE)
rm -f glew-2.2.0.tgz
rm -rf glew
wget https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.tgz
tar -xf glew-2.2.0.tgz
rm glew-2.2.0.tgz
mv glew-2.2.0 glew # rename
cd glew
make

cd ..

# Get glm
rm -rf glm
git clone https://github.com/g-truc/glm.git
cd glm
mkdir build
cd build
cmake ..
make

# Move glm to inlcude/glm
cd ..
mkdir include
mv glm include/glm
cd ..

# Get glfw
# Requires libwayland-dev and pkg-config and libxkbcommon-dev
echo "------------ WARNING ------------"
echo "GLFW requires libwayland-dev, pkg-config, libxkbcommon-dev, libglu1-mesa-dev (Debian-Based Package-Names)"
echo "Check if you have these installed on your system before pressing Enter..."
read -n 1 -p "------------ WARNING ------------"

rm -rf glfw
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake ..
make