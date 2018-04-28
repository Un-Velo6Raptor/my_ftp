/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_pwd(int fd_server __attribute__((unused)), t_client *client,
	char *home, char *command __attribute__((unused)))
{
	char tmp[MAX_LENGTH_COMMAND + 1] = "\0";

	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	getcwd(tmp, MAX_LENGTH_COMMAND);
	if (!tmp) {
		print_msg_to_client(client, "530");
		return 0;
	}
	if (tmp[strlen(tmp) - 1] != '/')
		strcat(tmp, "/");
	write_msg(client->fd, "257 \"");
	write_msg(client->fd, &tmp[strlen(home) - 1]);
	write_msg(client->fd, "\"\r\n");
	return 0;
}