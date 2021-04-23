all: sysinfo

sysinfo: sysinfo.c
	gcc -m64 -Wall -Werror -Os -s -static -nostdlib -fno-stack-protector -fno-math-errno -fno-unroll-loops -fmerge-all-constants -fno-ident -Wl,--build-id=none -Wl,-z,norelro -Wl,--gc-sections -fno-unwind-tables -fno-asynchronous-unwind-tables -Wl,--hash-style=gnu $< -o $@
	@cat $@ | wc -c
	./$@

strace: sysinfo
	strace ./$< > /dev/null

objdump: sysinfo
	objdump -x $<
	objdump -d $<

clean:
	rm -f sysinfo
