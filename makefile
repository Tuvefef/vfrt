CC = gcc
SRC = src/*.c 
BIN = rayt
# macro VF_INC_BVH as a flag to be able to use the renderSceneWithBvh function in main.c, which uses a BVH to speed up ray-object intersection tests.
# macro VF_CALC_EXEC_TIME_SCN as a flag to be able to use the calcSceneExecTime function in main.c, which calculates the execution time of the rendering process and prints it to the console.
MACROBVH = -DVF_INC_BVH
MACROTEXEC = -DVF_CALC_EXEC_TIME_SCN

FLGS = -Iinclude -lm $(MACROBVH) $(MACROTEXEC)
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
