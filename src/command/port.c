/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_port(int fd_server __attribute__((unused)), t_client *client __attribute__((unused)),
	char *home __attribute__((unused)), char *command __attribute__((unused)))
{
	printf("PORT\n");
	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	return 0;
}