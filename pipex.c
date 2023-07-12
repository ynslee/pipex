/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/12 12:13:37 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	argv_check(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("Infile error!");
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (pipex->outfile == -1)
		perror("Outfile error!");
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd1_argv)
		error_alloc2(pipex->cmd1_argv);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	if (!pipex->cmd2_argv)
		error_alloc2(pipex->cmd2_argv);
	return (0);
}

void	find_path(t_pipex *pipex, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	if (!envp[i])
		error_msg(pipex, 2);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!path)
		error_alloc(path);
	pipex->path = ft_split(path, ':');
	if (!pipex->path)
		error_alloc2(pipex->path);
	free(path);
}

char	*get_path(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*path_tmp;
	char	*path_cmd;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	else
	{
		while (pipex->path[i])
		{
			path_tmp = ft_strjoin(pipex->path[i], "/");
			path_cmd = ft_strjoin(path_tmp, cmd[0]);
			free(path_tmp);
			if (!path_cmd)
				error_alloc(path_cmd);
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
			free(path_cmd);
			path_cmd = NULL;
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong amount of arguments!\n"));
	else
	{
		pipex = ft_calloc(1, sizeof(t_pipex));
		if (!pipex)
			error_msg(pipex, 4);
		pipex->envp = envp;
		argv_check(argv, pipex);
		find_path(pipex, envp);
		if (pipe(pipex->fd) == -1)
			return (ft_printf("problem when making a pipe!\n"));
		printf("pipex->fd is %d\n", pipex->fd[1]);
		pipex->cmd1_path = get_path(pipex, pipex->cmd1_argv);
		pipex->cmd2_path = get_path(pipex, pipex->cmd2_argv);
		first_child_process(pipex);
		second_child_process(pipex);
		close_all(pipex);
		waitpid(pipex->pid1, NULL, 0);
		waitpid(pipex->pid2, NULL, 0);
		free_all(pipex);
	}
	return (0);
}
