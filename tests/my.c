#include <test.h>
#include <malloc_internal.h>


int	main(void) {
	t_test *ptr = (t_test *)malloc(sizeof(t_test *) * 4);
	size_t assigned = sizeof(sizeof(t_test *) * 4);
	if (!print_status_malloc(assigned, ptr))
		return (1);
	free(ptr);
}
