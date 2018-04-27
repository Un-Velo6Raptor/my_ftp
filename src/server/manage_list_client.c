/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include "my_ftp.h"

void init_list_client(t_client *list_empty)
{
	for (int idx = 0; idx < NB_CLIENT_MAX + 1; ++idx) {
		list_empty[idx].is_used = FALSE;
		list_empty[idx].username = FALSE;
		list_empty[idx].password = FALSE;
		list_empty[idx].fd = 0;
		list_empty[idx].pid = 0;
		list_empty[idx].data_mng.ip_client = NULL;
		list_empty[idx].data_mng.port_server = 0;
		list_empty[idx].data_mng.fd_socket = 0;
		list_empty[idx].data_mng.ip_server = NULL;
		list_empty[idx].data_mng.ip_client = NULL;
		list_empty[idx].mode = UNKNOWN;
	}
}

int assign_block_client(t_client *list_client, int client_fd)
{
	int ret = 0;

	for (int idx = 0; idx < NB_CLIENT_MAX + 1; ++idx) {
		if (list_client[idx].is_used == FALSE) {
			list_client[idx].is_used = TRUE;
			list_client[idx].fd = client_fd;
			ret = idx;
			break;
		}
	}
	return ret;
}

void reset_client(t_client *client)
{
	client->is_used = FALSE;
	client->username = FALSE;
	client->password = FALSE;
	if (client->mode != UNKNOWN && client->data_mng.fd_socket > 0) {
		close(client->data_mng.fd_socket);
	}
	client->data_mng.fd_socket = 0;
	client->data_mng.ip_client = NULL;
	client->data_mng.ip_server = NULL;
	shutdown(client->fd, SHUT_WR);
	close(client->fd);
	client->mode = UNKNOWN;
}

void close_all_client(t_client *list_client)
{
	for (int idx = 0; idx < NB_CLIENT_MAX + 1; ++idx) {
		if (list_client[idx].is_used == TRUE) {
			kill(list_client[idx].pid, SIGINT);
			print_msg_to_client(&list_client[idx], "426");
			shutdown(list_client[idx].fd, SHUT_WR);
			close(list_client[idx].fd);
		}
		list_client[idx].is_used = FALSE;
		list_client[idx].username = FALSE;
		list_client[idx].password = FALSE;
		if (list_client[idx].mode != UNKNOWN &&
			list_client[idx].data_mng.fd_socket > 0)
			close(list_client[idx].data_mng.fd_socket);
		list_client[idx].data_mng.fd_socket = 0;
		list_client[idx].data_mng.ip_client = NULL;
		list_client[idx].data_mng.ip_server = NULL;
		list_client[idx].mode = UNKNOWN;
	}
}
