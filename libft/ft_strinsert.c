#include "libft.h"

char	*ft_strinsert(char *str, char *to_insert, int i)
{
	int	insert_len;
	int	str_len;
	int	j;

	insert_len = ft_strlen(to_insert);	
	str_len = ft_strlen(str);
	str[insert_len + str_len] = '\0';
	j = str_len;
	while (j >= i)
	{
		str[j + insert_len] = str[j];
		--j;
	}
	j = 0;
	while (j < insert_len)
	{
		str[i + j] = to_insert[j];
		++j;
	}
	str[str_len + insert_len] = '\0';
	return (str);
}
