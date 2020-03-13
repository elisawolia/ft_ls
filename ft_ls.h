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
#include "libft/libft.h"

typedef	struct	s_opt
{
	uint16_t	l;
	uint16_t	a;
	uint16_t	R;
	uint16_t	t;
	uint16_t	r;
}				t_opt;

#endif
