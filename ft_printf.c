/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohy <hohy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:11:24 by hohypark          #+#    #+#             */
/*   Updated: 2021/07/09 19:27:36 by hohy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int         print(va_list ap, t_info *info)
{
    int     ret; 

    ret = 0;
    if(info->type == '%')
        ret = print_char('%', info);
    else if (info->type == 'c')
        ret = print_char(va_arg(ap, int), info);
    else if (info->type == 's')
        ret = print_string(va_arg(ap, char *), info);
    else if (info->type == 'd' || info->type == 'i')
        ret = print_nbr(va_arg(ap, int), info);
    else if (info->type == 'x' || info->type == 'X' || info->type == 'u')
        ret = print_nbr(va_arg(ap, unsigned int), info);
    else if (info->type == 'p')
        ret = print_nbr(va_arg(ap, unsigned long long), info);
    return (ret);
}

void        check_width(va_list ap, char *str, t_info *info, int idx)
{
    if (ft_isdigit(str[idx]))
    {
        if (info->prec == -1)
            info->width = info->width * 10 + str[idx] - 48;
        else
            info->prec = info->prec * 10 + str[idx] - 48;
    }
    else if (str[idx] == '*')
    {
        if (info->prec == -1)
        {
            info->width = va_arg(ap, int);
            if (info->width < 0)
            {
                info->left = 1;
                info->width *= -1;
            }
        }
    }
    else
        info->prec = va_arg(ap, int);
}

void    check_width(va_list ap, char *str, t_info *info, int idx)
{
    if (ft_isdigit(str[idx]))
    {
        while (ft_isdigit(str[idx]))
        {
            info->width = info->width * 10 + str[idx++] - 48;
        }
    }
    else if (str[idx] == '*')
    {
        info->width = va_arg(ap, int);
        if (info->width < 0){
            info->width *= -1;
            info->left = 1;
        }

    }
    else
        info->width = 0;

}

void    check_prec(va_list ap, char *str, t_info *info, int idx)
{
    if (str[idx] == '.')
    {
        info->prec = 0;
        if (ft_isdigit(str[++idx]))
        {
            info->prec = info->prec * 10 + str[idx] - 48;
        }
        else if(str[++idx] == '*')
        {
            info->prec = va_arg(ap, int);
        }
    }
    else
    {

    }
}

void        check_flag(va_list ap, char *str, t_info *info, int idx){
    if(str[idx] == '0' && info->width == 0 && info->prec == -1)
        info->zero = 1;
    else if (str[idx] == '-')
        info-> left = 1;
    else if (str[idx] == '.')
        info->prec = 0;
    else if (ft_isdigit(str[idx]) || str[idx] == '*')
        check_width_and_prec(ap, str, info, idx);
}

void		init_info(t_info *info)
{
	info->left = 0;
	info->zero = 0;
	info->width = 0;
	info->prec = -1;
	info->type = 0;
	info->nbr_base = 10;
	info->nbr_sign = 1;
}

int     parse_str(va_list ap, char *str){
    int     idx;
    int     ret;
    t_info  *info;

    idx = 0;
    ret = 0;
    if (!(info = malloc(sizeof(t_info) * 1)))
		return (-1);
    while (str[idx] != 0)
    {
        while(str[idx] != '%' && str[idx] != 0)
            ret += write(1, str[idx++], 1);
        if (str[idx] == '%')
        {
            init_info(info);
            while (str[++idx] != 0 && !(ft_strchr("cdispuxX%", str[idx])))
                check_flag(ap, str, info, idx);
            info->type = str[idx++];
            if ((info->left == 1 || info->prec > -1) && info->type != '%')
                info->zero = 0;
            ret += print(ap, info); 
        }
    }
    free(info);
    return (ret);
}

int     ft_printf(const char *str, ...){
    va_list     ap;
    int         ret;

    va_start(ap, str);
    ret = parse_str(ap, (char *)str);
    va_end(ap);
    return (ret);
}