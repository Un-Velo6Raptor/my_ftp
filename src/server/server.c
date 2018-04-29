/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include "my_ftp.h"

static int create_proccess_client(int fd_server, t_client *client, char *path,
	struct sockaddr_in *s_in_client __attribute__((unused)))
{
	int ret = 0;

	client->pid = fork();
	if (client->pid < 0 || !client->data_mng.ip_client) {
		fprintf(stderr, "Error: Can't fork\n");
		client->is_used = FALSE;
		ret = 84;
	} else if (client->pid == 0) {
		print_msg_to_client(client, "220");
		init_manage_command(fd_server, client, path);
		print_msg_to_client(client, "221");
		reset_client(client);
		exit(1);
	}
	return ret;
}

static int accept_client_connection(int fd_server, char *path,
	t_client *list_client
)
{
	struct sockaddr_in s_in;
	socklen_t s_in_size = sizeof(s_in);
	int client_fd;
	int current_client = 0;
	int ret = 0;

	client_fd = accept(fd_server, (struct sockaddr *)&s_in, &s_in_size);
	if (client_fd == -1 ||
		getsockname(client_fd, (struct sockaddr *)&s_in, &s_in_size) ==
			-1) {
		fprintf(stderr, "Error: Can't accept the client\n");
		ret = 84;
	} else {
		current_client = assign_block_client(list_client, client_fd);
		list_client[current_client].data_mng.ip_client = inet_ntoa(
			s_in.sin_addr);
		ret = create_proccess_client(fd_server,
			&list_client[current_client], path, &s_in);
	}
	return ret;
}

static int wait_client_proccess(t_client *list_client)
{
	int ret = 0;
	int status = 0;

	for (int idx = 0; idx < NB_CLIENT_MAX + 1; ++idx) {
		if (list_client[idx].is_used == TRUE) {
			waitpid(list_client[idx].pid, &status, WNOHANG);
			if (status != 0) {
				reset_client(&list_client[idx]);
			}
		}
	}
	return ret;
}

int loop_client_connection(int fd_server, char *path)
{
	static t_client list[NB_CLIENT_MAX + 1];
	int ret = 0;
	fd_set readfs;
	struct timeval wait;

	wait.tv_usec = 1000;
	init_list_client(list);
	while (!ret) {
		FD_ZERO(&readfs);
		FD_SET(fd_server, &readfs);
		if (select(fd_server + 1, &readfs, NULL, NULL, &wait) == -1) {
			ret = 84;
			break;
		}
		if (FD_ISSET(fd_server, &readfs))
			ret = accept_client_connection(fd_server, path, list);
		wait_client_proccess(list);
	}
	close_all_client(list);
	return ret;
}