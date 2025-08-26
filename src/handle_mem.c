/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:49:13 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/26 13:31:47 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_internal.h>

t_block_meta *g_meta = {0};

t_block_meta    *find_free_block(size_t size, t_block_meta **last) {
	t_block_meta    *curr = g_meta;

	while (curr)
	{
		if (curr->is_it_free and curr->size >= size)
			return (curr);
		*last = curr;
		curr = curr->next;
	}
	return (curr);
}

void	split_block(size_t size, t_block_meta *block) {
	if (block->size >= META_SIZE + size) {
		t_block_meta    *new_block = (t_block_meta*)((char*)(block + 1) + size);
		new_block->size = block->size - size - META_SIZE;
		new_block->next = block->next;
		new_block->is_it_free = true;
		block->size = size;
		block->next = new_block;
	}
}

inline t_block_meta	*get_last_block(void) {
	t_block_meta    *iter = g_meta;

	if (!iter)
		return (NULL);
	while (iter)
		iter = iter->next;
	return (iter);
}

t_block_meta	*request_meta(size_t size) {
	size_t  total_size = align_up(size + META_SIZE);
	void *ptr = GET_SYS_MEM(total_size);
	if (ptr == MAP_FAILED)
		return (NULL);
	t_block_meta    *block = (t_block_meta *)ptr;
	block->size = total_size - META_SIZE;
	block->next = NULL;
	block->is_it_free = false;
	if (!g_meta)
		g_meta = block;
	else {
		t_block_meta	*last = get_last_block();
		if (!last)
			return (NULL);
		last->next = block;
	}
	return (block);
}

