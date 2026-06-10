include ../../Commons.mk

SUBDIRS = $(ALL_LIBS)/utils \
		  $(ALL_LIBS)/session		  

include ../../Defines.mk

.PHONY: all clear init build

all: init build

clear:
	$(call run_recursive,clear)

init:
	$(call run_recursive,init)

build:
	$(call run_recursive,build)
