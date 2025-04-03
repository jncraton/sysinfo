const int STDOUT_FILENO = 1;
const int O_RDONLY = 0;

static inline long strlen(char *buf) {
  /*
  Returns the length of a string

  This function appoximiately emulates the following c code in x64 assembly:

  int length = 0

  while(buf[length] != '\0') {
    length++;
  }

  return length;
  */

  int length;

  asm("mov $-1, %%rax;"             // Initialize length at -1
      "loop: inc %%rax;"            // Begin loop
      "cmpb $0, (%%rax, %%rdi, 1);" // Load next char and compare to null
      "jne loop;"                   // Loop
      : "=a"(length)
      : "D"(buf)
      :);

  return length;
}

static inline void write(int fd, const char *buf, int count) {
  /*
  Executes the `write` system call

  write() writes up to count bytes from the buffer starting at buf to the
  file referred to by the file descriptor fd.

  For more information, try `man write`.
  */
  asm("mov $1, %%rax;" // System call number
      "syscall;"
      : /* No outputs */
      : "D"(fd), "S"(buf), "d"(count)
      : "rcx", "r11" /* Registers clobbered by syscall */ );
}

static inline void exit(int code) {
  /*
  Executes the `exit` system call

  exit() terminates the calling process "immediately". Any open file
  descriptors belonging to the process are closed.

  For more information, try `man exit`.
  */

  asm("mov $60, %%rax;" // System call number
      "syscall;"
      : /* No outputs */
      : "D"(code)
      : "rcx", "r11" /* Registers clobbered by syscall */ );

  __builtin_unreachable();
}

/**
Your code begins here
**/

static inline long open(char *pathname, int flags) {
  /*
  Executes the `open` system call

  The open() system call opens the file specified by pathname. If the
  specified file does not exist, it may optionally (if O_CREAT is specified
   in flags) be created by open().

  The return value of open() is a file descriptor, a small, nonnegative
  integer that is used in subsequent system calls (read(2), write(2),
  lseek(2), fcntl(2), etc.) to refer to the open file. The file
  descriptor returned by a successful call will be the lowest-numbered file
  descriptor not currently open for the process.

  For more information, try `man open`.
  */

  return -1;
}

static inline long read(int fd, char *buf, int count) {
  /*
  Executes the `read` system call

  read() attempts to read up to count bytes from file descriptor fd into
  the buffer starting at buf.

  For more information, try `man read`.
  */

  return -1;
}

void _start() {
  /*
  Program entry point

  This program should be modified to show CPU load average from
  /proc/loadavg and memory usage from /proc/meminfo.
  */

  char buf[4096] = "sysinfo 1.0\n\n";

  write(STDOUT_FILENO, buf, strlen(buf));

  exit(0);
}
