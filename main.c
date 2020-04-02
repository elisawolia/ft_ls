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
#include <stdio.h>

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

void	read_opt(char *str, t_opt *opt)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			opt->l = 1;
		if (str[i] == 'a')
			opt->a = 1;
		if (str[i] == 't')
			opt->t = 1;
		if (str[i] == 'R')
			opt->R = 1;
		if (str[i] == 'r')
			opt->r = 1;
		if (str[i] != 'l' && str[i] != 'a' && str[i] != 't' && str[i] != 'R' && str[i] != 'r')
		{
			perror("ft_ls");
			// printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			free(opt);
			exit(1);
		}
		i++;
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
		printf("%.12s ", tmp->time);
		printf("%s\n", tmp->file_name);
	/*	printf("name: %s\n", tmp->file_name);
		printf("mode: %lo\n", tmp->mode);
		printf("links: %ld\n", tmp->link);
		printf("uid: %ld\n", tmp->uid);
		printf("gid: %ld\n", tmp->gid);
		printf("size: %lld\n", tmp->size);
		printf("time: %s\n", (tmp->time));*/
		tmp = tmp->next;
	}
}

void print_list(t_dir *dir)
{
	t_file *tmp;

	tmp = dir->files;
	while(tmp != NULL)
	{
		printf("%-*s",dir->max_name + 1, tmp->file_name);
		tmp = tmp->next;
	}
	printf("\n");
}

int		count_max(long long n)
{
	int i;

	i = 1;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	file_add(t_file **alst, t_file *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

void	dir_prt(t_dir *dir)
{
	t_dir	*tmp;

	tmp = dir;
	if (!tmp->sub)
	{
		printf("there is no sub!\n");
	}
	else
	{
		tmp = tmp->sub;
		while (tmp->next)
		{
			printf("%s ", tmp->name);
			tmp = tmp->next;
		}
		printf("\n");
	}
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

t_dir	*new_dir(char *name)
{
	t_dir	*dir;
	
	dir = NULL;
	if (!(dir = ft_memalloc(sizeof(t_dir))))
	{	
		perror("malloc");
		exit(1);
	}
	if (!(dir->name = ft_strjoin(name, "/")))
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

t_file	*new_file(struct dirent *d, t_dir *dir)
{
	t_file	*file;
	char	*f_name;
	struct stat sb;

	if (!(f_name = ft_strjoin(dir->name, d->d_name)))
	{
		perror("malloc");
		exit(1);
	}
	if (lstat(f_name, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
    }
	if (!(file = ft_memalloc(sizeof(t_file))))
	{	
		perror("malloc");
		exit(1);
	}
	if (!(file->file_name = ft_strdup(d->d_name)))
	{	
		perror("malloc");
		exit(1);
	}
	dir->total += (long long)sb.st_blocks;
	file->mode = (unsigned long)sb.st_mode;
	if (S_ISDIR(file->mode))
		dir_sub(dir, new_dir(file->file_name));
	file->uid = (long)sb.st_uid;
	file->gid = (long)sb.st_gid;
	file->link = (long)sb.st_nlink;
	file->size = (long long)sb.st_size;
	file->time = ft_strdup(ctime(&sb.st_mtime) + 4);
	file->next = NULL;
	dir->max_uid = MAX(dir->max_uid, ft_strlen(getpwuid(file->uid)->pw_name));
	dir->max_gid = MAX(dir->max_gid, ft_strlen(getgrgid(file->gid)->gr_name));
	dir->max_name = MAX(dir->max_name, ft_strlen(d->d_name));
	dir->max_size = MAX(dir->max_size, count_max(file->size));
	free(f_name);
	return (file);
}

t_dir	*init_dir(DIR *dir, t_opt *opt, char *name)
{
	struct	dirent *d;
	t_dir	*direct;

	d = NULL;
	if (!(direct = new_dir(name)))
		return (0);
	while ((d = readdir(dir)) != NULL)
	{
		if ((d->d_name[0] != '.' && !opt->a) || opt->a)
			file_add(&(direct->files), new_file(d, direct));
	}
	mergeSort(&(direct->files), &defSort);
	if (opt->r)
		reverse(&(direct->files));
//	print_list(file);
//	dir_prt(direct);
	return (direct);
}

void	print_opt(t_opt *opt)
{
	printf("-------OPTIONS--------\n");
	printf("l is %u\n", opt->l);
	printf("a is %u\n", opt->a);
	printf("t is %u\n", opt->t);
	printf("r is %u\n", opt->r);
	printf("R is %u\n", opt->R);
	printf("\n");
}

void	read_dir(char *dirname, t_opt **opt)
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
//	print_opt(*opt);
	direct = init_dir(dir, *opt, dirname);
	if ((*opt)->l == 1)
	{
		printf("total %lld\n", direct->total);
		print_list_l(direct);
	}
	else
	{
		print_list(direct);
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
			read_opt(argv[i], opt);
		else
			break;		
		i++;
	}
	if (i == argc)
	{
		read_dir(dirname, &opt);
	}
	else 
	{
		while (i < argc)
		{
			if (argc - i > 1)
				printf("%s:\n", argv[i]);
			dirname = argv[i];
			read_dir(dirname, &opt);
			i++;
			if (i < argc)
				printf("\n");
		}
	}
	free(opt);
	return (0);
}
