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
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Accept
#include <netinet/in.h>
#include <arpa/inet.h>

static int print_on_client_ip(char *msg, int fd_client, char const *ip)
{
	(void)ip;

	if (write(fd_client, msg, strlen(msg)) == -1)
		return (84);
	return 0;
}

static int listen_to_server(int fd, int port __attribute__((unused)))
{
	if (listen(fd, 42) == 1)
		return (84);
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);
	int client_fd;
	char *client_ip;

	client_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_size);
	if (client_fd == -1) {
		fprintf(stderr, "Can't accept the client\n");
		return 84;
	}
	client_ip = inet_ntoa(s_in_client.sin_addr);
	printf("client IP: %s\n", client_ip);
	print_on_client_ip("Hello world\n", client_fd, client_ip);
	if (close(client_fd))
		return 84;
	return 0;
}

int main(int argc, char **argv)
{
	struct protoent *pe;
	struct sockaddr_in s_in;
	int fd;
	int port;

	if (argc != 2)
		return 84;
	pe = getprotobyname("TCP");
	port = atoi(argv[1]);

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;

	if (!pe)
		return 84;
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return 84;
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(fd);
		return 84;
	}
	int ret = listen_to_server(fd, port);
	close(fd);
	return ret;
}