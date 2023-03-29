CPP = g++
CPP_EMCC = emcc

WORKSPACE = .
BUILDFOLDER = ./build

SRCDIR1 = $(WORKSPACE)/Framework
SRCDIR2 = $(WORKSPACE)/Framework/Render
SRCDIR3 = $(WORKSPACE)/Framework/Render/Shader
SRCDIR4 = $(WORKSPACE)/Framework/Node
SRCDIR5 = $(WORKSPACE)/src

LDFLAGS = -lglew -lsdl2 -framework OpenGL
LDFLAGS_EMCC = -s USE_SDL=2 -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s USE_GLFW=3 -O3 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS="['png']" --preload-file Resources



SRCS = $(foreach dir, $(WORKSPACE) $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) ${SRCDIR5}, $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

TARGET = build/mac/main
TARGET_EMCC = build/wasm_helltaker/wasm.js

all : $(TARGET)
	$(CPP) -Wall -Wextra -o $(TARGET) $(notdir $(OBJS)) $(LDFLAGS)

$(TARGET) :
	$(CPP) -std=c++17 -c  $(SRCS)

emcc : $(TARGET_EMCC)
	$(CPP_EMCC) -Wall -Wextra -o $(TARGET_EMCC) $(notdir $(OBJS)) $(LDFLAGS_EMCC)

$(TARGET_EMCC) :
	$(CPP_EMCC) -std=c++17 -c $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
	rm -f $(TARGET_EMCC)