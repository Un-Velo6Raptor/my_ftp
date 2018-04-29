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
	command_user, command_pass, command_quit, command_noop, command_help,
	command_cwd, command_cdup, command_pwd, command_dele, command_pasv,
	command_port, command_list, command_retr, command_stor, NULL};

static const char *list_prefix[
	NB_COMMAND + 1] = {"USER", "PASS", "QUIT", "NOOP", "HELP", "CWD",
		"CDUP", "PWD", "DELE", "PASV", "PORT", "LIST", "RETR", "STOR",
		NULL};

int manage_command(int fd_server, t_client *client, char *home, char *command)
{
	int ret = -1;

	#include <stdio.h>
	if (!strlen(command))
		return 0;
	for (int idx = 0; list_prefix[idx]; ++idx) {
		if (!strncasecmp(list_prefix[idx], command,
			strlen(list_prefix[idx])))
			ret = list_command[idx](fd_server, client, home,
				command);
	}
	if (ret == -1) {
		print_msg_to_client(client, "500");
		ret = 0;
	}
	return ret;
}