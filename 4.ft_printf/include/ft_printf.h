/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:06:43 by namkyu            #+#    #+#             */
/*   Updated: 2021/02/27 12:37:21 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define RIGHT_ALIGN 1
# define LEFT_ALIGN -1
# define TYPE_STRING 0

typedef	struct	s_format_list
{
	int		zero_len;
	char	zero_symbol;
	int		width;
	int		align;
	int		precision;
	int		strlen;
	char	*base;
	int		sign;
}				t_format_list;
/*
**		Parsing format part 1 (flag, width, precision)
*/
int				flag_parse(const char *format, t_format_list *f_list);
int				width_parse(const char *format,
							t_format_list *f_list, va_list *ap);
int				precision_parse(const char *format,
								t_format_list *f_list, va_list *ap);
int				ft_printf_parsing_1(const char *format,
									t_format_list *f_list,
									va_list *ap, int *ret);
int				ft_printf_parsing_2(const char *format,
									t_format_list *f_list, va_list *ap);
/*
** 		Parsing format part 2 (conversion)
*/
int				case_integer(t_format_list *f_list, va_list *ap);
int				case_undsigned_int(const char *format,
									t_format_list *f_list, va_list *ap);
int				case_character(const char *format,
								t_format_list *f_list, va_list *ap);
int				case_string(t_format_list *f_list, va_list *ap);
int				case_pointer(t_format_list *f_list, va_list *ap);
/*
**		display util
*/
void			print_str(t_format_list *f_list, const char *str);
int				print_width(t_format_list *f_list);
int				print_precision(t_format_list *f_list);
void			print_numbers(unsigned long long num, int base, char *base_str);
int				init_num_case(t_format_list *f_list, unsigned long long num);
/*
**		data utils
*/
void			num_data_input(unsigned long long num, t_format_list *f_list);
void			str_data_input(const char *str, t_format_list *f_list);
/*
**		main
*/
void			reset_flist(t_format_list *f_list);
int				ft_printf(const char *format, ...);

#endif
