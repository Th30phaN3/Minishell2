#include	<unistd.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str != NULL)
    {
      while (str[i])
	i++;
    }
  return (i);
}
