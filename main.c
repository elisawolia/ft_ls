/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

t_opt	*malloc_opt(void)
{
	t_opt *opt;

	if (!(opt = ft_memalloc(sizeof(t_opt))))
	{
		perror("malloc");
		exit(1);
	}
	opt->l = 0;
	opt->a = 0;
	opt ->r = 0;
	opt->R = 0;
	opt->t = 0;
	return (opt);
}

void	read_opt(char *str, t_opt **opt)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			(*opt)->l = 1;
		if (str[i] == 'a')
			(*opt)->a = 1;
		if (str[i] == 't')
			(*opt)->t = 1;
		if (str[i] == 'R')
			(*opt)->R = 1;
		if (str[i] == 'r')
			(*opt)->r = 1;
		if (str[i] != 'l' && str[i] != 'a' && str[i] != 't' && str[i] != 'R' && str[i] != 'r')
		{
			perror("ft_ls");
			// printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			free(*opt);
			exit(1);
		}
		i++;
	}
}

void	print_r(t_dir *dir, t_opt **opt)
{
	if (ft_strcmp(dir->name, "."))
	{
		ft_putchar('\n');
		printf("%s:\n",dir->name);
	}
	if ((*opt)->l == 1)
	{
		if (dir->total != 0)
			printf("total %lld\n", dir->total);
		print_list_l(dir);
	}
	else
	{
		print_list(dir);
	}
	mergeSortDir(&(dir->sub), &defSortDir, 1);
	mergeSortDir(&(dir->next), &defSortDir, 1);
	if (dir->sub)
	{
		read_dir(dir->sub->name, opt, dir->sub);
	}
	if (dir->next)
	{
		read_dir(dir->next->name, opt, dir->next);
	}
}
	

void print_list_l(t_dir *dir)
{
	t_file *tmp;

	tmp = dir->files;
	while(tmp != NULL)
	{
		if (S_ISBLK(tmp->mode))
			ft_putchar('b');
		else if (S_ISCHR(tmp->mode))
			ft_putchar('c');
		else if (S_ISFIFO(tmp->mode))
			ft_putchar('f');
		else if (S_ISREG(tmp->mode))
			ft_putchar('-');
		else if (S_ISDIR(tmp->mode))
			ft_putchar('d');
		else if (S_ISLNK(tmp->mode))
			ft_putchar('l');
		else
			ft_putchar('s');
		(S_IRUSR & tmp->mode) ? ft_putchar('r') : ft_putchar('-');
		(S_IWUSR & tmp->mode) ? ft_putchar('w') : ft_putchar('-');
		if (S_ISUID & tmp->mode)
			(S_IXUSR & tmp->mode) ? ft_putchar('s') : ft_putchar('S');
		else
			(S_IXUSR & tmp->mode) ? ft_putchar('x') : ft_putchar('-');
		(S_IRGRP & tmp->mode) ? ft_putchar('r') : ft_putchar('-');
		(S_IWGRP & tmp->mode) ? ft_putchar('w') : ft_putchar('-');
		if (S_ISGID & tmp->mode)
			(S_IXUSR & tmp->mode) ? ft_putchar('s') : ft_putchar('S');
		else
			(S_IXGRP & tmp->mode) ? ft_putchar('x') : ft_putchar('-');
		(S_IROTH & tmp->mode) ? ft_putchar('r') : ft_putchar('-');
		(S_IWOTH & tmp->mode) ? ft_putchar('w') : ft_putchar('-');
		if (S_ISVTX & tmp->mode)
			(S_IXUSR & tmp->mode) ? ft_putchar('t') : ft_putchar('T');
		else
			(S_IXOTH & tmp->mode) ? ft_putchar('x') : ft_putchar('-');
		printf("%4ld ", tmp->link);
		printf("%-*s", dir->max_uid + 1, getpwuid(tmp->uid)->pw_name);
		printf("%*s ", dir->max_gid + 1, getgrgid(tmp->gid)->gr_name);
		printf("%*lld ", dir->max_size, tmp->size);
		printf("%.12s ", ctime(&tmp->time) + 4);
		printf("%s\n", tmp->file_name);
		tmp = tmp->next;
	}
}

int 	rows_print(t_dir *dir)
{
	int 	i;
	int 	cols;
	int 	files;
	int 	res;
	struct  winsize w;

	i = 0;
	res = 1;
	files = count_files(dir->files);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	printf("DEF COLS ARE %hu\n", w.ws_col);
	printf("DEF ROWS ARE %hu\n", w.ws_row);
	cols = w.ws_col / (dir->max_name + 1);
	printf("ONE COLS ARE %d\n", cols);
    if (!cols)
      cols = 1;
    if ((dir->max_name + 1) * files < w.ws_col)
      cols = files;
    res = files / cols;
    if (files % cols)
      ++res;
	return (cols);
}

void print_list(t_dir *dir)
{
	int 	rows;
	int 	i;
	int 	j;
	t_file *tmp;
	
	tmp = dir->files;
	rows = rows_print(dir);
	i = 0;
	j = 0;
	printf("!!! rows = %d\n", rows);

	while (i < rows)
	{
		j = 0;
		tmp = dir->files;
		while(tmp != NULL)
		{
			if (j % rows == i)
				printf("%-*s\t",dir->max_name ,tmp->file_name);
			j++;
			tmp = tmp->next;
		}
		printf("\n");
		i++;
	}
/*	while(tmp != NULL)
	{
		if (i % 2 == 0)
			printf("%s\t",tmp->file_name);
		i++;
		tmp = tmp->next;
	}
	printf("\n");
	i = 0;
	tmp = dir->files;
	while(tmp != NULL)
	{
		if (i % 2 == 1)
			printf("%s\t",tmp->file_name);
		i++;
		tmp = tmp->next;
	}
	printf("\n");*/
}

void	read_dir(char *dirname, t_opt **opt, t_dir *d)
{
	t_dir	*direct;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		free(dir);
		free(*opt);
		exit(1);
	};
	direct = init_dir(dir, *opt, dirname, d);
//	free(dir);
	if ((*opt)->R == 1)
	{
		print_r(direct, opt);
	}
	else if ((*opt)->l == 1)
	{
		printf("total %lld\n", direct->total);
		print_list_l(direct);
	}
	else
	{
		print_list(direct);
	}
//	free_dir(&direct);
}

void	read_mult_dir(char **dirname, int i, int argc, t_opt **opt)
{
	t_dir	*direct;
	t_dir	*tmp;
	DIR		*dir;
	int 	j;

	j = i;
	direct = NULL;
	tmp = NULL;
	while (j < argc)
	{
		dir = opendir(dirname[j]);	
		if (!dir)
			perror("diropen");
		dir_next(&direct, init_dir(dir, *opt, dirname[j], NULL));
		j++;
	}
	mergeSortDir(&direct, &defSortDir, 0);
	tmp = direct;
	while (tmp != NULL)
	{
		if ((*opt)->R == 0 && argc != i + 1)
			printf("%s:\n",tmp->name);
		if ((*opt)->R == 1)
		{
			print_r(tmp, opt);
		}
		else if ((*opt)->l == 1)
		{
			printf("total %lld\n", tmp->total);
			print_list_l(tmp);
		}
		else
		{
			print_list(tmp);
		}
		if (tmp->mult != NULL)
			ft_putchar('\n');
		tmp = tmp->mult;
	}
}

int	main(int argc, char **argv)
{
	t_opt	*opt;
	char	*dirname;
	int		i;

	i = 1;
	opt = malloc_opt();
	dirname = ".";
	while (i < argc)
	{
		if (argv[i][0] == '-')
			read_opt(argv[i], &opt);
		else
			break;		
		i++;
	}
	if (i == argc)
	{
		read_dir(dirname, &opt, NULL);
	}
	else 
	{
		read_mult_dir(argv, i, argc, &opt);
	}
	//free(opt);
	return (0);
}
