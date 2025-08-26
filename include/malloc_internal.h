/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:30:59 by codespace         #+#    #+#             */
/*   Updated: 2025/08/26 13:32:10 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef and
	#define and &&
#endif

#ifndef or
	#define or ||
#endif

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif

#ifndef ERROR
	#define ERROR -1
#endif

#include <stddef.h>
#include <sys/mman.h>

#define SYSTEM_SIZE	(size_t)getpagesize()
#define GET_SYS_MEM(S)	mmap(NULL, S, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);



typedef enum s_boolean
{
	false,
	true
} t_boolean;

typedef	int	bool;

/**
 * @brief Defines the alignment requirement for memory allocations.
 *
 * This macro calculates the alignment to be used for memory allocations.
 * It selects the greater value between:
 * - Twice the size of a `size_t` type.
 * - The alignment requirement of a `long double` type.
 *
 * This ensures that allocated memory is properly aligned for the most
 * restrictive data types, improving performance and avoiding undefined
 * behavior due to misaligned memory access.
 */
#define MALLOC_ALIGNMENT (2 * sizeof(size_t) < __alignof__(long double) \
						? __alignof__(long double) : 2 * sizeof(size_t))
/**
 * @brief Aligns a given number up to the nearest multiple of MALLOC_ALIGNMENT.
 *
 * This function ensures that the input number is rounded up to the next
 * multiple of MALLOC_ALIGNMENT, which is typically used to satisfy memory
 * alignment requirements for efficient memory access.
 *
 * @param num The number to be aligned.
 * @return The aligned number, which is the smallest multiple of MALLOC_ALIGNMENT
 *         that is greater than or equal to the input number.
 */
static inline size_t align_up(size_t num){ return (num + (MALLOC_ALIGNMENT - 1)) & ~(MALLOC_ALIGNMENT - 1); }

typedef	struct s_block_meta	t_block_meta;


#define META_SIZE sizeof(t_block_meta)

struct s_block_meta
{
	size_t			size;
	t_block_meta	*next;
	bool			is_it_free;
};

extern	t_block_meta	*g_meta;

t_block_meta    *find_free_block(size_t size, t_block_meta **last);
void    split_block(size_t size, t_block_meta *block);
t_block_meta	*get_last_block(void);
t_block_meta	*request_meta(size_t size);