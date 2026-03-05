/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:01:45 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/05 04:14:10 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int parse()
{
    /* verif_map_extension */
    /* verif */

    /* floadfill from start */
}

int verif_map_extension(char *s)
(
    int len;
    
    len = ft_strlen(s);
    if(s[len - 4] != '.' || s[len - 3] != 'b' || s[len - 2] != 'e' || s[len - 3] != 'b')
        return (1);
    return (0);
)