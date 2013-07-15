CXX=g++
CXXFLAGS=`pkg-config --cflags libglademm-2.4`
LDFLAGS=`pkg-config --libs libglademm-2.4`
all: vmap

vmap: examplewindow.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS)
    