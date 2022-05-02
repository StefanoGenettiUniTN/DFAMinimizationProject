CC = gcc
OBJFILES = graph.o minDfaPartition.o main.o
TARGET = main.out

all: $(TARGET)
	@echo "Program compiled"
$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)

clean:
	rm -f *.o
.PHONY: clean
