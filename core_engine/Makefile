CC = C:/msys64/ucrt64/bin/gcc.exe
CFLAGS ?= -std=c17 -g -Wall -Wextra
CPPFLAGS ?= -Iinclude -IC:/msys64/ucrt64/include/ncurses
LDFLAGS ?= -LC:/msys64/ucrt64/lib
LDLIBS ?= -lncursesw
RM ?= rm -f

TARGET = app.exe
SRC = src/main.c src/engine.c src/canvas.c src/shapes.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
