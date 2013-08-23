export DIST_ROOT=$(CURDIR)/../
include $(DIST_ROOT)/scripts/Makefile.inc
download:pre-download
	@echo "$(BLUE)\t Fetching Library$(RESET)"
	@cd $(LIBRARY_DIR) && make download >make_log
	@touch .downloadstamp

configure:pre-configure
	@echo "$(BLUE)\t Configuring Library$(RESET)"
	@cd $(LIBRARY_DIR) && make configure >make_log
	@touch .configurestamp

build:pre-build
	@echo "$(BLUE)\t Building LIBRARY$(RESET)"
	@cd $(LIBRARY_DIR) && make build >make_log

clean:pre-clean
	@echo "$(BLUE)\t Cleaning LIBRARY$(RESET)"
	@cd $(LIBRARY_DIR) && make clean >make_log
	

install:

delete_source:pre-clean
	@cd $(LIBRARY_DIR) && rm package -rf
	@rm .downloadstamp

update:
	@echo "$(BLUE)\t Updating LIBRARY$(RESET)"
	@cd $(LIBRARY_DIR) && make update >make_log

unpack:
	@touch .unpackstamp

patch:
	@touch .patchstamp
