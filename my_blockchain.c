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

    node* new_link = malloc(sizeof(node));
    
    new_link = create_link_with_nid(nid);

    status->nodes += 1;

    append_link(new_link, head);

    return 0;
}

int ls_l(int argc, char** argv, node* head, sync_status* status)
{
    head = head->next;
    while(head != NULL)
    {
        if (!argv[1])
        {
            printf("%d\n", head->nid);
        }
        else
        {
            while (head->blocks != NULL)
            {
                printf("%s", head->blocks->bid);
                head->blocks = head->blocks->next; 
            }
        }
            
        head = head->next;
    }
    return 0;
}

int add_block(int argc, char** argv, node* head, sync_status* status)
{
    //if(current_node->block_counter + 1 > MAGIC_NUMBER)
        //return ERROR_ONE
    //add new block . . .
     //current_node->block_counter ++ ;
}

int select_option(int argc, char** argv, node* head, sync_status* status)
{
    int i = 0;
    if(my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "node") == 0 && argc == 3)
    {
        i  = add_node(argc, argv, head, status);
        return i;
    }
    else if (my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "block") == 0 && argc == 4)
    {
        printf("//run add block\n"); 
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "node") == 0 && argc == 3)
    {
        printf("//run rm node \n");
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "block") == 0 && argc == 3)
    {
        printf("//run rm block \n");
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
    node* head = malloc(sizeof(node));
    head->next = NULL;
    int fd = open("backup.txt", O_RDWR | O_APPEND, S_IRWXU);
    if (fd == -1)
    {
        status->status = 's';
        status->nodes = 0;
    }
    else
    {
        char* input = readline(fd);
        // printf("input = %s\n", input);
        int loop_count = 0;
        while(input[0] != '\0')
        {
            // printf("loop_count = %d\n", loop_count);
            int string_count = delimiter_count(input, ' ') + 1;
            char** string_array = split_string(input, ' ');
            select_option(string_count, string_array, head, status);
            free_string_array(string_array, string_count);
            input = readline(fd);
            // printf("loop_count = %d\n", loop_count);
            // printf("input = %s\n", input);
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
    int node_count = read_list(head);
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