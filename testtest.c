
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>//perror, strerror
#include <sys/wait.h>//wait, waitpid
#include <fcntl.h>
#include <errno.h>
#include <string.h>

char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);

typedef struct s_pipex{
	char	*cmd1;
	char	*cmd2;
	char	*path;
	char	*cmd_path;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	**envp;
	int		fd[2];
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
}			t_pipex;

char	**split_command(char *argv)
{
	char	**cmd;
	int		i;

	cmd = ft_split(argv, ' ');
	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], ' ') != 0)
			cmd[i] = ft_strtrim(cmd[i], " ");
		i++;
	}
	return (cmd);
}

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
		exit(1);
	pipex->cmd2_argv = split_command(argv[3]);
	if (!pipex->cmd2_argv)
		exit(1);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	int i = 0;

	if (argc != 5)
		return (printf("Wrong amoung=t of arguments!\n"));
	pipex = malloc(sizeof(t_pipex));// change it to ft_calloc later.
	if (!pipex)
		return (printf("error in allocating pipex"));
	argv_check(argv, pipex);
	pipex->envp = find_path(envp);
	if (!pipex -> envp)
		exit(1);
	if (pipe(pipex->fd[2]) == -1)
		return (1);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (1);
	if (pipex->pid1 == 0)
		first_child_process(pipex, fd[0], fd[1]);

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
	return (0);
}
