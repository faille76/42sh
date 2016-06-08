/*
** b_sort_flag.c for sort in /home/josso/rendu/psu/PSU_2015_42sh
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue May 24 14:59:08 2016 Arthur Josso
** Last update Wed May 25 18:50:13 2016 Arthur Josso
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin_sort.h"

static t_type_tab       g_tab[] =
  {
    {F_I, 'i'},
    {F_F, 'f'},
    {F_N, 'n'},
    {F_R, 'r'},
    {F_H, 'h'},
    {NONE, '\0'}
  };

static t_incomp_tab	g_incomp[] =
  {
    {F_F, F_N, "uppercase or lowercase doesn't matter for numeric sort"},
    {F_I, F_N, "Cannot ignore non-printable char for numeric sort"},
    {NONE, NONE, NULL}
  };

static int      incomp_flag(t_flag      flag)
{
  int		i;

  i = 0;
  while (g_incomp[i].flag_1 != NONE)
    {
      if ((flag & g_incomp[i].flag_1) && (flag & g_incomp[i].flag_2))
	{
	  fprintf(stderr, "sort: %s\n", g_incomp[i].s);
	  return (1);
	}
      i++;
    }
  return (0);
}

static int      err_bad_arg(char const  *s,
			    char	unknow)
{
  if (!unknow)
    fprintf(stderr, "sort: bad argument: %s\n", s);
  else
    fprintf(stderr, "sort: bad argument: %s: bad flag: %c\n", s, unknow);
  return (1);
}

static int      add_flags(t_flag        *flags,
			  char const    *s)
{
  int           i;
  int           j;
  bool          unknow_flag;

  i = 1;
  while (s[i])
    {
      unknow_flag = true;
      j = 0;
      while (g_tab[j].type != NONE)
	{
	  if (s[i] == g_tab[j].character)
	    {
	      *flags |= g_tab[j].type;
	      unknow_flag = false;
	    }
	  j++;
	}
      if (unknow_flag)
	return (err_bad_arg(s, s[i]));
      i++;
    }
  if (i == 1)
    return (err_bad_arg(s, '\0'));
  return (0);
}

t_flag		get_flags(int   ac,
			  char  **av,
			  char  **file)
{
  t_flag        flags;
  int           i;

  *file = NULL;
  flags = 0;
  i = 1;
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  if (add_flags(&flags, av[i]) == 1)
	    return (-1);
	}
      else if (*file == NULL)
	*file = av[i];
      else
	{
	  fprintf(stderr, "sort: bad argument: %s\n", av[i]);
	  return (-1);
	}
      i++;
    }
  if (incomp_flag(flags) == 1)
    return (-1);
  return (flags);
}
