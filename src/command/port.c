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

static int check_car_command(char *command) {
	for (int idx = 0; command[idx] != '\0' ; ++idx) {
		if ((command[idx] < '0' || command[idx] > '9') && command[idx] != ',')
			return 1;
	}
	return 0;
}

static char *get_ip_user(char *command, int *port)
{
	char *ip_result = malloc(sizeof(char) * 16);
	char **tab = str_to_wordtab(&command[5], ',');

	if (!ip_result || !tab)
		return NULL;
	if (tablen(tab) != 6) {
		free_tab(tab);
		return NULL;
	}
	for (int idx = 0; tab[idx] ; ++idx) {
		if (atoi(tab[idx]) < 0 || atoi(tab[idx]) > 256) {
			free_tab(tab);
			return NULL;
		}
	}
	strcpy(ip_result, tab[0]);
	strcat(ip_result, ".");
	strcat(ip_result, tab[1]);
	strcat(ip_result, ".");
	strcat(ip_result, tab[2]);
	strcat(ip_result, ".");
	strcat(ip_result, tab[3]);
	*port = atoi(tab[4]) * 256 + atoi(tab[5]);
	return ip_result;
}

static int create_new_socket(t_client *client, char *command, int fd_server)
{
	client->data_mng.port_server = 0;
	client->data_mng.ip_server = get_ip_user(command, &client->data_mng.port_server);

	if (!client->data_mng.port_server || !client->data_mng.ip_server) {
		return 1;
	}
	return 0;
}

int command_port(int fd_server __attribute__((unused)),
	t_client *client __attribute__((unused)),
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
	if (check_car_command(&command[5]) || create_new_socket(client, command, fd_server))
		print_msg_to_client(client, "500");
	else {
		print_msg_to_client(client, "200");
		client->mode = FALSE;
	}
	return 0;
}