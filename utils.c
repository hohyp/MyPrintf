/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohy <hohy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:15:31 by hohy              #+#    #+#             */
/*   Updated: 2021/07/09 02:48:21 by hohy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     get_nbrlen(unsigned long long nbr, t_info *info)
{
    int     len;
    
    if(nbr == 0 && info->prec != 0)
        return (1);
    len = 0;
    while(nbr)
    {
        nbr /= info->nbr_base;
        len++;
    }
    return (len);
}

char    *base_converter(char type)
{
    if (type == 'd' || type == 'u' || type == 'i')
        return ("0123456789");
    else if (type == 'x' || type == 'p')
        return ("0123456789abcdef");
    else if (type == 'X')
        return ("0123456789ABCDEF");
    return (0);
}