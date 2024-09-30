/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:51:26 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/30 19:25:34 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int		line_path;
	int		pipe_fd[2];
	int		error;
	int		absolut_path;
	char	**cmds;
	char	**path_list;
	char	*path_to_access;
	char	**env;
	char	*file_1;
}	t_pipe;

//UTILS
void	pipe_creat(t_pipe *pipex);
void	ft_close_pipe(t_pipe *pipex);
void	check_fork(t_pipe *pipex);
void	if_perror(t_pipe *pipex);
int		invert_inout(t_pipe *pipex, int exe_cmd, int fd);
//PATH
void	check_files(char *infile, char *outfile, t_pipe *pipex);
void	check_args(int argc, char **argv, char **env, t_pipe *pipex);
void	find_path(char **env, t_pipe *pipe, char **argv);
char	**add_path(t_pipe *pipe, char *add, int len);
//VALID_INPUT
void	env_check(char **argv, t_pipe *pipex);
void	exe_cmd(char **argv, t_pipe pipex, int num_cmd);
void	exe_last_cmd(char **argv, char *file2, t_pipe pipex, int num_cmd);
void	clean_to_exit(int level_clean, t_pipe pipex);
#endif