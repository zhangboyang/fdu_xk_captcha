CC = gcc
CFLAGS = -I../../include -Wall -O2
LDFLAGS = -L../../src -lxkocr -ljpeg
OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
ocr_batch: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

test: ocr_batch
	time ./ocr_batch | diff -b ../../test/testdata/answer.txt -

clean: 
	rm -f ocr_batch $(OBJ)
	(cd ../../test/onlinetest; ./clean.sh)

