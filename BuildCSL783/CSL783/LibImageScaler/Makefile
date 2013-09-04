export DIST_ROOT=$(CURDIR)/../../
include $(DIST_ROOT)/scripts/Makefile.inc

PACKAGE_PATH=$(REPO_ROOT)/GenericController/

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
	@cd package && $(MAKE) LIBRARY >make_log 2>&1

clean:
	@cd package && $(MAKE) clean >make_log

install:
	@#cd $(PACKAGE_PATH) && make install >make_log
