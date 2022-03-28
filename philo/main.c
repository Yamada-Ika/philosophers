#include <stdlib.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}

int	main(void)
{
	void	*m;
	// static void	*m;

	m = malloc(100);
	return (0);
}
