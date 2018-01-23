#include	<stdlib.h>
#include	"my.h"

char    *my_malloc(int size)
{
  char  *str;
  int   i;

  i = 0;
  if ((str = malloc(size)) == NULL)
    return (NULL);
  while (i < size)
    str[i++] = 0;
  return (str);
}
