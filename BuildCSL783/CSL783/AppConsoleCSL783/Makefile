export DIST_ROOT=$(CURDIR)/../../
include $(DIST_ROOT)/scripts/Makefile.inc

PACKAGE_PATH=$(REPO_ROOT)/AppConsoleCSL783/

download:
	@ln -sf $(PACKAGE_PATH) package
	@touch .downloadstamp

update:
	@#git pull $(PACKAGE_PATH) -r $(LIBRARY_REV)  >git_log 2>&1

configure:

unpack:
	@cd package && $(MAKE) unpack >make_log 2>&1
patch:

build:
	@cd $(PACKAGE_PATH) && $(MAKE) BINARY >make_log 2>&1

clean:
	@cd $(PACKAGE_PATH) && $(MAKE) clean >make_log

install:
	@cd $(PACKAGE_PATH) && $(MAKE) install >make_log
