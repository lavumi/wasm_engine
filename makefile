CPP = g++
EMSCRIPTEN = emcc

WORKSPACE = .

SRC_DIR_0 = $(WORKSPACE)/src
SRC_DIR_1 = $(WORKSPACE)/Framework
SRC_DIR_2 = $(WORKSPACE)/Framework/Render
SRC_DIR_3 = $(WORKSPACE)/Framework/Render/Shader
SRC_DIR_4 = $(WORKSPACE)/Framework/Node
SRC_DIR_5 = $(WORKSPACE)/Framework/Util


LDFLAGS = -lglew -lsdl2 -framework OpenGL
LDFLAGS_EMSCRIPTEN = -s USE_SDL=2 -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s USE_GLFW=3 -O3 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS="['png']" --preload-file Resources



SRCS = $(foreach dir, $(WORKSPACE) $(SRC_DIR_0) $(SRC_DIR_1) $(SRC_DIR_2) $(SRC_DIR_3) $(SRC_DIR_4) ${SRC_DIR_5}, $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

TARGET = build/mac/main
TARGET_EMSCRIPTEN = build/wasm_helltaker/wasm.js

all : $(TARGET)
	$(CPP) -Wall -Wextra -o $(TARGET) $(notdir $(OBJS)) $(LDFLAGS)

$(TARGET) :
	$(CPP) -std=c++17 -c  $(SRCS)

emscripten : $(TARGET_EMSCRIPTEN)
	$(EMSCRIPTEN) -Wall -Wextra -o $(TARGET_EMSCRIPTEN) $(notdir $(OBJS)) $(LDFLAGS_EMSCRIPTEN)

$(TARGET_EMSCRIPTEN) :
	$(EMSCRIPTEN) -std=c++17 -c $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
	rm -f $(TARGET_EMSCRIPTEN)