#!/bin/sh
{ echo "# define __OFF 100000";cat main.c; } > tmp.c
gcc tmp.c
rm -f tmp.c
off=$(stat -c%s "a.out")
rm -f a.out
rm -f exec.c
{ echo "# define __OFF $off";cat main.c; } > exec.c
