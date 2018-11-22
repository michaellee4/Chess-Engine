CXX = g++
CXXFLAGS = -O3 -std=c++11 -I ./include/
TESTS = ./src/tests/
SRC = $(wildcard ./src/*.cc)
OBJS = $(patsubst %cc,%o,$(SRC))
RM = rm -f

all: ce

ce: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ce $(OBJS)

depend: .depend

.depend: $(SRC)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS)

dist-clean: clean
	rm -f *~ .depend

include .depend
