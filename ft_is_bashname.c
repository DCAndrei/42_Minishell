/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_bashname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:19:04 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/14 07:08:07 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Checks if variable name is complying to the name definition of bash.
**	@param		name the string to check
**	@return		1 if true, 2 if false, -1 if no string
*/

#include "minishell.h"

int	ft_is_bashname(char *name)
{
	if (!name)
		return (-1);
	if (!(ft_isalpha(*name) || *name == '_'))
		return (0);
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (0);
		name++;
	}
	return (1);
}

/*
#include <stdio.h>
int main()
{
	printf("_12321Aa => %i\n", ft_is_bashname("_12321Aa"));
	printf("12321Aa  => %i\n", ft_is_bashname("12321Aa"));
	printf("aaA121Aa => %i\n", ft_is_bashname("aaA12321Aa"));
	printf(" a       => %i\n", ft_is_bashname(" a"));
	printf("empty    => %i\n", ft_is_bashname(""));
	return (0);
}
*/