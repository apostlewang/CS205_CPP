CC := g++-10
# replace this with your correct compiler as identified above

ARCH := core2 # Replace this with your CPU architecture.
# core2 is pretty safe for most modern machines. 

CFLAGS := -march=$(ARCH) -O3 -fopenmp -lcblas -m64 -std=c++11 -mavx2

COMPILE_COMMAND := $(CC) $(CFLAGS)

OUTPUT := matrix

all: matrixmulti.cpp
	$(COMPILE_COMMAND) -o $(OUTPUT) matrixmulti.cpp

clean:
	rm -f *.o $(OUTPUT).*