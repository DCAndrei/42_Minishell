/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:32:38 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 21:49:58 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_whitespace(char c)
{
	if ((c >= 9 && c < 14) || c == 32)
		return (1);
	return (0);
}

void	ft_remove_ws(char **str)
{
	int		pos;
	int		start;
	char	*tmp;

	if (*str == NULL || (*str)[0] == '\0')
		return ;
	start = 0;
	while (ft_is_whitespace((*str)[start]) == 1 && **str != '\0')
		start += 1;
	pos = ft_strlen(*str) - 1;
	while (ft_is_whitespace((*str)[pos]) == 1 && pos > 0)
		pos -= 1;
	tmp = ft_substr_f(*str, start, pos - start + 2);
	free (*str);
	*str = tmp;
}

void	ft_free(char **str)
{
	int		i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
		i++;
	while (i >= 0)
	{
		free (str[i]);
		i--;
	}
	free (str);
}
