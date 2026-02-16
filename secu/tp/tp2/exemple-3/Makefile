.PHONY: clean distclean

program: main.o library.o
	ld -z noseparate-code -o program main.o library.o
	strip program

%.o: %.s
	as -o $@ $^

clean:
	rm -f main.o library.o

distclean: clean
	rm -f program
