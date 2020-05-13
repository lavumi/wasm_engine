echo 
echo 
echo ------ select build type ------
echo 0. MAC
echo 1. WASM
echo 
read input

if [ $input -eq 0 ]; then 
    # clang++ *.cpp -std=c++11 -Wall -Wextra -lglew -lsdl2 -framework OpenGL -g -v -o mac/app
    ./mac/make clean
    ./mac/make
fi

if [ $input -eq 1 ]; then 
    rm -rf wasm
    mkdir wasm
    emcc .././main.cpp  .././Framework/InputHandler.cpp .././Framework/TestCube.cpp  .././Framework/Render/Camera.cpp .././Framework/Render/Render.cpp .././Framework/Render/Shader.cpp -std=c++17 -s WASM=1 -s USE_SDL=2 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -O3 -v -o wasm/index.js
fi


