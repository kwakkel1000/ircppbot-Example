include ../MODULE_CONFIG

CXX_CFLAGS 		=
CXX_LDFLAGS 	=
LIBRARIES 		= $(CXX_SYSLIBS)

MODULE_NAME		= Example

default: $(OUTPUT)
Debug: all
Release: all
all: default


$(OUTPUT): $(SRC_DIR)$(OBJECTS)
	$(CXX_LINK) -o $(LIB_DIR)$@ $(OBJECTS) $(LIBRARIES)

cleanDebug: clean
cleanRelease: clean
clean:
	rm -f $(OBJECTS) $(LIB_DIR)$(OUTPUT)

cleanall: clean