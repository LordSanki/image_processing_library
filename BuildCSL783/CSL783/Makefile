export DIST_ROOT=$(CURDIR)/../
include $(DIST_ROOT)/scripts/Makefile.inc
download:pre-download
	@echo "$(BLUE)\t Fetching AppGuiCSL783$(RESET)"
	@cd $(APPGUICSL783_DIR) && make download >make_log
	@echo "$(BLUE)\t Fetching APPCONSOLE783$(RESET)"
	@cd $(APPCONSOLECSL783_DIR) && make download >make_log
	@echo "$(BLUE)\t Fetching CONTROLLER$(RESET)"
	@cd $(CONTROLLER_DIR) && make download >make_log
	@echo "$(BLUE)\t Fetching LIBIMAGESCALER$(RESET)"
	@cd $(LIBIMAGESCALER_DIR) && make download >make_log
	@touch .downloadstamp

configure:pre-configure
	@echo "$(BLUE)\t Configuring LIBIMAGESCALER$(RESET)"
	@cd $(LIBIMAGESCALER_DIR) && make configure >make_log
	@echo "$(BLUE)\t Configuring CONTROLLER$(RESET)"
	@cd $(CONTROLLER_DIR) && make configure >make_log
	@echo "$(BLUE)\t Configuring AppGuiCSL783$(RESET)"
	@cd $(APPGUICSL783_DIR) && make configure >make_log
	@echo "$(BLUE)\t Configuring APPCONSOLE783$(RESET)"
	@cd $(APPCONSOLECSL783_DIR) && make configure >make_log
	@touch .configurestamp

build:pre-build
	@echo "$(BLUE)\t Building LIBIMAGESCALER$(RESET)"
	@cd $(LIBIMAGESCALER_DIR) && make build >make_log
	@echo "$(BLUE)\t Building CONTROLLER$(RESET)"
	@cd $(CONTROLLER_DIR) && make build >make_log
	@echo "$(BLUE)\t Building AppGuiCSL783$(RESET)"
	@cd $(APPGUICSL783_DIR) && make build >make_log
	@echo "$(BLUE)\t Building APPCONSOLE783$(RESET)"
	@cd $(APPCONSOLECSL783_DIR) && make build >make_log

clean:pre-clean
	@echo "$(BLUE)\t Cleaning AppGuiCSL783$(RESET)"
	@cd $(APPGUICSL783_DIR) && make clean >make_log
	@echo "$(BLUE)\t Cleaning APPCONSOLE783$(RESET)"
	@cd $(APPCONSOLECSL783_DIR) && make clean >make_log
	@echo "$(BLUE)\t Cleaning CONTROLLER$(RESET)"
	@cd $(CONTROLLER_DIR) && make clean >make_log
	@echo "$(BLUE)\t Cleaning LIBIMAGESCALER$(RESET)"
	@cd $(LIBIMAGESCALER_DIR) && make clean >make_log
	

install:
	@cd $(APPGUICSL783_DIR) && $(MAKE) install >make_log
	@cd $(APPCONSOLECSL783_DIR) && $(MAKE) install >make_log


delete_source:pre-clean
	@#cd $(LIBRARY_DIR) && rm package -rf
	@rm .downloadstamp

update:
	@echo "$(BLUE)\t Updating AppGuiCSL783$(RESET)"
	@cd $(APPGUICSL783_DIR) && make update >make_log
	@echo "$(BLUE)\t Updating APPCONSOLE783$(RESET)"
	@cd $(APPCONSOLECSL783_DIR) && make update >make_log
	@echo "$(BLUE)\t Updating CONTROLLER$(RESET)"
	@cd $(CONTROLLER_DIR) && make update >make_log
	@echo "$(BLUE)\t Updating LIBIMAGESCALER$(RESET)"
	@cd $(LIBIMAGESCALER_DIR) && make update >make_log

unpack:
	@touch .unpackstamp

patch:
	@touch .patchstamp
