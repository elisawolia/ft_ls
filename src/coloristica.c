/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloristica.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 10:30:41 by mnidoque          #+#    #+#             */
/*   Updated: 2020/07/19 10:30:41 by mnidoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** RED				executable
** BLUE				directory
** MAGENTA			symboliclink
** GREEN			socket
** YELLOW			pipe
** BLUE+BG_CYAN		block special
** BLUE+BG_YELLOW	character special
** BLACK+BG_RED		executable with setuid bit set
** BLACK+BG_CYAN	executable with setgid bit set
** BLACK+BG_YELLOW	directory writable to others, without sticky bit
** BLACK+BG_GREEN	directory writable to others, with sticky bit
*/

char	*get_color_type(unsigned long mode)
{
	char *color;

	if (S_ISCHR(mode))
		color = ft_strjoin("{BLUE}", "{BGYELLOW}");
	if (S_ISBLK(mode))
		color = ft_strjoin("{BLUE}", "{BGCYAN}");
	if (S_ISFIFO(mode))
		color = ft_strdup("{YELLOW}");
	if (S_ISSOCK(mode))
		color = ft_strdup("{GREEN}");
	if (S_ISLNK(mode))
		color = ft_strdup("{MAGENTA}");
	if (S_ISDIR(mode))
	{
		if ((mode & S_IWOTH) == S_IWOTH)
		{
			((mode & S_ISVTX) == S_ISVTX) ?
			color = ft_strjoin("{BLACK}", "{BGGREEN}") : 0;
			((mode & S_ISVTX) != S_ISVTX) ?
			color = ft_strjoin("{BLACK}", "{BGYELLOW}") : 0;
		}
		else
			color = ft_strdup("{BLUE}");
	}
	return (color);
}

char	*get_color(unsigned long mode)
{
	char *color;

	if (S_ISREG(mode) && (mode & S_ISUID) == S_ISUID)
		color = ft_strjoin("{BLACK}", "{BGRED}");
	else if (S_ISREG(mode) && (mode & S_ISGID) == S_ISGID)
		color = ft_strjoin("{BLACK}", "{BGCYAN}");
	else if (!(S_ISREG(mode)))
		color = get_color_type(mode);
	else if ((mode & S_IXUSR) == S_IXUSR || (mode & S_IXGRP) == S_IXGRP
		|| (mode & S_IXOTH) == S_IXOTH)
		color = ft_strdup("{RED}");
	else
		color = ft_strdup("{EOC}");
	return (color);
}
