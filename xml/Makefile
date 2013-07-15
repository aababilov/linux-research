PROJECT := xml
CXX := g++
CXXFLAGS := -Wall -g `pkg-config --cflags libxml-2.0 glib-2.0`
LDFLAGS :=  `pkg-config --libs libxml-2.0 glib-2.0`


all: $(PROJECT)

$(PROJECT): $(PROJECT).o xmlparser.o
	$(CXX) -o $@ $^ $(LDFLAGS)