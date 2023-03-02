#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include"parsing.h"

int		ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int parsing(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (!ft_isascii(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int is_valid_env()
{

}

char	*check_type(t_struct *str)
{
	while ()
	{
		if (ft_strcmp(, ">") || ft_strcmp(, ">>") || ft_strcmp(, "<<") || ft_strcmp(, "<"))
			str->type = T_REDIRECT;
		else if (ft_strcmp(, "|"))
			str->type = T_PIPE;
		else if (ft_strcmp(, ";"))
			str->type = T_SEP;
		else if (ft_strcmp(, "\n") && !str->next)
			str->type = T_NEWLINE;
		else if (is_valid_env())
			str->type = T_ENV;
		else
			str->type = T_WORD;
	}
	return (NULL);
}

int main(int ac, char **av) 
{
    int i = 0;
    while(av[i])
    {
        if (parsing(av[i]))
        {
            printf("%d\n",parsing(av[i]));
            check_type(av[i]);
        }
        i++;
    }
    return 0;
}
