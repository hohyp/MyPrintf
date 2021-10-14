/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohy <hohy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:21:45 by hohy              #+#    #+#             */
/*   Updated: 2021/07/09 19:01:48 by hohy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include "./libft/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_info
{
	int			left;
	int			zero;
	int			width;
	int			prec;
	char		type;
	int			nbr_base;
	int			nbr_sign;
}				t_info;

int			ft_printf(const char*str, ...);
int     	parse_str(va_list ap, char *str);
void		init_info(t_info *info);
void        check_flag(va_list ap, char *str, t_info *info, int idx);
int         print(va_list ap, t_info *info);

char    	*base_converter(char type);
int     	get_nbrlen(unsigned long long nbr, t_info *info);


int     	print_char(int c, t_info *info);
int     	put_width(int width, int len, int zero);

int			put_pointer_prefix(char **buf);
int			put_minus(t_info *info, char **buf);
int			put_minus2(int buf_len, t_info *info, char **buf);
int			put_prec_str(unsigned long long nbr, t_info *info, char **buf);
int			print_nbr(unsigned long long nbr, t_info *info);

char		*parse_buf(char *str, int end, int len);
int			put_width_str(char **buf, t_info *info);
int			print_string(char *str, t_info *info);

#endif
