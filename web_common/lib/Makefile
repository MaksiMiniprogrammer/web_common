include ../../Commons.mk

SUBDIRS = $(ALL_LIBS)/json		\
		  $(ALL_LIBS)/utils		\
		  $(ALL_LIBS)/http		\
		  $(ALL_LIBS)/session	\
		  $(ALL_LIBS)/server	\

include ../../Defines.mk

.PHONY: all clear init build

all: init build

clear:
	$(call run_recursive,clear)

init:
	$(call run_recursive,init)

build:
	$(call run_recursive,build)
