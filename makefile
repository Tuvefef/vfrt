CC = gcc
SRC = src/*.c 
BIN = rayt
# macro VF_INC_BVH as a flag to be able to use the renderSceneWithBvh function in main.c, which uses a BVH to speed up ray-object intersection tests.
MACROBVH = -DVF_INC_BVH
MACROTEXEC = -DVF_CALC_EXEC_TIME_SCN

FLGS = -Iinclude -lm -lSDL2 $(MACROBVH)

all:
	$(CC) $(SRC) -o $(BIN) $(FLGS)

run: $(BIN)
	./$(BIN)
	

clean:
	rm -f $(BIN)
	
.PHONY: all run clean debug
