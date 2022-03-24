/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:48:56 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/14 10:49:02 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lst2arr(t_list *lst)
{
	int		num_vars;
	char	**res;
	int		i;

	num_vars = ft_lstsize(lst);
	if (!lst || num_vars == 0)
		return ((char **) NULL);
	res = (char **) malloc(sizeof(char *) * (num_vars + 1));
	if (!res)
		return ((char **) NULL);
	i = 0;
	while (lst)
	{
		res[i] = ft_strdup((char *)(lst->content));
		i++;
		lst = lst->next;
	}
	res[i] = (char *) NULL;
	return (res);
}

/*
#include "minishell.h"
#include "env_init.c"

int	main(int argc, char *argv[], char *envp[])
{
	char **arr;
	char **curr;
	t_list *lst = env_init(envp);
	arr = ft_lst2arr(lst);
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	ft_lstclear(&lst, free);
	curr = arr;
	while(*curr)
	{
		free(*curr);
		curr++;
	}
	free(arr);
}
*/