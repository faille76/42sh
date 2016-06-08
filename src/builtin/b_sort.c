/*
** b_sort.c for sort in /home/josso/rendu/psu/PSU_2015_42sh
**
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
**
** Started on  Mon May 23 16:59:12 2016 Arthur Josso
** Last update Fri Jun  3 23:33:00 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "shell.h"
#include "builtin_sort.h"
#include "my.h"

static int	get_fd(char	*path)
{
  int		fd;

  if (path == NULL)
    return (STDIN_FILENO);
  if (access(path, F_OK) == -1)
    {
      fprintf(stderr, "sort: %s: no such file\n", path);
      return (-1);
    }
  if ((fd = open(path, O_RDONLY)) == -1)
    {
      fprintf(stderr, "sort: cannot open %s\n", path);
      return (-1);
    }
  return (fd);
}

static char	**get_tab(int	fd)
{
  int		size;
  char		*next;
  char		**tab;
  char		*s;

  size = 0;
  next = NULL;
  if ((tab = malloc(sizeof(char *))) == NULL)
    return (NULL);
  tab[0] = NULL;
  while ((s = get_next_line(fd, &next, &size)) != NULL)
    if ((tab = my_tab_realloc(tab, s)) == NULL)
      return (NULL);
  if (next)
    free(next);
  return (tab);
}

static void	show_tab(t_tab	*tab)
{
  int		i;

  if (tab->flag & F_R)
    {
      i = tab->size - 1;
      while (i >= 0)
	printf("%s\n", tab->tab[i--]);
    }
  else
    {
      i = 0;
      while (tab->tab[i])
	printf("%s\n", tab->tab[i++]);
    }
}

static bool	print_help(t_tab	*tab)
{
  if (!(tab->flag & F_H))
    return (false);
  printf("Usage: sort [OPTION]... [FILE]\n\n");
  printf("With no FILE, read standard input.\n\n");
  printf("Ordering options:\n");
  printf("  -f,\tfold lower case to upper case characters\n");
  printf("  -i,\tconsider only printable characters\n");
  printf("  -n,\tcompare according to string numerical value\n");
  printf("  -r,\treverse the result of comparisons\n");
  return (true);
}

int	       	b_sort(int	ac,
		       char	**av,
		       t_shell	*shell)
{
  t_tab		tab;
  char 		*file;
  int		fd;

  if (!shell->write)
    return (EXIT_SUCCESS);
  if ((tab.flag = get_flags(ac, av, &file)) == -1)
    return (EXIT_SUCCESS);
  if (print_help(&tab))
    return (EXIT_SUCCESS);
  if ((fd = get_fd(file)) == -1)
    return (EXIT_FAILURE);
  if ((tab.tab = get_tab(fd)) == NULL)
    return (EXIT_FAILURE);
  if (gen_tmp(&tab) == 1)
    return (EXIT_FAILURE);
  sort_tab(&tab);
  show_tab(&tab);
  my_tab_free(tab.tab);
  my_tab_free(tab.tmp_s);
  if (tab.tmp_f)
    free(tab.tmp_f);
  return (EXIT_SUCCESS);
}
