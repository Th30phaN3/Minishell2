#include	"minishell2.h"

int		how_many_pipes(t_list *cmd)
{
  t_list	*tmp;
  int		i;

  i = 0;
  tmp = cmd;
  while (tmp->redirect[0] == PIPE && my_strcmp(tmp->redirect, OR) != 0)
    {
      tmp = tmp->prev;
      i++;
    }
  return (i + 1);
}

int		exec_without_pipe(t_shell *shell, t_list *cmd, char **path)
{
  int		pid;
  int		stat;

  (void)cmd;
  if ((pid = fork()) < 0)
    return (my_putstr_fd("Error: fork failed.\n", 2));
  if (pid == 0)
    {
      if (dup2(shell->in, STDIN) < 0)
	return (my_putstr_fd("Error: dup2 failed.\n", 2));
      if (dup2(shell->out, STDOUT) < 0)
	return (my_putstr_fd("Error: dup2 failed.\n", 2));
      if (is_builtin(shell->cmd->name) == 0)
	launch_builtins(shell, 1);
      else
	if (exec_normal_cmd(shell, path, 1) == -1)
	  return (-1);
      close_all_fd(shell);
    }
  else
    while (wait(&stat) != pid);
  return (0);
}

int		my_pipe(t_shell *shell, char **path, t_piped *pp, int nb)
{
  if (pp->nb != 0)
    {
      if (dup2(pp->fd, shell->in) < 0)
	return (my_putstr_fd("Error: dup2 failed.\n", 2));
    }
  if (pp->nb != nb - 1 || (pp->nb == nb - 1 && \
			   shell->cmd->redirect[0] == RL))
    {
      if (pp->nb == nb - 1)
	file_end(shell, pp);
      else
	{
	  if (dup2(pp->pipefd[1], shell->out) < 0)
	    return (my_putstr_fd("Error: dup2 failed.\n", 2));
	  close(pp->pipefd[0]);
	}
    }
  if (is_builtin(shell->cmd->name) == 0)
    launch_builtins(shell, 1);
  else
    if (exec_normal_cmd(shell, path, 1) == -1)
      return (-1);
  return (0);
}

int		launch_pipe(t_shell *shell, char **path, t_piped *pp, int nb)
{
  if (pipe(pp->pipefd))
    return (my_putstr_fd("Error: pipe failed.\n", 2));
  if ((pp->pid = fork()) == 0)
    {
      if (my_pipe(shell, path, pp, nb) == -1)
	return (-1);
    }
  else
    {
      waitpid(pp->pid, &pp->stat, 0);
      close(pp->pipefd[1]);
      pp->fd = pp->pipefd[0];
      shell->cmd = shell->cmd->prev;
      pp->nb++;
    }
  return (0);
}

int		my_minipipe(t_shell *shell, t_list *cmd, char **path)
{
  t_piped	*pp;
  int		nb;

  if ((pp = malloc(sizeof(*pp))) == NULL)
    return (my_putstr_fd("Error: malloc failed.\n", 2));
  pp->nb = 0;
  nb = how_many_pipes(cmd);
  while (pp->nb  < nb)
    {
      if (launch_pipe(shell, path, pp, nb) == -1)
	return (-1);
    }
  free(pp);
  return (0);
}
