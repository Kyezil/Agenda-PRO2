CXX = g++
CXXFLAGS = -c -std=c++11 -O2 -Wshadow -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare
LDFLAGS =
SRC = main.cc agenda.cc tasca.cc data.cc
LIB = comanda.cc token.cc
OBJ = $(SRC:.cc=.o)
EXE = main

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(LIB) -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm $(EXE) $(OBJ)
