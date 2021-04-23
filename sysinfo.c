const int STDOUT_FILENO = 1;
const int O_RDONLY = 0;

static inline long strlen(char *buf) {
  /*
  Returns the length of a string

  This function appoximiatelt emulates the following c code in x64 assembly:

  int length = 0

  while(buf[length] == '\0') {
    length++;
  }

  return length;
  */

  int length;

  asm("mov $-1, %%eax;"             // Initialize length at -1
      "%=: inc %%eax;"              // Begin loop
      "cmpb $0, (%%rax, %%rdi, 1);" // Load next char and compare to null
      "jne %=b;"                    // Loop
      : "=a"(length)
      : "D"(buf)
      :);

  return length;
}

static inline long read(int fd, char *buf, int count) {
  /*
  Executes the `read` system call
  */

  return 0;
}

static inline void write(int fd, const char *buf, int count) {
  /*
  Executes the `write` system call
  */
  asm("mov $1, %%rax;" // System call number
      "syscall;"
      : /* No outputs */
      : "D"(fd), "S"(buf), "d"(count)
      : "rcx", "r11", "memory");
}

static inline long open(char *pathname, int flags) {
  /*
  Executes the `open` system call
  */

  return -1;
}

static inline void exit(int code) {
  /*
  Executes the `exit` system call
  */

  asm("mov $60, %%rax;" // System call number
      "syscall;"
      : /* No outputs */
      : "D"(code)
      : "rcx", "r11", "memory");

  __builtin_unreachable();
}

void _start() {
  /*
  Program entry point
  */
  char msg[32] = "Hello, world";
  
  write(STDOUT_FILENO, msg, strlen(msg));

  exit(0);
}
