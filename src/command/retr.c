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

static void exec_command(t_client *client, int client_fd, char *command)
{
	int saved_stdout = dup(1);

	dup2(client_fd, 1);
	if (system(command) != 0) {
		dup2(saved_stdout, 1);
		print_msg_to_client(client, "550");
	} else
		dup2(saved_stdout, 1);
	close_reset_socket(client);
}

static int retr_pasv(t_client *client, char **tab)
{
	char command[MAX_LENGTH_COMMAND] = "cat ";
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);
	int client_fd;

	strcat(command, tab[1]);
	print_msg_to_client(client, "150");
	client_fd = accept(client->data_mng.fd_socket,
		(struct sockaddr *)&s_in_client, &s_in_size);
	if (client_fd == -1) {
		print_msg_to_client(client, "425");
		return 0;
	}
	exec_command(client, client_fd, command);
	close(client_fd);
	print_msg_to_client(client, "226");
	return 0;
}

static int retr_port(t_client *client, char **tab)
{
	char command[MAX_LENGTH_COMMAND] = "cat ";
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);

	strcat(command, tab[1]);
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
	exec_command(client, client->data_mng.fd_socket, command);
	print_msg_to_client(client, "226");
	return 0;
}

int command_retr(int fd_server __attribute__((unused)), t_client *client,
	char *home __attribute__((unused)), char *command
)
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
	if (!tab || tablen(tab) != 2)
		print_msg_to_client(client, "550");
	else if (client->mode == TRUE)
		retr_pasv(client, tab);
	else
		retr_port(client, tab);
	free_tab(tab);
	return 0;
}