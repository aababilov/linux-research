LDFLAGS := `pkg-config --libs litesql`
CXXFLAGS := `pkg-config --cflags litesql`
OBJECTS := example.o  exampledatabase.o

all: example 

clean:
	$(RM) $(OBJECTS) *~*

example: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

exampledatabase.cpp exampledatabase.hpp: exampledatabase.xml
	litesql-gen $^ >/dev/null

exampledatabase.o: exampledatabase.cpp exampledatabase.hpp