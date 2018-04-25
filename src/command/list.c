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

static int list_pasv(t_client *client, char **tab)
{
	char command[MAX_LENGTH_COMMAND] = "ls -la ";
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);
	int client_fd;
	int saved_stdout = dup(1);

	if (tablen(tab) > 1)
		strcat(command, tab[1]);
	client_fd = accept(client->data_mng.fd_socket, (struct sockaddr *)&s_in_client,
		&s_in_size);
	dup2(client_fd, 1);
	system(command);
	dup2(saved_stdout, 1);
	client->mode = UNKNOWN;
	setsockopt(client->data_mng.fd_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1},
		sizeof(int));
	close(client->data_mng.fd_socket);
	close(client_fd);
	client->data_mng.fd_socket = 0;
	return 0;
}

static int list_port(t_client *client, char **command)
{
	return 0;
}

int command_list(int fd_server __attribute__((unused)),
	t_client *client,
	char *home __attribute__((unused)),
	char *command)
{
	char **tab = NULL;

	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	if (client->mode == UNKNOWN) {
		print_msg_to_client(client, "425");
		return 0;
	}
	tab = str_to_wordtab(command, ' ');
	if (!tab)
		return 0;
	if (client->mode == TRUE)
		list_pasv(client, tab);
	else
		list_port(client, tab);
	print_msg_to_client(client, "150");
	print_msg_to_client(client, "226");
	free_tab(tab);
	return 0;
}