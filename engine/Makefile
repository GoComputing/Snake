# ****************************** Makefile config ***************************** #
.PHONY: all run debug clean mrproper
.SECONDARY:


# *********************************** Paths ********************************** #
BIN=bin
SRC=src
OBJ=obj
INC=include


# ******************************** Build setup ******************************* #
LIBRARIES=glfw3 glew
CL=ar
CLFLAGS=rvs
CXX=g++
CXXFLAGS=$(shell pkg-config --cflags $(LIBRARIES)) -Wall -Wextra -pedantic -c \
	-g -I$(INC)/
DEBUGGER=gdb


# ********************************** Modules ********************************* #
EXEC=$(BIN)/libengine.a

MODULES  = $(OBJ)/system.o
MODULES += $(OBJ)/shader.o
MODULES += $(OBJ)/tools.o
MODULES += $(OBJ)/model.o
MODULES += $(OBJ)/texture.o

HEADERS_ONLY  = $(INC)/motor.hpp


# ******************************* General rules ****************************** #
all: $(EXEC)


# ********************************** Linking ********************************* #
$(BIN)/%: $(MODULES)
	$(CL) $(CLFLAGS) -o $@ $(MODULES)


# ********************************* Compiling ******************************** #
$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.hpp $(HEADERS_ONLY)
	$(CXX) -o $@ $< $(CXXFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS_ONLY)
	$(CXX) -o $@ $< $(CXXFLAGS)


# *********************************** Clean ********************************** #
clean:
	-rm $(OBJ)/*.o

mrproper: clean
	-rm $(EXEC)
