/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:15:05 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/13 07:47:51 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_init(char *envp[])
{
	size_t	i;
	t_list	*env_list;

	if (!envp)
		return (NULL);
	i = 0;
	env_list = ft_lstnew(ft_strdup(envp[i]));
	i++;
	while (envp[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (env_list);
}
