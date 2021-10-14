/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohy <hohy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:10:06 by hohy              #+#    #+#             */
/*   Updated: 2021/07/09 02:49:27 by hohy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     print_char(int c, t_info *info)
{
    int     ret;

    ret = 0;
    if (info->type == '%' && info->left == 1)
        info->zero = 0;
    if (info->left == 1)
        ret += ft_putchar(c);
    ret += put_width(info->width, 1, info->zero);
    if (info->left == 0)
        ret += ft_putchar(c);
    return (ret);
}

int     put_width(int width, int len, int zero)
{
    int     ret;

    ret = 0;
    while (len < width)
    {
        if (zero == 1)
            ft_putchar('0');
        else
            ft_putchar(' ');
        len++;
        ret++;
    }
    return (ret);
}