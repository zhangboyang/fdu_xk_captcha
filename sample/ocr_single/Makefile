CC = gcc
CFLAGS = -I../../include -Wall -O2
LDFLAGS = -L../../src -lxkocr -ljpeg
OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
ocr_single: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

onlinetest:
	(cd ../../test/onlinetest; ./run.sh)

clean: 
	rm -f ocr_single $(OBJ)

