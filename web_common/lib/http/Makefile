include ../../../Commons.mk

TARGET = http
TARGET_LIB = $(RESULT_LIB)/$(LIB_PREFIX)$(TARGET)$(SH_LIB_SUFFIX)

SOURCES = $(wildcard $(ALL_LIBS)/$(TARGET)/src/*.cpp)
OBJECTS = $(patsubst $(ALL_LIBS)/$(TARGET)/src/%.cpp,$(RESULT_OBJ)/$(TARGET)/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

all: clear init build

-include $(DEPENDS)

init:
	mkdir -p $(RESULT_INCLUDE)/$(TARGET)
	mkdir -p $(RESULT_OBJ)/$(TARGET)
	cp -ru $(ALL_LIBS)/$(TARGET)/include/* $(RESULT_INCLUDE)/$(TARGET)

build: $(TARGET_LIB)

clear:
	rm -rf $(RESULT_OBJ)/$(TARGET)
	rm -rf $(RESULT_INCLUDE)/$(TARGET)
	rm -f $(TARGET_LIB)

$(TARGET_LIB): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LPATH) -o $@

$(RESULT_OBJ)/$(TARGET)/%.o: $(ALL_LIBS)/$(TARGET)/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clear init build