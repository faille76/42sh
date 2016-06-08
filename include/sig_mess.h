/*
** sig_mess.h for sig mess in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  1 18:19:03 2016 Frederic ODDOU
** Last update Sun May 22 01:57:04 2016 oddou_f
*/

#pragma once

typedef struct 		s_sig_mess
{
  int			sig;
  char			*mess;
}			t_sig_mess;

void			sig_display(int			status);

extern t_sig_mess	g_sig_mess[];
