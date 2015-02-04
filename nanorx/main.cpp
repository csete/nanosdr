/*
 * Copyright (c) 2015, Alexandru Csete
 * All rights reserved.
 *
 * This software is licensed under the terms and conditions of the
 * Simplified BSD License. See license.txt for details.
 *
 */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int      keep_running = 1;

void signal_handler(int signo)
{
    fprintf(stderr, "\nCaught signal: %d\n", signo);

    keep_running = 0;
}


int main(int argc, char **argv)
{
    int             exit_code = EXIT_FAILURE;

    // setup signal handler
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        printf("Warning: Can't catch SIGINT\n");
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        printf("Warning: Can't catch SIGTERM\n");


    while (keep_running)
    {
        usleep(100000);
    }

    fprintf(stderr, "Shutting down...\n");
    exit_code = EXIT_SUCCESS;

  cleanup:

    exit(exit_code);
}
