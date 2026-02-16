.PHONY: clean distclean

program: ex1.o library.o
	ld -z noseparate-code -o program ex1.o library.o
	strip program

%.o: %.s
	as -o $@ $^

clean:
	rm -f ex1.o library.o

distclean: clean
	rm -f program
