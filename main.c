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

void print_list_l(t_file *file)
{
	t_file *tmp;

	tmp = file;
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
		printf("%-*s", 20, getpwuid(tmp->uid)->pw_name);
		printf("%s ", getgrgid(tmp->gid)->gr_name);
		printf("%*lld ", 7, tmp->size);
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

void	file_add(t_file **alst, t_file *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

t_file	*new_file(struct dirent *d, long long *total)
{
	t_file	*file;
	struct stat sb;

	if (lstat(d->d_name, &sb) == -1)
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
	*total += (long long)sb.st_blocks;
	file->mode = (unsigned long)sb.st_mode;
	file->uid = (long)sb.st_uid;
	file->gid = (long)sb.st_gid;
	file->link = (long)sb.st_nlink;
	file->size = (long long)sb.st_size;
	file->time = ft_strdup(ctime(&sb.st_mtime) + 4);
	file->next = NULL;
	return (file);
}

t_file	*init_dir(DIR *dir, t_opt *opt, long long *total)
{
	t_file	*file;
	struct	dirent *d;

	d = NULL;
	file = NULL;
	while ((d = readdir(dir)) != NULL)
	{
		if ((d->d_name[0] != '.' && !opt->a) || opt->a)
			file_add(&file, new_file(d, total));
	}
//	print_list(file);
	return (file);
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

void	read_files(char *dirname, t_opt **opt, long long *total)
{
	t_file	*file;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		free(*opt);
		exit(1);
	};
	print_opt(*opt);
	file = init_dir(dir, *opt, total);
	printf("total %lld\n", *total);
	if ((*opt)->l == 1)
		print_list_l(file);
}

int	main(int argc, char **argv)
{
//	DIR		*dir;
	long long	total;
	t_opt	*opt;
	char	*dirname;
	int		i;

	i = 1;
	total = 0;
	opt = malloc_opt();
//	dir = NULL;
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
		read_files(dirname, &opt, &total);
	/*	dir = opendir(dirname);
		if (!dir)
		{
			perror("diropen");
			free(opt);
			exit(1);
		};
		print_opt(opt);
		t_file *file = init_dir(dir);*/
	}
	else 
	{
		while (i < argc)
		{
			total = 0;
			printf("%s:\n", argv[i]);
			dirname = argv[i];
		/*	dir = opendir(dirname);
			if (!dir)
			{
				perror("diropen");
				free(opt);
				exit(1);
			};
			print_opt(opt);*/
		/*	while((direct = readdir(dir)) != NULL)
			{
				printf("%llu - %s [%d] %d\n", direct->d_ino, direct->d_name,
						direct->d_type, direct->d_reclen);
			}*/
			read_files(dirname, &opt, &total);
			i++;
			if (i < argc)
				printf("\n");
		}
	}
	free(opt);
//	free(direct);
	return (0);
}
