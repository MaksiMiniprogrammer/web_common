MAIN_PROJECT := web_common

MAIN_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

RESULT_PATH		:= $(MAIN_PATH)_result
RESULT_BIN  	:= $(RESULT_PATH)/bin
RESULT_INCLUDE	:= $(RESULT_PATH)/include/$(MAIN_PROJECT)
RESULT_OBJ		:= $(RESULT_PATH)/obj
RESULT_LIB		:= $(RESULT_PATH)/lib
RESULT_DATA		:= $(RESULT_PATH)/data
RESULT_SCRIPTS	:= $(RESULT_PATH)/scripts

MAIN_DIR		:= $(MAIN_PATH)$(MAIN_PROJECT)
TEST_DIR 		:= $(MAIN_PATH)tests

LIB_PREFIX  	:= lib
SH_LIB_SUFFIX	:= .so
ST_LIB_SUFFIX	:= .a

CSS			= gcc
CXX 		= g++
CXXFLAGS 	= -Wall -g -Wextra -fPIC -I$(RESULT_PATH)/include/ -MMD -MP
LDFLAGS 	= -shared 
LLIBS		= -lpthread 
LPATH		= -L$(RESULT_LIB) -Wl,-rpath,'$$ORIGIN/../lib'

INSTALL_PATH = /opt/$(MAIN_PROJECT)
INSTALL_BIN = $(INSTALL_PATH)/bin
INSTALL_LIB = $(INSTALL_PATH)/lib
INSTALL_SBIN = $(INSTALL_PATH)/sbin
SYSTEM_CACHE = $(INSTALL_PATH)/cache
LOG_DIR = /var/log/$(MAIN_PROJECT)
ETC_DIR = /etc/$(MAIN_PROJECT)
SYMLINK_TARGET := /usr/local/bin/$(MAIN_PROJECT)
DATA_DIR = /var/lib/$(MAIN_PROJECT)

BACKUP_DIR  = /var/backups/$(MAIN_PROJECT)
BACKUP_NAME = config_data_backup_$(shell date +%Y%m%d_%H%M%S).tar.gz

ALL_LIBS = $(MAIN_DIR)/lib
ALL_APPS = $(MAIN_DIR)/app