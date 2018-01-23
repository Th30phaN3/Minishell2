#include	"my.h"

int		strlen_nb(int nb)
{
  int		i;

  if (!nb)
    return (1);
  i = (nb < 0) ? 1 : 0;
  while (nb)
    {
      i++;
      nb = nb / 10;
    }
  return (i);
}
