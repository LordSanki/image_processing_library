export DIST_ROOT?=$(CURDIR)/../../../
include $(DIST_ROOT)/scripts/Makefile.inc

INCLUDE+= -I$(CONTROLLER_ROOT)/include -I$(LIBIMAGESCALER_ROOT)/include -isystem$(BOOST_ROOT)/include -isystem$(LIBOPENCV_ROOT)/include
src=ImageScaler.cpp

TARGET:= libimagescaler

LIBRARY: $(src:%.cpp=$(OBJDIR)/%.o)
	$(AR) -rs $(LIBDIR)/$(TARGET).a $<

BINARY:

download:

unpack: $(LIBDIR) $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR): 
	mkdir -p $(OBJDIR)

patch:

configure:

install:

clean:
	rm -f $(OBJDIR)/*

$(OBJDIR)/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@


