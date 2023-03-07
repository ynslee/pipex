
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

char	*has_single_quote(char *str)
{
	char	*cmd;
	char	*quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!str[i])
	{
		j++;
		if (str[i] == 39)
			break ;
		i++;
	}
	while (!str[j])
	{
		if (str[j] == 39)
			break ;
		j++;
	}
	if (!str[j])
		exit(1);
	cmd = ft_substr(str, i, j - i + 1);
	if (!cmd)
		error_alloc(cmd);
	quote = cmd;
	free(cmd);
	return (quote);
}

char	**split_command(char *str)
{
	char	**cmd;
	char	*cmdname;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = NULL;
	while (str[i] && ft_strchr(str, 39) != 0)
		i++;
	if (ft_strchr(str, 39) != 0)
	{
		cmd[1] = has_single_quote(str);
		cmdname = ft_strtrim(str, cmd[1]);
		if (!cmdname)
			error_alloc(cmdname);
		cmd[0] = ft_split_one_str_out(cmdname, ' ');
		free(cmdname);
	}
	else
	{
		cmd = ft_split(str, ' ');
		if (!cmd)
			error_alloc2(cmd);
	}
	return (cmd);
}

int	main(int argc, char **argv)
{
	int		i;
	char	**print;

	i = 0;
	if (argc == 1)
		return (1);
	print = split_command(argv[1]);
	while (!print)
	{
		printf("argument is %s\n", print[i]);
		i++;
	}
	return (0);
}
