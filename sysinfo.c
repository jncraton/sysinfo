const int STDOUT_FILENO = 1;
const int O_RDONLY = 0;

static inline long strlen(char *buf) {
  /*
  Returns the length of a string

  This function appoximiately emulates the following c code in x64 assembly:

  int length = 0

  while(buf[length] == '\0') {
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
  */
  asm("mov $1, %%rax;" // System call number
      "syscall;"
      : /* No outputs */
      : "D"(fd), "S"(buf), "d"(count)
      : "rcx", "r11", "memory");
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

/** 
Your code begins here
**/

static inline long open(char *pathname, int flags) {
  /*
  Executes the `open` system call
  */

  return -1;
}

static inline long read(int fd, char *buf, int count) {
  /*
  Executes the `read` system call
  */

  return -1;
}

void _start() {
  /*
  Program entry point
  */  

  char buf[4096] = "Hello, world!\n";

  write(STDOUT_FILENO, buf, strlen(buf));

  exit(0);
}
