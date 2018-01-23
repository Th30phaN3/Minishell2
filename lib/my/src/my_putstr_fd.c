#include	"my.h"

int		my_putstr_fd(char *str, int fd)
{
  int		i;

  i = 0;
  if (fd < 0)
    return (-1);
  while (str[i])
    write(fd, &str[i++], 1);
  return (-1);
}
