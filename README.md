### 1. MAC install libs

    brew install glew
    brew install sdl2
    brew install glm



### 2. WASM BUILD

```    
    //Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

    //Enter that directory
cd emsdk

    //Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

    //Download and install the latest SDK tools.
./emsdk install latest

    //Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

    //Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```




### 3. TODO works
- 화면 전환시에 ( dt 가 큰 값이 오면) 큐브 틀어짐
- 변경한 것만 빌드하는 cmake
- emcc 빌드 매번 등록 안해도 되게...


<!-- done -->
<!-- - emcc 빌드할 때 REMOTE_PACKAGE_PATH 변경 필요 -->