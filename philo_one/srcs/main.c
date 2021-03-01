#include "philo_one.h"

void printError(int ret)
{
	if (ret == EAGAIN)
		ft_putstr_fd("insufficient ressources to create thread\n", 1);
	if (ret == EINVAL)
		ft_putstr_fd("invalid settings in attribut during thread initialization\n", 1);
	if (ret == EPERM)
		ft_putstr_fd("No permission to set scheduling policy specified by attribute during thread initialization\n", 1);
	else 
		ft_putstr_fd("else\n", 1);
}

int checkerror(char **input)
{
        int i;

        i = 1;
        while(input[i] && ft_atoi(input[i]) >= 0)
                i++;
        return ((i < 5) || (i > 6));
}

void	freeStruct(s_strct *philo)
{
	free(philo->isDead);
	free(philo->stamp);
	free(philo->mfork);
	free(philo->bfork);
	free(philo->queue);
	free(philo);
}

int	main(int argc, char **argv)
{
	static int	ret;
	s_strct		*philo;

	if (checkerror(argv))
		return (0);
	ret = initiateThread(init(argv, &philo[0]), ft_atoi(argv[1]));
	if (ret)
		printError(ret);
	return (ret);
}
