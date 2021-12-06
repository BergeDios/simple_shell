##Simple Shell By Santiago Goyret and Martin Casamayou
> This is our final project of the first trimester for Holberton School. We were asked to code a simple Unix shell like from 0. A Shell for those unaware is an interactive command-line interpreter( a.k.a receives commands via user input and runs whatever it's commanded if allowed). We created a custom shell that would receive this command via the CLI(Command Line Interface).
> It allows users to type in a set of commands with arguments if there's a chance. For example: "ls" to display directory files, "echo" to print out words to the standard input, etc). 
> Our shell might be more similar to Ken Thompson's very first shell in the way that is basic but it handles leaks really well, very much like more recent shell iterations.


### Description
> This repository holds all the code necessary for our custom shell to run.
> Our shell currently handles the executions of executables found in the enviromental variable PATH, with or without their full path. Firstly though before checking this functions the shell checks if the input is one of our built-in functions. Currently our buil-ins are the following:

#### Built-ins
* ```exit``` exits shell
* ```env``` prints enviromental variables
* ```cd``` changes directories
* ```history``` send every input when exiting shell to a file at $HOME named "log"

#### Functions and system calls used
```read```, ```write```, ```malloc```, ```signal```, ```free```, ```getcwd```, ```chdir```, ```access```, ```execve```, ```wait```, ```exit```, ```getline```, ```fork```, ```perror```

#### How To Install, Compile, and Use
**Install and Compile**
```
(your_terminal)$ git clone https://github.com/BergeDios/simple_shell.git
(your_terminal)$ cd simple_shell
(your_terminal)$ gcc -Wall -Werror -Wextra -pedantic -Wno-format *.c -o simple_shell
```
**Non-Interactive Mode**
```
Example:
echo "ls -l" | ./simple_shell
```
**Interactive Mode**
```Activates the shell```
```
(your_terminal)$ ./simple_shell
$
```
Sample Usage
```
$ ls -l /simple_shell
total 8
drwxr-xr-x 2 root  4096 Dec 6 08:44 day_0
-rw-r--r-- 1 root  14 Dec 3 14:26 README.md

$ echo "This is a pretty cool!"
This is pretty cool!

$ man ./man_1_simple_shell (opens our manpage for more information)
```
Stop and return to your original shell
```
$ exit
(your_terminal)$
```

### Authors
Martin Casamayou [![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/martin-casamayou-del-pino-24b554222/)
Santiago Goyret [![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/santiago-goyret-093837103/)
