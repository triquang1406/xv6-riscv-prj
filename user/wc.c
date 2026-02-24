#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void
wc(int fd, char *name, int show_lines, int show_words, int show_chars)
{
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf("wc: read error\n");
    exit(1);
  }
  
  // Print ONLY requested fields
  int first = 1;
  if(show_lines){
    printf("%d", l);
    first = 0;
  }
  if(show_words){
    if(!first) printf(" ");
    printf("%d", w);
    first = 0;
  }
  if(show_chars){
    if(!first) printf(" ");
    printf("%d", c);
    first = 0;
  }
  printf(" %s\n", name);
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int show_lines = 0, show_words = 0, show_chars = 0;

  i = 1;
  // Parse flags first
  while(i < argc && argv[i][0] == '-'){
    for(char *p = argv[i] + 1; *p; p++){
      if(*p == 'l') show_lines = 1;
      if(*p == 'w') show_words = 1;  
      if(*p == 'c') show_chars = 1;      
    }
    i++;
  }
  if(!show_lines && !show_words && !show_chars){
        show_lines = show_words = show_chars = 1;
  }

  if(i >= argc){
    // No files after flags, use stdin
    int l = 0, w = 0, c = 0;
    int n, inword = 0;
    while((n = read(0, buf, sizeof(buf))) > 0){
      for(int j = 0; j < n; j++){
        c++;
        if(buf[j] == '\n') l++;
        if(strchr(" \r\t\n\v", buf[j])) inword = 0;
        else if(!inword){ w++; inword = 1; }
      }
    }
    if(show_lines) printf("%d", l);
    if(show_words) printf(" %d", w);
    if(show_chars) printf(" %d", c);
    printf(" -\n");
    exit(0);
  }

  // Process files
  for(; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i], show_lines, show_words, show_chars);
    close(fd);
  }
  exit(0);
}

