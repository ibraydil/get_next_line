#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char *get_next_line(int fd)
{
  static char *leftover = NULL;
  char    buf[BUFFER_SIZE + 1];
  ssize_t n;

  n = read(fd, buf, BUFFER_SIZE);
  if (n < 0)
    return NULL;
  buf[n] = '\0';
  return ();
}
