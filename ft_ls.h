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
	char			*time;
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
*	Sorting functions
*
*/

void	mergeSort(t_file **h, int (*f)(t_file *a, t_file *b));
t_file	*sortedMerge(t_file *a, t_file *b, int (*f)(t_file *a, t_file *b));
void	frontBackSplit(t_file *src, t_file **front, t_file **back);
int		defSort(t_file *a, t_file *b);
void	reverse(t_file **lst);

#endif
