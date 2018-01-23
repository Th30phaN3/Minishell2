#include	"minishell2.h"

char            *take_path(char *path, int j)
{
  char          *res;
  int           k;

  k = 0;
  res = NULL;
  if (path != NULL && path[5] == 0)
    res = getcwd(res, 0);
  else
    {
      res = my_malloc(my_strlen(path) - 4);
      while (path[j])
        res[k++] = path[j++];
      res[k] = 0;
    }
  return (res);
}

int		file_end(t_shell *shell, t_piped *pp)
{
  take_output(shell, shell->cmd);
  if (dup2(shell->out, STDOUT) < 0)
    return (my_putstr_fd("Error: dup2 failed.\n", 2));
  close(pp->pipefd[0]);
  close(pp->pipefd[1]);
  return (0);
}

int             is_not_redirect(char *red)
{
  if (red != NULL)
    {
      if (red[0] == PIPE || red[0] == RL || red[0] == RR || \
          my_strcmp(red, DRL) == 0 || my_strcmp(red, DRR) == 0)
        {
          if (my_strcmp(red, OR) != 0)
            return (-1);
        }
    }
  return (0);
}

int		is_output(char *red)
{
  if (red[0] == RL)
    return (0);
  return (-1);
}

int		is_input(char *red)
{
  if (red[0] == RR)
    return (0);
  return (-1);
}
