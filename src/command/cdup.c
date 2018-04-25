/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_cdup(int fd_server __attribute__((unused)), t_client *client,
	char *home, char *command __attribute__((unused)))
{
	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	command_cwd(fd_server, client, home, "CWD ..");
	return 0;
}