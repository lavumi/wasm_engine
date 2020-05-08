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
    emcc ../main.cpp ../Framework/Render.cpp ../Framework/InputHandler.cpp -std=c++17 -s WASM=1 -s USE_SDL=2 -O3 -o wasm/index.js
fi

