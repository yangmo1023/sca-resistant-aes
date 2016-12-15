src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -Wl,--gc-sections
CFLAGS = -g -O3 -fdata-sections -ffunction-sections -DUNROLL_TRANSPOSE

CC=sparc-elf-gcc
OBJD=sparc-elf-objdump

name = bitslice

$(name):  _testbench $(obj)
	$(CC) $(LDFLAGS) -o $@ $(obj) $(LDFLAGS)
	$(OBJD) -D $@ -S -l > $@.lst



test: _test $(obj)
	$(CC) $(LDFLAGS) -o $(name) $(obj) $(LDFLAGS)
	$(OBJD) -D $(name) > $(name).lst

footprint: _footprint $(obj)
	$(CC) $(LDFLAGS) -o $(name) $(obj) $(LDFLAGS)

bs.o:
	$(CC) -fverbose-asm $(CFLAGS) -S -o bs.s bs.c
	./clear_regs.py bs.s bs.s
	$(CC) $(CFLAGS) -c -o bs.o bs.s


_test: tests/tests.c
	$(eval obj+=$@.o)
	$(eval CFLAGS+= -DRUN_TESTS=1)
	$(CC) -c $(CFLAGS) -o $@.o $^

_footprint: tests/tests.c
	$(eval obj+=$@.o)
	$(eval CFLAGS+= -DRUN_TESTS=1 -DTEST_FOOTPRINT=1)
	$(CC) -c $(CFLAGS) -o $@.o $^

_testbench: testbench/app.c
	$(eval obj+=_testbench.o)
	$(eval LDFLAGS+= -lcrypto)
	$(CC) -c $(CFLAGS) -o $@.o $^


clean:
	rm -f $(obj) _test.o _footprint.o _testbench.o $(name)
