#include "philo.h"

void	ft_lstadd_back(t_table **lst, t_table *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
