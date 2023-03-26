#include "parsing.h"

char	*env_key(char *str)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	p = malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		p[i] = str[i];
		i++;
	}
	return (p[i] = '\0', p);
}

char	*env_value(char *str)
{
	int		i;
	char	*p;
	int		j;

	j = 0;
	i = 0;
	while (*str != '=')
		str++;
	if (*str)
		str++;
	while (str[i])
		i++;
	p = malloc(i + 1);
	i = 0;
	if (!p)
		return (NULL);
	while (str[i])
		p[j++] = str[i++];
	return (p[j] = '\0', p);
}

void	setting_var(char *environ, t_env *tmp)
{
	tmp->key = env_key(environ);
	tmp->value = env_value(environ);
}

void	free_node(t_env *head)
{
	t_env	*tmp;

	while (head)
    {
		tmp = head;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		head = head->next;
		free(tmp);
	}
	exit(1);
}

t_env	*creat_node(void)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->key = NULL;
	p->value = NULL;
	return (p);
}

t_env	*export_linked_list(char **environ)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = 0;
	head = creat_node();
	if (head == NULL)
		exit(1);
	head->key = env_key(environ[i]);
	if (!head->key)
		exit(1);
	head->value = env_value(environ[i]);
	head->equal_c = 1;
	i++;
	head->printed = -1;
	tmp = head;
	while (environ[i])
	{
		tmp->next = creat_node();
		if (tmp->next == NULL)
			free_node(head);
		tmp = tmp->next;
		setting_var(environ[i], tmp);
		tmp->equal_c = 1;
		if (!tmp->key || !tmp->value)
			return (tmp->next = NULL, free_node(head), NULL);
		tmp->printed = -1;
		i++;
	}
	return (tmp->next = NULL, head);
}

void print_env_variables(t_data *data)
{
    t_env *env = data->env;
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

int	setting_data(t_data *data, char **env)
{
	data->env = export_linked_list(env);
	data->shell_level = 1;
	if (!data->env)
		return (1);
	return (0);
}