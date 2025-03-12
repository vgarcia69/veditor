#include "libft.h"

char	*ft_strinsert(char *str, char *to_insert, int i)
{
	int	insert_len;
	int	insert_len_cpy;
	int	str_len;

	insert_len = ft_strlen(to_insert);	
	str_len = ft_strlen(str);
	str[insert_len + str_len] = '\0';
	insert_len_cpy = insert_len;
	while (str_len-- != i)
		str[str_len + insert_len] = str[str_len];
	while (insert_len_cpy--)
		str[i + insert_len_cpy] = to_insert[insert_len_cpy];
	return (str);
}
