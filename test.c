
#include <unistd.h>
#include <stdio.h>

// char	**split_command(char *argv)
// {
// 	char	**cmd;
// 	int		i;

// 	// cmd = ft_split(argv, ' ');
// 	i = 0;
// 	if (ft_strchr(argv[i], 39) != 0)
// 		has_single_quote(argv)
// 		while (argv[i])
// 		{
// 			if (argv[i] = 39)
// 				break;
// 			i++;
// 		}
// 			while
// 	return (cmd);
// }

// char *has_single_quote(char *argv)
// {
// 	char	*cmd;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (!argv[i])
// 	{
// 		j++;
// 		if (argv[i] == 39)
// 			break ;
// 		i++;
// 	}
// 	while (!argv[j])
// 	{
// 		if (argv[j] == 39)
// 			break ;
// 		j++;
// 	}
// 	cmd = ft_substr(argv, i, j - i + 1);
// }