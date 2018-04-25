/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_help(int fd_server __attribute__((unused)), t_client *client __attribute__((unused)),
	char *home __attribute__((unused)), char *command __attribute__((unused)))
{
	if (client->username != TRUE || client->password != TRUE) {
		print_msg_to_client(client, "530");
	} else {
		write_msg(client->fd, "214-The following commands are recognized.\r\n");
		write_msg(client->fd, " ABOR ACCT ALLO APPE CDUP CWD  DELE EPRT EPSV FEAT HELP LIST MDTM MKD\r\n");
		write_msg(client->fd, " MODE NLST NOOP OPTS PASS PASV PORT PWD  QUIT REIN REST RETR RMD  RNFR\r\n");
		write_msg(client->fd, " RNTO SITE SIZE SMNT STAT STOR STOU STRU SYST TYPE USER XCUP XCWD XMKD\r\n");
		write_msg(client->fd, " XPWD XRMD\r\n");
		print_msg_to_client(client, "214");
	}

	return 0;
}