# minishell | 1337-KH [![hmokhtar's 42 minishell Score](https://badge42.vercel.app/api/v2/cl9rg4yop01490gjwu202zrsw/project/2636394)](https://github.com/JaeSeoKim/badge42) 
As beautiful as a shell 🐚
### Table of Contents

* [Introduction](#introduction)
	* [What the Shell?](#what-the-shell)
* [Our Implementation of Minishell](#our-implementation-of-minishell)
	* [Lexer and Expander](#lexer-and-expander)
	* [Parser](#parser)
	* [Executor](#executor)
	* [Mind Map](#mind-map)
* [Builtins](#builtins)
* [Prompt](#prompt)
* [Extras](#extras)
	* [Running without Environment](#running-without-environment)
* [Installation](#installation)
	* [Basic Usage](#basic-usage)
	* [Demos](#demos)
* [References](#references)
* [Summary](#summary)
* [License](#license)
* [Authors](#authors)


## Introduction

This project is all about recreating your very own (mini)shell, taking bash (Bourne Again SHell) as a reference.


#### What is Shell?

As we just said, we are asked to implement our shell, but what is a shell to begin with? If we think of (for example) Linux as a nut or a seashell, the kernel/seed is the nut's core and must be surrounded by a cover or shell. Likewise, the shell we are implementing works as a command interpreter securely communicating with the OS kernel, and allows us to perform several tasks from a command line, namely execute commands, create or delete files or directories, or read and write content of files, among (many) other things

## Our Implementation of Minishell

The general idea for this shell is to read a string of commands in a prompt using [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html). Before anything, it is highly recommended to take a deep dive into the [bash manual](https://www.gnu.org/software/bash/manual/bash.html), as it goes over every detail we had to consider when doing this project. ``Minishell`` involves heavy parsing of the string read by ``readline``, thus it is crucial to divide the code of the project into different parts: the ``lexer``, the ``expander``, the ``parser``, and lastly the ``executor``


### Lexer and Expander

This first part covers the part of our code in charge of expanding environment variables with ``$`` followed by characters, Here we also split the input string into small chunks or tokens to handle pipes, redirections, and expansions better.

After reading from the ``stdin`` we use a function which separates the string taking spaces and quotes into account. For example:

```
string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
output: {echo, "hello      there", how, are, 'you 'doing?, $USER, |wc, -l, >outfile, NULL}
```
Then, we apply the expander functions on top of every substring of the original string, resulting in something similar to this:

```
output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |wc, -l, >outfile, NULL}
Note: if a variable is not found, the $var part of the string will be replaced by an empty string
```

Lastly, we have another split function called ``check_others`` which separates with ``<``, ``|``, or ``>``, but only if those chars are outside of quotes:

```
output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
```

### Parser

The parser is in charge of storing the tokenized string and saving it in a useful manner for the executor to use later. Our data structure is managed as follows:

```C
typedef struct s_args
{
 char          *arg;
 struct s_args *head;
 struct s_args *next;
}   t_args;

typedef struct s_exe
{
 char  *cmd;
 char  *option;
 t_args  *arg;
 char  **args;
 char  *stdin;
 char  *stdout;
 char  *stdin2;
 char  *stdout2;
 t_env *envr;
 struct s_exe *next;
 struct s_exe *head;
}   t_exe;
```
Here is a short summary of what every variable is used for

| Parameter | Description |
| :-------: | :---------: |
| ``cmd`` | Stores a command name (ls, pwd, ...), or a path to the executable file |
| ``arg`` | Linked list of all arguments (ls -l -a, pwd -L, ...) |
| ``args`` | Array of arguments (ls -l -a, pwd -L, ...), used for execve function |
| ``stdin`` | Input redirection (ls < file.txt, pwd < file.txt, ...) |
| ``stdout`` | Output redirection (ls > file.txt, pwd > file.txt, ...) |
| ``stdin2`` | Input redirection (ls << file.txt, pwd << file.txt, ...) |
| ``stdout2`` | Output redirection (ls >> file.txt, pwd >> file.txt, ...) |
| ``envr`` | Linked list of environment variables (PATH, HOME, ...) |


After running our lexer and expander, we have a two-dimensional array. Following the previous example, it was the following:

```
{echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
```

Now, our parser starts building the linked list of args (``t_args *arg``), which is filled in the following way:

1. Iterate over the one-dimensional array
2. Whenever a redirection is found, check the type of redirection and retrieve a file descriptor containing the info we need as the infile
3. Check that the file descriptor that has been opened is valid (!= -1) and continue
4. If a pipe is found, add a new node to the list of commands
5. In all other cases add whatever words are found to the argument list (``argv``) we call ``full_cmd``

Here's how the variables will look like according to the example we used before:

```
cmds:
	cmd 1:
		infile: 0 (default)
		outfile: 1 (redirected to pipe)
		full_path: NULL (because echo is a builtin)
		full_cmd: {echo, hello there, how, are, you doing?, pixel, NULL}
	cmd 2:
		infile: 0 (contains output of previous command)
		outfile: 3 (fd corresponding to the open file 'outfile')
		full_path: /bin/wc
		full_cmd: {wc, -l, NULL}
```

### Executor

With all our data properly on our structs, the ``executer`` has all the necessary information to execute commands. For this part we use separate processess to execute non-builtins commands inside child processes that redirect ``stdin`` and ``stdout``. If we are given a full path (e.g. ``/bin/ls``) then we do not need to look for the full path of the command and can execute directly with [execve](https://www.man7.org/linux/man-pages/man2/execve.2.html). If we are given a relative path then we use the ``PATH`` environment variable to determine the ``full_path`` of a command. After all commands have started running, we retrieve the exit status of the most recently executed command with the help of [waitpid](https://linux.die.net/man/2/waitpid)

Once all commands have finished running the allocated memory is freed and a new prompt appears to read the next command

### Mind Map

Here is a handy mindmap of our code structure to help you understand everything we mentioned previously

![Concept Map - Frame 5](https://user-images.githubusercontent.com/71781441/144017004-aa68e8d7-5da7-4ece-afc6-b8ab100113df.jpg)
![Concept Map - Frame 4](https://user-images.githubusercontent.com/71781441/144017016-ef2bb606-c301-42c6-88f1-8ed4339d22cd.jpg)

## Builtins

We were asked to implement some basic builtins with the help of some functions, here is a brief overview of them:

| Builtin | Description | Options | Parameters | Helpful Functions |
| :-----: | :---------: | :-----: | :--------: | :---------------: |
| ``echo`` | Prints arguments separated with a space followed by a new line | ``-n`` | :heavy_check_mark: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``cd`` | Changes current working directory, updating ``PWD`` and ``OLDPWD`` | :x: | :heavy_check_mark: | [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html) |
|  ``pwd``| Prints current working directory | :x: | :x: | [getcwd](https://www.man7.org/linux/man-pages/man3/getcwd.3.html) |
| ``env`` | Prints environment | :x: | :x: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``export`` | Adds/replaces variable in environment | :x: | :heavy_check_mark: | :x: |
| ``unset`` | Removes variable from environment | :x: | :heavy_check_mark: | :x: |

## Prompt

As mentioned previously, we use ``readline`` to read the string containing the shell commands. To make it more interactive, ``readline`` receives a string to be used as a prompt. We have tweaked the looks of it to be nice to use. The prompt is structured as follows:

```
Bash@Allah $>
```
![Screenshot](https://github.com/haytham10/minishell/blob/main/imgs/1.png?raw=true)

## Extras

These are a few neat extras that were not explicitly mentioned on the subject of the project but we thought would make the whole experience nicer

### Running without Environment

When running new instances of minishell or minishell withouth environment (``env -i ./minishell``), some environment variables need to be updated manualy, namely the shell level (``SHLVL``) or the ``_`` variable

Here's the env when minishell is launched without an environment:

![Screenshot](https://raw.githubusercontent.com/haytham10/minishell/main/imgs/2.png)


## Installation

* Prerequisites

Make sure you have these packages installed:

```
gcc make python-norminette readline (valgrind on Linux)
Note for MacOS: to install a recent version of readline, you need to use homebrew: brew install readline
```

* Cloning the Repositories

```shell
git clone https://github.com/haytham10/minishell.git
cd minishell
make
```

### Basic Usage

As per the norm, this project compiles an executable called ``minishell``, and it is compiled using the ``.c`` files.

#### Demos

As we developed the project, we recorded some demos of how the project looked. Here is an overview of the most relevant "releases" we made:

* ``v1.0`` Basic stuff working, no pipes or exit status redirection

![minishell](https://raw.githubusercontent.com/haytham10/minishell/main/imgs/3.png)


* ``v2.0`` Pipes working, plus some exit statuses

![minishell](https://raw.githubusercontent.com/haytham10/minishell/main/imgs/4.png)


* ``v3.0`` Heavily cleaned code, misc fixes, ready for submission :)

![minishell](https://raw.githubusercontent.com/haytham10/minishell/main/imgs/5.png)


## References

* [minishell - 42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
* [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)


## Summary

This was our biggest project yet, and it sure was challenging. Co-developing can be tricky. We had fun in the process though :)

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Authors

- [@Haytham Mokhtari](https://github.com/haytham10)

Octobre 27th, 2022
