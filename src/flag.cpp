/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:27:25 by flohrel           #+#    #+#             */
/*   Updated: 2022/01/16 02:34:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

int32_t		set_flag(int32_t *field, int32_t flag)
{
	return ((*field) |= flag);
}

int32_t		check_flag(int32_t field, int32_t flag)
{
	return (field & flag);
}

void	clear_flag(int32_t *field, int32_t flag)
{
	(*field) &= ~(flag);
}
