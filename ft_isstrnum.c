/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 08:34:29 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/14 09:04:48 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isstrnum(char *str)
{
	if (!str)
		return (-1);
	if (!(ft_isdigit(*str) || *str == '+' || *str == '-'))
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("NULL %i\n", ft_isstrnum(NULL));
	printf("-1123 %i\n", ft_isstrnum("-1123"));
	printf("+1123 %i\n", ft_isstrnum("+1123"));
	printf("-112+3 %i\n", ft_isstrnum("-112+3"));
	printf("empty %i\n", ft_isstrnum(""));
	printf("11a1 %i\n", ft_isstrnum("11a1"));
	printf("aaa %i\n", ft_isstrnum("aaa"));
	printf("123 %i\n", ft_isstrnum("123"));
	return (0);
}
*/