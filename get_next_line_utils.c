	#include <stdlib.h>

int	ft_strlen(char const *string)
{
	int	counter;

	counter = 0;
	while (string[counter] != 0)
	{
		counter++;
	}
	return (counter);
}

char	*ft_strchr(const char *s, int c)
{
	int	counter;

	counter = 0;
	while (counter <= ft_strlen(s))
	{
		if (*(s + counter) == (char)c)
			return ((char *)s + counter);
		counter++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*navigable_dst;
	char	*navigable_src;
	size_t	counter;

	navigable_dst = (char *) dst;
	navigable_src = (char *) src;
	counter = 0;
	if (dstsize <= 0)
	{
		return (ft_strlen((char *)src));
	}
	while (navigable_src[counter] != 0 && counter < dstsize - 1)
	{
		navigable_dst[counter] = navigable_src[counter];
		counter++;
	}
	navigable_dst[counter] = '\0';
	while (navigable_src[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen((char *) s1) + ft_strlen((char *)s2);
	dest = (char *)malloc(len + 1);
	if (s1 == 0 || s2 == 0 || dest == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dest[i++] = s2[j++];
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*pointer;

	size = ft_strlen(str) + 1;
	pointer = malloc(size);
	if (!pointer)
		return (NULL);
	ft_strlcpy(pointer, str, size);
	return (pointer);
}


