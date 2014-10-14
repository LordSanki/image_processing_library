export DIST_ROOT=$(CURDIR)/../
include $(DIST_ROOT)/scripts/Makefile.inc
download:pre-download
	@#echo "$(BLUE)\t Fetching LIBCURL$(RESET)"
	@#cd $(LIBCURL_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching LIBJPEG$(RESET)"
	@#cd $(LIBJPEG_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching LIBOPENCV$(RESET)"
	@#cd $(LIBOPENCV_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching LIBPGSQL$(RESET)"
	@#cd $(LIBPGSQL_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching BOOST$(RESET)"
	@#cd $(BOOST_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching LIBSQLITE$(RESET)"
	@#cd $(LIBSQLITE_DIR) && $(MAKE) download >make_log
	@#echo "$(BLUE)\t Fetching LIBSOCI$(RESET)"
	@#cd $(LIBSOCI_DIR) && $(MAKE) download >make_log
	@touch .downloadstamp

configure:pre-configure
	@#echo "$(BLUE)\t Configuring LIBCURL$(RESET)"
	@#cd $(LIBCURL_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring LIBJPEG$(RESET)"
	@#cd $(LIBJPEG_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring LIBOPENCV$(RESET)"
	@#cd $(LIBOPENCV_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring LIBPGSQL$(RESET)"
	@#cd $(LIBPGSQL_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring BOOST$(RESET)"
	@#cd $(BOOST_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring LIBSQLITE$(RESET)"
	@#cd $(LIBSQLITE_DIR) && $(MAKE) configure >make_log
	@#echo "$(BLUE)\t Configuring LIBSOCI$(RESET)"
	@#cd $(LIBSOCI_DIR) && $(MAKE) configure >make_log
	@touch .configurestamp

build:pre-build
	@#echo "$(BLUE)\t Building LIBOPENCV$(RESET)"
	@#cd $(LIBOPENCV_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building BOOST$(RESET)"
	@#cd $(BOOST_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building LIBSQLITE$(RESET)"
	@#cd $(LIBSQLITE_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building LIBPGSQL$(RESET)"
	@#cd $(LIBPGSQL_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building LIBSOCI$(RESET)"
	@#cd $(LIBSOCI_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building LIBCURL$(RESET)"
	@#cd $(LIBCURL_DIR) && $(MAKE) build >make_log
	@#echo "$(BLUE)\t Building LIBJPEG$(RESET)"
	@#cd $(LIBJPEG_DIR) && $(MAKE) build >make_log

update:
	@#echo "$(BLUE)\t Updating LIBOPENCV$(RESET)"
	@#cd $(LIBOPENCV_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating BOOST$(RESET)"
	@#cd $(BOOST_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating LIBSQLITE$(RESET)"
	@#cd $(LIBSQLITE_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating LIBPGSQL$(RESET)"
	@#cd $(LIBPGSQL_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating LIBSOCI$(RESET)"
	@#cd $(LIBSOCI_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating LIBCURL$(RESET)"
	@#cd $(LIBCURL_DIR) && $(MAKE) update >make_log
	@#echo "$(BLUE)\t Updating LIBJPEG$(RESET)"
	@#cd $(LIBJPEG_DIR) && $(MAKE) update >make_log

clean:pre-clean
	@#cd $(LIBCURL_DIR) && $(MAKE) clean >make_log
	@#cd $(LIBJPEG_DIR) && $(MAKE) clean >make_log
	@#cd $(LIBOPENCV_DIR) && $(MAKE) clean >make_log
	@#cd $(LIBPGSQL_DIR) && $(MAKE) clean >make_log
	@#cd $(LIBSQLITE_DIR) && $(MAKE) clean >make_log
	@#cd $(BOOST_DIR) && $(MAKE) clean >make_log
	@#cd $(LIBSOCI_DIR) && $(MAKE) clean >make_log
	

install:
	@#cd $(LIBCURL_DIR) && $(MAKE) install >make_log
	@#cd $(LIBJPEG_DIR) && $(MAKE) install >make_log
	@#cd $(LIBOPENCV_DIR) && $(MAKE) install >make_log
	@#cd $(LIBPGSQL_DIR) && $(MAKE) install >make_log
	@#cd $(LIBSQLITE_DIR) && $(MAKE) install >make_log
	@#cd $(BOOST_DIR) && $(MAKE) install >make_log
	@#cd $(LIBSOCI_DIR) && $(MAKE) install >make_log

delete_source:pre-clean
	@#cd $(LIBCURL_DIR) && rm package -rf
	@#cd $(LIBJPEG_DIR) && rm package -rf
	@#cd $(LIBOPENCV_DIR) && rm package -rf
	@#cd $(LIBPGSQL_DIR) && rm package -rf
	@#cd $(LIBSQLITE_DIR) && rm package -rf
	@#cd $(BOOST_DIR) && rm package -rf
	@#cd $(LIBSOCI_DIR) && rm package -rf
	@rm .downloadstamp

unpack:pre-unpack
	@touch .unpackstamp

patch:pre-patch
	@touch .patchstamp
