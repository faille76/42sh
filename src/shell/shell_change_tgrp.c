/*
** shell_change_tgrp.c for tgrp in /src/shell/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Tue May 31 14:31:05 2016 Frederic ODDOU
** Last update Wed Jun  1 19:16:31 2016 Frederic ODDOU
*/

#include <unistd.h>

void			shell_change_tgrp(pid_t			pid)
{
  if (isatty(STDIN_FILENO))
    {
      tcsetpgrp(STDERR_FILENO, pid);
      tcsetpgrp(STDIN_FILENO, pid);
      tcsetpgrp(STDOUT_FILENO, pid);
    }
}
