PLUGIN_NAME = single_trace

HEADERS = single-trace.h

SOURCES = single-trace.cpp\
          moc_single-trace.cpp

LIBS = 

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
