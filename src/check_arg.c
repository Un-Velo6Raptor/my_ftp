/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_ftp.h"

static void print_help(void)
{
	printf("USAGE:  ./server port path\n");
	printf("        port  is the port number on which "
	       "the server socket listens\n");
	printf("        path  is the path to the home "
	       "directory for the Anonymous user\n");
}

static int is_a_dir(char *path)
{
	struct stat sb;
	int ret = 0;

	if (lstat(path, &sb) == -1) {
		fprintf(stderr, "Error: Path doesn't exist\n");
		ret = 84;
	} else if (!S_ISDIR(sb.st_mode)) {
		fprintf(stderr, "Error: This is not a directory\n");
		ret = 84;
	}
	return ret;
}

int check_arg(int argc, char **argv)
{
	int ret = 0;

	if (argc == 2 && !strcmp(argv[1], "-help"))
		print_help();
	else if (argc == 3 && atoi(argv[1]) > 0 && !is_a_dir(argv[2]))
		ret = init_and_launch_server(atoi(argv[1]), argv[2]);
	else {
		fprintf(stderr, "USAGE:  ./server port path\n");
		ret = 84;
	}
	return ret;
}