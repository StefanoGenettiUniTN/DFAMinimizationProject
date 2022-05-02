CC = gcc
OBJFILES = common.o graph.o list.o main.o mfset.o stack.o
TARGET = main.out

all: $(TARGET)
	@echo "Program compiled"
$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)

clean:
	rm -f *.o
.PHONY: clean