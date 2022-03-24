/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 06:54:58 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/13 06:58:05 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key(char *str, char separator)
{
	char	*res;
	char	*eq_pos;

	if (!str)
		return (NULL);
	eq_pos = ft_strchr(str, separator);
	if (!eq_pos)
		return (NULL);
	res = ft_strdup(str);
	res[eq_pos - str] = '\0';
	return (res);
}
