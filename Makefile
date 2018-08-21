# ****************************** Makefile config ***************************** #
.PHONY: all run debug prebuild clean mrproper
.SECONDARY:


# *********************************** Paths ********************************** #
BIN=bin
SRC=src
OBJ=obj
INC=include
ENGINE_PATH=engine


# ******************************** Build setup ******************************* #
LIBRARIES=glfw3 glew
CL=g++
CLFLAGS=-L$(ENGINE_PATH)/$(BIN) -lengine \
	$(shell pkg-config --static --libs $(LIBRARIES))
CXX=g++
CXXFLAGS=$(shell pkg-config --cflags $(LIBRARIES)) -Wall -Wextra -pedantic -c \
	-g -I$(INC)/ -I$(ENGINE_PATH)/$(INC)
DEBUGGER=gdb


# ********************************** Modules ********************************* #
EXEC=$(BIN)/main

EXTERNAL_LIBS  = $(ENGINE_PATH)/$(BIN)/libengine.a

MODULES  = $(OBJ)/snake.o
MODULES += $(OBJ)/tools.o

HEADERS_ONLY  = $(INC)/tools.hpp


# ******************************* General rules ****************************** #
all: prebuild $(EXEC)


run: $(EXEC)
	@./$<

debug: $(EXEC)
	$(DEBUGGER) ./$<

prebuild:
	@make -C $(ENGINE_PATH)


# ********************************** Linking ********************************* #
$(BIN)/%: $(OBJ)/%.o $(MODULES) $(EXTERNAL_LIBS)
	$(CL) -o $@ $< $(MODULES) $(CLFLAGS)


# ********************************* Compiling ******************************** #
$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.hpp $(HEADERS_ONLY)
	$(CXX) -o $@ $< $(CXXFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS_ONLY)
	$(CXX) -o $@ $< $(CXXFLAGS)


# *********************************** Clean ********************************** #
clean:
	-make -C $(ENGINE_PATH) clean
	-rm $(OBJ)/*.o

mrproper: clean
	make -C $(ENGINE_PATH) mrproper
	-rm $(EXEC)
