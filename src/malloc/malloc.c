#include <malloc_internal.h>


void	*malloc(size_t size) {
	if (size >= SIZE_MAX_MMAP)
		return (NULL);
	t_block_meta	*last = NULL;
	t_block_meta	*block = find_free_block(size, &last);

	if (block) {
		split_block(size, block);
		block->is_it_free = false;
	}
	else {
		block = request_meta(size);
		if (!block)
			return (NULL);
	}
	return ((void *)(block + 1));
}