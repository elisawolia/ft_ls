/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/08/27 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** maximum file information size
*/

void	dir_info(struct stat sb, t_file *file, t_dir *dir, struct dirent *d)
{
	dir->total += (long long)sb.st_blocks;
	dir->max_link = max(dir->max_link,
							count_max(file->link));
	dir->max_uid = max(dir->max_uid,
							(int)ft_strlen(getpwuid(file->uid)->pw_name));
	dir->max_gid = max(dir->max_gid,
							(int)ft_strlen(getgrgid(file->gid)->gr_name));
	dir->max_name = max(dir->max_name, (int)ft_strlen(d->d_name));
	dir->max_size = max(dir->max_size, count_max(file->size));
}
