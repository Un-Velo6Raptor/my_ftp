/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_pass(int fd_server __attribute__((unused)), t_client *client,
	char *home __attribute__((unused)), char *command)
{
	char **tab = NULL;

	if (client->username == TRUE && client->password == TRUE) {
		print_msg_to_client(client, "230");
	} else if (client->username != TRUE) {
		print_msg_to_client(client,
			(client->username == FALSE) ? "503" : "530");
	} else {
		tab = str_to_wordtab(command, ' ');
		if (!tab)
			return 0;
		print_msg_to_client(client, "230");
		client->password = TRUE;
		free_tab(tab);
	}
	return 0;
}