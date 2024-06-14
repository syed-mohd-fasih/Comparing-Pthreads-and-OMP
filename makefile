# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2
CFLAGS_OMP = -fopenmp
CFLAGS_THREADS = -lpthread

# Directories:
#   Source Files
SRC_DIR = src
SRC_FILE = src/main.c
SRC_DIR_OMP = $(SRC_DIR)/omp
SRC_DIR_THREADS = $(SRC_DIR)/pthreads
#   Binary Files
BIN_DIR = bin
BIN_DIR_OMP = $(BIN_DIR)/omp
BIN_DIR_THREADS = $(BIN_DIR)/pthreads

# List of source files (all .c files in SRC_DIR_OMP and SRC_DIR_THREADS)
SRCS_OMP = $(wildcard $(SRC_DIR_OMP)/*.c)
SRCS_THREADS = $(wildcard $(SRC_DIR_THREADS)/*.c)

# List of target executables
EXECS_OMP = $(SRCS_OMP:$(SRC_DIR_OMP)/%.c=$(BIN_DIR_OMP)/%)
EXECS_THREADS = $(SRCS_THREADS:$(SRC_DIR_THREADS)/%.c=$(BIN_DIR_THREADS)/%)
MAIN = $(BIN_DIR)/comparing_omp_and_pthreads

# Default target
all: $(EXECS_OMP) $(EXECS_THREADS) $(MAIN)

# Main file that controls the Project:
$(MAIN): $(SRC_FILE) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_FILE) -o $@

# Rule to compile each OpenMP source file into a separate executable
$(BIN_DIR_OMP)/%: $(SRC_DIR_OMP)/%.c | $(BIN_DIR_OMP)
	$(CC) $(CFLAGS) $(CFLAGS_OMP) $< -o $@

# Rule to compile each Pthreads source file into a separate executable
$(BIN_DIR_THREADS)/%: $(SRC_DIR_THREADS)/%.c | $(BIN_DIR_THREADS)
	$(CC) $(CFLAGS) $(CFLAGS_THREADS) $< -o $@

# Ensure the binary directories exist
$(BIN_DIR_OMP):
	mkdir -p $@

$(BIN_DIR_THREADS):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean
