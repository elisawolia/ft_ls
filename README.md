# FT_LS

Own reproduction one of the most used command: ls

------

**Usage:**

1. Clone project
2. Compile project by use command
3. Clean object files
4. Use (options are described below)
5. Clean ft_ls file

------

**Options:**

<u>Mandatory Part:</u>

`-l` Output in a column with additional information 

`-R` Recursively search directories

`-a` Show hidden files and directories

`-r` Reverse sort

`-t` Sort by last time of modification

<u>Bonus Part:</u>

`-C` Sort by last status change time

`-m` Output to a line separated by commas

`-S` Sort files by size

`-G` Colored output like [oh-my-zsh](https://github.com/ohmyzsh/ohmyzsh) color scheme

`-1` Output in a column without additional information



------

**Example:**

```bash
>./ft_ls -la
total 496
drwxr-xr-x 14 aleksandr staff   448 Jul 28 18:54 .
drwxr-xr-x 20 aleksandr staff   640 Jul 28 03:06 ..
drwxr-xr-x 16 aleksandr staff   512 Jul 28 18:55 .git
-rw-r--r--  1 aleksandr staff  2275 Jul 28 01:03 Makefile
-rw-r--r--  1 aleksandr staff   645 Jul 28 18:54 README.md
-rw-r--r--  1 aleksandr staff   510 Jul 26 17:54 README.txt
-rw-r--r--  1 aleksandr staff    9 Jul 26 17:54 author
-rwxr-xr-x  1 aleksandr staff  61000 Jul 28 18:26 ft_ls
drwxr-xr-x  3 aleksandr staff   96 Jul 28 01:03 includes
drwxr-xr-x  6 aleksandr staff   192 Jul 26 17:54 libft
-rw-r--r--  1 aleksandr staff  57472 Jul 28 18:26 libft.a
-rw-r--r--  1 aleksandr staff 114288 Jul 28 18:26 libftprintf.a
drwxr-xr-x 21 aleksandr staff   672 Jul 28 18:26 obj
drwxr-xr-x 21 aleksandr staff   672 Jul 28 01:03 src
```

------

**Helpful links:**

