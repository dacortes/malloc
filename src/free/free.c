/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:53:19 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/26 23:59:30 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_internal.h>

void coalesce() {
	t_block_meta *curr = g_meta;
	while (curr && curr->next) {
		if (curr->is_it_free && curr->next->is_it_free) {
			curr->size += META_SIZE + curr->next->size;
			curr->next = curr->next->next;
		}
		else
			curr = curr->next;
	}
}

void free(void *ptr) {
	if (!ptr)
		return;

	t_block_meta *block = (t_block_meta *)ptr - 1;
	block->is_it_free = true;
	coalesce();
}
