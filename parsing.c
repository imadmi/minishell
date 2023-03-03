#include "parsing.h"

char *ft_fgets(char *str, int n, FILE *stream) 
{
    int i = 0;
    int c = fgetc(stream);

    while (i < n - 1 && c != EOF && c != '\n') 
    {
        str[i++] = c;
        c = fgetc(stream);
    }

    if (c == '\n') 
    {
        str[i++] = c;
    }

    str[i] = '\0';
    if (i == 0 && c == EOF) 
    {
        return NULL;
    }
    return str;
}


int ft_strcspn(const char *str1, const char *str2) 
{
    int len1 = ft_strlen(str1);
    int len2 = ft_strlen(str2);
    int i = 0, j;

    while (i < len1) {
        j = 0;
        while (j < len2 && str1[i] != str2[j]) 
        {
            j++;
        }
        if (j < len2) 
        {
            return i;
        }
        i++;
    }

    return len1;
}

char* ft_strcpy(char* dest, const char* src) 
{
    char* original_dest = dest;

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return original_dest;
}

char* get_input() 
{
    printf("Minishell> ");
    
    char input[100];
    ft_fgets(input, 100, stdin);
    
    input[ft_strcspn(input, "\n")] = 0;
    
    char *str = (char*) malloc(strlen(input) + 1);
    ft_strcpy(str, input);
    
    return str;
}

void add_to_list(t_struct **head, t_struct **tail, char *str) 
{
    t_struct *new_node = (t_struct*) malloc(sizeof(t_struct));
    new_node->value = (char*) malloc(strlen(str) + 1);
    ft_strcpy(new_node->value, str);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

void print_list(t_struct *head) {
    printf("> ");
    t_struct *current = head;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

void free_list(t_struct *head) {
    t_struct *current = head;
    while (current != NULL) {
        t_struct *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
}

char *findTokenStart(const char *str, const char *delim) {
    while (*str != '\0') {
        if (strchr(delim, *str) == NULL) {
            return (char*) str;
        }
        str++;
    }
    return NULL;
}

char *findTokenEnd(const char *str, const char *delim) {
    const char *s = str;

    while (*s != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*s == *d) {
                return (char *)s;
            }
            d++;
        }
        s++;
    }
    return (char *)s;
}

char *ft_strtok(char *str, const char *delim) 
{
    char *lastToken = NULL;
    char *tokenStart;
    char *tokenEnd;

    if (str != NULL) 
    {
        lastToken = str;
    } 
    else 
    {
        lastToken = strtok(NULL, delim);
        if (lastToken == NULL) 
        {
            return NULL;
        }
    }
    tokenStart = findTokenStart(lastToken, delim);
    if (tokenStart == NULL) 
    {
        return NULL;
    }
    tokenEnd = findTokenEnd(tokenStart, delim);
    if (*tokenEnd != '\0') 
    {
        *tokenEnd = '\0';
        lastToken = tokenEnd + 1;
    } 
    else 
    {
        lastToken = tokenEnd;
    }
    return tokenStart;
}

int main() 
{
    t_struct *head = NULL;
    t_struct *tail = NULL;
    
    while (1) {
        char *input = get_input();
        char *token = ft_strtok(input, " ");
        while (token != NULL) {
            add_to_list(&head, &tail, token);
            token = ft_strtok(NULL, " ");
        }
        print_list(head);
        free(input);
        free_list(head);
        head = NULL;
        tail = NULL;
    }
    
    return 0;
}
