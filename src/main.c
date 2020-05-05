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
	opt->rec = 0;
	opt->t = 0;
	opt->one = 0;
	opt->c = 0;
	opt->s = 0;
	return (opt);
}

void	read_opt(char *str, t_opt **opt)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
		{
			(*opt)->l = 1;
			if ((*opt)->one == 1)
				(*opt)->one = 0;
			if ((*opt)->c == 1)
				(*opt)->c = 0;
		}
		if (str[i] == 'a')
			(*opt)->a = 1;
		if (str[i] == 't')
			(*opt)->t = 1;
		if (str[i] == 'R')
			(*opt)->rec = 1;
		if (str[i] == 'r')
			(*opt)->r = 1;
		if (str[i] == 'S')
		{
			(*opt)->s = 1;
			if ((*opt)->t == 1)
				(*opt)->t = 0;
		}
		if (str[i] == '1')
		{
			(*opt)->one = 1;
			if ((*opt)->l == 1)
				(*opt)->l = 0;
			if ((*opt)->c == 1)
				(*opt)->c = 0;
		}
		if (str[i] == 'C')
		{
			(*opt)->c = 1;
			if ((*opt)->l == 1)
				(*opt)->l = 0;
			if ((*opt)->one == 1)
				(*opt)->one = 0;
		}
		if (str[i] != 'S' && str[i] != 'C' && str[i] != '1' && str[i] != 'l' && str[i] != 'a' && str[i] != 't' && str[i] != 'R' && str[i] != 'r')
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
	else if ((*opt)->one == 1)
	{
		print_one(dir);
	}
	else
	{
		print_list(dir);
	}
	merge_sort_dir(&(dir->sub), &def_sort_dir, 1);
	merge_sort_dir(&(dir->next), &def_sort_dir, 1);
	if ((*opt)->t)
	{
		merge_sort_dir(&(dir->sub), &time_sort_dir, 1);
		merge_sort_dir(&(dir->next), &time_sort_dir, 1);
	}
	if ((*opt)->s)
	{
		merge_sort_dir(&(dir->sub), &size_sort_dir, 1);
		merge_sort_dir(&(dir->next), &size_sort_dir, 1);
	}
	if ((*opt)->r)
	{
		reverse_dir_next(&(dir->sub));
		reverse_dir_next(&(dir->next));
		reverse_dir_sub(&(dir->sub));
		reverse_dir_sub(&(dir->next));
	}
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
	int 	col_width;
	int 	files_count;
	struct  winsize w;
	int 	numcols;
	int 	numrows;

	files_count = count_files(dir->files);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col_width = (dir->max_name + 8) & ~7; // col_width = ближайшей число кратное 8 (по табу)
	numcols = (w.ws_col / col_width > 0) ? w.ws_col / col_width : 1;
	numrows = files_count / numcols;
	if (files_count % numcols)
		++numrows;
	return (numrows);
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
}

void print_one(t_dir *dir)
{
	t_file *tmp;
	
	tmp = dir->files;
	while(tmp != NULL)
	{
		printf("%s\n",tmp->file_name);
		tmp = tmp->next;
	}
}

void	read_dir(char *dirname, t_opt **opt, t_dir *d)
{
	t_dir	*direct;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		free(*opt);
		exit(1);
	};
	direct = init_dir(dir, *opt, dirname, d);
	closedir(dir);
	if ((*opt)->rec == 1)
	{
		print_r(direct, opt);
	}
	else if ((*opt)->l == 1)
	{
		printf("total %lld\n", direct->total);
		print_list_l(direct);
	}
	else  if ((*opt)->one == 1)
	{
		print_one(direct);
	}
	else
	{
		print_list(direct);
	}
	if ((*opt)->rec != 1 || (!direct->next && !direct->sub && !direct->mult))
		free_dir(&direct);
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
	merge_sort_dir(&direct, &def_sort_dir, 0);
	if ((*opt)->s)
		merge_sort_dir(&direct, &size_sort_dir, 0);
	else if ((*opt)->t)
		merge_sort_dir(&direct, &time_sort_dir, 0);
	if ((*opt)->r)
		reverse_dir_mult(&direct);
	tmp = direct;
	while (tmp != NULL)
	{
		if ((*opt)->rec == 0 && argc != i + 1)
			printf("%s:\n",tmp->name);
		if ((*opt)->rec == 1)
		{
			print_r(tmp, opt);
		}
		else if ((*opt)->l == 1)
		{
			printf("total %lld\n", tmp->total);
			print_list_l(tmp);
		}
		else  if ((*opt)->one == 1)
		{
			print_one(direct);
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
	dirname = ft_strdup(".");
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
	free(opt);
	free(dirname);
/*	int t = 0;
	while (1)
		t++;*/
	return (0);
}