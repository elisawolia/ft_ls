/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(char *name)
{
	t_dir	*dir;
	
	dir = NULL;
	if (!(dir = ft_memalloc(sizeof(t_dir))))
	{	
		perror("malloc");
		exit(1);
	}
	if (!(dir->name = ft_strdup(name)))
	{
		perror("malloc");
		exit(1);
	}
	dir->max_uid = 0;
	dir->max_gid = 0;
	dir->max_size = 0;
	dir->max_name = 0;
	dir->total = 0;
	dir->files = NULL;
	dir->sub = NULL;
	dir->next = NULL;
	return (dir);
}

void	dir_sub(t_dir *dir, t_dir *new)
{
	t_dir	*tmp;

	tmp = dir;
	if (new == NULL)
		return ;
	if (!tmp->sub)
	{
		dir->sub = new;
	}
	else
	{
		tmp = tmp->sub;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	dir_next(t_dir **alst, t_dir *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

t_dir	*init_dir(DIR *dir, t_opt *opt, char *name, t_dir *di)
{
	struct	dirent *d;
	t_dir	*direct;

	d = NULL;
	if (di != NULL)
	{
		direct = di;
	}
	else if (!(direct = new_dir(name)))
		return (0);
	while ((d = readdir(dir)) != NULL)
	{
		if ((d->d_name[0] != '.' && !opt->a) || opt->a)
			file_add(&(direct->files), new_file(d, direct));
	}
	mergeSort(&(direct->files), &defSort);
	if (opt->t)
		mergeSort(&(direct->files), &timeSort);
	if (opt->r)
		reverse(&(direct->files));
//	print_list(file);
//	dir_prt(direct);
	return (direct);
}