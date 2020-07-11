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

void	sorting_dir_r(t_dir *dir, t_opt **opt)
{
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
}

void	print_r(t_dir *dir, t_opt **opt)
{
	if (ft_strcmp(dir->name, "."))
	{
		ft_putchar('\n');
		ft_printf("%s:\n", dir->name);
	}
	if ((*opt)->l == 1)
	{
		if (dir->total != 0)
			ft_printf("total %lld\n", dir->total);
		print_list_l(dir);
	}
	else if ((*opt)->one == 1)
		print_one(dir);
	else
		print_list(dir);
	sorting_dir_r(dir, opt);
	if (dir->sub)
		read_dir(dir->sub->name, opt, dir->sub);
	if (dir->next)
		read_dir(dir->next->name, opt, dir->next);
}

/*
** col_width = ближайшей число кратное 8 (по табу)
*/

int		rows_print(t_dir *dir)
{
	int				col_width;
	int				files_count;
	struct winsize	w;
	int				numcols;
	int				numrows;

	files_count = count_files(dir->files);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col_width = (dir->max_name + 8) & ~7;
	numcols = (w.ws_col / col_width > 0) ? w.ws_col / col_width : 1;
	numrows = files_count / numcols;
	if (files_count % numcols)
		++numrows;
	return (numrows);
}

void	printing(t_dir *direct, t_opt **opt)
{
	if ((*opt)->rec == 1)
		print_r(direct, opt);
	else if ((*opt)->l == 1)
	{
		if (!(*opt)->d)
			ft_printf("total %lld\n", direct->total);
		print_list_l(direct);
	}
	else if ((*opt)->one == 1)
		print_one(direct);
	else if ((*opt)->m == 1)
		print_m(direct);
	else
		print_list(direct);
}

void	read_dir(char *dirname, t_opt **opt, t_dir *d)
{
	t_dir	*direct;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	direct = init_dir(dir, *opt, dirname, d);
	closedir(dir);
	printing(direct, opt);
	if ((*opt)->rec != 1 || (!direct->next && !direct->sub && !direct->mult))
		free_dir(&direct);
}

void	printing_mult_dir(t_dir *direct, int i, int argc, t_opt **opt)
{
	t_dir	*tmp;

	tmp = direct;
	while (tmp != NULL)
	{
		if ((*opt)->d)
		{
			print_d(*opt, tmp);
			break ;
		}
		if ((*opt)->rec == 0 && argc != i + 1)
			ft_printf("%s:\n", tmp->name);
		if ((*opt)->rec == 1)
			print_r(tmp, opt);
		else if ((*opt)->l == 1)
		{
			ft_printf("total %lld\n", tmp->total);
			print_list_l(tmp);
		}
		else if ((*opt)->one == 1)
			print_one(tmp);
		else if ((*opt)->m == 1)
			print_m(tmp);
		else
			print_list(tmp);
		if (tmp->mult != NULL)
			ft_putchar('\n');
		tmp = tmp->mult;
	}
}

void	read_mult_dirs(char **dirname, int i, int argc, t_opt **opt)
{
	t_dir	*direct;
	DIR		*dir;
	int		j;

	j = i;
	direct = NULL;
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
	printing_mult_dir(direct, i, argc, opt);
}

/*
** Добавить в конце
** int t = 0;
** while (1)
** t++;
*/

int		main(int argc, char **argv)
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
			break ;
		i++;
	}
	if (i == argc)
		read_dir(dirname, &opt, NULL);
	else
		read_mult_dirs(argv, i, argc, &opt);
	free(opt);
	free(dirname);
	return (0);
}
