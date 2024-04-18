CC=g++
CFLAGS=-c -Wall -fPIC
LDFLAGS=-shared
SOURCES=StepperMotor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libsteppermotor.so
HEADER=StepperMotor.h
INSTALL_LIB_PATH=/usr/local/lib
INSTALL_INCLUDE_PATH=/usr/local/include

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

install:
	mkdir -p $(INSTALL_LIB_PATH)
	mkdir -p $(INSTALL_INCLUDE_PATH)
	cp $(LIBRARY) $(INSTALL_LIB_PATH)
	cp $(HEADER) $(INSTALL_INCLUDE_PATH)

uninstall:
	rm -f $(INSTALL_LIB_PATH)/$(LIBRARY)
	rm -f $(INSTALL_INCLUDE_PATH)/$(HEADER)

clean:
	rm -f $(OBJECTS) $(LIBRARY)

.PHONY: all install uninstall clean
