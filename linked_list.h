#ifndef linked_list_H
#define linked_list_H
#include <stdio.h>
#include <stdlib.h>
#include "my_c_functions.h"

typedef struct blocks_list
{
    int bid;
    struct blocks_list* next;
}blocks;

typedef struct node
{
    int nid;
    int block_counter;
    blocks* blocks;
    struct node* next;
}node;

node* create_link_with_nid(int nid);

// node* create_link_with_max_string_length(int max_string_length);

node* prepend_link(node* new_link, node* head);

void append_link(node* new_link, node* head);

void insert_link(node* new_link, node* previous_link);

int read_list(node* head);

node* return_next_link(node* link);

void free_linked_list(node* head);

//int read_list_on_demand(node* head, char* file_name);

#endif