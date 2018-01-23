#include	"my.h"

void		my_putnstr(char *str, int len)
{
  int		i;

  i = 0;
  while (str[i] && len > 0)
    {
      my_putchar(str[i++]);
      len--;
    }
}
