MODULES = hal
BOARD ?= edu-ciaa-nxp
VERBOSE=n
MUJU ?= ./muju

include $(MUJU)/module/base/makefile

doc:
	@mkdir -p $(DOC_DIR)
	doxygen Doxyfile
