#include "philo_two.h"

int main(int ac, char **av)
{
	t_data	data;

	if (!ft_init(&data, ac, av))
		return (usage());
	return (0);
}
