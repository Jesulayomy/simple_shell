<p align="center">
<img src="https://media.licdn.com/dms/image/C4D0BAQGCvVQPUIZ_qA/company-logo_200_200/0/1669838001590?e=1679529600&v=beta&t=4khijvPVq-p8JtNpIp4Dlwu_kbv7Bvn31oSegEoxwqk" alt="alx logo">
</p>

<h1 align="center"> A Simple shell program created with C </h1>

----------------------------------------------------------

<h2> Overview </h2>

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0].
```commandline
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

```commandline
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

---------------------------------------------------------

<h2> List of allowed functions and system calls </h2>
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

---------------------------------------------------------

<h2> Compilation </h2>
Can be compiled with
```commandline
 $ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

or by running the compilation script. (this runs with the valgrind memcheck tool, please install that before running this script)
```commandline
 $ ./compile.sh
```

--------------------------------------------------------------------------------

<h2> Libraries :scroll: </h2>

-> [shell.h](shell.h)
-> errno.h
-> fcntl.h
-> limits.h
-> signal.h
-> stddef.h
-> stdio.h
-> stdlib.h
-> string.h
-> sys/stat.h
-> sys/types.h
-> sys/wait.h
-> unistd.h

--------------------------------------------------------------------------------

<h2> Contributors </h2>

<table>
<tr>
<td align="center"><a href="https://github.com/micoliser"><img src="https://avatars.githubusercontent.com/u/108087255?v=4" width="80px;" alt=""/><br /><sub><b>Micoliser</b></sub></a></td>

<td align="center"><a href="https://github.com/Jesulayomy"><img src="https://avatars.githubusercontent.com/u/113533393?s=96&v=4" width="80px;" alt=""/><br /><sub><b>Jesulayomy</b></sub></a></td>
</tr>
</table>

--------------------------------------------------------------------------------
