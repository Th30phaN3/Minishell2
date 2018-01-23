#include	"minishell2.h"

void		launch_builtins(t_shell *shell, int i)
{
  shell->env = exec_builtin(shell->cmd, shell->env);
  if (i == 1)
    exit(0);
}

void            close_all_fd(t_shell *shell)
{
  if (shell->in != STDIN)
    {
      if (shell->in != -1)
        close(shell->in);
      shell->in = STDIN;
    }
  if (shell->out != STDOUT)
    {
      if (shell->out != -1)
        close(shell->out);
      shell->out = STDOUT;
    }
}

int             exec_correct(int good, char *redir, int nb)
{
  if (nb == 0)
    return (0);
  if (my_strcmp(redir, OR) == 0)
    {
      if (good == -1)
        return (0);
      return (-1);
    }
  if (my_strcmp(redir, AND) == 0)
    {
      if (good == 0)
        return (0);
      return (-1);
    }
  return (0);
}

int             my_rr(t_shell *shell, t_list *cmd)
{
  struct stat   stats;
  int           fd;

  if (cmd->name != NULL)
    stat(cmd->name, &stats);
  if ((fd = open(cmd->name, O_RDONLY, 0600)) == -1 || \
      S_ISDIR(stats.st_mode) || S_ISLNK(stats.st_mode))
    {
      shell->in = ERROR_FD;
      my_putstr_fd(cmd->name, 2);
      return (my_putstr_fd(": Permission denied.\n", 2));
    }
  shell->in = fd;
  return (0);
}

char		*my_drr(t_shell *shell, t_list *cmd)
{
  char		*str;
  char		*buff;

  (void)shell;
  if ((buff = malloc(sizeof(char) * 2)) == NULL)
    return (NULL);
  buff[0] = 0;
  buff[1] = 0;
  my_putstr("? ");
  while (my_strcmp(str = get_next_line(STDIN), cmd->name) != 0)
    {
      my_putstr("? ");
      str = my_strcat(str, "\n");
      buff = my_strcat(buff, str);
      free(str);
    }
  buff[my_strlen(buff)] = 0;
  return (buff);
}
