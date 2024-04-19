CC=gcc
C_FLAGS = -Wall -Wextra
DEV_FLAGS = $(C_FLAGS) -std=c17 -g -O0
BUILD_FLAGS_O1 = $(C_FLAGS) -O1 -fomit-frame-pointer -march=native
BUILD_FLAGS_O2 = $(C_FLAGS) -O2 -fomit-frame-pointer -march=native
BUILD_FLAGS_O3 = $(C_FLAGS) -O3 -fomit-frame-pointer -march=native 
BUILD_FLAGS_LTO = $(BUILD_FLAGS_O3) -flto
SRCS = main.c
OBJS = $(SRCS:.c=.o)
ASM_FILES = $(SRCS:.c=.s)
EXEC_DEV = main_dev
EXEC_O1 = main_o1
EXEC_O2 = main_o2
EXEC_O3 = main_o3
EXEC_LTO = main_lto

all: $(EXEC_DEV) $(EXEC_O1) $(EXEC_O2) $(EXEC_O3) $(EXEC_LTO) assembly

$(EXEC_DEV): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC_DEV) $(DEV_FLAGS)

$(EXEC_O1): $(SRCS)
	$(CC) -c $^ $(BUILD_FLAGS_O1)
	$(CC) $(OBJS) -o $(EXEC_O1) $(BUILD_FLAGS_O1)

$(EXEC_O2): $(SRCS)
	$(CC) -c $^ $(BUILD_FLAGS_O2)
	$(CC) $(OBJS) -o $(EXEC_O2) $(BUILD_FLAGS_O2)

$(EXEC_O3): $(SRCS)
	$(CC) -c $^ $(BUILD_FLAGS_O3)
	$(CC) $(OBJS) -o $(EXEC_O3) $(BUILD_FLAGS_O3)

$(EXEC_LTO): $(SRCS)
	$(CC) -c $^ $(BUILD_FLAGS_LTO)
	$(CC) $(OBJS) -o $(EXEC_LTO) $(BUILD_FLAGS_LTO)

%.o: %.c
	$(CC) -c $< -o $@ $(DEV_FLAGS)

%.s: %.c
	$(CC) -S $< -o $@ $(DEV_FLAGS)

assembly: $(ASM_FILES)

.PHONY: build_o1 build_o2 build_o3 build_lto

build_o1: $(EXEC_O1)
build_o2: $(EXEC_O2)
build_o3: $(EXEC_O3)
build_lto: $(EXEC_LTO)

clean:
	rm -f $(OBJS) $(ASM_FILES) $(EXEC_DEV) $(EXEC_O1) $(EXEC_O2) $(EXEC_O3) $(EXEC_LTO)

