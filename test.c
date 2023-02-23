#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *) s1;
	st2 = (unsigned char *) s2;
	while ((i < n) && ((*st1 != '\0') || (*st2 != '\0')))
	{
		if (*st1 == *st2)
		{
			st1++;
			st2++;
			i++;
		}
		else
		{
			return (*st1 - *st2);
		}
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	ft_count_words(char const *s, char c)
{
	int	count_word;

	count_word = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count_word++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (count_word);
}

static char	**ft_freeall(char **out)
{
	int	i;

	i = 0;
	while (out[i])
	{
		free(out[i++]);
	}
	free(out);
	return (NULL);
}

static void	ft_putintostr(char **str, char const *s, char c)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (*s == c)
			s++;
		tmp = s;
		while (*tmp && *tmp != c)
			tmp++;
		if (*tmp == c || tmp > s)
		{
			*str = ft_substr(s, 0, tmp - s);
			if (!str || !*str)
			{
				ft_freeall(str);
				return ;
			}
			s = tmp;
			str++;
		}
	}
	*str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words(s, c);
	out = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!out)
		return (NULL);
	ft_putintostr(out, s, c);
	return (out);
}

// int main() {
//     char str1[] = "Hello world!";
//     char str2[] = "Hello there!";
//     int result1, result2, result3, result4;

//     // Compare the first 5 characters of str1 and str2
//     result1 = strncmp(str1, str2, 7);
// 	result2 = ft_strncmp(str1, str2, 7);

//     // Compare the first 7 characters of str1 and str2
//     result3 = strncmp(str1, str2, 11);
// 	result4 = ft_strncmp(str1, str2, 11);

//     // Print the results
//     printf("Result 1: %d\n", result1);
//     printf("Result 2: %d\n", result2);
//     printf("Result 3: %d\n", result3);
//     printf("Result 4: %d\n", result4);
	
//     return 0;
// }

// char	*find_str(char **env)
// {
// 	int i;
// 	char **path;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (strncmp("PATH=", env[i], 5) == 0)
// 			break;
// 		i++;
// 	}
// 	path = 

// }
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	out = malloc (sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	**get_env(char **env)
{
	int		i;
	char	*path;
	char	**path_env;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	path = ft_substr(env[i], 5, ft_strlen(env[i]));
	if (!path)
		return (NULL);
	printf("path here %s\n", path_env[i]);
	path_env = ft_split(path, ':');
	if (!path_env)
		return (NULL);
	free(path);
	printf("path here %s\n", path_env[1]);
	return (path_env);
}

int	main(int argc, char** argv, char **env)
{
	
	printf("tttt %s\n", env[1]);
	printf("find env: %s", *get_env(env));
	return (0);
}
