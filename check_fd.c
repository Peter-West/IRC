/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:11:08 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:11:16 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->ret_sel > 0))
	{
		if (FD_ISSET(i, &e->readfds))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->writefds))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->readfds) || FD_ISSET(i, &e->writefds))
			e->ret_sel--;
		i++;
	}
}
