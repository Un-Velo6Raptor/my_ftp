/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include "my_ftp.h"

int command_user(int fd_server __attribute__((unused)), t_client *client,
	char *home __attribute__((unused)), char *command)
{
	char **tab = NULL;

	if (client->username == TRUE && client->password == TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	tab = str_to_wordtab(command, ' ');
	if (!tab)
		return 0;
	if (tablen(tab) >= 2) {
		client->username =
			(!strcasecmp(tab[1], "Anonymous")) ? TRUE : UNKNOWN;
		print_msg_to_client(client, "331");
	} else
		print_msg_to_client(client, "530");
	free_tab(tab);
	return 0;
}