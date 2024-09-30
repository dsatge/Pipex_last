/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:50:40 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 19:43:16 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	env_check(char **argv, t_pipe *pipex)
{
	int	err;

	err = 0;
	if (access(argv[2], F_OK) != 0)
	{
		err++;
		perror("pipex: env_check");
	}
	if (access(argv[3], F_OK) != 0)
	{
		err++;
		perror("pipex: env_check");
	}
	if (err == 2)
		exit(127);
	pipex->env = NULL;
}

void	exe_cmd(char **argv, t_pipe pipex, int num_cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = open(pipex.file_1, O_RDONLY);
	if (invert_inout(&pipex, 0, fd) == -1)
		return ;
	pipex.cmds = ft_split(argv[num_cmd], ' ');
	if (pipex.cmds[0] != NULL && access(pipex.cmds[0], F_OK | X_OK) == 0
		&& execve(pipex.cmds[0], pipex.cmds, pipex.env) == -1)
		return (clean_to_exit(404, pipex), perror("exe_cmd:"));
	while (++i < pipex.line_path && pipex.absolut_path != -1
		&& pipex.cmds[0] != NULL)
	{
		free(pipex.path_to_access);
		pipex.path_to_access = ft_strjoin(pipex.path_list[i], pipex.cmds[0]);
		if (access(pipex.path_to_access, F_OK | X_OK) == 0
			&& execve(pipex.path_to_access, pipex.cmds, pipex.env) == -1)
			return (exit(127), perror("exe_cmd:"));
	}
	return (clean_to_exit(404, pipex), perror("exe_cmd:"));
}

void	exe_last_cmd(char **argv, char *file2, t_pipe pipex, int num_cmd)
{
	int		i;
	int		output_fd;

	i = -1;
	output_fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (invert_inout(&pipex, 1, output_fd) == -1)
		return ;
	pipex.cmds = ft_split(argv[num_cmd], ' ');
	if (pipex.cmds[0] != NULL && access(pipex.cmds[0], F_OK | X_OK) == 0
		&& execve(pipex.cmds[0], pipex.cmds, pipex.env) == -1)
		return (clean_to_exit(404, pipex), perror("exe_last_cmd:"));
	while (++i < pipex.line_path && pipex.absolut_path != -1
		&& pipex.cmds[0] != NULL)
	{
		free(pipex.path_to_access);
		pipex.path_to_access = ft_strjoin(pipex.path_list[i], pipex.cmds[0]);
		if (access(pipex.path_to_access, F_OK | X_OK) == 0
			&& execve(pipex.path_to_access, pipex.cmds, pipex.env) == -1)
			return (exit(127), perror("exe_last_cmd:"));
	}
	return (clean_to_exit(404, pipex), perror("exe_last_cmd:"));
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
