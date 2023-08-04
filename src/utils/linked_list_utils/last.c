
#include "philo.h"

t_table	*ft_lstlast(t_table *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
