#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Helper to manually pad integers since xv6 printf 
void
print_padded_int(int n, int width)
{
  int temp = n;
  int digits = 0;

  if(temp <= 0) digits = 1;
  while(temp > 0){
    temp /= 10;
    digits++;
  }

  while(width > digits){
    printf(" ");
    width--;
  }
  printf("%d", n);
}

// Helper function to read a line from a file descriptor
int
readline(int fd, char *buf, int maxlen)
{
  int n, i;
  char c;

  i = 0;
  while((n = read(fd, &c, 1)) > 0){
    buf[i] = c;
    if(c == '\n'){
      break;
    }
    i += 1;
    if(i >= (maxlen - 1)){
      break; // Cap the line length safely
    }
  }

  if(n < 0) return -1;
  if(n == 0 && i == 0) return 0;

  i += 1;
  buf[i] = '\0';
  return i;
}

void
cat(int fd, int show_lines)
{
  char buf[512];
  int n;
  int line_num = 1;

  if(show_lines){
    while((n = readline(fd, buf, sizeof(buf))) > 0){
      print_padded_int(line_num++, 6);
      printf("  %s", buf); // Standard cat spacing
    }
  } else {
    while((n = read(fd, buf, sizeof(buf))) > 0){
      if (write(1, buf, n) != n) {
        fprintf(2, "cat: write error\n");
        exit(1);
      }
    }
  }

  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int show_lines = 0;

  if(argc > 1 && strcmp(argv[1], "-n") == 0){
    show_lines = 1;
    i = 2;
  } else {
    i = 1;
  }

  if(argc <= i){
    cat(0, show_lines);
    exit(0);
  }

  for(; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    cat(fd, show_lines);
    close(fd);
  }
  exit(0);
}