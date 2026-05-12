CC = gcc
SRC = src/*.c 
BIN = rayt
FLGS = -Iinclude -lm 
RPPM = rayt.ppm
RPNG = rayt.png
CNVRT = convert

all:
	$(CC) $(SRC) -o $(BIN) $(FLGS)

run: $(BIN)
	./$(BIN) > $(RPPM)
	$(CNVRT) $(RPPM) $(RPNG)
	
clean:
	rm -f $(BIN)
	rm $(RPPM)
	rm $(RPNG)
	
.PHONY: all run clean debug
