
#include "philo.h"

void	ft_lstclear(t_table **lst)
{
	t_table	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
