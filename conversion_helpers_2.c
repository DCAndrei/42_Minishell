/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_helpers_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:21:36 by acretu            #+#    #+#             */
/*   Updated: 2022/03/13 10:08:21 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_array(char **str)
{
	int		size;
	int		i;
	char	**ret;

	if (str == NULL)
		return (NULL);
	size = 0;
	while (str[size] != NULL)
		size += 1;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
		ft_pipe_fork_error('m');
	ret[size] = NULL;
	i = 0;
	while (i < size)
	{
		ret[i] = ft_strdup(str[i]);
		i += 1;
	}
	return (ret);
}
