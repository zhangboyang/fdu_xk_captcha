CFLAGS = -I../../include -ansi -pedantic -Wall -O2
LDFLAGS = -L../../src -lxkocr -ljpeg
OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
ocr_single: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

clean: 
	rm -f ocr_single $(OBJ)
