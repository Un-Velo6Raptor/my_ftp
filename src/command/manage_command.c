/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include <stdlib.h>
#include "my_ftp.h"

static int (*list_command[NB_COMMAND])(int, t_client *, char *, char *) = {
	command_user,
	command_pass,
	command_quit,
	command_noop,
	command_help,
	command_cwd,
	NULL
};

static const char *list_prefix[NB_COMMAND + 1] = {
	"USER",
	"PASS",
	"QUIT",
	"NOOP",
	"HELP",
	"CWD",
	NULL
};

static enum bool is_logged(t_client *client) {
	enum bool ret = FALSE;

	if (client->username == TRUE && client->password == TRUE)
		ret = TRUE;
	else
		print_msg_to_client(client, "530");
	return ret;
}

// ret == -1: Never used
int manage_command(int fd_server, t_client *client, char *home, char *command)
{
	int ret = -1;

	for (int idx = 0; list_prefix[idx] ; ++idx) {
		if (!strncmp(list_prefix[idx], command, strlen(list_prefix[idx])))
			ret = list_command[idx](fd_server, client, home, command);
	}
	if (ret == -1 && is_logged(client))
		print_msg_to_client(client, "500");
	return ret;
}