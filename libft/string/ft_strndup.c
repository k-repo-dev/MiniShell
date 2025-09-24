#include "../libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
