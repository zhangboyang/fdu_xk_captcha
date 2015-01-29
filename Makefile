all:
	(cd src; $(MAKE))
	(cd sample/ocr_single; $(MAKE))
	(cd sample/ocr_batch; $(MAKE))

test: all
	(cd sample/ocr_batch; $(MAKE) $@)

onlinetest: all
	(cd sample/ocr_batch; $(MAKE) $@)

clean:
	(cd src; $(MAKE) $@)
	(cd sample/ocr_single; $(MAKE) $@)
	(cd sample/ocr_batch; $(MAKE) $@)

