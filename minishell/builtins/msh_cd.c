/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/12 17:53:29 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_cd_home(t_shell *shell, char *home)
{
	home = find_env(shell->u_env, "HOME=")
	
}

void	msh_cd_target(t_shell *shell)
{
	
}

void	msh_cd(t_shell *shell)
{
	char	*home;

	if (shell->command->target)
		msh_cd_target(shell);
	else
	{
		home = NULL;
		msh_cd_home(shell, home);
	}
}
