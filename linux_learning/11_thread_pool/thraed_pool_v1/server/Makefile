# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall

# 找到所有的 .c 文件
SOURCES = $(wildcard *.c)

# 获取当前文件夹的名称
DIR_NAME = $(notdir $(CURDIR))

# 定义最终可执行文件的名称（当前文件夹的名称）
EXECUTABLE = $(DIR_NAME).out

# 默认目标
all: $(EXECUTABLE)

# 从所有的 .c 文件编译生成可执行文件
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) -lpthread

# 清理编译生成的文件
clean:
	rm -f $(EXECUTABLE)
