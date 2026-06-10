include Commons.mk

SUBDIRS = $(ALL_LIBS)

include Defines.mk

.PHONY: all init full-clear clear build test install uninstall

all: init build

init:
	mkdir -p $(RESULT_PATH) $(RESULT_DATA) $(RESULT_INCLUDE) $(RESULT_OBJ) $(RESULT_BIN) $(RESULT_LIB) $(TEST_OBJ_DIR) $(RESULT_SCRIPTS)

full-clear:
	rm -rf $(RESULT_PATH)

clear:
	$(call run_recursive,clear)

build-lib:
	$(MAKE) -C $(ALL_LIBS)

build-app:
	$(MAKE) -C $(ALL_APP)

build: build-lib

test:
	$(MAKE) -C $(TEST_DIR) clear
	$(MAKE) -C $(TEST_DIR)

install:
	mkdir -p $(INSTALL_BIN) $(INSTALL_LIB) $(INSTALL_SBIN) $(LOG_DIR) $(ETC_DIR) $(DATA_DIR) $(SYSTEM_CACHE)
	cp -Pp $(RESULT_BIN)/* $(INSTALL_BIN) 2>/dev/null || true
	cp -Pp $(RESULT_LIB)/* $(INSTALL_LIB) 2>/dev/null || true
	cp -Pp $(RESULT_SCRIPTS)/* $(INSTALL_SBIN) 2>/dev/null || true
	chmod 777 $(SYSTEM_CACHE)
	chmod 777 $(LOG_DIR)
	chmod 777 $(DATA_DIR)
	ln -sf $(INSTALL_BIN)/$(MAIN_PROJECT) $(SYMLINK_TARGET)

uninstall:
	rm -f $(SYMLINK_TARGET)
	rm -rf $(INSTALL_BIN)
	rm -rf $(INSTALL_LIB)
	rm -rf $(INSTALL_SBIN)
	rm -rf $(SYSTEM_CACHE)
	rm -rf $(LOG_DIR)
	rmdir $(INSTALL_PATH) 2>/dev/null || true

purge: uninstall
	rm -rf $(DATA_DIR)
	rm -rf $(ETC_DIR)

backup:
	@mkdir -p $(BACKUP_DIR)
	@if [ -d "$(DATA_DIR)" ] || [ -d "$(ETC_DIR)" ]; then \
		echo "Создание резервной копии конфигурации и данных..."; \
		tar -czf $(BACKUP_DIR)/$(BACKUP_NAME) \
			$$([ -d "$(DATA_DIR)" ] && echo "$(DATA_DIR)") \
			$$([ -d "$(ETC_DIR)" ] && echo "$(ETC_DIR)"); \
		echo "Установка прав доступа 600 на архив..."; \
		chmod 777 $(BACKUP_DIR)/$(BACKUP_NAME); \
		echo "Резервная копия успешно создана: $(BACKUP_DIR)/$(BACKUP_NAME)"; \
		ls -l $(BACKUP_DIR)/$(BACKUP_NAME); \
	else \
		echo "Ошибка: Директории $(DATA_DIR) и $(ETC_DIR) не найдены. Нечего бэкапить."; \
	fi
