

cfiles 	:= $(wildcard *.cpp)
cobjs 	:= $(patsubst %.cpp, %.out, $(cfiles))
cflags 	:= -g -std=c++11
cc 			:= clang++
all: $(cobjs)

%.out: %.cpp
	$(cc) $< -o $@ $(cflags)

.PHONY: clean

clean:
	rm $(cobjs)
