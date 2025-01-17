/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/11 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function allocate memory for main structure of project
*/

t_opt		*malloc_opt(void)
{
	t_opt *opt;

	if (!(opt = ft_memalloc(sizeof(t_opt))))
		malloc_err();
	opt->l = 0;
	opt->a = 0;
	opt->m = 0;
	opt->d = 0;
	opt->r = 0;
	opt->rec = 0;
	opt->t = 0;
	opt->one = 0;
	opt->c = 0;
	opt->s = 0;
	opt->g = 0;
	opt->r_output = 0;
	opt->err = 0;
	return (opt);
}

/*
** processing of entered options 3 of 3
*/

static void	opt_check_continue_next(char str, t_opt *opt)
{
	if (str == 'd')
	{
		opt->d = 1;
		opt->rec = 0;
	}
	if (str == 'G')
		opt->g = 1;
}

/*
** processing of entered options 2 of 3
*/

static void	opt_check_continue(char str, t_opt *opt)
{
	if (str == '1')
	{
		opt->one = 1;
		opt->l = 0;
		opt->c = 0;
		opt->m = 0;
	}
	if (str == 'm')
	{
		opt->m = 1;
		opt->l = 0;
		opt->one = 0;
		opt->c = 0;
	}
	if (str == 'C' && opt->m != 1)
	{
		opt->c = 1;
		opt->l = 0;
		opt->one = 0;
	}
	opt_check_continue_next(str, opt);
}

/*
** processing of entered options 1 of 3
*/

static void	opt_check(char str, t_opt *opt)
{
	if (str == 'd')
		opt->d = 1;
	if (str == 'l')
	{
		opt->l = 1;
		opt->one = 0;
		opt->c = 0;
		opt->m = 0;
	}
	if (str == 'a')
		opt->a = 1;
	if (str == 't')
		opt->t = 1;
	if (str == 'R')
		opt->rec = 1;
	if (str == 'r')
		opt->r = 1;
	if (str == 'S')
	{
		opt->s = 1;
		opt->t = 0;
	}
	opt_check_continue(str, opt);
}

/*
** read options that are passed to the program
*/

void		read_opt(char *str, t_opt **opt)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		opt_check(str[i], *opt);
		if (str[i] != 'd' && str[i] != 'S' && str[i] != 'C'
			&& str[i] != '1' && str[i] != 'l' && str[i] != 'a' && str[i] != 'G'
			&& str[i] != 't' && str[i] != 'R' && str[i] != 'r' && str[i] != 'm')
		{
			ft_printf_fd(2, "usage: ./ft_ls [-GRSC1alrtm] [file ...]\n");
			exit(1);
		}
		i++;
	}
}
