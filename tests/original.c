/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:22:22 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/26 21:23:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_test t_test;

struct s_test
{
	int	a;
	unsigned long b;
	char	*c;
	t_test	*next;
};


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

int	main(void) {
	char *ptr = malloc(sizeof(t_test *) * 4);
	size_t assigned = sizeof(sizeof(t_test *) * 4);
	if (!ptr) {
		dprintf(1, "Estoy malito :c\n");
		return 1;
	}
	dprintf(1, "%s[ASSIGNED SIZE]%s size = %lu\n", BLUE, END, sizeof(ptr));
	dprintf(1, "%s[SIZE]%s size = %lu\n", BLUE, END, assigned);
	dprintf(1, "%s[SIZE]%s memory size malloc = %lu\n", BLUE, END, sizeof(ptr));
	if (sizeof(ptr) == assigned)
		dprintf(1, "%s[TEST]%s memory size %sOK%s\n", BLUE, END, GREEN, END);
	else
		dprintf(1, "%s[ERROR]%s memory size %sKO%s\n", RED, END, RED, END);
	dprintf(1, "%s[REFERENCE]%s number pointer = %p\n", BLUE, END, ptr);
	free(ptr);
}