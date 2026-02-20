.PHONY: clean distclean

program: ex4w.o library.o
	ld -z noseparate-code -o program ex4w.o library.o
	strip program

%.o: %.s
	as -o $@ $^

clean:
	rm -f ex4w.o library.o

distclean: clean
	rm -f program
