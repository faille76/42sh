/*
** utils_signal.c for utils signal in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  1 18:17:59 2016 Frederic ODDOU
** Last update Sun May 01 18:30:19 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sig_mess.h"

void			sig_display(int			status)
{
  int			i;

  i = 0;
  if (WIFSIGNALED(status))
    {
      while (g_sig_mess[i].mess != NULL)
	{
	  if (g_sig_mess[i].sig == WTERMSIG(status))
	    {
	      fprintf(stderr, "%s", g_sig_mess[i].mess);
	      if (WCOREDUMP(status))
		fprintf(stderr, " (core dumped)");
	      fprintf(stderr, "\n");
	      return ;
	    }
	  i++;
	}
    }
}
