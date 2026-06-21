include ../../../Commons.mk

TARGET = json

all: clear init

-include $(DEPENDS)

init:
	mkdir -p $(RESULT_INCLUDE)/$(TARGET)
	mkdir -p $(RESULT_OBJ)/$(TARGET)
	cp -ru $(ALL_LIBS)/$(TARGET)/* $(RESULT_INCLUDE)/$(TARGET)

clear:
	rm -rf $(RESULT_OBJ)/$(TARGET)
	rm -rf $(RESULT_INCLUDE)/$(TARGET)
	rm -f $(TARGET_LIB)

.PHONY: all clear init build