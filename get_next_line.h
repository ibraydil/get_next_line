#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define  -D BUFFER_SIZE=42
# endif

char *get_next_line(int fd);

#endif
