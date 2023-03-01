/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/01 15:45:31 by yoonslee         ###   ########.fr       */
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

// char	**split_command(char *argv)
// {
// 	char	**cmd;
// 	int		i;

// 	cmd = ft_split(argv, ' ');
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_strchr(cmd[i], ' ') != 0)
// 			cmd[i] = ft_strtrim(cmd[i], " ");
// 		i++;
// 	}
// 	return (cmd);
// }

int	argv_check(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("Infile error!");
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror("Outfile error!");
	pipex->cmd1_argv = split_command(argv[2]);
	if (!pipex->cmd1_argv)
		// exit(1);
	pipex->cmd2_argv = split_command(argv[3]);
	if (!pipex->cmd2_argv)
		// exit(1);
	return (0);
}

char	*find_path(t_pipex *pipex, char **envp)
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
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!path)
		return (NULL);
	return (path);
}

void	first_child_process(t_pipex *pipex)
{
	close(pipex->fd[0]);
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		exit(1);
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		exit(1);
	// close(pipex->fd[1]);
	pipex->cmd1_path = get_path(pipex, pipex->cmd1_argv);
	if (!pipex->cmd1_path)
	{
		ft_putstr_fd("Error; cmd1 not found\n", 2);
		exit(1);
	}
	execve(pipex->cmd1_path, args, pipex->envp);
}

// void *get_path(t_pipex *pipex, char **cmd)
// {
// 	int		i;
// 	char	*path_env;

// 	i = 0;
// 	while (pipex->envp[i])
// 	{
// 		path_env = ft_strjoin(pipex->envp[i], "/");
// 		path_env = ft_strjoin(path_env, cmd[0]);
// 		if (access(path_env, X_OK) == 0)
// 			return (path_env);
// 		free(path_env);
// 		i++;
// 	}
// 	return (NULL);
// }

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong amount of arguments!\n"));
	pipex = malloc(sizeof(t_pipex));// change it to ft_calloc later.
	if (!pipex)
		return (ft_printf("error in allocating pipex"));
	argv_check(argv, pipex);
	pipex->env = find_path(pipex, envp);
	pipex->path = ft_split(pipex->env, ':');
	if (!pipex->path)
		exit(1);
	if (pipe(pipex->fd[2]) == -1)
		return (ft_printf("problem when making a pipe!\n"));
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		exit(1);
	if (pipex->pid1 == 0)
		first_child_process(pipex);

	// int i = 0;
	// while (pipex->cmd1_argv[i])
	// {
	// 	printf("%s\n", pipex->cmd1_argv[i]);
	// 	i++;
	// }
	// i = 0;
	// while (pipex->cmd2_argv[i])
	// {
	// 	printf("%s\n", pipex->cmd2_argv[i]);
	// 	i++;
	// }
	int i = 0;
	while (pipex->path[i])
	{
		printf("%s\n", pipex->path[i]);
		i++;
	}
	printf("%s\n", pipex->env);

	return (0);
}
