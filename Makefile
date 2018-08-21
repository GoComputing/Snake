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
CL=g++
CLFLAGS=$(shell pkg-config --static --libs $(LIBRARIES))
CXX=g++
CXXFLAGS=$(shell pkg-config --cflags $(LIBRARIES)) -Wall -Wextra -pedantic -c \
	-g -I$(INC)/
DEBUGGER=gdb


# ********************************** Modules ********************************* #
EXEC=$(BIN)/main

MODULES  = $(OBJ)/system.o
MODULES += $(OBJ)/shader.o
MODULES += $(OBJ)/tools.o
MODULES += $(OBJ)/model.o

HEADERS_ONLY  = $(INC)/motor.hpp


# ******************************* General rules ****************************** #
all: $(EXEC)


run: $(EXEC)
	@./$<

debug: $(EXEC)
	$(DEBUGGER) ./$<


# ********************************** Linking ********************************* #
$(BIN)/%: $(OBJ)/%.o $(MODULES)
	$(CL) -o $@ $< $(MODULES) $(CLFLAGS)


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
