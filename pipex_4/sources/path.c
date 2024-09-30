/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:49:53 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 14:54:35 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_files(char *infile, char *outfile, t_pipe *pipex)
{
	int	file1;
	int	file2;

	file1 = open(infile, O_RDONLY);
	file2 = open(outfile, O_RDONLY);
	if (file1 < 0)
	{
		if (access(infile, F_OK) != 0)
			perror("infile access");
		else if (access(infile, R_OK | W_OK) != 0)
			perror("infile permission");
		pipex->error = 1;
	}
	if (file2 < 0 || pipex->error == 1)
	{
		if (access(outfile, F_OK) != 0 && pipex->error == 0)
			return ;
		else if (access(outfile, R_OK | W_OK) != 0)
			perror("outfile permission");
		pipex->error = 1;
	}
	close(file1);
	close(file2);
}

void	check_args(int argc, char **argv, char **env, t_pipe *pipex)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: please give 4 arguments for the right execution of \
			pipex\n", 2);
		exit(EXIT_FAILURE);
	}
	if (env[0] == NULL)
	{
		pipex->absolut_path = -1;
		env_check(argv, pipex);
	}
	else
		pipex->env = env;
	pipex->path_to_access = NULL;
	pipex->cmds = NULL;
	pipex->path_list = NULL;
	pipex->error = 0;
	pipex->file_1 = argv[1];
	init_files(argv[1], argv[argc - 1], pipex);
}

void	find_path(char **env, t_pipe *pipex, char **argv)
{
	int		line_env;
	int		line;
	char	*path;

	path = NULL;
	if (env[0] == NULL)
	{
		pipex->line_path = 0;
		return ;
	}
	line_env = ft_count_line_split(env);
	line = 0;
	while (line < (line_env - 1) && ft_strncmp(env[line], "PATH=", 5) != 0)
		line++;
	if (ft_strncmp(env[line], "PATH=", 5) != 0)
	{
		pipex->absolut_path = -1;
		env_check(argv, pipex);
		return ;
	}
	path = ft_strtrim(env[line], "PATH=");
	pipex->path_list = ft_split(path, ':');
	free(path);
	pipex->line_path = ft_count_line_split(pipex->path_list);
	pipex->path_list = add_path(pipex, "/", pipex->line_path);
}

char	**add_path(t_pipe *pipe, char *add, int len)
{
	int		line;
	char	**new;

	line = 0;
	new = malloc(sizeof(char *) * (len + 1));
	while (line < len)
	{
		new[line] = ft_strjoin(pipe->path_list[line], add);
		if (!new[line])
		{
			perror("path creation");
			ft_freetab(new);
			clean_to_exit(2, *pipe);
		}
		line++;
	}
	ft_freetab(pipe->path_list);
	new[line] = 0;
	return (new);
}

void	ft_close_pipe(t_pipe *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
