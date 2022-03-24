/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 09:56:30 by acretu            #+#    #+#             */
/*   Updated: 2022/03/12 22:54:20 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_f(char const *s, unsigned int start, size_t len)
{
	size_t		len_s;
	size_t		len_ret;
	char		*ret;

	if (s == NULL)
		return (NULL);
	len_s = 0;
	while (s[len_s] != '\0')
		len_s++;
	if (start > len_s)
	{
		ret = (char *)malloc(sizeof(char));
		if (ret == NULL)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	len_ret = len_s - start + 1;
	if (len < len_ret)
		len_ret = len;
	ret = (char *)malloc(len_ret);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, (s + start), len_ret);
	return (ret);
}
