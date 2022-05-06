CPP = g++
CPP_EMCC = emcc

WORKSPACE = ../.

SRCDIR1 = $(WORKSPACE)/Framework
SRCDIR2 = $(WORKSPACE)/Framework/Render

LDFLAGS = -lglew -lsdl2 -framework OpenGL
LDFLAGS_EMCC = -s WASM=1 -s USE_SDL=2 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -O3



# SRCS = $(foreach dir, . ..  $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) $(SRCDIR5) $(SRCDIR6) $(SRCDIR7) $(SRCDIR8), $(wildcard $(dir)/*.cpp))

SRCS = $(foreach dir, $(WORKSPACE) $(SRCDIR1) $(SRCDIR2), $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

TARGET = mac/main
TARGET_EMCC = wasm/index.js

all : $(TARGET)
	$(CPP) -Wall -Wextra -o $(TARGET) $(notdir $(OBJS)) $(LDFLAGS)

$(TARGET) :
	$(CPP) -std=c++17 -c  $(SRCS)

emcc : $(TARGET_EMCC)
	$(CPP_EMCC) -Wall -Wextra -o $(TARGET_EMCC) $(notdir $(OBJS)) $(LDFLAGS_EMCC)

$(TARGET_EMCC) :
	$(CPP_EMCC) $(LDFLAGS_EMCC) -std=c++17 -c $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
	rm -f $(TARGET_EMCC)