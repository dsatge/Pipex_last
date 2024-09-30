/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:32:23 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 19:26:42 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	pipex;
	pid_t	pid;

	check_args(argc, argv, env, &pipex);
	find_path(env, &pipex, argv);
	pipe_creat(&pipex);
	pid = fork();
	if (pid == -1)
		check_fork(&pipex);
	if (pid == 0)
		exe_cmd(argv, pipex, 2);
	pid = fork();
	if (pid == -1)
		check_fork(&pipex);
	if (pid == 0)
		exe_last_cmd(argv, argv[argc - 1], pipex, 3);
	ft_close_pipe(&pipex);
	wait(NULL);
	wait(NULL);
	if (pipex.error == 1)
		clean_to_exit(2, pipex);
	clean_to_exit(1, pipex);
	return (0);
}
