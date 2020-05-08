echo 
echo 
echo ------ select build type ------
echo 0. MAC
echo 1. WASM
echo 
read input

if [ $input -eq 0 ]; then 
    rm -r build/mac
    mkdir build/mac
    clang++ *.cpp -std=c++11 -Wall -Wextra -lglew -lsdl2 -framework OpenGL -g -v -o build/mac/app
fi

if [ $input -eq 1 ]; then 
    rm -rf build/wasm
        mkdir build/wasm
    emcc main.cpp -std=c++11 -s WASM=1 -s USE_SDL=2 -O3 -o build/wasm/index.js
fi

