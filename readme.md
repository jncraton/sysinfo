sysinfo
=======

This program displays information about the local system. In particular, it CPU load average from `/proc/loadavg` and memory usage from `/proc/meminfo`.

This program demonstates the use of inline assembly and system calls. It will not `#include` or link against any external files. It does not use the C standard library.

Your task is to properly implement the `open` and `read` system calls and use them to implement the program. Examples have been provided for the `write` and `exit` system calls.

Documentation
-------------

The following links may be helpful.

- [Embedding assembly in gcc](https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Extended-Asm)
- [x86-64 machine register constraints](https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints)
- [Kernel calling convention (Section A.2)](https://refspecs.linuxfoundation.org/elf/x86_64-abi-0.99.pdf)
- [Kernel System Call numbers](https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl)

Expected Output
---------------

The completed program will produce output that looks approximately like the following:

```
Load Average
0.24 0.45 0.52 3/1107 702033

Memory Usage
MemTotal:       32202816 kB
MemFree:         6661620 kB
MemAvailable:   19755544 kB
Buffers:         1536760 kB
Cached:         11621876 kB
SwapCached:            0 kB
Active:         16603636 kB
Inactive:        6919156 kB
Active(anon):   10898016 kB
Inactive(anon):    88672 kB
Active(file):    5705620 kB
Inactive(file):  6830484 kB
Unevictable:      534808 kB
Mlocked:              16 kB
SwapTotal:       2097148 kB
SwapFree:        2097148 kB
Dirty:               136 kB
Writeback:             0 kB
AnonPages:      10899012 kB
Mapped:           664072 kB
Shmem:            627672 kB
KReclaimable:    1023236 kB
Slab:            1303804 kB
SReclaimable:    1023236 kB
SUnreclaim:       280568 kB
KernelStack:       17856 kB
PageTables:        47600 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:    18198556 kB
Committed_AS:   14965320 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       49232 kB
VmallocChunk:          0 kB
Percpu:            21120 kB
HardwareCorrupted:     0 kB
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB
FileHugePages:         0 kB
FilePmdMapped:         0 kB
CmaTotal:              0 kB
CmaFree:               0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:               0 kB
DirectMap4k:      775088 kB
DirectMap2M:    18458624 kB
DirectMap1G:    14680064 kB
```

Open, Read, and Write
---------------------

The following example program that will output the first 4096 bytes of the file `/proc/loadavg` may be useful example of the `open`, `read`, and `write` system calls in action:

```c
#include <unistd.h>
#include <fcntl.h>

int main() {
  char buf[4096];

  int fd = open("/proc/loadavg", O_RDONLY);
  
  int bytes_read = read(fd, buf, 4096);

  write(STDOUT_FILENO, buf, bytes_read);
}
```
