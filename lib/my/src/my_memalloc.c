#include	<stdlib.h>
#include	"my.h"

void            *my_memalloc(int size)
{
  char          *ptr;

  if (size <= 0)
    return (NULL);
  ptr = my_malloc(size * sizeof(*ptr));
  return ((void*)ptr);
}
