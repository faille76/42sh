/*
** builtin.h for builtin in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:44:07 2016 Frederic ODDOU
** Last update Mon May 23 16:58:59 2016 Arthur Josso
*/

#pragma once

#include "shell.h"

#define NOT_BUILTIN	-1
#define NOT_ID		-1
#define ERROR_FATAL	-1

#define TOO_ARG		"%s: Too many arguments.\n"
#define FEW_ARG		"%s: Too few arguments.\n"
#define NO_FOLDER	"%s: Not a directory.\n"
#define NO_PERMIT	"%s: Permission denied.\n"
#define SYNTAX_EXP	"%s: Expression Syntax.\n"
#define IS_BUILTIN	"%s: shell built-in command.\n"
#define IS_BUILTIN_W	"%s is a shell built-in\n"

typedef struct		s_builtin
{
  char			*name;
  int			(*func)(int ac, char **av, t_shell *shell);
}			t_builtin;

typedef struct		s_echo_type
{
  char			*str;
  char			c;
}			t_echo_type;

char			*b_getenv(char			**tab,
				  char			*name);
char			*b_findenv(char			**tab,
				   char			*name);
int			b_get_id_env(char		**tab,
				     char		*name);

short			b_is_builtin(char		*name);
int			b_exec(t_shell			*shell,
			       t_pipe			*pipe);

int			b_env(int			ac,
			      char			**av,
			      t_shell			*shell);
int			b_setenv(int			ac,
				 char			**av,
				 t_shell		*shell);
int			b_unsetenv(int			ac,
				   char			**av,
				   t_shell		*shell);
int			b_which(int			ac,
				char			**av,
				t_shell			*shell);
int			b_exit(int			ac,
			       char			**av,
			       t_shell			*shell);
int			b_cd(int			ac,
			     char			**av,
			     t_shell			*shell);
int			b_builtins(int			ac,
				   char			**av,
				   t_shell		*shell);
int			b_set(int			ac,
			      char			**av,
			      t_shell			*shell);
int			b_alias(int			ac,
				char			**av,
				t_shell			*shell);
int			b_jobs(int			ac,
			       char			**av,
			       t_shell			*shell);
int			b_fg(int			ac,
			     char			**av,
			     t_shell			*shell);
int			b_history(int			ac,
				  char			**av,
				  t_shell		*shell);
int			b_export(int			ac,
				 char			**av,
				 t_shell		*shell);
int			b_sort(int			ac,
			       char			**av,
			       t_shell			*shell);
int			b_echo(int			ac,
			       char			**av,
			       t_shell			*shell);
int			b_yes(int			ac,
			      char			**av,
			      t_shell			*shell);
int			b_whoami(int			ac,
				 char			**av,
				 t_shell		*shell);
int			b_pwd(int			ac,
			      char			**av,
			      t_shell			*shell);
int			b_unset(int			ac,
				char			**av,
				t_shell			*shell);
int			b_where(int			ac,
				char			**av,
				t_shell			*shell);

extern t_builtin	g_builtin[];
