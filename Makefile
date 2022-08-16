
##---------------------------------------------------------------------
## Makefile for OpenGLRenderer
##
##
## SOURCES
##---------------------------------------------------------------------

TARGET = OpenGLRenderer
DIR_OUT = ./bin
SUBDIR = include include/imgui include/imgui/backends source source/core source/3D source/3D/Primatives
SOURCES = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.cpp))

OBJS = $(addprefix $(DIR_OUT)/, $(SOURCES:cpp=o))
OBJS += ./include/glad/glad.o

LINUX_GL_LIBS = -lGL
LIBS = $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

INC_DIRS = -I./ $(addprefix -I, $(SUBDIR))
CXXFLAGS = -std=c++17 $(INC_DIRS)
CXXFLAGS += -g -Wall -Wformat

PCH_SRC = ./source/PCH.hpp
PCH_OUT = $(DIR_OUT)/pch.hpp.gch

##---------------------------------------------------------------------
## BUILD FLAGS
##---------------------------------------------------------------------

all: $(TARGET)
	@echo Build complete

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)


$(PCH_OUT): $(PCH_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(DIR_OUT)/%.o: %.cpp $(PCH_OUT)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) -c -o $@ $<

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean-all:
	rm -f $(TARGET) $(OBJS)

clean-core:
	rm -rf $(DIR_OUT)/source/core

clean-3d:
	rm -rf $(DIR_OUT)/source/3d

clean:
	rm -rf $(DIR_OUT)/source
