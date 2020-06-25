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
#include "../libft/libft/includes/libft.h"
#include "../libft/ft_printf/includes/ft_printf.h"

/*
 * t_opt is a structure, that holds given flags
 * a - include directory entries whose names begin with a dot (.)
 * c - (-C) force multi-column output
 * d - directories are listed as plain files (not searched recursively)
 * l - list in long format
 * m - list files across the page, separated by commas
 * one - (-1) force output to be one entry per line
 * r - reverse the order of the sort
 * rec - (-R) recursively list subdirectories encountered
 * s - (-S) sort files by size
 * t - sort by time modified (most recently modified first)
 *     before sorting the operands by lexicographical order
*/

typedef	struct		s_opt
{
	uint16_t		a;
	uint16_t		c;
	uint16_t		d;
	uint16_t		l;
	uint16_t		m;
	uint16_t		one;
	uint16_t		r;
	uint16_t		rec;
	uint16_t		s;
	uint16_t		t;
}					t_opt;

/*
 * t_file is a list, that holds information about the files
 * file_name - name of the file
 * mode - type of the file (file/dit/soft link/etc)
 * uid - user identifier
 * gid - group identifier
 * link - number of links
 * size - the size of the file
 * time - time of last modification
*/

typedef struct		s_file
{
	char			*file_name;
	char			*soft_link;
	unsigned long	mode;
	long			uid;
	long			gid;
	long			link;
	long long		size;
	time_t			time;
	long			sec;
	long			nsec;
	struct s_file	*next;
}					t_file;

/*
 * t_dir is a list, that holds information about the directory
 * name - name of the directory
 * all of the max_* are needed for -l output
 * max_uid - max number of letters in uid's of files
 * max_gid - max number of letters in gid's of files
 * max_link - max number of letters in link's of files
 * max_size - max number of letters in size's of files
 * max_name - max number of letters in name's of files
 * total - the total number of file system blocks
 * size - total size of the dir, needed to sort directories
 * time - time of last modification of the directory, needed for sorting
 * files - list of all tje files in the directory
 * sub - the directory inside of this directory
 * next - the sibling directory
 * mult - next directory, when directories are specified 
*/

typedef	struct		s_dir
{
	char			*name;
	int				max_uid;
	int				max_gid;
	int				max_link;
	int				max_size;
	int				max_name;
	long long		total;
	long long		size;
	time_t 			time;
	struct s_file	*files;
	struct s_dir	*sub;
	struct s_dir	*next;
	struct s_dir	*mult;	
}					t_dir;

/*
*
*	Delete later
*
*/

void				print_opt(t_opt *opt);
void				dir_prt(t_dir *dir);

/*
*
*	Sorting functions
*
*/

void				merge_sort(t_file **h, double (*f)(t_file *a, t_file *b));
t_file				*sorted_merge(t_file *a, t_file *b, double (*f)(t_file *a, t_file *b));
void				front_back_split(t_file *src, t_file **front, t_file **back);
double				def_sort(t_file *a, t_file *b);
double				time_sort(t_file *a, t_file *b);
double				time_sort_sec(t_file *a, t_file *b);
double				time_sort_nsec(t_file *a, t_file *b);
double				size_sort(t_file *a, t_file *b);
void				reverse(t_file **lst);

double				def_sort_dir(t_dir *a, t_dir *b);
double				time_sort_dir(t_dir *a, t_dir *b);
double				size_sort_dir(t_dir *a, t_dir *b);
void				merge_sort_dir(t_dir **h, double (*f)(t_dir *a, t_dir *b), int flag);
t_dir				*sorted_merge_dir(t_dir *a, t_dir *b, double (*f)(t_dir *a, t_dir *b), int flag);
void				front_back_split_dir(t_dir *src, t_dir **front, t_dir **back, int flag);
void				reverse_dir_next(t_dir **lst);
void				reverse_dir_sub(t_dir **lst);
void				reverse_dir_mult(t_dir **lst);

void				read_dir(char *dirname, t_opt **opt, t_dir *d);

int					count_max(long long n);
int					ft_findedot(char *name);
int					count_files(t_file *file);
void				ft_putspace(ssize_t n);
ssize_t 			max(ssize_t a, ssize_t b);

t_file				*new_file(struct dirent *d, t_dir *dir, char *name);
void				file_add(t_file **alst, t_file *new);
t_dir				*init_dir(DIR *dir, t_opt *opt, char *name, t_dir *di);
void				dir_sub(t_dir *dir, t_dir *new);
void				dir_next(t_dir **alst, t_dir *new);
t_dir				*new_dir(char *name, time_t time, long long size);

void				print_list(t_dir *dir);
void				print_list_l(t_dir *dir);
void				print_one(t_dir *dir);
void				print_m(t_dir *dir);
void				print_d(t_opt *opt, t_dir *dir);
int 				rows_print(t_dir *dir);

void				free_files(t_file **list);
void				free_dir(t_dir **dir);
void				malloc_err(void);
void				lstat_error(void);

#endif
