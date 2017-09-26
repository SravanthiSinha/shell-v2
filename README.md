# shell-v2
Shell Version 2 - A re-creation of a UNIX shell using C.
## Download and Run Instructions

Clone Repo:
```
$ git clone https://github.com/SravanthiSinha/shell-v2.git
```

Compile:
```
$ make
```

Run the Executable:
```
$ ./hsh
```

To find all about features supported, run the manual:
```
$ man ./man_1_hsh
```

To run tests use run_checks.bash $foldername of tests:
```
$ ./run_checks.bash $folderno
```

## Development details
The project concepts are explored in

* https://github.com/SravanthiSinha/EYNTK-SHELL/blob/master/EYNTK-Shell-v1/README.md

* https://github.com/SravanthiSinha/EYNTK-SHELL/blob/master/EYNTK-Shell-v2/README.md

## hsh 1.0 +

A UNIX command line interpreter.

Usage: hsh

* Displays a prompt and wait for the user to type a command. A command line always ends with a new line.
* The prompt is displayed again each time a command has been executed.
* If an executable cannot be found, prints an error message and display the prompt again.
* Handle errors.
* Handles the "end of file" condition (Ctrl+D)
* Handles command lines with arguments
* Handles and parse the PATH environment variable

#### Builtins

Implemented the built-in command **exit**:

* exit built-in  behaves exactly like sh's
* Handles arguments

Implemented the built-in command **cd**:

* Changes the current directory of the process.
* Command syntax: cd [path]
* If no argument is given to cd the command is interpreted like cd $HOME
* Handles the command cd -

Implemented the built-in command **env**:

* Prints the current environment

Implemented the built-in command **setenv**:

* Sets the environment variable

Implemented the built-in command **unsetenv**:

* Unset/remove the environment variable

#### Redirections
Handles the stream redirections **>, < , >> , << , | **

Usage:

**[command]> file**   Redirect standard output to file.

**[command]>> file**  Append standard output to file.

**[command]< file**   Redirect standard input from file.

**[command] | [command2..]**   Redirect command output input of command2

The following redirection is often called a **here-document**.

[command]<< delimiter

here-doc-text ...

delimiter
```
$ echo Holberton School > test
$ cat -e test
Holberton School$
$
$ rm -f test
$ echo Holberton School >> test
$ cat -e test
Holberton School$
$ echo Holberton School >> test
$ cat -e test
Holberton School$
Holberton School$
$ cat -e small_file
Holberton$
Second line$
$ rev < small_file
notrebloH
enil dnoceS
$
$ cat -e << HOLBERTON
> qwertyuiop
> ls -l                          
> cat -e small_file
> HOLBERTONnope
> nopeHOLBERTON
> HOLBERTON
> HOLBERTON
qwertyuiop$
ls -l$
cat -e small_file$
HOLBERTONnope$
nopeHOLBERTON$
HOLBERTON $
$
$ ls /var | rev
spukcab
ehcac
hsarc
bil
lacol
kcol
gol
liam
scirtem
tpo
nur
loops
pmt
$ ls -lr /var | cat -e
total 44$
drwxrwxrwt  2 root root     4096 Aug 28 21:53 tmp$
drwxr-xr-x  9 root root     4096 Aug  3  2016 spool$
lrwxrwxrwx  1 root root        4 Jun  5 17:51 run -> /run$
drwxr-xr-x  2 root root     4096 Aug  3  2016 opt$
drwxrwsrwt  2 root whoopsie 4096 Aug  3  2016 metrics$
drwxrwsr-x  2 root mail     4096 Aug  3  2016 mail$
drwxrwxr-x 14 root syslog   4096 Aug 28 10:56 log$
lrwxrwxrwx  1 root root        9 Jun  5 17:51 lock -> /run/lock$
drwxrwsr-x  2 root staff    4096 Apr 10  2014 local$
drwxr-xr-x 73 root root     4096 Aug 12 18:06 lib$
drwxrwsrwt  2 root whoopsie 4096 Aug 28 14:56 crash$
drwxr-xr-x 17 root root     4096 Aug  3  2016 cache$
drwxr-xr-x  2 root root     4096 Aug 24 10:24 backups$
```

#### Control operators
Handles the commands separator **; , && , ||**

```
$ ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /hbtn ; ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /var ; ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
$ ls /var ; ls /hbtn ; ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$
$ ls /var && ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /hbtn && ls /var
ls: cannot access /hbtn: No such file or directory
$ ls /var && ls /var && ls /var && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
$ ls /var && ls /var && ls /var && ls /hbtn && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
$
$ ls /var || ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
$
```
