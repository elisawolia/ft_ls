/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:36:33 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 14:16:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** library to work with standatd printf
** library to work with indefinite number of arguments
** personal library
** library for using wchar_t type
*/

# include <stdio.h>
# include <stdarg.h>
# include <wchar.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>
# include "../../libft/includes/libft.h"

# define BUFF_SIZE 1024

/*
** main struct of printf:
** buf - buffer
** str - input line
** count - line coursor str
** count_buf - line coursor buf
** offset - number of offsets
** precision - number of precision
** if_precisison - if there is a precision
** dot - . after %
** grille - # after %
** plus - + after %
** space - ␣ after %
** zero - 0 after %
** is_unicode - check is char unicode
** first_char_pos - first char position from start/prev%
** percent_pos - position of %
** res - count of buf ???
** cont - container helps program to contain big numbers
** count_2 - backup count variable value
** fd - file descriptor
*/

typedef struct	s_env
{
	char		*buf;
	char		*str;
	int			count;
	int			count_buf;
	int			offset;
	int			precision;
	int			is_precision;
	int			dot;
	int			grille;
	int			plus;
	int			minus;
	int			space;
	int			zero;
	int			is_unicode;
	int			first_char_pos;
	int			percent_pos;
	int			res;
	uintmax_t	cont;
	int			count_2;
	int			fd;
	int			caps;
	int			base;
	int			nb_digit;
}				t_env;

/*
** help struct for flag %f:
** exp - exponent, unsigned, used to get the exponent number
** exp_res - result exponent number, signed, is a result of exp - exp_num
** bit - original bit size of array
** mant_num - bits for mantisse
** res_bit - resulting size of array (can be changed while calculating)
** exp_num - exp in max power minus 1, used to calculate res_exp
** sign - sign of number
** compos - comma position in result
** int *bits - array of sizes, used in calcualting
*/

typedef struct	s_fenv
{
	char				bit;
	char				sign;
	int					res_bit;
	int					compos;
	int					exp_num;
	int					mant_num;
	long unsigned int	exp;
	long long int		exp_res;
	int					*bits;
}				t_fenv;

/*
** ft_printf.c
*/

void			set_def(t_env *env);
t_env			*malloc_env(char *str);
int				ft_printf_fd(int fd, const char *line, ...);
int				ft_printf(const char *line, ...);

/*
** error.c
*/

void			malloc_error(void);
void			combi_error(void);

/*
** buffun.c
*/

void			to_buff_offset(t_env *env);
void			to_buff_str(char *str, t_env *env);
void			to_buff_char(char c, t_env *env);
void			to_buff_block(t_env *env);

/*
** flags.c
*/
void			set_nb_digit(t_env *env);
void			find_flag_continue(t_env *env, va_list args);
void			find_flag(t_env *env, va_list args);
int				check_flag(char c);
void			check_preflag(t_env *env);

/*
** flags_help.c
*/

void			set_base(t_env *env);
void			set_nb_digit(t_env *env);

/*
** offpre.c
*/

void			set_precision(int init_index, t_env *env);
void			set_offset(int init_index, t_env *env);

/*
** flag_size.c
*/

void			length_flags(t_env *env, va_list args);

/*
** util.c
*/

char			*space_offset(t_env *env, char *res, int minus, int flag_char);
char			*zero_offset(t_env *env, char *res, int minus);
char			*precision(t_env *env, char *res, int minus);
void			plus_minus(t_env *env, char **res, int minus, int num);
void			space(t_env *env, char **res, int zero);

/*
** flag_color.c
*/

int				paint(t_env *env, char *color, char *color_id);
void			flag_color(t_env *env);

/*
** num flagsi
*/

void			put_precision(t_env *env, int arg_size);
void			put_zero(t_env *env);
void			flag_di(t_env *env);
void			flag_di_util(t_env *env);
char			*flag_di_help(t_env *env);

void			flag_x(t_env *env);
void			flag_x_util(t_env *env);
char			*flag_x_help(t_env *env);

void			flag_o(t_env *env);
char			*flag_o_help(t_env *env);

/*
** num flags
*/

void			flag_s(t_env *env, va_list args);
void			flag_c(t_env *env);
void			flag_per(t_env *env);

/*
** calculator
*/

void			mult_by_column(int *num1, int *num2, int *rez, int *bit);
int				cut_num(int **num, int bit);

/*
** float_output.c
*/

void			float_zero(t_fenv **fenv, t_env *env);
void			float_output(t_env *env, t_fenv *fenv, int *res);
void			put_unval(t_fenv **fenv, t_env *env, int error);

/*
** float_calc.c
*/

int				*calc_res(unsigned long long int mant,
							t_fenv *fenv, int long_ch);
int				*prec(int *num, int prec, t_fenv *fenv);

/*
** float_util.c
*/

int				*new_arr(long long unsigned int num, int bit);
void			copy_int(int *num1, int *num2, int bit1, int bit2);
void			free_fenv(t_fenv *fenv);
int				num_size(t_env *env, t_fenv *fenv);
void			wider_arr(int **res, int **num1, int *bits);

/*
** flag_f.c
*/

void			flag_f(t_env *env, va_list args);
void			prec_def(t_env *env);

/*
** flag_lf.c
*/

void			flag_lf(t_env *env, va_list args);
void			float_flags(t_env *env, va_list args);
void			flag_valid(t_env *env);

#endif
