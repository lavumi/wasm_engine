echo 
echo ------ select build type ------
echo 1. MAC
echo 2. WASM
echo 
read -r input

if [ "$input" -eq 1 ]; then
    # clang++ *.cpp -std=c++11 -Wall -Wextra -lglew -lsdl2 -framework OpenGL -g -v -o mac/app
    make clean
    make
fi

if [ "$input" -eq 2 ]; then
    rm -rf wasm
    mkdir wasm
    make clean
    make emcc
    scp -r build/wasm_helltaker lavu.me:Works/WebPage/public
fi


