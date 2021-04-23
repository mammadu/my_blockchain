#ifndef linked_list_H
#define linked_list_H
#include <stdio.h>
#include <stdlib.h>
#include "my_c_functions.h"

typedef struct blocks_list
{
    char* bid;
    struct blocks_list* next;
}blocks;

typedef struct node
{
    int nid;
    blocks* blocks;
    struct node* next;
}node;

node* create_link_with_nid(int nid);

// node* create_link_with_max_string_length(int max_string_length);

node* prepend_link(node* new_link, node* head);

void append_link(node* new_link, node* head);

void remove_next_link(node* prior_link);

void insert_link(node* new_link, node* previous_link);

int read_list(node* head);

node* return_next_link(node* link);

void free_block_list(blocks* head);

void free_linked_list(node* head);

blocks* create_block_with_bid(char* bid);

int check_bid(blocks* head, char* bid);

void append_block(blocks* new_link, blocks* head);

int block_list_length(blocks* head);

void free_sync_list(blocks* head);

//int read_list_on_demand(node* head, char* file_name);

#endif