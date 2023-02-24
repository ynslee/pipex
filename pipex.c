/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/24 13:46:17 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
1. First check if the argument count 
2. check open file, close file
3. split the cmd1 cmd2 to use with execve later on
4. find envp paths to execute commands
5. make a pipe to use child functions
5. write infile and execute child1 process/use dup2 to change stdin
6. read child1 process result and execute child2 process/use dup2 to change stdout
7. check if everything is closed
opens argv[4] in write-only mode with create and truncate options and sets file permissions to 0644
execve is a system call in Unix and Unix-like operating systems, which is used to execute a new program within the current process.

When a program executes execve, it replaces the current program code and memory space with the new program's code and memory space. The new program becomes the current process, and it starts executing from its main function.

The execve system call takes three arguments: the first argument is the path to the new program, the second argument is an array of strings that represent the program's arguments, and the third argument is an array of strings that represent the program's environment variables.

The execve system call is commonly used in Unix systems to implement the functionality of shell commands such as ls, grep, cat, and many others. When you run a command in the shell, the shell uses execve to execute the corresponding program, and the program replaces the shell process.
*/

int	argv_check(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("Infile error!");
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror("Outfile error!");
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd1_argv)
		exit(1);
	pipex->cmd1 = ft_strjoin("/", pipex->cmd1_argv[0]);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	if (!pipex->cmd2_argv)
		exit(1);
	pipex->cmd2 = ft_strjoin("/", pipex->cmd2_argv[0]);
	return (0);
}

char	*find_path(char **envp)
{
	int		i;
	char	*path;
	char	**env_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!path)
		return (NULL);
	return (path);
}



void	first_child_process(t_pipex *pipex, int fd[0], int fd[1])
{
	if (pipex->outfile == -1)
		exit(1);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		exit(1);
	close (pipex->infile);
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		exit(1);
	close(fd[1]);
		pipex->cmd1_path = ft_split(pipex->envp, ':');
	if (!pipex->cmd1_paths)
		exit(1);
	pipex->cmd2_path = ft_split(pipex->envp, ':');
	if (!pipex ->cmd2_path)
		exit(1);
	get_cmd_path(pipe->cmd_path, pipe->cmd1_cmd1_pths)//use inside the first pipe
	execve()
}

int	get_path(t_pipex *pipex)
{
	int		i;
	char	**path_env;

	i = 0;
	path_env = get_env(pipex->env);
	if (!path_env)
		return (1);
	if (get_path_cmd1(path_env, pipex) == 1)
		return (1);
	if (get_path_cmd2(path_env, pipex) == 1)
		return (1);
	free_char(path_env);
	return (0);
}

int	get_path_cmd1(t_pipex *pipex)
{
	int		i;
	char	*paths[];

	i = 0;
	paths = pipex->cmd_path;
	while (paths[i])
	{
		pipex->cmd_path = ft_strjoin(path_env[i] + "/", pipex->cmd1);
		if (!pipex->cmd1_path)
			return (1);
		if (access(pipex->cmd1_path, X_OK) == 0)
			break ;
		if (pipex->cmd1_path)
		{
			free(pipex->cmd1_path);
			pipex->cmd1_path = NULL;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong amoung=t of arguments!\n"));
	pipex = malloc(sizeof(t_pipex));// change it to ft_calloc later.
	if (!pipex)
		return (ft_printf("error in allocating pipex"));
	argv_check(argv, pipex);
	pipex->envp = find_path(envp);
	if (!pipex -> envp)
		exit(1);
	if (pipe(pipex->fd[2]) == -1)
		return (1);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (1);
	if (pipiex->pid1 == 0)
		first_child_process(pipex, fd[0], fd[1]);

	

	return (0);
}
