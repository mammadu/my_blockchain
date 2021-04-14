#include "linked_list.h"

node* create_link_with_nid(int nid)
{
    node* link = malloc(sizeof(node));
    link->nid = nid;
    link->block_counter = 0;
    link->blocks = malloc(sizeof(char*) * MAGIC_NUMBER);
    return link;
}

//starts a link with memory allocated to receive a string later on
// node* create_link_with_max_string_length(int max_string_length)
// {
//     node* link = malloc(sizeof(node));
//     link->string = malloc(max_string_length * sizeof(char));
//     link->next = NULL;
//     return link;
// }

//adds a node before another node
node* prepend_link(node* new_link, node* head)
{
    new_link->next = head;
    head = new_link;
    return head;
}

//loops to very end of Linked list and adds passed as argument
void append_link(node* new_link, node* head)
{
    node* current = head;

    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_link;
    new_link->next = NULL;
}

//Insert node in between two nodes
void insert_link(node* new_link, node* previous_link)
{
    new_link->next = previous_link->next;
    previous_link->next = new_link;
}

//How many links are in a given linked list
//Prints string to console

//We might have to change this function to suit the needs of my_blockchain
//ls vs. ls -l
int read_list(node* head)
{  
    int index = 0;
    while (head != NULL)
    {
        index++;
        my_putnbr(head->nid);
        my_putstr("\n");
        head = head->next;
    }
    return index;
}

//prints on the stdout the file_name in case it exist on archive
// int read_list_on_demand(node* head, char* file_name)
// {  
//     int finding = 0;
//     while (head != NULL)
//     {
        
//         if(my_strcmp(head->bid, file_name) == 0)
//         {
//             my_putstr(head->bid);
//             my_putstr("\n");
//             finding += 1;
//         }

//         head = head->next;
//     }
//     if (finding == 0)
//     {
//         my_putstr("my_tar: ");
//         my_putstr(file_name);
//         my_putstr(": Not found in archive\n");
//     }

//     return finding;
// }


//return address of next link
node* return_next_link(node* link)
{
    node* next_link = link->next;
    return next_link;
}

void free_linked_list(node* head)
{
    node* temp;
    while (head != NULL)
    {
        int i = 0;
        temp = head;
        //free(temp->nid);
        //free(temp->nid);
        
        while(i < temp->block_counter)
        {
            free(temp->blocks[i]);
            i += 1;
        }    

        free(temp->blocks);    
        head = head->next;
        free(temp);
    }
}