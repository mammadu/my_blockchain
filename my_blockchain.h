#ifndef my_blockchain_H
#define my_blockchain_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "my_c_functions.h"

typedef struct sync_status{
    char status;
    int nodes;
}sync_status;

char* readine();

int input_validation(char* string);

int select_option(int argc, char** argv);

void prompt(sync_status* status);

void save_to_backup(char* input);

#endif