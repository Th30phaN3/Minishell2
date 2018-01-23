#ifndef		_MINISHELL_2_H_
# define	_MINISHELL_2_H_

#include        <sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<dirent.h>
#include	<signal.h>
#include        <unistd.h>
#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include	<sys/wait.h>

#include	"my.h"
#include	"my_printf.h"
#include	"get_next_line.h"

# define	STDIN		0
# define	STDOUT		1
# define	ERROR_FD	-1

# define	PIPE '|'
# define	RL '>'
# define	RR '<'
# define	DRL ">>"
# define	DRR "<<"
# define	OR "||"
# define	AND "&&"
# define	SMCL ';'

typedef struct	s_list
{
  int		nb;
  char		*name;
  char		**opt;
  char		*redirect;
  int		good;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

typedef	struct	s_shell
{
  t_list	*cmd;
  char		**env;
  char		*buff;
  int		in;
  int		out;
  int		ok;
}		t_shell;

typedef char**    (*blt)(t_list*, char**, int);

typedef struct	s_built
{
  char          *str;
  blt          f;
}		t_built;

typedef struct	s_piped
{
  int		pipefd[2];
  pid_t		pid;
  int		fd;
  int		stat;
  int		nb;
}		t_piped;

void		aff_prompt(char**);
void		get_cmd(t_shell*);
void		free_tab(char**);
void		my_exit(char*);
int		cmd_error(t_list*, char*);
void		my_free_list(t_list*);
void		close_all_fd(t_shell*);
void		my_d_control(t_shell*);
void		catch_sigint(int);
void		rm_elem_list(t_list*);
void		launch_builtins(t_shell*, int);
int		check_pid(int, int);
int		is_not_redirect(char*);
int		is_only_numbers(char*);
int		my_spe_compare(char*, char*, int);
int		compare_var(char*, char**);
int		all_var_exist(char**, char**);
int		spe_char(char, int);
int		check_line(char**);
int		my_count_char(char*, char);
int		all_good(t_list*, int);
int		verif_redirect(t_list*, int);
int		redirect_ok_next(char*, int, int, int);
int		redirect_ok(char*, int, int, int);
int		error_detector(t_list*, char*, int);
char		*epur_pipe_dash(char*, int, int);
char		*epur_str(char*, int, int);
char		*my_malloc(int);
void		*my_memalloc(int);
void		modif_static(char*, char*);
char		*take_path(char*, int);
char		*find_path(char**, int, int);
char		**get_paths(char**);
int		bin_exist(char**, char*, int);
int		exec_bin(char*, t_shell*, int, int);
int		exec_binpath(t_shell*, char**, int, int);
char		*find_bin(char**, char*, int);
char		*get_varenv(char*);
char		**fill_my_env(char**);
char		*get_user(char**);
char		*get_name_cmd(char*, int*, int);
char		**get_opt_cmd(char*, int*, int, char*);
char		*take_redirect(char*, int);
int		move_in_cmd(char*, t_list**, int, int);
int		parse_cmd(char*, t_list**, int);
int		nb_opt(char*, int*);
int		len_opt(char*, int*);
int		move_in_directory(char*);
char		**new_env_with_pwd(char**, char*, char*);
char		**cd_minus(t_list*, char**, char*);
char		**modif_pwd(char**, char*, char*, int);
char		**cd_with_arg(t_list*, char**, char*);
char		**cd_null(t_list*, char**, int, char*);
int		var_exist(char**, char*);
char		*create_var_env(char*, char*);
char		**next_setenv(char**, t_list*, int, int);
void		aff_list(t_list*, char*);
int		is_builtin(char*);
char		**exec_buitin(t_list*, char**);
int		error_setenv(t_list*, int, int, int);
char		**exec_builtin(t_list*, char**);
char		**my_cd(t_list*, char**, int);
char		**my_env(t_list*, char**, int);
char		**my_unsetenv(t_list*, char**, int);
char		**my_setenv(t_list*, char**, int);
char		**exit_builtin(t_list*, char**, int);
int		my_rr(t_shell*, t_list*);
char		*my_drr(t_shell*, t_list*);
int		my_rl(t_shell*, t_list*);
int		my_drl(t_shell*, t_list*);
int		exec_normal_cmd(t_shell*, char**, int);
int		do_it(t_shell*, int);
void		change_spe_redirect(t_shell*);
int		exec_correct(int, char*, int);
int		exec_cmd(t_shell*);
int		my_shell(t_shell*);
int		minishell2(t_shell*, char**, int);
int		is_input(char*);
int		is_output(char*);
void		take_input(t_shell*, t_list*);
void		take_output(t_shell*, t_list*);
int		file_end(t_shell*, t_piped*);
int		my_pipe(t_shell*, char**, t_piped*, int);
int		launch_pipe(t_shell*, char**, t_piped*, int);
int		my_minipipe(t_shell*, t_list*, char**);
int		exec_without_pipe(t_shell*, t_list*, char**);

#endif
