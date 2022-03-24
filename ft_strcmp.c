/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:50:29 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/03 09:16:22 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l1 > l2)
		return (ft_memcmp(s1, s2, l2 + 1));
	return (ft_memcmp(s1, s2, l1 + 1));
}

/*
#include <stdio.h>

int main()
{
	printf("%d\n", ft_strcmp("abc", "abcd"));
	printf("%d\n", ft_strcmp("abcd", "abc"));
	printf("%d\n", ft_strcmp("abc", "abc"));
}*/