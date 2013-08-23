export DIST_ROOT=$(CURDIR)

include $(DIST_ROOT)/scripts/Makefile.inc

MCONFIG.local:
	@echo "\n****Tips****\n$(YELLOW)Remember to create $(RED)MCONFIG.local$(RESET) from $(RED)MCONFIG.local.sample$(RESET) and edit it suitably.";

prompt: echorevisions MCONFIG.local
	@echo "$(YELLOW)Edit the $(RED)DEVELOPER_BUILD$(YELLOW) variable in $(RED)MCONFIG.local$(YELLOW) to use stable or head revisions$(RESET)\n";

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

echorevisions:
	@echo "\n\n$(YELLOW)DEVELOPER_BUILD: $(RED)$(DEVELOPER_BUILD)$(RESET)";
	@echo "$(YELLOW)LibImageScaler: Rev $(RED)$(LIBIMAGESCALER_REV)$(RESET)";
	@echo "$(YELLOW)Controller: Rev $(RED)$(CONTROLLER_REV)$(RESET)";
	@echo "$(YELLOW)AppGuiCSL783: Rev $(RED)$(APPGUICSL783_REV)$(RESET)";
	@echo "$(YELLOW)AppConsole783: Rev $(RED)$(APPCONSOLECSL783_REV)$(RESET)";

download: echorevisions
	@echo "\n$(YELLOW) View $(RED)svn_checkout_log$(YELLOW) file for checkout logs $(RESET)";
	@echo "$(BLUE) FETCHING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) download;
	@echo "$(BLUE) FETCHING CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) download;
	@echo "$(GREEN) Checkout Complete.. $(RESET)\n";
	@touch .downloadstamp

configure: .downloadstamp
	@echo "$(BLUE) CONFIGURING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) configure;
	@echo "$(BLUE) CONFIGURING CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) configure;
	@echo "$(GREEN)Configure Complete.\n Please Edit scripts/MCONFIG.local before building to configure the project dependencies$(RESET)";
	@touch .configurestamp

build: .configurestamp prompt $(OUTPUT_DIR)
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

update: echorevisions
	@echo "$(BLUE) UPDATING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) update;
	@echo "$(BLUE) UPDATING CSL783 $(RESET)"
	@cd $(CSL783_DIR) && $(MAKE) update;
	@echo "\n$(GREEN) Update Complete...$(RESET)\n";

install:
	@echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$OUTPUT_DIR:$$QTDIR/lib:$$LIBOPENCV_ROOT/lib" >$(OUTPUT_DIR)/source_me;
	@echo "export PATH=$$PATH:$$OUTPUT_DIR" >>$(OUTPUT_DIR)/source_me;
	@touch .installstamp

patch:
	@touch .patchstamp

unpack:
	@touch .unpackstamp
