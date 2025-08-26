/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:38:49 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/26 23:56:15 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>

#ifndef and
	#define and &&
#endif

#ifndef or
	#define or ||
#endif

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

#define END	"\033[m"
#define RED	"\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW	"\033[1;33m"
#define BLUE	"\033[1;34m"
#define TUR	"\033[1;35m"
#define CYAN	"\033[1;36m"
#define ORANGE	"\033[38;5;208m"
#define PURPLE	"\033[38;5;128m"

/* error messages */
#define FT_LS "\033[1;31mft_ls: \033[m"
#define ERR_MALLOC "%serror trying to allocate memory `%s'\n"
#define ERR_INVALID "%sinvalid option -- '%s'\n"
#define ERR_OPEN "%scannot open directory '%s':%s\n"
#define WARNING_POINTER "%sWarning%s: func: %s pointer %s are null\n"

typedef struct s_test t_test;

struct s_test
{
	int	a;
	unsigned long b;
	char	*c;
	t_test	*next;
};

inline void print_bits(unsigned int num) {
    for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--) {
        dprintf(1,"%d", (num >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    dprintf(1, "\n");
}

#define ERROR_ASSIGNED "assigned is zero"
#define ERROR_PTR "the pointer is null"

int	print_status_malloc(size_t assigned, t_test *ptr) {
	if (!assigned || !ptr) {
		dprintf(1, "%s[ERROR]%s %s\n", RED, END, !assigned ? ERROR_ASSIGNED : ERROR_PTR);
		return (0);
	}
	dprintf(1, "%s[ASSIGNED SIZE]%s size = %lu\n", BLUE, END, sizeof(ptr));
	dprintf(1, "%s[SIZE]%s size = %lu\n", BLUE, END, assigned);
	dprintf(1, "%s[SIZE]%s memory size malloc = %lu\n", BLUE, END, sizeof(ptr));
	if (sizeof(ptr) == assigned)
		dprintf(1, "%s[TEST]%s memory size %sOK%s\n", BLUE, END, GREEN, END);
	else
		dprintf(1, "%s[ERROR]%s memory size %sKO%s\n", RED, END, RED, END);
	dprintf(1, "%s[REFERENCE]%s number pointer = %p\n", BLUE, END, ptr);
	return (1);
}