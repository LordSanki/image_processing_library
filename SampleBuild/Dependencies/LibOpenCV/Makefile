CMAKE		:= cmake
#################### Version of opencv provided ##################################
OPENCV_VER	:= opencv-2.4.5
################## directory where cmake will build files ######################
TEMP_DIR	:= cmake_build_dir

download:
	wget -c http://citylan.dl.sourceforge.net/project/opencvlibrary/opencv-unix/2.4.5/$(OPENCV_VER).tar.gz
	touch .downloadstamp
update:


unpack: pre-unpack
	cd package && tar -xzvf ../$(OPENCV_VER).tar.gz
	mkdir -p package/$(TEMP_DIR)
	touch .unpackstamp

patch: pre-patch
	touch .patchstamp

configure: pre-configure
	export PKG_CONFIG_PATH=$(LIBFFMPEG_ROOT)/lib/pkgconfig && \
	cd package/$(TEMP_DIR) && $(CMAKE) -DBUILD_EXAMPLES=OFF -DBUILD_DOCS=OFF \
			-DBUILD_NEW_PYTHON_SUPPORT=OFF -DBUILD_PACKAGE=OFF\
			-DBUILD_TESTS=OFF -DCMAKE_C_FLAGS="-O3" -DCMAKE_CXX_FLAGS="-O3" \
			-DCMAKE_INSTALL_PREFIX=$(CURDIR)/package/\
			-DJPEG_INCLUDE_DIR=$(LIBJPEG_ROOT)/include \
			-DJPEG_LIBRARY=$(LIBJPEG_ROOT)/lib/libjpeg.a \
			-DOPENCV_EXTRA_EXE_LINKER_FLAGS="-L$(LIBJPEG_ROOT)/lib -ljpeg -ltiff" \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DWITH_FFMPEG=ON \
			-DCMAKE_VERBOSE_MAKEFILE=ON \
			../$(OPENCV_VER);
	touch .configurestamp

build: pre-build
	cd package/$(TEMP_DIR) && make -j3
	touch .buildstamp

install: pre-install
	cd package/$(TEMP_DIR) && make install
	touch .installstamp

clean: pre-clean
	rm -rf $(TEMP_DIR)/*
	touch .cleanstamp

