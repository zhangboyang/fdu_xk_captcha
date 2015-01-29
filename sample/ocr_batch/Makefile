CFLAGS = -I../../include -ansi -pedantic -Wall -O2
LDFLAGS = -L../../src -lxkocr -ljpeg
OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
ocr_batch: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

test: ocr_batch
	time ./ocr_batch | diff - ../../test/testdata/answer.txt

onlinetest:
	(cd ../../test/onlinetest; ./run.sh)

clean: 
	rm -f ocr_batch $(OBJ)
	(cd ../../test/onlinetest; ./clean.sh)
