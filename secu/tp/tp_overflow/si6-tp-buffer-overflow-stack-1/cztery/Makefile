.PHONY: clean distclean all

TARGET=cztery

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -O2 -no-pie -o $@ $^

clean:

distclean: clean
	rm -f $(TARGET)
