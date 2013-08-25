export DIST_ROOT=$(CURDIR)/../../
include $(DIST_ROOT)/scripts/Makefile.inc

PACKAGE_PATH=$(REPO_ROOT)/AppConsoleCSL783/

download:
	@#git checkout  -r $(LIBRARY_REV) >git_log 2>&1

update:
	@#git pull $(PACKAGE_PATH) -r $(LIBRARY_REV)  >git_log 2>&1

configure:

unpack:

patch:

build:
	@cd $(PACKAGE_PATH) && make BINARY >make_log 2>&1

clean:
	@cd $(PACKAGE_PATH) && make clean >make_log

install:
	@#cd $(PACKAGE_PATH) && make install >make_log
