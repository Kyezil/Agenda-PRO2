CXX = g++
CXXFLAGS = -c -std=c++0x -O2 -Wshadow -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -DND_DEBUG -D_JUDGE_ -D_GLIBCXX_DEBUG
LDFLAGS =
SRC = program.cc agenda.cc tasca.cc data.cc
LIB = comanda.cc token.cc
OBJ = $(SRC:.cc=.o)
EXE = program.exe

all: $(SRC) $(EXE)
jutge:
	tar -cvf practica.tar Makefile $(SRC) agenda.hh tasca.hh data.hh

debug: CXXFLAGS += -D_GLIBCXX_DEBUG -pg
debug: $(EXE) $(SRC)

$(EXE): $(OBJ)
	$(CXX) -D_GLIBCXX_DEBUG -DND_DEBUG -D_JUTGE_ $(LDFLAGS) $(OBJ) $(LIB) -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm $(EXE) $(OBJ) practica.tar
