export DIST_ROOT?=$(CURDIR)/../../../
include $(DIST_ROOT)/scripts/Makefile.inc

INCLUDE+= -I$(CONTROLLER_ROOT)/include -isystem$(BOOST_ROOT)/include -isystem$(LIBOPENCV_ROOT)/include

src=AppGenericConsole.cpp

LIBS= -lcontroller -limagescaler -lopencv_core -lopencv_highgui -lopencv_imgproc -lpthread -lboost_thread

TARGET:= AppConsole

LIBRARY: 

BINARY: $(src:%.cpp=$(OBJDIR)/%.o)
	$(CXX) $(CFLAGS) $< $(LDFLAGS) $(LIBS) -o $(BINDIR)/$(TARGET)

download:

unpack: $(OBJDIR) $(BINDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR): 
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

patch:

configure:

install:
	install -m 700 $(BINDIR)/$(TARGET) $(OUTPUT_DIR)

clean:


$(OBJDIR)/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@


