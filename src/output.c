#include	"minishell2.h"

char            **my_spe_tabdup(int beg, char **tab, int len)
{
  int           i;
  char          **res;

  i = 0;
  res = my_memalloc(sizeof(char*) * len);
  while (tab[beg] != NULL)
    {
      res[i] = my_strdup(tab[beg]);
      i++;
      beg++;
    }
  res[i] = NULL;
  return (res);
}

void            change_spe_redirect(t_shell *shell)
{
  char          *tmp_file;

  tmp_file = my_strdup(shell->cmd->prev->opt[0]);
  shell->cmd->opt = my_spe_tabdup(1, shell->cmd->prev->opt, \
                                  tab_len(shell->cmd->prev->opt));
  shell->cmd->name = my_strdup(shell->cmd->opt[0]);
  free(shell->cmd->prev->name);
  shell->cmd->prev->name = tmp_file;
  shell->cmd->prev->opt[0] = NULL;
}

int		aff_error_open(t_shell *shell, char *name)
{
  shell->out = ERROR_FD;
  my_putstr_fd(name, 2);
  return (my_putstr_fd(": Permission denied.\n", 2));
}

int		my_rl(t_shell *shell, t_list *cmd)
{
  struct stat	stats;
  int		fd;

  if (cmd->name != NULL)
    {
      if ((fd = open(cmd->name, O_CREAT | O_TRUNC | O_WRONLY, 0600)) != -1)
	{
	  stat(cmd->name, &stats);
	  if (!(S_ISDIR(stats.st_mode) || S_ISLNK(stats.st_mode)))
	    shell->out = fd;
	  else
	    return (aff_error_open(shell, cmd->name));
	}
      else
	return (aff_error_open(shell, cmd->name));
    }
  else
    shell->out = ERROR_FD;
  return (0);
}

int		my_drl(t_shell *shell, t_list *cmd)
{
  struct stat   stats;
  int           fd;

  if (cmd->name != NULL)
    {
      if ((fd = open(cmd->name, O_CREAT | O_RDWR | O_APPEND, 00666)) != -1)
	{
	  stat(cmd->name, &stats);
	  if (!(S_ISDIR(stats.st_mode) || S_ISLNK(stats.st_mode)))
	    shell->out = fd;
	  else
	    return (aff_error_open(shell, cmd->name));
	}
      else
	return (aff_error_open(shell, cmd->name));
    }
  else
    shell->out = ERROR_FD;
  return (0);
}
