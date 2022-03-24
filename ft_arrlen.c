/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:12:31 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/02 10:23:06 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Returns the number of elements in an NULL-terminated pointer array.
**	@param	NULL-terminated array of pointers
**	@return	number of elements
*/

int	ft_arrlen(char **arr)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!arr)
		return (-1);
	while (arr[i++])
		count++;
	return (count);
}

/*
#include <stdio.h>
int main() {
	char *a = "abc";
	char *b = "abc";
	char *c = "abc";

	char *arr[5];
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = NULL;
	printf("#Elems: %i\n", ft_arrlen(arr));

}
*/