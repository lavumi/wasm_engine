CPP = g++

WORKSPACE = ../.

SRCDIR1 = $(WORKSPACE)/Framework


LDFLAGS = -lncurses -lglew -lsdl2
FRAMEWORK = OpenGL


# SRCS = $(foreach dir, . ..  $(SRCDIR1) $(SRCDIR2) $(SRCDIR3) $(SRCDIR4) $(SRCDIR5) $(SRCDIR6) $(SRCDIR7) $(SRCDIR8), $(wildcard $(dir)/*.cpp))

SRCS = $(foreach dir, $(WORKSPACE) $(SRCDIR1), $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

TARGET = mac/main

all : $(TARGET)
	$(CPP) -Wall -Wextra -o $(TARGET) $(notdir $(OBJS)) $(LDFLAGS) -framework $(FRAMEWORK)

$(TARGET) :
	$(CPP) -std=c++17 -c  $(SRCS)

clean : 
	rm -f *.o
	rm -f $(TARGET)