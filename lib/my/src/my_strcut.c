#include	<stdlib.h>

char		*my_strcut(char *src, int beg, int end)
{
  char		*res;
  int		j;

  j = 0;
  if ((res = malloc(sizeof(char) * (my_strlen(src) + 1))) == NULL)
    return (NULL);
  while (beg <= end)
    res[j++] = src[beg++];
  res[j] = 0;
  return (res);
}
