/*
** shell.h for shell in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:39 2016 Frederic ODDOU
** Last update Mon May 23 15:12:33 2016 oddou_f
*/

#pragma once

#include <stdbool.h>
#include "enum.h"

#define NAME_SHELL	"FredouSH"

#define ERROR_FUNCTION	"Error: %s function failled.\n"
#define ERROR_NOTFOUND	"%s: Command not found.\n"
#define ERROR_NOMATCH	"%s: No match.\n"
#define ERROR_NOFILE	"%s: No such file or directory.\n"
#define ERROR_NOTFOLDER	"%s: N'est pas un dossier.\n"

#define ERROR_NOSCRIPT	"%s: Aucun fichier ou dossier de ce type.\n"

#define ERROR_ALLOW	"%s: Permission denied.\n"
#define ERROR_NOEXEC	"Binary file not executable.\n"
#define ERROR_FORMAT	"%s: Exec format error. Binary file not executable.\n"

#define MESS_SUSPENDED	"\r[%u]\t+ %d Suspended\t%s\n"
#define MESS_CTRLD	"Use \"exit\" to leave %s.\n"

#define HISTORY_LIMIT	50

#define LIMIT_BUF_QUOTE	10000000

#define SHRC		".42shrc"

typedef struct		s_commands
{
  char			*str;
  short			index_delim;
  struct s_commands	*next;
  struct s_commands	*prev;
}			t_commands;

typedef struct		s_pipe
{
  pid_t			pid;
  t_commands		*commands;
  int			ac;
  char			**av;
  char			*path;
  int			fd[2];
  char			*redi[4];
  struct s_pipe		*next;
  struct s_pipe		*prev;
}			t_pipe;

typedef struct		s_list
{
  t_commands		*commands;
  t_pipe		*pipe;
  short			type_separator;
  bool			treat;
  bool			background;
  struct s_list		*next;
  struct s_list		*prev;
}			t_list;

typedef struct		s_alias
{
  char			**av_origin;
  char			**av_to;
  struct s_alias	*next;
  struct s_alias	*prev;
}			t_alias;

typedef struct		s_locales
{
  char			*name;
  char			*value;
  struct s_locales	*next;
  struct s_locales	*prev;
}			t_locales;

typedef struct		s_pid
{
  pid_t			pid;
  pid_t			pgid;
}			t_pid;

typedef struct		s_jobs
{
  unsigned int		id;
  char			*name;
  pid_t			pid;
  struct s_jobs		*next;
  struct s_jobs		*prev;
}			t_jobs;

typedef struct		s_past
{
  unsigned int		id;
  char			*str;
  time_t		date;
  struct s_past		*next;
  struct s_past		*prev;
}			t_past;

typedef struct		s_shell
{
  bool			write;
  int			fd[2];
  int			last_return;
  t_pid			pid;
  char			*oldpwd;
  char			**ae;
  t_locales		*locales;
  char			**path;
  t_commands		*commands;
  t_list		*list;
  t_pipe		*pipe;
  t_alias		*alias;
  t_jobs		*jobs;
  t_past		*history;
  bool			exit_active;
}			t_shell;

typedef struct		s_ps1
{
  char			*replace;
  void			(*func)(t_shell	*shell);
}			t_ps1;

bool			shell_init(t_shell			*shell,
				   int				ac,
				   char				**av,
				   char				**ae);
void			shell_signal(bool			ign);
bool			shell_close(t_shell			*shell,
				    unsigned char		value);
bool			shell_get_commands_moul(t_shell		*shell);
bool			shell_get_commands(t_shell		*shell);
void			shell_commands_free(t_shell		*shell);
char			*shell_get_path(t_shell			*shell,
					char			*name);

bool			shell_list_treat(t_shell		*shell);
void			shell_prompt(t_shell			*shell);

bool			shell_redirection(t_shell 		*shell,
					  t_pipe 		*pipe,
					  int			*fd);

bool			shell_dup(t_shell			*shell,
				  t_pipe			*pipe);

void			shell_step(t_shell			*shell,
				   char				*str);

int			shell_treat_parenthese(t_shell		*shell,
					       t_pipe		*pipe);
void			shell_treat_backquotes(t_shell		*shell,
					       t_pipe		*pipe);

int			shell_wait_status(int			status);

bool			shell_treat_glob(t_pipe			*pipe);

bool			shell_script(t_shell			*shell,
				     int			ac,
				     char			**av);

bool			shell_load_42shrc(t_shell		*shell);

void			shell_change_tgrp(pid_t			pid);

void			shell_background(t_shell		*shell);

/*
** shell_treat_pipe.c
*/

pid_t			shell_treat_pipe_do(t_shell	*shell,
					    t_pipe	*pipe);
void			shell_treat_pipe_wait(t_shell	*shell,
					      t_list	*list,
					      t_pipe	*pipe,
					      pid_t	pgid);

/*
** shell_pipe.c
*/

void			shell_pipe_close(t_pipe			*pipe);
void			shell_pipe_open(t_shell			*shell,
					t_pipe			*mypipe);

/*
** shell_prompt_func.c
*/

void			shell_prompt_user(t_shell		*shell);
void			shell_prompt_version(t_shell		*shell);
void			shell_prompt_ret_value(t_shell		*shell);
void			shell_prompt_nb_line(t_shell		*shell);
void			shell_prompt_directory(t_shell		*shell);
void			shell_prompt_echap(t_shell		*shell);
void			shell_prompt_time(t_shell		*shell);
