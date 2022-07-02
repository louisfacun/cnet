EXECUTABLE = cnet
VPATH = ./src
OBJECTDIR = ./obj/

CC = gcc
CFLAGS = -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC
LDFLAGS = -lm

OBJECT = activation.o matrix.o cnet.o
OBJECTS = $(addprefix $(OBJECTDIR), $(OBJECT))
HEADERS = $(wildcard *.h)

all: obj $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJECTDIR)%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)