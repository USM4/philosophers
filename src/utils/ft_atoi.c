

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	s;

	i = 0;
	x = 0;
	s = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
				s++;
			i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = x * 10 + str[i] - '0';
			i++;
	}
	if (s % 2 == 1)
		x *= -1;
	return (x);
}
