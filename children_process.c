/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:56:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/03 14:26:07 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		exit(1);
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			exit(1);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			exit(1);
		close_all(pipex);
		if (!pipex->cmd1_path)
		{
			ft_putstr_fd("Error; first command not found\n", 2);
			exit(127);
		}
		if (execve(pipex->cmd1_path, pipex->cmd1_argv, pipex->envp) < 0)
		{
			perror("error, child1 execve failed");
			exit(1);
		}
	}
}

void	second_child_process(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_msg(pipex, 3);
	if (pipex->pid2 == 0)
	{
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			exit(1);
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			exit(1);
		close_all(pipex);
		if (!pipex->cmd2_path)
		{
			ft_putstr_fd("Error; second command not found\n", 2);
			exit(127);
		}
		if (execve(pipex->cmd2_path, pipex->cmd2_argv, pipex->envp) < 0)
		{
			perror("error, child1 execve failed");
			exit(1);
		}
	}
}
