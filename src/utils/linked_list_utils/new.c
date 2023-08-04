
#include "philo.h"

t_table	*ft_lstnew(int nbr)
{
	t_table	*newnode;

	newnode = malloc(sizeof(t_table));
	if (!newnode)
		return (NULL);
	newnode->nbr = nbr;
	newnode->next = NULL;
	return (newnode);
}
