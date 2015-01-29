CFLAGS = -ansi -pedantic -Wall -O2
OBJ = jpeg.o captcha.o ocr.o
TARGET = libxkocr.a

all: $(TARGET)

clean: 
	rm -f $(TARGET) $(OBJ)

libxkocr.a: $(OBJ)
	$(AR) rv $@ $^

captcha.o: captcha.c xk.h captcha.h popcnt.h popcnt_data.h
jpeg.o: jpeg.c xk.h captcha.h jpeg.h
ocr.o: ocr.c xk.h jpeg.h captcha.h ocr.h ocr_data.h
	$(CC) -c -o $@ $< $(CFLAGS)

