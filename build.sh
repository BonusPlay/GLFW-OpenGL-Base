GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
NOCOLOR="\033[0m"

if [ $1 == "Debug"]; then
	BUILD_TYPE="Debug"
else
	BUILD_TYPE="Release"
fi

echo -e -n "${YELLOW}[WARNING]${NOCOLOR} To build GLFW on linux it is required to install 'xorg-dev' and 'opengl' packages. Did you install them (y/n)? "
read -p "" choice
case "$choice" in
	n|N ) [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1
esac

echo -e "${GREEN}> Initializing git submodules${NOCOLOR}"

# util for restoring submodules from .gitmodules file

git config -f .gitmodules --get-regexp '^submodule\..*\.path$' |
    while read path_key path
    do
        url_key=$(echo $path_key | sed 's/\.path/.url/')
        url=$(git config -f .gitmodules --get "$url_key")
        git submodule add $url $path
    done

git submodule update --init --recursive
git submodule update --recursive

echo -e "${GREEN}> Building submodules${NOCOLOR}"
cd lib

# assimp
if [ ! -d assimp/build ]
then
	echo -e "${GREEN}[1/4] building assimp${NOCOLOR}"
	mkdir -p assimp/build
	cd assimp/build
	cmake -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ..
	make -j$(nproc)
	cd ../..
else
	echo -e "${GREEN}[1/4] assimp build found${NOCOLOR}"
fi

# bass
if [ ! -d bass/x64 ]
then
	echo -e "${GREEN}[2/4] building bass${NOCOLOR}"
	mkdir -p bass
	cd bass
	wget http://uk.un4seen.com/files/bass24-linux.zip
	unzip bass24-linux.zip -d .
	rm bass24-linux.zip
	cd ..
else
	echo -e "${GREEN}[2/4] bass build found${NOCOLOR}"
fi

# glfw
if [ ! -d glfw/build ]
then
	echo -e "${GREEN}[3/4] building glfw${NOCOLOR}"
	mkdir -p glfw/build
	cd glfw/build
	cmake -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF -DGLFW_VULKAN_STATIC=OFF -DCMAKE_BUILD_TYPE=Release ..
	make -j$(nproc)
	cd ../..
else
	echo -e "${GREEN}[3/4] glfw build found${NOCOLOR}"
fi

# imgui
echo -e "${GREEN}[4/4] copying imgui${NOCOLOR}"
cp imgui/*.cpp ../src/imgui
cp imgui/imconfig.h ../src/imgui

echo -e "${GREEN} > Building main project for ${BUILD_TYPE}${NOCOLOR}"
mkdir -p ../build
cd ../build
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make -j$(nproc)
echo -e "${GREEN} > Copying resources${NOCOLOR}"
cp -r ../src/res .
