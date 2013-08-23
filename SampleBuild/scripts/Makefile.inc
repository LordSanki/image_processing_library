DIST_ROOT?=$(CURDIR)/../

include $(DIST_ROOT)/scripts/MCONFIG

MAKE	:= make --no-print-directory 
STAGE   := $(CURDIR)/Stage/
ARCH_PKG:= x86
OBJDIR	:= obj/

all: .downloadstamp .unpackstamp .patchstamp .configurestamp .buildstamp .installstamp

pre-download:

.downloadstamp:
	@rm -f .unpackstamp .patchstamp .configurestamp .buildstamp .installstamp .cleanstamp
	@$(MAKE) download

pre-unpack: .downloadstamp
	@rm -f .unpackstamp .patchstamp .configurestamp .buildstamp .installstamp .cleanstamp

.unpackstamp: .downloadstamp
	@$(MAKE) unpack

pre-patch: .unpackstamp
	@rm -f .configurestamp .buildstamp .installstamp .cleanstamp

.patchstamp: .unpackstamp
	@$(MAKE) patch

pre-configure: .patchstamp
	@rm -f .buildstamp .installstamp .cleanstamp

.configurestamp: .patchstamp
	@$(MAKE) configure

pre-build: .configurestamp
	@rm -f .installstamp .cleanstamp

.buildstamp: .configurestamp
	@$(MAKE) build

pre-install: .buildstamp
	@rm -f .cleanstamp

.installstamp: .buildstamp
	@$(MAKE) install

pre-clean:
	@rm -rf .patchstamp .configurestamp .buildstamp .installstamp

.cleanstamp:
	@$(MAKE) clean

pre-veryclean: .cleanstamp
	@rm -rf .unpackstamp .downloadstamp

.verycleanstamp:
