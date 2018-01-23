#include	"minishell2.h"

int		is_builtin(char *str)
{
  if (my_strcmp(str, "cd") == 0 || my_strcmp(str, "env") == 0 || \
      my_strcmp(str, "unsetenv") == 0 || my_strcmp(str, "setenv") == 0 || \
      my_strcmp(str, "exit") == 0)
    return (0);
  return (-1);
}

char		**exec_builtin(t_list *builtin, char **env)
{
  t_built	built[5] = {{"cd", my_cd},
			    {"env", my_env},
			    {"unsetenv", my_unsetenv},
			    {"setenv", my_setenv},
			    {"exit", exit_builtin},
  };
  int		i;
  int		ok;

  i = 0;
  ok = 0;
  while (i < 5)
    {
      if (my_strcmp(builtin->name, built[i].str) == 0 && ok == 0)
	{
	  env = built[i].f(builtin, env, 0);
	  ok = 1;
	}
      i++;
    }
  return (env);
}

int		exec_normal_cmd(t_shell *shell, char **path, int i)
{
  char		*bin;

  if (bin_exist(path, shell->cmd->opt[0], 0) == 1)
    exec_binpath(shell, path, i, 0);
  else
    {
      if (check_line(shell->cmd->opt) == 1)
	{
	  bin = shell->cmd->opt[0];
	  if (exec_bin(bin, shell, i, 0) == -1)
	    {
	      my_printf("%s: Command not found.\n", shell->cmd->name);
	      shell->cmd->good = -1;
	      return (-1);
	    }
	}
      else
	{
	  shell->cmd->good = -1;
	  my_printf("%s: Command not found.\n", shell->cmd->name);
	  return (-1);
	}
    }
  return (0);
}

int		do_it(t_shell *shell, int nb)
{
  char		**path;

  path = get_paths(shell->env);
  if (is_builtin(shell->cmd->name) == 0 && \
      exec_correct(shell->cmd->next->good, \
		   shell->cmd->next->redirect, shell->cmd->next->nb) == 0)
    {
      launch_builtins(shell, 0);
      shell->in = STDIN;
      shell->out = STDOUT;
      shell->cmd = shell->cmd->prev;
      nb = shell->cmd->nb;
    }
  else
    nb = minishell2(shell, path, nb);
  free_tab(path);
  return (nb);
}

int		exec_cmd(t_shell *shell)
{
  int		nb;

  nb = 0;
  shell->in = STDIN;
  shell->out = STDOUT;
  free(shell->buff);
  while (shell->cmd->nb != 0)
    shell->cmd = shell->cmd->next;
  if ((nb = do_it(shell, nb)) == -1)
    return (-1);
  while (nb != 0 && shell->cmd->name[0] != 0)
    {
      if ((nb = do_it(shell, nb)) == -1)
	return (-1);
    }
  return (0);
}
