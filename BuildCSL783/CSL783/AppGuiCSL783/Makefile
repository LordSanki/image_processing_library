export DIST_ROOT=$(CURDIR)/../../
include $(DIST_ROOT)/scripts/Makefile.inc

download:
	@git clone <Path>/Library package -r $(LIBRARY_REV) >git_log 2>&1

update:
	@git pull package -r $(LIBRARY_REV)  >git_log 2>&1

configure:

unpack:

patch:

build:
	@cd package && make LIBRARY >make_log 2>&1

clean:
	@cd package && make clean >make_log

install:
	@#cd package && make install >make_log
