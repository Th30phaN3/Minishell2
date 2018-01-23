#include	"minishell2.h"

int             error_setenv(t_list *builtin, int nb, int p_c, int p_o)
{
  char          first;
  int           i;

  i = 0;
  if (nb > 3)
    return (cmd_error(builtin, "setenv: Too many arguments.\n"));
  while (builtin->opt[1][i])
    {
      if (builtin->opt[1][i] == '(')
        p_o++;
      if (builtin->opt[1][i] == ')')
        p_c++;
      i++;
    }
  if (p_c > p_o)
    return (cmd_error(builtin, "Too many )'s.\n"));
  if (p_o > p_c)
    return (cmd_error(builtin, "Too many ('s.\n"));
  first = builtin->opt[1][0];
  if ((first < 'a' || first > 'z') && (first < 'A' || first > 'Z'))
    return (cmd_error(builtin, "setenv: Variable name must" \
                      " begin with a letter.\n"));
  return (0);
}

void	modif_static(char *oldpwd, char *value)
{
  if (value != NULL)
    oldpwd = my_strdup(value);
  (void)oldpwd;
}

void            rm_elem_list(t_list *list)
{
  list->prev->next = list->next;
  list->next->prev = list->prev;
}

void            catch_sigint(int sig_num)
{
  signal(SIGINT, catch_sigint);
  my_putstr("\b\b  \n$>");
  sig_num = sig_num;
}

int		check_pid(int pid, int stat)
{
  if (WIFSIGNALED(stat))
    {
      if (WTERMSIG(stat) == 11 || pid == 11)
	{
	  my_putstr_fd("Segmentation fault\n", 2);
	  return (-1);
	}
      if (WTERMSIG(stat) == 8 || pid == 8)
	{
	  my_putstr_fd("Floating point exception\n", 2);
	  return (-1);
	}
      if (WTERMSIG(stat) == 10 || pid == 7)
	{
	  my_putstr_fd("Program received signal [[SIGBUS]], Bus error.\n", 2);
	  return (-1);
	}
    }
  return (0);
}
