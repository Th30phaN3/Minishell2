#include	"minishell2.h"

void		take_input(t_shell *shell, t_list *cmd)
{
  if (my_strcmp(cmd->redirect, DRR) == 0)
    {
      shell->buff = my_drr(shell, cmd->prev);
      free(cmd->redirect);
      cmd->redirect = my_strdup(cmd->prev->redirect);
      rm_elem_list(cmd->prev);
      shell->ok = 1;
    }
  if (cmd->redirect[0] == RR && my_strcmp(cmd->redirect, DRR) != 0)
    {
      my_rr(shell, cmd->prev);
      free(cmd->redirect);
      cmd->redirect = my_strdup(cmd->prev->redirect);
      rm_elem_list(cmd->prev);
      shell->ok = 2;
    }
}

void		take_output(t_shell *shell, t_list *cmd)
{
  if (my_strcmp(cmd->redirect, DRL) == 0)
    {
      my_drl(shell, cmd->prev);
      free(cmd->redirect);
      cmd->redirect = my_strdup(cmd->prev->redirect);
      rm_elem_list(cmd->prev);
    }
  if (cmd->redirect[0] == RL && my_strcmp(cmd->redirect, DRL) != 0)
    {
      my_rl(shell, cmd->prev);
      free(cmd->redirect);
      cmd->redirect = my_strdup(cmd->prev->redirect);
      rm_elem_list(cmd->prev);
    }
}

int		exec_redirect_cmd(t_shell *shell, char **path)
{
  while (is_not_redirect(shell->cmd->redirect) == -1)
    {
      take_input(shell, shell->cmd);
      take_output(shell, shell->cmd);
      take_input(shell, shell->cmd);
      if (shell->in == ERROR_FD || shell->out == ERROR_FD)
	return (-1);
      if (shell->cmd->redirect[0] == PIPE && \
	  my_strcmp(shell->cmd->redirect, OR) != 0)
	{
	  if (my_minipipe(shell, shell->cmd, path) == -1)
	    return (-1);
	}
      else
	if (exec_without_pipe(shell, shell->cmd, path) == -1)
	  return (-1);
      if (shell->cmd->nb == 0)
	shell->cmd = shell->cmd->next;
    }
  if (shell->ok == 1)
    free(shell->buff);
  return (0);
}

int		minishell2(t_shell *shell, char **path, int nb)
{
  shell->ok = 0;
  if (shell->cmd->name[0] == 0 && shell->cmd->redirect[0] == RL)
    change_spe_redirect(shell);
  if (shell->cmd->name != NULL && shell->cmd->name[0] != 0 && \
      exec_correct(shell->cmd->next->good, \
		   shell->cmd->next->redirect, nb) == 0)
    {
      if (is_not_redirect(shell->cmd->redirect) == 0)
	exec_normal_cmd(shell, path, 0);
      else
	exec_redirect_cmd(shell, path);
    }
  close_all_fd(shell);
  shell->cmd = shell->cmd->prev;
  nb = shell->cmd->nb;
  shell->ok = 0;
  return (nb);
}
