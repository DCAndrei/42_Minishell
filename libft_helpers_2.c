/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:45:59 by acretu            #+#    #+#             */
/*   Updated: 2022/03/12 22:54:49 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_ch(char const *s1, char c)
{
	char		*ret;
	size_t		len_s1;
	size_t		i;

	if (s1 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len_s1 + 1 + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		ret[i] = s1[i];
		i += 1;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}

static	size_t	ft_s_size(char const *s, char c);

char	**ft_split_f(char const *s, char c)
{
	char		**array;
	const char	*s_init;
	size_t		size;
	size_t		i;

	if (s == NULL)
		return (NULL);
	s_init = s;
	array = NULL;
	size = ft_s_size(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s == c && *s != '\0')
			s++;
		s_init = ft_strchr(s, c);
		*(array + i) = ft_substr_f(s, 0, (s_init - s) + 1);
		s = s_init + 1;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

static	size_t	ft_s_size(char const *s, char c)
{
	size_t		size;
	char const	*t;

	size = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		t = s;
		while (*t != '\0' && *t == c)
			t++;
		if (*t != '\0')
		{
			size++;
			t++;
		}
		while (*t != '\0' && *t != c)
			t++;
		s = t;
	}
	return (size);
}
