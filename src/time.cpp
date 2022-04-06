/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:17:48 by flohrel           #+#    #+#             */
/*   Updated: 2021/12/11 16:31:43 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static t_chrono	g_chrono = { 0, 0 };

/**
 * @brief Function to call right before execution
 * 
 */
void	chrono_start(void)
{
	g_chrono.start = clock();
}

/**
 * @brief Function to call right after execution
 * 
 */
void	chrono_end(void)
{
	g_chrono.end = clock();
}

/**
 * @brief Display execution time for every function listed
 * 
 */
float	get_execution_time(void)
{
	return (((float)(g_chrono.end - g_chrono.start) * 1000) / CLOCKS_PER_SEC);
}