LDFLAGS := -ljsoncpp
CPPFLAGS := -I/usr/include/jsoncpp

all: json

json: json.o
	$(CXX) -o $@ $< $(LDFLAGS)
