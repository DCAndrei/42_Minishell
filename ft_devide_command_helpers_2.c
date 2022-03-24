/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devide_command_helpers_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:58:45 by acretu            #+#    #+#             */
/*   Updated: 2022/03/19 19:03:07 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_com_size(char *str)
{
	int		i;
	int		size;
	int		q[2];

	i = 0;
	size = 0;
	q[0] = 0;
	q[1] = 0;
	while (str[i] != '\0')
	{
		while (ft_is_whitespace(str[i]) == 1 && str[i] != '\0')
			i += 1;
		while (ft_is_whitespace(str[i]) == 0 && str[i] != '\0')
		{
			if (str[i] == '\'' && q[1] % 2 == 0)
				q[0] += 1;
			else if (str[i] == '"' && q[0] % 2 == 0)
				q[1] += 1;
			i += 1;
		}
		if (q[0] % 2 == 0 && q[1] % 2 == 0)
			size += 1;
	}
	return (size);
}

void	ft_cut_string(char **str, int start, int end)
{
	char	*first;
	char	*second;
	char	*ret;
	char	*tmp;

	first = ft_substr_f((*str), 0, start + 1);
	second = ft_substr_f((*str) + end, 0, ft_strlen(*str) - end + 1);
	tmp = ft_strjoin_ch(first, ' ');
	ret = ft_strjoin(tmp, second);
	free (first);
	free (tmp);
	free (second);
	free (*str);
	*str = ret;
}

int	ft_len(char *str)
{
	int		i;

	i = 0;
	while (ft_is_whitespace(str[i]) == 1 && str[i] != '\0')
		i += 1;
	while (ft_is_whitespace(str[i]) == 0 && str[i] != '\0')
		i += 1;
	return (i);
}

char	*ft_return_position(char *str, char c)
{
	int		i;
	int		q[2];

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			q[0] += 1;
		else if (str[i] == 34)
			q[0] += 1;
		if (str[i] == c && q[0] % 2 == 0 && q[0] % 2 == 0)
			return (&str[i]);
		i += 1;
	}
	return (NULL);
}
