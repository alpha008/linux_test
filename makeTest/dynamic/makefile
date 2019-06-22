DIR=./source
BIN=libdynamictest.so
SHARE=-fPIC -shared -o
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
	@mkdir -p libdynamic/
	$(CO) ./libdynamic/$@ $^
$(DIR)/%.o:$(DIR)/%.cpp
	$(CC) $(CFLAGE) $(SHARE)  $@ -c $<
.PHONY:clean
clean:
	rm -rf ./libdynamic
	rm $(OBJ)
