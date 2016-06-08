/*
** ctrl_l.c for ctrl_l in /lib/getch/src/rd/
**
** Made by Frederic ODDOU
** Login   <login_x@epitech.eu>
**
** Started on  Wed May 25 14:26:23 2016 Frederic ODDOU
** Last update Sat Jun  4 18:10:50 2016 Frederic ODDOU
*/

#include <stdio.h>
#include "rd.h"

int     rd_ctrl_l(t_rd *rd, int key)
{
  (void)key;
  printf("\e[1;1H\e[2J");
  fflush(stdout);
  rd_disp(rd);
  return (0);
}
