.PHONY: clean distclean

program: ex2.o library.o
	ld -z noseparate-code -o program ex2.o library.o
	strip program

%.o: %.s
	as -o $@ $^

clean:
	rm -f ex2.o library.o

distclean: clean
	rm -f program
