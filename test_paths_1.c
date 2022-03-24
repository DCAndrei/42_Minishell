/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_paths_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:29:02 by acretu            #+#    #+#             */
/*   Updated: 2022/03/20 17:29:43 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_final_path(char *pathdir, char *cmd);

int	ft_check_path(char **cmmd, char *envp[])
{
	char	*path;

	path = ft_get_path(cmmd[0], envp);
	if (path == NULL)
		return (1);
	free (path);
	return (0);
}

char	*ft_get_path(char *cmd, char *envp[])
{
	int		i;
	char	**path;
	char	*final_path;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	path = ft_return_path(envp);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		final_path = get_final_path(path[i], cmd);
		if (access(final_path, F_OK) == 0)
		{
			ft_free(path);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free(path);
	return (NULL);
}

char	**ft_return_path(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
		return (NULL);
	return (path);
}

static char	*get_final_path(char *pathdir, char *cmd)
{
	char	*final_path;
	char	*tmp;

	tmp = ft_strjoin_ch(pathdir, '/');
	final_path = ft_strjoin(tmp, cmd);
	free (tmp);
	return (final_path);
}
