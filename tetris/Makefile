CC=gcc
CFLAGS=-o
PARAM=-Wall
CUR=$(shell pwd)
SRC=$(CUR)/src
SRCS=$(SRC)/*.c
TARGET=$(CUR)/bin/exe
.PHONY:$(TARGET)
all:$(TARGET)
$(TARGET):$(SRCS)
	$(CC) $^ $(CFLAGS) $@ $(PARAM)
clean:
	@-rm -rf $(TARGET)
	@-rm -rf $(CUR)/include/*~
	@-rm -rf $(SRC)/*~
create:
	@-mkdir src/
	@-mkdir include/
	@-mkdir bin/

