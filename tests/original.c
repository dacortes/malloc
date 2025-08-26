/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:22:22 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/26 23:58:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>
#include <stdlib.h>

int	main(void) {
	t_test *ptr = (t_test *)malloc(sizeof(t_test *) * 4);
	size_t assigned = sizeof(sizeof(t_test *) * 4);
	if (!print_status_malloc(assigned, ptr))
		return (1);
	free(ptr);
}