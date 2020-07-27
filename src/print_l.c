/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/33 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/33 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_filename(uint16_t color, char *line, t_file *tmp)
{
	char		*color_name;
	char		*end_name;
	char		*pattern;

	color_name = NULL;
	end_name = NULL;
	pattern = NULL;
	if (color)
	{
		color_name = get_color(tmp->mode);
		end_name = ft_strjoin(line, "{EOC}");
		pattern = ft_strjoin(color_name, end_name);
		ft_printf(pattern, tmp->file_name);
	}
	else
		ft_printf(line, tmp->file_name);
	free(color_name);
	free(end_name);
	free(pattern);
}

static void	print_type(unsigned long mode)
{
	if (S_ISBLK(mode))
		ft_putchar('b');
	else if (S_ISCHR(mode))
		ft_putchar('c');
	else if (S_ISFIFO(mode))
		ft_putchar('f');
	else if (S_ISREG(mode))
		ft_putchar('-');
	else if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISLNK(mode))
		ft_putchar('l');
	else
		ft_putchar('s');
}

static void	print_rights(unsigned long mode)
{
	(S_IRUSR & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWUSR & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISUID & mode)
		(S_IXUSR & mode) ? ft_putchar('s') : ft_putchar('S');
	else
		(S_IXUSR & mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IRGRP & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWGRP & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISGID & mode)
		(S_IXUSR & mode) ? ft_putchar('s') : ft_putchar('S');
	else
		(S_IXGRP & mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IROTH & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWOTH & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISVTX & mode)
		(S_IXUSR & mode) ? ft_putchar('t') : ft_putchar('T');
	else
		(S_IXOTH & mode) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

static void	print_soft_link(t_file *file)
{
	if (S_ISLNK(file->mode))
		ft_printf(" -> %s", file->soft_link);
}

void	print_list_l(t_dir *dir, uint16_t color)
{
	t_file *tmp;

	tmp = dir->files;
	while (tmp != NULL)
	{
		print_type(tmp->mode);
		print_rights(tmp->mode);
		ft_putspace((dir->max_link + 1) -
			(long long int)(count_max(tmp->link)));
		ft_printf("%ld %s", tmp->link, getpwuid(tmp->uid)->pw_name);
		ft_putspace((dir->max_uid + 1) -
			(long int)ft_strlen(getpwuid(tmp->uid)->pw_name));
		ft_putspace((dir->max_gid + 1) -
			(long int)ft_strlen(getgrgid(tmp->gid)->gr_name));
		ft_printf("%s ", getgrgid(tmp->gid)->gr_name);
		ft_putspace((dir->max_size + 1) -
			(long long int)(count_max(tmp->size)));
		ft_printf("%d ", tmp->size);
		ft_printf("%.12s ", ctime(&tmp->time) + 4);
		print_filename(color, "%s", tmp);
		print_soft_link(tmp);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
