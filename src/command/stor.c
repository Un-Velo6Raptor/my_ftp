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
#include <stdlib.h>
#include <fcntl.h>
#include "my_ftp.h"

void close_reset_socket(t_client *client)
{
	client->mode = UNKNOWN;
	setsockopt(client->data_mng.fd_socket, SOL_SOCKET, SO_REUSEADDR,
		&(int){1}, sizeof(int));
	close(client->data_mng.fd_socket);
	client->data_mng.fd_socket = 0;
}

static int read_socket(t_client *client, int fd, char *file)
{
	int fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	char buffer[1024];
	int nb_read = 0;

	if (fd_file == -1) {
		print_msg_to_client(client, "550");
		return 1;
	}
	do {
		nb_read = read(fd, buffer, 1023);
		if (nb_read < 0) {
			close(fd_file);
			print_msg_to_client(client, "550");
			return 1;
		}
		buffer[nb_read] = '\0';
		write(fd_file, buffer, strlen(buffer));
	} while (nb_read > 0);
	close(fd_file);
	return 0;
}

static int stor_pasv(t_client *client, char *file)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);
	int client_fd;
	int ret = 0;

	print_msg_to_client(client, "150");
	client_fd = accept(client->data_mng.fd_socket,
		(struct sockaddr *)&s_in_client, &s_in_size);
	if (client_fd == -1) {
		print_msg_to_client(client, "425");
		return 0;
	}
	ret = read_socket(client, client_fd, file);
	close_reset_socket(client);
	close(client_fd);
	if (!ret)
		print_msg_to_client(client, "226");
	return 0;
}

static int stor_port(t_client *client, char *file)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);

	client->data_mng.fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client->data_mng.fd_socket == -1)
		return 0;
	s_in_client.sin_family = AF_INET;
	s_in_client.sin_addr.s_addr = inet_addr(client->data_mng.ip_server);
	s_in_client.sin_port = htons(client->data_mng.port_server);
	print_msg_to_client(client, "150");
	if (connect(client->data_mng.fd_socket, &s_in_client, s_in_size) ==
		-1) {
		print_msg_to_client(client, "425");
		return 0;
	}
	if (!read_socket(client, client->data_mng.fd_socket, file))
		print_msg_to_client(client, "226");
	close_reset_socket(client);
	return 0;
}

int command_stor(int fd_server __attribute__((unused)), t_client *client,
	char *home __attribute__((unused)), char *command
)
{
	char **tab = NULL;

	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	} else if (client->mode == UNKNOWN) {
		print_msg_to_client(client, "425");
		return 0;
	}
	tab = str_to_wordtab(command, ' ');
	if (!tab || tablen(tab) != 2)
		print_msg_to_client(client, "550");
	else if (client->mode == TRUE)
		stor_pasv(client, tab[1]);
	else
		stor_port(client, tab[1]);
	free_tab(tab);
	return 0;
}