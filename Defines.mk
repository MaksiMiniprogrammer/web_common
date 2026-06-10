define run_recursive
    @for dir in $(SUBDIRS); do \
        if [ -f $$dir/Makefile ]; then \
            $(MAKE) -C $$dir $(1); \
        fi \
    done
endef