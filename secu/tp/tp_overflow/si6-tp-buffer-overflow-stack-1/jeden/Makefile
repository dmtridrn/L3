.PHONY: clean distclean all

TARGET=jeden

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -o $@ $^

clean:

distclean: clean
	rm -f $(TARGET)
