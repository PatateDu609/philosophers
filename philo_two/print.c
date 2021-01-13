#include "philo_two.h"

static char	*ft_event_to_string(t_events event)
{
	if (event == DIED)
		return ("died");
	if (event == TAKEN_FORK)
		return ("has taken a fork");
	if (event == SLEEPING)
		return ("is sleeping");
	if (event == EATING)
		return ("is eating");
	if (event == THINKING)
		return ("is thinking");
	return (NULL);
}

void	print_message(t_events event, t_philo *philo)
{
	long	ts;

	ts = ft_timestamp(philo->data);
	printf("%ld %d %s\n", ts, philo->nb, ft_event_to_string(event));
}
