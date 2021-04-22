#include "my_blockchain.h"


//readline
//read a character
//combine into the return_string
//continue reading characters until read "\n"
//return return_str

//quick commit

char* readline(int input_source)
{
    char* str = malloc(sizeof(char)); //str is malloc'd so we can free it later
    str[0] = '\0';
    char* character = malloc(sizeof(char));
    int characters_read = read(input_source, character, 1);
    // printf("characters_read = %d\n", characters_read);
    // printf("the character is %s\n", character);
    // printf("the value of character is %d\n", character[0]);

    while (characters_read > 0 && character[0] != '\n')
    {
        char* temp = str; //we make a temporay string to free everything stored at that location.
        str = combine_strings(temp, character);
        free(temp);
        // free(character);
        // char* character = malloc(sizeof(char));
        int characters_read = read(input_source, character, 1);
        // printf("the character is %s\n", character);
        // printf("the value of character is %d\n", character[0]);
        // printf("str is %s\n", str);
    }
    free(character);

    return str; //if no characters are passed, str == "\0"
}

int input_validation(char* string)
{
    int validation = space_validator(string);
    return validation;
}

/*
int sync_evaluation(node* head, sync_status* status)
{
    //we need to check for difference
    //
}
*/

int check_node_existence(node* head, int nid)
{
    while(head != NULL)
    {
        if (head->nid == nid)
            return ERROR_TWO;
        head = head->next;
    }
    return 0;
}

int add_node(int argc, char** argv, node* head, sync_status* status)
{
    if (my_str_is_numeric(argv[2]) == 0)
        return ERROR_SIX;

    int nid = my_atoi_base(argv[2] , DECIMAL_BASE);

    if (check_node_existence(head, nid) == ERROR_TWO)
        return ERROR_TWO;

    node* new_link = create_link_with_nid(nid);

    if (status->nodes == 0)
    {
        head->nid = new_link->nid;
        head->blocks = new_link->blocks;
        head->next = new_link->next;
        free(new_link);
    }
    else
    {
        append_link(new_link, head);
    }

    status->nodes += 1;

    return 0;
}

// int rm_node(int argc, char** argv, node** address_of_head, sync_status* status)
// {
//     int i = 2;

//      node* original_head = address_of_head[0];

//     if (argv[i][0] == '*')
//     {
//         free_linked_list(original_head);
//         return 0;
//     }

//     while (i < argc)
//     {
//         while(address_of_head[0] != NULL)
//         {
//             int node_to_remove = my_atoi_base(argv[i], DECIMAL_BASE);
//             if (address_of_head[0]->nid == node_to_remove) //remove head
//             {
//                 // printf("[debug] address of head = %p\n", original_head);
//                 // printf("[debug] address of head->next = %p\n", original_head->next);
//                 node* temp_to_delete = address_of_head[0];
//                 address_of_head[0] = address_of_head[0]->next;
//                 temp_to_delete->next = NULL;
//                 free_linked_list(temp_to_delete);
//                 original_head = address_of_head[0];
//                 // printf("[debug] address of head = %p\n", original_head);
//             }
//             else if (address_of_head[0]->next != NULL && address_of_head[0]->next->nid == node_to_remove)
//             {
//                 remove_next_link(address_of_head[0]);
//             }
//             else
//             {
//                 address_of_head[0] = address_of_head[0]->next;
//             }
//         }
//         address_of_head[0] = original_head;
//         i++;
//     }
//     address_of_head[0] = original_head;
//     // read_list(address_of_head[0]);
//     // printf("[debug] address of head = %p\n", original_head);
//     // printf("[debug] head nid = %d\n", address_of_head[0]->nid);
//     return 0;
// }

int rm_node(int argc, char** argv, node* head, sync_status* status)
{
    int i = 2;

    node* original_head = head;

    if (argv[i][0] == '*')
    {
        free_linked_list(head);
        return 0;
    }

    while (i < argc)
    {
        while(head != NULL)
        {
            int node_to_remove = my_atoi_base(argv[i], DECIMAL_BASE);
            if (head->nid == node_to_remove) //remove head
            {
                node* temp_to_free = head->next; //store next link in variable

                //make head point to next link items
                head->nid = head->next->nid;
                head->blocks = head->next->blocks;
                head->next = head->next->next;

                //free next link
                temp_to_free->blocks = NULL;
                temp_to_free->next = NULL;
                free_linked_list(temp_to_free);
            }
            else if (head->next != NULL && head->next->nid == node_to_remove)
            {
                remove_next_link(head);
            }
            else
            {
                head = head->next;
            }
        }
        head = original_head;
        i++;
    }
    return 0;
}

int ls_l(int argc, char** argv, node* head, sync_status* status)
{
    while(head != NULL)
    {
        blocks* temp = head->blocks;
        if (!argv[1])
        {
            printf("%d\n", head->nid);
        }
        else if(my_strcmp("-l", argv[1]) == 0)
        {
            if (head->blocks == NULL)
            {
                printf("%d:\n", head->nid);
            }
            while (head->blocks != NULL)
            {
                printf("%d: %s,\n", head->nid, head->blocks->bid);
                head->blocks = head->blocks->next; 
            }
        }
        else
        {
            return ERROR_SIX;
        }
        head->blocks = temp;
        head = head->next;
    }
    return 0;
}

int remove_block(int argc, char** argv, node* head, sync_status* status)
{
    //rm block bid... remove the bid identified blocks from all nodes where these blocks are present.

    char* bid = my_strdup(argv[2]);
    // read_list(head);
    
    int i = 0;
    while(head != NULL)
    {
        // printf("i = %d\n", i);
        // printf("head->nid = %d\n", head->nid);
        // printf("[DEBUG] head->blocks = %p\n", head->blocks);
        if(head->blocks != NULL && my_strcmp(head->blocks->bid, bid) == 0) //case if the head of the block list is == bid
        {
            blocks* temp0 = head->blocks;
            head->blocks = head->blocks->next;
            free(temp0->bid);
            free(temp0);
        }

        blocks* original_head_block = head->blocks;
        while(head->blocks != NULL) //case if bid == consequent blocks
        {
            blocks* temp;
            
            if(head->blocks->next != NULL && my_strcmp(head->blocks->next->bid, bid) == 0)
            {
                temp = head->blocks->next->next;     
                free(head->blocks->next->bid);
                free(head->blocks->next);
                head->blocks->next = temp;
                continue;
            }
            
            head->blocks = head->blocks->next;
        }

        head->blocks = original_head_block;

        head = head->next;
        i++;
    }

    free(bid);
    return 0;
}

void mini_add_block(char* bid, node* head)
{
    //int check_bid(blocks* head, char* bid)

    if (head->blocks != NULL && check_bid(head->blocks, bid) == 0)
    {
        //add block
        blocks* new_link = malloc(sizeof(blocks));
        new_link->bid = my_strdup(bid);
        append_block(new_link, head->blocks);
    }
    else if(head->blocks == NULL && check_bid(head->blocks, bid) == 0)
    {
        head->blocks = malloc(sizeof(blocks));
        head->blocks->bid = my_strdup(bid);
        head->blocks->next = NULL;
    }
    else
    {
        print_error(ERROR_THREE);
        printf("@ node %d\n", head->nid);
    }

}


int add_block(int argc, char** argv, node* head, sync_status* status)
{
    //add block bid nid
    int node_existence = 0;  
    char* bid = my_strdup(argv[2]);
    node *temp_head = head;

    if (my_strcmp(argv[3], "*") == 0)
    {
        while (head != NULL)
        {
            mini_add_block(bid, head);
            head = head->next;
        }
        return 0;
    }
    
    int i = 3;

    while (i < argc)
    {
        head = temp_head;
        int nid = my_atoi_base(argv[i], DECIMAL_BASE);
        node_existence = 0;

        while(head != NULL)
        {
            if(head->nid == nid)
            {
                node_existence = 1;
                int check = check_bid(head->blocks, bid);
                // printf("check = %d\n", check);
                if (check == 0)
                {
                    blocks* to_append = create_block_with_bid(bid);
                    if (head->blocks == NULL)
                    {
                        head->blocks = to_append;
                    }
                    else
                    {
                        append_block(to_append, head->blocks);
                    }
                }
                else
                {
                        print_error(ERROR_THREE);
                        printf("at node: %d\n", nid);
                }
            }
            head = head->next;
        }

        if (node_existence == 0)
        {
            print_error(ERROR_FOUR);
            printf("at node: %d\n", nid);
        }
        i += 1;

    }
    free(bid);

    return 0;
}

int select_option(int argc, char** argv, node* head, sync_status* status)
{
    int i = 0;
    if(my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "node") == 0 && argc == 3)
    {
        i  = add_node(argc, argv, head, status);
        return i;
    }
    else if (my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "block") == 0)
    {
        //printf("//run add block\n"); 
        i = add_block(argc, argv, head, status);
        return i;
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "node") == 0 && argc >= 3)
    {
        i = rm_node(argc, argv, head, status);
        return i;
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "block") == 0 && argc == 3)
    {
        i = remove_block(argc, argv, head, status);
        return i;

    }
    else if (my_strcmp(argv[0], "ls") == 0 && argc <= 2)
    {
        //we need to validate the second argument looking for a l
        i  = ls_l(argc, argv, head, status);
        return i;
    }
    else if (my_strcmp(argv[0], "sync") == 0 && argc == 1)
    {
        printf("argc = %d\n", argc);
        printf("//sync\n");
    }
    else
    {
        return ERROR_SIX;
    }

    return ERROR_SIX;//?????
}

void prompt(sync_status* status)
{
    my_putstr("[");
    char* str = malloc(2 * sizeof(char));
    str[0] = status->status;
    str[1] = '\0';
    my_putstr(str);
    char* nodes = my_itoa_base(status->nodes, 10);
    my_putstr(nodes);
    my_putstr("]> ");
    free(str);
    free(nodes);
}

void save_to_backup(char* input)
{
    if(my_strcmp("ls", input) == 0 || my_strcmp("ls -l", input) == 0)
        return;
    int fd = open("backup.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    write(fd, input, my_strlen(input));
    write(fd, "\n", 1);
    close(fd);
}

node* load_backup(sync_status* status)
{
    node* head = create_link_with_nid(0);
    // node* head = malloc(sizeof(node));
    // head->next = NULL;
    int fd = open("backup.txt", O_RDWR | O_APPEND, S_IRWXU);
    if (fd == -1)
    {
        status->status = 's';
        status->nodes = 0;
    }
    else
    {
        char* input = readline(fd);
        int loop_count = 0;
        while(input[0] != '\0')
        {
            printf("%s\n", input);
            int string_count = delimiter_count(input, ' ') + 1;
            printf("string count = %d\n", string_count);
            char** string_array = split_string(input, ' ');
            select_option(string_count, string_array, head, status);
            free_string_array(string_array, string_count);
            free(input);
            input = readline(fd);
            loop_count++;
        }
        free(input);
    }
    return head;
}

void print_error (int error)
{
    if (error == ERROR_ONE)
    {
        my_putstr("no more resources available on the computer\n");
    }
    else if (error == ERROR_TWO)
    {
        my_putstr("this node already exists\n");
    }
    else if (error == ERROR_THREE)
    {
        my_putstr("this block already exists\n");
    }
    else if (error == ERROR_FOUR)
    {
        my_putstr("node doesn't exist\n");
    }
    else if (error == ERROR_FIVE)
    {
        my_putstr("block doesn't exist\n");
    }
    else
    {
        my_putstr("command not found\n");
    }
}

int main()
{
    //initialized linked list here
    sync_status* status = malloc(sizeof(sync_status));
    status->status = 's';
    status->nodes = 0;
    node* head = load_backup(status);
    // int node_count = read_list(head);
    //head->next = NULL;
    prompt(status); 

    char* input = readline(STDIN);
    // int space_count = delimiter_count(input, ' ');
    int error;
    
    while(input[0] == '\0' || my_strcmp(input, "quit") != 0) 
    {
        if (input_validation(input) == 0)
        {
            int string_count = delimiter_count(input, ' ') + 1;
            char** string_array = split_string(input, ' ');

            error = select_option(string_count, string_array, head, status);
            if (error == 0)
            {
                save_to_backup(input);
            }
            else
            {
                print_error(error);
            }            
            free_string_array(string_array, string_count);
        }
        else
        {   
            //print the error
            error = ERROR_SIX;
            print_error(error);
        }
        char* temp = input; //we make a temporay string to free everything stored at that location.
        free(temp);
        prompt(status);
        input = readline(STDIN);
        // space_count = delimiter_count(input, ' ');
    }
    free(input);
    free(status);
    free_linked_list(head);

    return 0;
}