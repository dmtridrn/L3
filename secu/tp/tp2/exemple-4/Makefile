.PHONY: clean distclean

program: ex4.o library.o
	ld -z noseparate-code -o program ex4.o library.o
	strip program

%.o: %.s
	as -o $@ $^

clean:
	rm -f ex4.o library.o

distclean: clean
	rm -f program
