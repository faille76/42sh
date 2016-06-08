/*
** utils.h for utils in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 12:42:47 2016 Frederic ODDOU
** Last update Sat May 21 21:50:00 2016 oddou_f
*/

#pragma once

#include <stdbool.h>
#include "shell.h"

#define NOT_FOUND	(-1)
#define DELIM_VAR_OPEN	'{'
#define DELIM_VAR_CLOSE	'}'

/*
** Gestion des commandes (Ajout / Suppression / Vide / Purge / Back)
*/

t_commands		*utils_commands_add_right(t_commands	*commands,
						  char		*str,
						  short		index_delim);
void			utils_commands_delete_elem(t_shell	*shell,
						   t_commands	*commands);
void			utils_commands_delete_list(t_commands	*commands);
void			utils_commands_purge_elem(t_commands	*commands);
t_commands		*utils_commands_go_back(t_commands	*commands);

/*
** Gestion de la liste (Ajout / Suppression / Vide / Back)
*/

t_list			*utils_list_add_right(t_list		*list,
					      t_commands	*commands,
					      short		type_separator);
void			utils_list_delete_elem(t_shell		*shell,
					       t_list		*list);
void			utils_list_delete_list(t_list		*list);
t_list			*utils_list_go_back(t_list		*list);

/*
** Gestion des pipes (Ajout / Suppression / Vide / Back)
*/

void			utils_pipe_delete_command(t_pipe	*pipe,
						  t_commands	*commands);
t_pipe			*utils_pipe_add_right(t_pipe		*pipe,
					      t_commands	*commands);
void			utils_pipe_delete_elem(t_list		*list,
					       t_pipe		*pipe);
void			utils_pipe_delete_list(t_pipe		*pipe);
t_pipe			*utils_pipe_go_back(t_pipe		*pipe);

/*
** Convertie les commandes en tab
*/

bool			utils_commands_to_tab(t_shell		*shell,
					      t_pipe		*pipe);

/*
** Obtention de la variable environnement ou locale
*/

char			*utils_get_var(t_shell			*shell,
				       t_commands		*commands);
char			*utils_get_homepath(t_commands		*commands);

/*
** Fusion pour alias et set
*/

bool			utils_if_fusion(char			**tab);
bool			utils_tab_fusion(char			**tab,
					 char			*reponse[2]);

/*
** Gestion des locales
*/

t_locales		*utils_locales_add_right(char		*reponse[2],
						 t_locales	*commands);
t_locales		*utils_locales_add_left(char		*reponse[2],
						t_locales	*loc);
void			utils_locales_delete_elem(t_locales	*loc);
void			utils_locales_delete_list(t_locales	*loc);
t_locales		*utils_locales_find_elem(char		*name,
						 t_locales	*loc);

/*
** Gestion des alias
*/

void			utils_alias_delete_list(t_alias		*alias);
void			utils_alias_delete_elem(t_alias		*alias);
t_alias			*utils_alias_add_left(t_alias		*alias,
					      char		**av_origin,
					      char		**av_to);
t_alias			*utils_alias_add_right(t_alias		*alias,
					       char		**av_origin,
					       char		**av_to);

/*
** Remplacement des alias
*/

char			**utils_alias_replace(t_shell		*shell,
					      char		**av,
					      bool		press);

/*
** Gestion des jobs
*/

t_jobs			*utils_jobs_go_back(t_jobs		*jobs);
t_jobs			*utils_jobs_go_end(t_jobs		*jobs);
t_jobs			*utils_jobs_add_right(t_jobs		*jobs,
					      char		*name,
					      pid_t		pid);
void			utils_jobs_delete_list(t_shell		*shell,
					       t_jobs		*jobs);
void			utils_jobs_delete_elem(t_shell		*shell,
					       t_jobs		*jobs);

/*
** Gestion de l'historique
*/

t_past			*utils_history_add_right(t_past		*history,
						 char		*str);
void			utils_history_delete_elem(t_past	*history);
void			utils_history_delete_list(t_past	*history);
t_past			*utils_history_go_back(t_past		*past);
void			utils_history_delete_excedent(t_past	*history);

/*
** Gestion des alias spéciaux
*/

bool			utils_special_alias_set(t_shell		*shell,
						char		**reponse);
bool			utils_special_alias_execute(t_shell	*shell,
						    char	*name);

/*
** Gestion des variables
*/

char			*utils_get_var_find(t_shell		*shell,
					    char		*find);
char			*utils_get_acolade(char			*find);
int			utils_get_acolade_count(char		*find);

char			*utils_get_history(t_shell		*shell,
					   char			*str);
