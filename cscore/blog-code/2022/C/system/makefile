

cfiles := $(wildcard *.c ./proc/*.c ./cextension/*.c ansi/*c coroutine/*c)
cobjs  := $(patsubst %.c, %.out, $(cfiles))
cc     := gcc
cflags := -g -lpthread -fopenmp
all: $(cobjs)


%.out: %.c

	$(cc) $< -o $@ $(cflags)

pdf: ./proc/pstree.dot ./proc/pstree.out
	./proc/pstree.out > ./proc/pstree.dot
	dot -Tpdf ./proc/pstree.dot -o ./proc/pstree.pdf

.PHONY: clean

clean:
	rm $(cobjs)
