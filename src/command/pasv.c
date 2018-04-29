/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "my_ftp.h"

static void reset_sockaddr(struct sockaddr_in *s_in)
{
	s_in->sin_family = AF_INET;
	s_in->sin_port = htons(0);
	s_in->sin_addr.s_addr = INADDR_ANY;
}

static int bind_and_get_ip_server(t_client *client, int fd_server)
{
	struct sockaddr_in s_in;
	socklen_t len;

	len = sizeof(socklen_t);
	reset_sockaddr(&s_in);
	if (bind(client->data_mng.fd_socket, (struct sockaddr *)&s_in,
		sizeof(s_in)) == -1 || listen(client->data_mng.fd_socket, 1)) {
		close(client->data_mng.fd_socket);
		return 84;
	} else {
		reset_sockaddr(&s_in);
		if (getsockname(client->data_mng.fd_socket,
			(struct sockaddr *)&s_in, &len) == -1) {
			close(client->data_mng.fd_socket);
			return 84;
		}
		client->data_mng.port_client = ntohs(s_in.sin_port);
	}
	return 0;
}

static int create_new_socket(t_client *client, int fd_server)
{
	struct protoent *pe = getprotobyname("TCP");
	int fd_socket = 0;

	if (!pe)
		return 84;
	fd_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd_socket == 0)
		return 84;
	client->data_mng.fd_socket = fd_socket;
	if (bind_and_get_ip_server(client, fd_server))
		return 84;
	return 0;
}

static void display_pasv_mode(t_client *client)
{
	char **tmp = str_to_wordtab(client->data_mng.ip_client, '.');
	char port[MAX_LENGTH_COMMAND];

	sprintf(port, "%d,%d).\r\n", client->data_mng.port_client / 256,
		client->data_mng.port_client % 256);
	if (!tmp || !port)
		print_msg_to_client(client, "552");
	write_msg(client->fd, "227 Entering Passive Mode (");
	for (int idx = 0; tmp[idx]; ++idx) {
		write_msg(client->fd, tmp[idx]);
		write_msg(client->fd, ",");
	}
	write_msg(client->fd, port);
	free_tab(tmp);
}

int command_pasv(int fd_server, t_client *client,
	char *home __attribute__((unused)),
	char *command __attribute__((unused)))
{
	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	if (client->mode != UNKNOWN && client->data_mng.fd_socket > 0) {
		if (setsockopt(client->data_mng.fd_socket, SOL_SOCKET,
			SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
			fprintf(stderr, "Can't close old socket\n");
		close(client->data_mng.fd_socket);
		client->data_mng.fd_socket = 0;
	}
	if (create_new_socket(client, fd_server))
		print_msg_to_client(client, "552");
	else {
		display_pasv_mode(client);
		client->mode = TRUE;
	}
	return 0;
}