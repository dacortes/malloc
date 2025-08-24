/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:30:59 by codespace         #+#    #+#             */
/*   Updated: 2025/08/24 19:32:40 by dacortes         ###   ########.fr       */
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

# define TINY_MAX   512
# define SMALL_MAX  4096
# define PAGE_SIZE  4096

#define SYSTEM_SIZE	(size_t)getpagesize()
#define MEMORY_PAGE	mmap(NULL, SYSTEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

#include <stddef.h>

// TINY → hasta, por ejemplo, 512 bytes.
// SMALL → hasta 4 KB.
// LARGE → lo demás.
typedef enum s_zone_type {
	TINY,
	SMALL,
	LARGE
} e_zone_type;

enum s_boolean
{
	false,
	true
} e_boolean;

typedef struct	s_mallinfo		t_mallinfo;
typedef struct	s_arena			t_arena;


struct s_mallinfo
{
	int arena;     /* Non-mmapped space allocated (bytes) */
	int ordblks;   /* Number of free chunks */
	int smblks;    /* Number of free fastbin blocks */
	int hblks;     /* Number of mmapped regions */
	int hblkhd;    /* Space allocated in mmapped regions (bytes) */
	int usmblks;   /* See below */
	int fsmblks;   /* Space in freed fastbin blocks (bytes) */
	int uordblks;  /* Total allocated space (bytes) */
	int fordblks;  /* Total free space (bytes) */
	int keepcost;  /* Top-most, releasable space (bytes) */
};

/**
 * struct s_malloc_chunk - Represents a memory chunk in a custom malloc implementation.
 *
 * This structure is used to manage memory chunks in a doubly linked list.
 * It contains metadata about the chunk's size and pointers to neighboring
 * chunks for efficient memory management.
 *
 * Members:
 * @mchunk_prev_size: Size of the previous chunk (if it is free). This is used
 *                    to navigate backward in memory.
 * @mchunk_size:      Size of the current chunk in bytes, including the overhead
 *                    for metadata.
 * @fd:               Forward pointer to the next free chunk in the doubly linked list.
 * @bk:               Backward pointer to the previous free chunk in the doubly linked list.
 * @fd_nextsize:      Forward pointer to the next free chunk of the same size.
 * @bk_nextsize:      Backward pointer to the previous free chunk of the same size.
 */
typedef struct	s_malloc_chunk	t_malloc_chunk;

struct s_malloc_chunk
{
	size_t	mchunk_prev_size;
	size_t	mchunk_size;

	t_malloc_chunk	*fd;
	t_malloc_chunk	*bk;
	
	t_malloc_chunk	*fd_nextsize;
	t_malloc_chunk	*bk_nextsize;
};

/* 
	Helpers de chunk
*/
#define INUSE_FLAG   ((size_t)1)   /* bit 0 */
#define MMAP_FLAG    ((size_t)2)   /* optional */
#define NON_MAIN     ((size_t)4)   /* optional multi-arena */
#define SIZE_MASK    (~(size_t)0x7)

/**
 * @brief Retrieves the size of a memory chunk.
 *
 * This function extracts the size of a memory chunk by applying a bitwise AND
 * operation between the chunk's `mchunk_size` field and the `SIZE_MASK` constant.
 * The `SIZE_MASK` is used to filter out any metadata or flags that may be stored
 * in the `mchunk_size` field, leaving only the actual size of the chunk.
 *
 * @param chunk A pointer to the memory chunk whose size is to be retrieved.
 * @return The size of the memory chunk, with metadata or flags masked out.
 */
static inline size_t	chunk_size(t_malloc_chunk *chunk) { return (chunk->mchunk_size & SIZE_MASK); }

/**
 * @brief Checks if a memory chunk is currently in use.
 *
 * This function determines whether a given memory chunk is marked as "in use"
 * by examining the `mchunk_size` field of the chunk and checking if the
 * `INUSE_FLAG` bit is set.
 *
 * @param chunk A pointer to the memory chunk to be checked.
 * @return Non-zero if the chunk is in use, 0 otherwise.
 */
static inline int		chunk_inuse(t_malloc_chunk *chunk) {return ((chunk->mchunk_size & INUSE_FLAG) != 0); }

/**
 * @brief Sets the "in-use" flag for a given memory chunk.
 *
 * This function modifies the `mchunk_size` field of the provided
 * `t_malloc_chunk` structure to mark the chunk as being in use.
 * It achieves this by performing a bitwise OR operation with the
 * `INUSE_FLAG` constant.
 *
 * @param chunk Pointer to the memory chunk to be marked as in use.
 */
static inline void		set_inuse(t_malloc_chunk *chunk) { chunk->mchunk_size |= INUSE_FLAG; }

/**
 * @brief Marks a memory chunk as free by clearing the in-use flag in its size field.
 *
 * This function modifies the `mchunk_size` field of the given memory chunk
 * to indicate that the chunk is no longer in use. It does so by performing
 * a bitwise AND operation with the complement of the `INUSE_FLAG`.
 *
 * @param chunk A pointer to the memory chunk to be marked as free.
 */
static inline void		set_free(t_malloc_chunk *chunk) { chunk->mchunk_size &= ~INUSE_FLAG; }

/**
 * @brief Converts a pointer to a memory chunk into a pointer to the user-accessible memory.
 *
 * This function takes a pointer to a memory chunk (t_malloc_chunk) and returns
 * a pointer to the memory region that is accessible to the user. It calculates
 * the user memory address by adding the size of the t_malloc_chunk metadata
 * structure to the chunk pointer.
 *
 * @param chunk Pointer to the memory chunk (t_malloc_chunk).
 * @return Pointer to the user-accessible memory region.
 */
static inline void				*chunk_to_user(t_malloc_chunk *chunk) { return (void*)(((char*)chunk) + sizeof(t_malloc_chunk)); }


/**
 * @brief Converts a user pointer to its corresponding memory chunk pointer.
 *
 * This function takes a pointer to a user-allocated memory block and calculates
 * the address of the associated memory chunk metadata. The metadata is assumed
 * to be stored immediately before the user-accessible memory block.
 *
 * @param ptr Pointer to the user-allocated memory block.
 * @return Pointer to the associated memory chunk metadata (t_malloc_chunk).
 */
static inline t_malloc_chunk	*user_to_chunk(void* ptr){ return (t_malloc_chunk*)(((char*)ptr) - sizeof(t_malloc_chunk)); }

/*	
	Alignment	
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

/*	
	Allocator parameters	
*/

#define NFASTBINS	6
#define NBINS		64
#define MIN_CHUNK	(sizeof(t_malloc_chunk))

typedef struct s_bin_head	t_bin_head;
typedef struct s_arena		t_arena;

struct s_bin_head
{
	t_malloc_chunk	sentinel;
};

struct s_arena
{
	t_malloc_chunk	*top;
	t_malloc_chunk	*fastbins[NFASTBINS];
	t_bin_head		bins[NBINS];
};

static t_arena g_arena;

// typedef struct s_block
// {
// };



t_mallinfo g_mallinfo = {0};