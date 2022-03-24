/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:14:45 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 11:02:31 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//link it with -lreadline

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_line		line;
	t_each		**c;
	t_status	sh;

	if (argc != 1)
		return (errmsg(argv[1], NULL, ERRSH, 127));
	sh.sh_env = NULL;
	while (1)
	{
		ft_sh_init(&sh, envp);
		c = NULL;
		signal(SIGINT, handle_sigint_rl);
		signal(SIGQUIT, SIG_IGN);
		if (ft_check_line(&line, &sh, &c) == 0)
		{
			ft_create_cmds(&line, &c, &sh);
			if (c[0] != NULL)
				ft_pipeline(&sh, c);
			else
				ft_free_full_struct(&c);
		}
		else
			ft_line_fail(&line, &sh);
	}
	return (0);
}
