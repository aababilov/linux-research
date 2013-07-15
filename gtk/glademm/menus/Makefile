CXX=g++
CXXFLAGS=`pkg-config --cflags --libs libglademm-2.4`
all: menus

menus: example.o
	$(CXX) -o $@ $^ $(CXXFLAGS)
    