/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

static int verify_path(t_client *client, char *home, char *dir, char *new_dir)
{
	if (strncmp(home, new_dir, strlen(home) - 1))
		chdir(home);
	return 1;
}

static int check_change_directory(t_client *client, char *home, char *to)
{
	char actual_dir[MAX_LENGTH_COMMAND + 1] = "\0";
	char new_dir[MAX_LENGTH_COMMAND + 1] = "\0";

	getcwd(actual_dir, MAX_LENGTH_COMMAND);
	if (actual_dir == NULL) {
		print_msg_to_client(client, "550");
		return 0;
	}
	strcat(actual_dir, "/");
	if (chdir(to) == -1) {
		print_msg_to_client(client, "550");
		return 0;
	}
	getcwd(new_dir, MAX_LENGTH_COMMAND);
	if (new_dir == NULL) {
		print_msg_to_client(client, "550");
		return 0;
	} else if (strlen(new_dir) > 0 && new_dir[strlen(new_dir) - 1] != '/')
		strcat(new_dir, "/");
	return verify_path(client, home, actual_dir, new_dir);
}

int command_cwd(int fd_server __attribute__((unused)), t_client *client,
	char *home, char *command
)
{
	char **tab = NULL;

	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
		return 0;
	}
	tab = str_to_wordtab(command, ' ');
	if (tablen(tab) == 1)
		print_msg_to_client(client, "550");
	else if (tablen(tab) && check_change_directory(client, home, tab[1]) == 1)
		print_msg_to_client(client, "250");
	return 0;
}