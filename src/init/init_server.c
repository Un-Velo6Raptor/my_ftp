/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my_ftp.h"

static int init_listen(int fd_server)
{
	int ret = 0;

	if (listen(fd_server, 100)) {
		fprintf(stderr, "Error: Can't init listen\n");
		ret = 84;
	}
	return ret;
}

static int init_bind(int fd_server, int port)
{
	struct sockaddr_in s_in;
	int ret = 0;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd_server, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		fprintf(stderr, "Error: Can't bind the socket\n");
		ret = 84;
	}
	return ret;
}

int init_and_launch_server(int port, char *path)
{
	struct protoent *pe = getprotobyname("TCP");
	int fd_server = 0;
	int ret = 84;

	if (!pe) {
		fprintf(stderr, "Error: Can't getprotobyname\n");
		return 84;
	}
	fd_server = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd_server == -1)
		fprintf(stderr, "Error: Can't create the socket\n");
	if (!init_bind(fd_server, port) && !init_listen(fd_server))
		printf("Start loop fork accept client\n");
	close(fd_server);
	return ret;
}