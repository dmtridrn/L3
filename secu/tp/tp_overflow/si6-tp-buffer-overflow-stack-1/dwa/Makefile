.PHONY: clean distclean all

TARGET=dwa

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -O1 -o $@ $^

clean:

distclean: clean
	rm -f $(TARGET)
