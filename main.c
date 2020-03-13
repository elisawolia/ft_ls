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

void	print_n(DIR *dir)
{
	struct dirent *d;

	d = NULL;
	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] != '.')
			printf("%s\n", d->d_name);
	}
}

void	print(t_opt *opt, DIR *dir)
{
	if (opt->l == 0)
		print_n(dir);
}

int	main(int argc, char **argv)
{
	DIR		*dir;
	struct	dirent *direct;
	t_opt	*opt;
	char	*dirname;
	int		i;

	i = 1;
	direct = NULL;
	opt = malloc_opt();
	dir = NULL;
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
		dir = opendir(dirname);
		if (!dir)
		{
			perror("diropen");
			free(opt);
			exit(1);
		};
		print_opt(opt);
	/*	while((direct = readdir(dir)) != NULL)
		{
			printf("%llu - %s [%d] %d\n", direct->d_ino, direct->d_name,
					direct->d_type, direct->d_reclen);
		}*/
		print(opt, dir);
	}
	else 
	{
		while (i < argc)
		{
			printf("%s:\n", argv[i]);
			dirname = argv[i];
			dir = opendir(dirname);
			if (!dir)
			{
				perror("diropen");
				free(opt);
				exit(1);
			};
			print_opt(opt);
		/*	while((direct = readdir(dir)) != NULL)
			{
				printf("%llu - %s [%d] %d\n", direct->d_ino, direct->d_name,
						direct->d_type, direct->d_reclen);
			}*/
			print(opt, dir);
			i++;
			if (i < argc)
				printf("\n");
		}
	}
	free(opt);
	free(dir);
	free(direct);
	return (0);
}
