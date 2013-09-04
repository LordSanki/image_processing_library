export DIST_ROOT=$(CURDIR)

include $(DIST_ROOT)/scripts/Makefile.inc

download: 
	@echo "$(BLUE) SETTING UP DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) download;
	@echo "$(BLUE) SETTING UP  CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) download;
	@touch .downloadstamp

configure: .downloadstamp
	@echo "$(BLUE) CONFIGURING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) configure;
	@echo "$(BLUE) CONFIGURING CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) configure;
	@echo "$(GREEN)Configure Complete.\n Please Edit scripts/MCONFIG.local before building to configure the project dependencies$(RESET)";
	@touch .configurestamp

build: .configurestamp
	@echo "\n$(YELLOW) View $(RED)make_log$(YELLOW) file for build logs $(RESET)";
	@echo "$(BLUE) BUILDING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) build;
	@echo "$(BLUE) BUILDING CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) build;
	@echo "$(GREEN) Build Complete...$(RESET)\n";

clean: pre-clean
	@#cd $(DEPS_DIR) && $(MAKE) clean;
	@cd $(CSL783_DIR) && $(MAKE) clean;
	@echo "\n$(GREEN) Cleaned...$(RESET)\n";

update: 
	@#echo "$(BLUE) UPDATING DEPENDENCIES $(RESET)"
	@#cd $(DEPS_DIR) && $(MAKE) update;
	@echo "\n$(GREEN) Update Complete...$(RESET)\n";

install:
	@cd $(CSL783_DIR) && $(MAKE) install;
	@echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$OUTPUT_DIR:$$QTDIR/lib:$$LIBOPENCV_ROOT/lib" >$(OUTPUT_DIR)/source_me;
	@echo "export PATH=$$PATH:$$OUTPUT_DIR" >>$(OUTPUT_DIR)/source_me;
	@touch .installstamp

patch:
	@touch .patchstamp

unpack:
	@touch .unpacktamp
