/*
** builtin_sort.h for sort in /home/josso/rendu/psu/PSU_2015_42sh
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue May 24 14:29:13 2016 Arthur Josso
** Last update Wed May 25 18:49:49 2016 Arthur Josso
*/

#pragma once

#include "shell.h"

typedef enum    e_flag_type
  {
    F_I		= 1 << 0,
    F_F		= 1 << 1,
    F_N		= 1 << 2,
    F_R		= 1 << 3,
    F_H		= 1 << 4,
    NONE	= 1 << 5
  }		t_flag_type;

typedef char	t_flag;

typedef struct	s_type_tab
{
  t_flag_type	type;
  char		character;
}		t_type_tab;

typedef struct	s_incomp_tab
{
  t_flag_type	flag_1;
  t_flag_type	flag_2;
  char const	*s;
}		t_incomp_tab;

typedef struct	s_tab
{
  char		**tab;
  char		**tmp_s;
  float		*tmp_f;
  int		size;
  t_flag	flag;
}		t_tab;

t_flag		get_flags(int   ac,
			  char  **av,
			  char  **file);
int		gen_tmp(t_tab	*tab);
void		sort_tab(t_tab	*tab);
