src1 = part1.c
src1+= ../common/str_utils.c

obj = $(src1:.c=.o)

main: $(obj)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) main

.PHONY: run
run:
	make clean && make && ./main

