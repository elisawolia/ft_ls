/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:59:26 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:40 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "libft/libft.h"

#define MAX(a,b) (a > b) ? a : b

typedef	struct	s_opt
{
	uint16_t	l;
	uint16_t	a;
	uint16_t	R;
	uint16_t	t;
	uint16_t	r;
}				t_opt;

typedef struct s_file
{
	char			*file_name;
	unsigned long	mode;
	long			uid;
	long			gid;
	long			link;
	long long		size;
	time_t			time;
	struct s_file	*next;
}				t_file;

typedef	struct s_dir
{
	char			*name;
	int				max_uid;
	int				max_gid;
	int				max_size;
	int				max_name;
	long long		total;
	struct s_file			*files;
	struct s_dir			*sub;
	struct s_dir			*next;
}				t_dir;

/*
*
*	Delete later
*
*/

#include <stdio.h>
void	print_opt(t_opt *opt);
void	dir_prt(t_dir *dir);


/*
*
*	Sorting functions
*
*/

void	mergeSort(t_file **h, double (*f)(t_file *a, t_file *b));
t_file	*sortedMerge(t_file *a, t_file *b, double (*f)(t_file *a, t_file *b));
void	frontBackSplit(t_file *src, t_file **front, t_file **back);
double		defSort(t_file *a, t_file *b);
double		timeSort(t_file *a, t_file *b);
void	reverse(t_file **lst);

double		defSortDir(t_dir *a, t_dir *b);
void	mergeSortDir(t_dir **h, double (*f)(t_dir *a, t_dir *b));
t_dir	*sortedMergeDir(t_dir *a, t_dir *b, double (*f)(t_dir *a, t_dir *b));
void frontBackSplitDir(t_dir *src, t_dir **front, t_dir **back);



int		count_max(long long n);

t_file	*new_file(struct dirent *d, t_dir *dir);
void	file_add(t_file **alst, t_file *new);
t_dir	*init_dir(DIR *dir, t_opt *opt, char *name);
void	dir_sub(t_dir *dir, t_dir *new);
void	dir_next(t_dir **alst, t_dir *new);
t_dir	*new_dir(char *name);



#endif
