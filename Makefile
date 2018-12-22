CXX = g++
CXXFLAGS = -O3 -Wall -Werror -std=c++11 -I $(INCLUDE)
INCLUDE = include
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.cc)
OBJS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRC))
LINLOCATION = bin/linux/ce
NAME = ce
MW = x86_64-w64-mingw32-g++
MWFLAGS = -O3 -std=c++11 -I $(INCLUDE) -static-libgcc -static-libstdc++ -static -D__NO_INLINE__ -Wall -Werror
MWLOCATION = bin/win64/ce.exe

all: ce

ce: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(NAME)

linux: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(LINLOCATION) $(OBJS)

windows:
	$(MW) $(MWFLAGS) -o $(MWLOCATION) $(SRC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

depend: .depend

.depend: $(SRC)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

dist-clean: clean
	rm -f *~ .depend

include .depend
