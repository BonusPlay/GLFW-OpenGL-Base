read -p "To build GLFW on linux it is required to install 'xorg-dev' and 'opengl' packages. Did you install them (y/n)? " choice
case "$choice" in
	n|N ) [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1
esac

echo "> Initializing git submodules"

# util for restoring submodules from .gitmodules file

#if [ ! -d 
#git config -f .gitmodules --get-regexp '^submodule\..*\.path$' |
#    while read path_key path
#    do
#        url_key=$(echo $path_key | sed 's/\.path/.url/')
#        url=$(git config -f .gitmodules --get "$url_key")
#        git submodule add $url $path
#    done

git submodule update --init --recursive
git submodule update --recursive

echo "> Building submodules"
cd lib

# assimp
if [ ! -d assimp/build ] 
then
	echo "   > building assimp"
	mkdir -p assimp/build
	cd assimp/build
	cmake -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_TESTS=OFF ..
	make -j$(nproc)
	cd ../..
else
	echo "   > assimp build found"
fi

# bass
if [ ! -d bass/x64 ]
then
	echo "   > building bass"
	mkdir -p bass
	cd bass
	wget http://uk.un4seen.com/files/bass24-linux.zip
	unzip bass24-linux.zip -d .
	rm bass24-linux.zip
	cd ..
else
	echo "   > bass build found"
fi

# glfw
if [ ! -d glfw/build ] 
then
	echo "   > building glfw"
	mkdir -p glfw/build
	cd glfw/build
	cmake -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF -DGLFW_VULKAN_STATIC=OFF ..
	make -j$(nproc)
	cd ../..
else
	echo "   > glfw build found"
fi

# imgui
echo "   > copying imgui"
cp imgui/*.cpp ../src/imgui

echo "> Building main project"
mkdir -p ../build
cd ../build
cmake ..
make -j$(nproc)