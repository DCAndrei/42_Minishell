/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:37:41 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/15 18:34:23 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_entry(t_list *start, t_list **lprtd);

void	env_print(t_list *sh_env, int fd)
{
	int		size;
	t_list	*lprtd;

	size = ft_lstsize(sh_env);
	if (!size)
		return ;
	lprtd = NULL;
	while (size)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(get_next_entry(sh_env, &lprtd), fd);
		size--;
	}
}

static char	*get_next_entry(t_list *sh_env, t_list **lprtd)
{
	t_list	*curr;
	t_list	*last;

	curr = sh_env;
	last = NULL;
	while (curr)
	{
		if (!*lprtd)
		{
			if (!last)
				last = sh_env;
			if (ft_strcmp((char *)curr->content, (char *) last->content) < 0)
				last = curr;
		}
		else if (!last && (ft_strcmp((char *)curr->content, \
			(char *)(*lprtd)->content) > 0))
			last = curr;
		else if (last && (ft_strcmp((char *)curr->content, \
			(char *)last->content) < 0) && (ft_strcmp((char *)curr->content, \
			(char *)(*lprtd)->content) > 0))
			last = curr;
		curr = curr->next;
	}
	*lprtd = last;
	return ((char *)last->content);
}
