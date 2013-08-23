export DIST_ROOT=$(CURDIR)

include $(DIST_ROOT)/scripts/Makefile.inc

# Grab ordered list of packages and store in PACKAGES
include $(DIST_ROOT)/scripts/build_order.$(PRODUCT_NAME)

PACKAGES=$(subst ",,${_PACKAGES_})
DEVICE_PACKAGES=$(subst ",,${_DEVICE_PACKAGES_})
HOST_PACKAGES=$(subst ",,${_HOST_PACKAGES_})

PATH:=$(CURDIR)/host/bin:$(CURDIR)/host/usr/bin:$(CURDIR)/host/usr/local/bin:$(PATH)
export PATH
export MAKEFLAGS

MCONFIG.local:
	@echo "\n****Tips****\n$(YELLOW)Remember to create $(RED)MCONFIG.local$(RESET) from $(RED)MCONFIG.local.sample$(RESET) and edit it suitably.";

prompt: echorevisions MCONFIG.local
	@echo "$(YELLOW)Edit the $(RED)DEVELOPER_BUILD$(YELLOW) variable in $(RED)MCONFIG.local$(YELLOW) to use stable or head revisions$(RESET)\n";

echorevisions:
	@echo "\n\n$(YELLOW)DEVELOPER_BUILD: $(RED)$(DEVELOPER_BUILD)$(RESET)";
	@echo "$(YELLOW)LibMFCC: Rev $(RED)$(LIBMFCC_REV)$(RESET)";
	@echo "$(YELLOW)LibKLiPREngine_2: Rev $(RED)$(LIBKLIPRENGINE_2_REV)$(RESET)";
	@echo "$(YELLOW)AppGuiKLiPR: Rev $(RED)$(APPGUIKLIPR_REV)$(RESET)";
	@echo "$(YELLOW)LibManagerKLiPR: Rev $(RED)$(LIBMANAGERKLIPR_REV)$(RESET)";
	@echo "$(YELLOW)LibKLiPR: Rev $(RED)$(LIBKLIPR_REV)$(RESET)";
	@echo "$(YELLOW)LibIPCamera: Rev $(RED)$(LIBIPCAMERA_REV)$(RESET)";

download: echorevisions
	@echo "\n$(YELLOW) View $(RED)svn_checkout_log$(YELLOW) file for checkout logs $(RESET)";
	@echo "$(BLUE) FETCHING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) download;
	@echo "$(BLUE) FETCHING AKSHAR $(RESET)"
	@cd $(AKSHAR_DIR) && $(MAKE) download;
	@echo "$(BLUE) FETCHING GUI $(RESET)"
	@cd $(GUI_DIR) && $(MAKE) download;
	@echo "$(GREEN) Checkout Complete.. $(RESET)\n";
	@touch .downloadstamp

configure: .downloadstamp
	@echo "$(BLUE) CONFIGURING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) configure;
	@echo "$(BLUE) CONFIGURING AKSHAR $(RESET)"
	@cd $(AKSHAR_DIR) && $(MAKE) configure;
	@echo "$(BLUE) CONFIGURING GUI $(RESET)"
	@cd $(GUI_DIR) && $(MAKE) configure;
	@echo "$(GREEN)Configure Complete.\n Please Edit scripts/MCONFIG.local before building to configure the project dependencies$(RESET)";
	@touch .configurestamp

#for i in $(PACKAGES) ;\
#do \
#	if [ "z$$i" != "z" ] ; \
#	then \
#		echo "$(BLUE) Building $$i...$(RESET)"; \
#		(cd $$i && $(MAKE) >error 2>&1) || break; \
#	fi \
#done

build: .configurestamp prompt
	@echo "\n$(YELLOW) View $(RED)make_log$(YELLOW) file for build logs $(RESET)";
	@echo "$(BLUE) BUILDING DEPENDENCIES $(RESET)"
	@cd $(DEPS_DIR) && $(MAKE) build;
	@echo "$(BLUE) BUILDING AKSHAR $(RESET)"
	@cd $(AKSHAR_DIR) && $(MAKE) build;
	@echo "$(BLUE) BUILDING GUI $(RESET)"
	@cd $(GUI_DIR) && $(MAKE) build;
	@echo "$(GREEN) Build Complete...$(RESET)\n";

clean: pre-clean
	@#cd $(DEPS_DIR) && $(MAKE) clean;
	@cd $(AKSHAR_DIR) && $(MAKE) clean;
	@cd $(GUI_DIR) && $(MAKE) clean;
	@echo "\n$(GREEN) Cleaned...$(RESET)\n";

update: echorevisions
	@#echo "$(BLUE) UPDATING DEPENDENCIES $(RESET)"
	@#cd $(DEPS_DIR) && $(MAKE) update;
	@echo "$(BLUE) UPDATING AKSHAR $(RESET)"
	@cd $(AKSHAR_DIR) && $(MAKE) update;
	@echo "$(BLUE) UPDATING GUI $(RESET)"
	@cd $(GUI_DIR) && $(MAKE) update;
	@echo "\n$(GREEN) Update Complete...$(RESET)\n";

install:
	@echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$OUTPUT_DIR:$$QTDIR/lib:$$LIBOPENCV_ROOT/lib" >$(OUTPUT_DIR)/source_me;
	@echo "export PATH=$$PATH:$$OUTPUT_DIR" >>$(OUTPUT_DIR)/source_me;
	@touch .installstamp

patch:
	@touch .patchstamp

unpack:
	@touch .unpackstamp
