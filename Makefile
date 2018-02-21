TEST=interface

CFLAGS = -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

all: $(TEST)


clean:
	-rm -rf $(TARGET)
