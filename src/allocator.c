/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:25:34 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/24 19:32:39 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc_internal.h>

bool bins_init_once(void) {
    static inited = 0;

    if (inited)
        return false;
    for (int i = 0; i < NFASTBINS; i++)
        g_arena.fastbins[i] = NULL;
    for (int i = 0; i < NBINS; i++) {
        
    }
    g_arena.top = NULL;
    inited = true;
    return (true);
}