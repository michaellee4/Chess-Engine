CXX = g++
CXXFLAGS = -O3 -Wall -Werror -std=c++11 -I $(INCLUDE)
INCLUDE = include
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.cc)
OBJS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRC))
NAME = ce

all: ce

ce: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

depend: .depend

.depend: $(SRC)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

dist-clean: clean
	rm -f *~ .depend

include .depend
