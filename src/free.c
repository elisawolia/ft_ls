/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/11 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** free clearing the directory structure
*/

void	free_dir(t_dir **dir)
{
	free((*dir)->name);
	(*dir)->name = NULL;
	if ((*dir)->files)
		free_files(&((*dir)->files));
	if ((*dir)->sub)
		free_dir(&((*dir)->sub));
	if ((*dir)->next)
		free_dir(&((*dir)->next));
	if ((*dir)->mult)
		free_dir(&((*dir)->mult));
	free(*dir);
	*dir = NULL;
}

/*
** free clearing the file structure
*/

void	free_files(t_file **list)
{
	if ((*list)->file_name)
	{
		free((*list)->file_name);
		(*list)->file_name = NULL;
		if ((*list)->soft_link != NULL)
			free((*list)->soft_link);
	}
	if ((*list)->next)
		free_files(&((*list)->next));
	free(*list);
	*list = NULL;
}

/*
** free temp variable names for new files
*/

void	free_new_file(char **f_name, char **dir_name, char **new_dir_name)
{
	free(*f_name);
	free(*dir_name);
	free(*new_dir_name);
}
