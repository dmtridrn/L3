.PHONY: clean distclean all

TARGET=trzy

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -O2 -o $@ $^

clean:

distclean: clean
	rm -f $(TARGET)
