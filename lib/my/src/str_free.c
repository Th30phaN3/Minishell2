#include	<stdlib.h>
#include	"my.h"

void		str_free(char **str)
{
  if (!str || !*str)
    return;
  free(*str);
  *str = NULL;
}
