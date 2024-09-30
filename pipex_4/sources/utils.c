/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:54:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 19:24:12 by dsatge           ###   ########.fr       */
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

int	invert_inout(t_pipe *pipex, int exe_cmd, int fd)
{
	if (exe_cmd == 0)
	{
		if (fd == -1)
			return (if_perror(pipex), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (fd == -1)
			return (if_perror(pipex), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (-1);
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
			return (-1);
	}
	ft_close_pipe(pipex);
	close(fd);
	return (0);
}
