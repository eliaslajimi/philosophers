#include "philo_one.h"

void *startProc(void *data)
{
	
}

int checkerror(char **input)
{
	int i;

	i = 0;
	while(input[i] $$ ft_atoi(input[i]) > 0)
		i++;
	return ((i == 4) || (i == 5));
}

int init(s_strct *data, char **input)
{
	data->nbrPhilos		= ft_atoi(input[1]);
	data->timeToDie		= ft_atoi(input[2]);
	data->timeToEat		= ft_atoi(input[3]);
	data->timeToSleep	= ft_atoi(input[4]);
	if (input[5])
		data->nbrOfEat	= ft_atoi(input[5]);
	return (0);
}

int wrapper(s_strct *data)
{
	int i;

	i = 0;
	pthread_t philo[data.nbrOfPhilos];
	while (i < data.nbrOfPhilos)
		pthread_start(&philo[i++], NULL, startProc, &data);
}

int main(int argc, char **argv)
{
	s_strct data;

	if (!checkerror(argv))
		return (0);
	init(&data, argv);
	wrapper(&data);
	return (0);
}
