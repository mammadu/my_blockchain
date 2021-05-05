#ifndef my_blockchain_H
#define my_blockchain_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "my_c_functions.h"
#include "linked_list.h"

#define STDIN (0)
#define STDOUT (1)
#define STDERR (2)

#define ERROR_ONE (1)
#define ERROR_TWO (2)
#define ERROR_THREE (3)
#define ERROR_FOUR (4)
#define ERROR_FIVE (5)
#define ERROR_SIX (6)

#define DECIMAL_BASE (10)

typedef struct sync_status{
    char status;
    int nodes;
}sync_status;

char* readine();

int input_validation(char* string);

int select_option(int argc, char** argv, node* head, sync_status* status);

void prompt(sync_status* status);

void save_to_backup(char* input);

void print_error (int error);

int add_node(int argc, char** argv, node* head, sync_status* status);

int remove_node(int argc, char** argv, node* head, sync_status* status);

int add_block(int argc, char** argv, node* head, sync_status* status);

void mini_add_block(char* bid, node* head);

int sync_list(int argc, char** argv, node* head, sync_status* status);

blocks* sync_blocks(node* head);

int sync_status_checker(node* head, sync_status* status);

char* block_string_joint(blocks* head);


#endif