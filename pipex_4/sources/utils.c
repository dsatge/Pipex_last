/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:54:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 18:14:04 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipe_creat(t_pipe *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		clean_to_exit(0, *pipex);
	}
}

void	ft_close_pipe(t_pipe *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	clean_to_exit(int level_clean, t_pipe pipex)
{
	if (level_clean >= 0 && pipex.absolut_path != -1)
	{
		ft_freetab(pipex.path_list);
	}
	if (level_clean >= 1)
	{
		if (pipex.cmds)
			ft_freetab(pipex.cmds);
		if (pipex.path_to_access)
			free(pipex.path_to_access);
	}
	if (level_clean >= 2 && level_clean != 404)
	{
		exit(EXIT_FAILURE);
	}
	if (level_clean == 404)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
}

void	check_fork(t_pipe *pipex)
{
	perror("fork:");
	clean_to_exit(0, *pipex);
}

void	if_perror(t_pipe *pipex)
{
	perror("error read:");
	pipex->error = 1;
}
