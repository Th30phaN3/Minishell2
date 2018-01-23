#include	"minishell2.h"

char		**modif_pwd(char **env, char *oldpwd, char *pwd, int i)
{
  int		o;
  int		p;

  o = 0;
  p = 0;
  while (env[i] != NULL && my_spe_compare(env[i], "OLDPWD", 6) != 0)
    i++;
  if (env[i] != NULL)
    env[i] = create_var_env("OLDPWD", oldpwd);
  else
    o++;
  i = 0;
  while (env[i] != NULL && my_spe_compare(env[i], "PWD", 3) != 0)
    i++;
  if (env[i] != NULL)
    env[i] = create_var_env("PWD", pwd);
  else
    p++;
  if (p > 0 || o > 0)
    env = new_env_with_pwd(env, oldpwd, pwd);
  return (env);
}

int		move_in_directory(char *path)
{
  struct stat	stats;

  if (path == NULL || access(path, F_OK) < 0)
    {
      my_printf("%s: No such file or directory.\n", path);
      return (-1);
    }
  lstat(path, &stats);
  if (!S_ISDIR(stats.st_mode))
    {
      my_printf("%s: Not a directory.\n", path);
      return (-1);
    }
  if (access(path, X_OK) < 0)
    {
      my_printf("%s: Permission denied.\n", path);
      return (-1);
    }
  if (chdir(path) < 0)
    {
      my_printf("Can't open %s.\n", path);
      return (-1);
    }
  return (0);
}

char		**cd_minus(t_list *builtin, char **env, \
			   char *oldpwd)
{
  char          *path;
  char          *old;

  old = NULL;
  path = my_strdup(oldpwd);
  old = getcwd(old, 0);
  if (move_in_directory(path) != -1)
    modif_static(oldpwd, old);
  else
    builtin->good = -1;
  free(old);
  free(path);
  return (env);
}

char		**cd_null(t_list *builtin, char **env, \
			  int i, char *oldpwd)
{
  char          *path;
  char          *old;

  while (env[i] != NULL && my_spe_compare(env[i], "HOME", 4) != 0)
    i++;
  old = NULL;
  if (env[i] != NULL)
    path = my_strcut(env[i], 5, my_strlen(env[i]) - 1);
  else
    path = NULL;
  old = getcwd(old, 0);
  if (move_in_directory(path) != -1)
    modif_static(oldpwd, old);
  else
    builtin->good = -1;
  free(old);
  free(path);
  return (env);
}

char		**cd_with_arg(t_list *builtin, char **env, char *oldpwd)
{
  char		*old;

  old = NULL;
  old = getcwd(old, 0);
  if (move_in_directory(builtin->opt[1]) != -1)
    modif_static(oldpwd, old);
  else
    builtin->good = -1;
  free(old);
  return (env);
}
