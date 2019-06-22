DIR=./source
BIN=libstatic_test.a
SHARE=-share
CFLAGE=-std=c++11 \
		-I./include
LFLAG=
CC=g++
AR=ar -cr
CO=$(AR)

SRC=$(wildcard $(DIR)/*.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

all:$(BIN)
$(BIN):$(OBJ)
	@mkdir -p libstatic/
	$(CO) ./libstatic/$@ $^
$(DIR)/%.o:$(DIR)/%.cpp
	$(CC) $(CFLAGE) -o $@ -c $<
.PHONY:clean
clean:
	rm -rf ./libstatic
	rm $(OBJ)
