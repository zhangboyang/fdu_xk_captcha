all: xkocr ocr_single ocr_batch

xkocr:
	(cd src; $(MAKE))

ocr_single: xkocr
	(cd sample/ocr_single; $(MAKE))

ocr_batch: xkocr
	(cd sample/ocr_batch; $(MAKE))

test: ocr_batch
	(cd sample/ocr_batch; $(MAKE) $@)

onlinetest: ocr_single
	(cd sample/ocr_single; $(MAKE) $@)

clean:
	(cd src; $(MAKE) $@)
	(cd sample/ocr_single; $(MAKE) $@)
	(cd sample/ocr_batch; $(MAKE) $@)

