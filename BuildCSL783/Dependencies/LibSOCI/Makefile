export DIST_ROOT=$(CURDIR)/../../
include $(DIST_ROOT)/scripts/Makefile.inc

download:
	@svn co http://10.20.50.7/svn/KLiPR/01_Software/LibSOCI/trunk/ package -r $(LIBSOCI_REV) >svn_checkout_log 2>&1

update:
	@svn up package -r $(LIBSOCI_REV)  >svn_checkout_log 2>&1

unpack:

patch:

configure:

build:
	@cd package && $(MAKE) >make_log 2>&1
clean:
	@cd package && $(MAKE) clean >make_log

install:

