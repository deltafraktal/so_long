/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:16:11 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/09 22:33:20 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int send_error(char *msg)
{
    ft_printf(BOLD PURPLE "Error\n"END YELLOW "%s\n" END, msg);
    return (1);
}