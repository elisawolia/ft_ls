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
		printf("%.12s ", ctime(&tmp->time) + 4);
		printf("%s\n", tmp->file_name);
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
