/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_commands_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:11 by acretu            #+#    #+#             */
/*   Updated: 2022/03/06 20:46:02 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char(char *str, char c)
{
	int		i;
	int		q[2];
	int		ret;

	q[0] = 0;
	q[1] = 0;
	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			q[0] += 1;
		else if (str[i] == 39)
			q[1] += 1;
		if (q[0] % 2 == 0 && q[1] % 2 == 0 && str[i] == c)
			ret += 1;
		i += 1;
	}
	if (ret == 0)
		ret = -1;
	return (ret);
}

int	ft_extract_options(char *str)
{
	int		i;

	i = 0;
	while (ft_is_whitespace(str[i]) == 1 && str[i] != '\0')
		i += 1;
	while (ft_is_whitespace(str[i]) == 0 && str[i] != '\0')
		i += 1;
	while (ft_is_whitespace(str[i]) == 1 && str[i] != '\0')
		i += 1;
	return (i);
}
