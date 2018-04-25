/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include <string.h>
#include "my_ftp.h"

int command_dele(int fd_server __attribute__((unused)), t_client *client,
	char *home, char *command
)
{
	char **tab = NULL;

	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	tab = str_to_wordtab(command, ' ');
	if (!tab)
		return 0;
	if (tablen(tab) == 1)
		print_msg_to_client(client, "550");
	else {
		if (unlink(tab[1]) == -1)
			print_msg_to_client(client, "550");
		else
			print_msg_to_client(client, "250");
	}
	return 0;
}