#include	"minishell2.h"

int		all_good(t_list *cmd, int ok)
{
  if (my_strcmp(cmd->redirect, OR) != 0 && cmd->redirect[0] == PIPE &&	\
      is_output(cmd->next->redirect) == 0)
    ok = -1;
  if (is_input(cmd->redirect) == 0 && \
      my_strcmp(cmd->next->redirect, OR) != 0 && \
      cmd->next->redirect[0] == PIPE)
    ok = -2;
  if (is_input(cmd->redirect) == 0 && is_input(cmd->next->redirect) == 0)
    ok = -2;
  if (is_output(cmd->redirect) == 0 && is_output(cmd->next->redirect) == 0)
    ok = -1;
  return (ok);
}

int		verif_redirect(t_list *cmd, int ok)
{
  while (cmd->nb != 0)
    cmd = cmd->next;
  if (cmd->redirect[0] == RL && \
      (is_input(cmd->prev->redirect) == 0 || \
       is_output(cmd->prev->redirect) == 0) && cmd->prev->opt[1] == NULL)
    ok = -1;
  cmd = cmd->prev;
  while (cmd->nb != 0)
    {
      ok = all_good(cmd, ok);
      if (ok == -1)
	return (my_putstr_fd("Ambiguous output redirect.\n", 2));
      if (ok == -2)
	return (my_putstr_fd("Ambiguous input redirect.\n", 2));
      if (cmd->next->name[0] == 0 && cmd->next->redirect[0] == RL && \
	  cmd->opt[1] == NULL)
	return (my_putstr_fd("Invalid null command.\n", 2));
      cmd = cmd->prev;
    }
  return (0);
}

int             redirect_ok_next(char *s, int i, int j, int k)
{
  int           ok;

  ok = 0;
  if ((spe_char(s[0], 0) == 1 && s[0] != RL) || \
      (i > 0 && spe_char(s[i], 0) == 1 && s[i - 1] == SMCL))
    ok = -2;
  if (s[i] == PIPE && (s[j] == 0 || s[j] == SMCL || s[j] == '&'))
    ok = -2;
  if (j < my_strlen(s) && s[i] == PIPE && s[j] == PIPE &&
      (s[k] == 0 || s[k] == SMCL || s[k] == '&' || s[k] == PIPE))
    ok = -2;
  if (s[i] == '&' && (s[j] == 0 || s[j] == PIPE || \
		      s[j] == RL || s[j] == RR || s[j] == SMCL))
    ok = -2;
  if (s[i] == '&' && (s[j] != '&' && i > 0 && s[i - 1] != '&'))
    ok = -2;
  if (j < my_strlen(s) && s[i] == '&' && s[j] == '&' &&
      (s[k] == 0 || s[k] == SMCL || s[k] == '&' || s[k] == PIPE))
    ok = -2;
  if (ok == -2)
    my_putstr_fd("Invalid null command.\n", 2);
  return (ok);
}

int             redirect_ok(char *s, int i, int j, int k)
{
  int           ok;

  ok = 0;
  if (s[i] == PIPE && (s[j] == RL || s[j] == RR))
    ok = -1;
  if (s[i] == RR && (s[j] == RL || s[j] == SMCL || \
		      s[j] == 0 || s[j] == '&' || s[j] == PIPE))
    ok = -1;
  if (s[i] == RL && (s[j] == RR || s[j] == SMCL || \
		      s[j] == 0 || s[j] == '&' || s[j] == PIPE))
    ok = -1;
  if (j < my_strlen(s) && s[i] == RL && s[j] == RL && \
      (s[k] == RL || s[k] == RR || s[k] == PIPE || s[k] == '&' || s[k] == 0))
    ok = -1;
  if (j < my_strlen(s) && s[i] == RR && s[j] == RR && \
      (s[k] == RR || s[k] == RL || s[k] == PIPE || s[k] == '&' || s[k] == 0))
    ok = -1;
  if (ok == -1)
    my_putstr_fd("Missing name for redirect.\n", 2);
  return (ok);
}

int		error_detector(t_list *cmd, char *s, int i)
{
  while (s[++i])
    {
      if (spe_char(s[i], 0) == 1)
	if (i < my_strlen(s) && redirect_ok(s, i, i + 1, i + 2) != 0)
	  return (-1);
    }
  i = -1;
  if (verif_redirect(cmd, 0) == -1)
    return (-1);
  while (s[++i])
    {
      if (spe_char(s[i], 0) == 1)
	if (i < my_strlen(s) && redirect_ok_next(s, i, i + 1, i + 2) != 0)
	  return (-1);
    }
  return (0);
}
