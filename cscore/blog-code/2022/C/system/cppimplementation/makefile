

cfiles := $(wildcard *.cpp)
cobjs  := $(patsubst %.cpp, %.out, $(cfiles))
cc     := clang++
cflags := -g -lpthread
all: $(cobjs)

%.out: %.c

	$(cc) $(cflags) $< -o $@

.PHONY: clean

clean:
	rm $(cobjs)
