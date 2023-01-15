src = main.c
src+= ../common/str_utils.c

obj = $(src:.c=.o)

main: $(obj)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) main

.PHONY: run
run:
	make clean && make && ./main

