#include "my_blockchain.h"


//readline
//read a character
//combine into the return_string
//continue reading characters until read "\n"
//return return_str



char* readline()
{
    char* str = malloc(sizeof(char)); //str is malloc'd so we can free it later
    str[0] = '\0';
    char* character = malloc(sizeof(char));
    int characters_read = read(0, character, 1);
    // printf("the character is %s\n", character);
    // printf("the value of character is %d\n", character[0]);

    while (character[0] != '\n')
    {
        char* temp = str; //we make a temporay string to free everything stored at that location.
        str = combine_strings(temp, character);
        free(temp);
        // free(character);
        // char* character = malloc(sizeof(char));
        int characters_read = read(0, character, 1);
        // printf("the character is %s\n", character);
        // printf("the value of character is %d\n", character[0]);
        // printf("str is %s\n", str);
    }
    free(character);
    return str; //if no characters are passed, str == \0
}

int input_validation(char* string)
{
    int validation = space_validator(string);
    /*
    1: no more resources available on the computer
    2: this node already exists
    3: this block already exists
    4:  node doesn't exist
    5: block doesn't exist
    6: command not found
    */
    return validation;
}

int select_option(int argc, char** argv)
{
    int i = 0;
    if(my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "node") == 0)
    {
        printf("//run add node \n");
    }
    else if (my_strcmp(argv[0], "add") == 0 && my_strcmp(argv[1], "block") == 0)
    {
        printf("//run add block\n"); 
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "node") == 0)
    {
        printf("//run rm node \n");
    }
    else if (my_strcmp(argv[0], "rm") == 0 && my_strcmp(argv[1], "block") == 0)
    {
        printf("//run rm block \n");
    }
    else if (my_strcmp(argv[0], "ls") == 0)
    {
        printf("//ls\n");
    }
    else if (my_strcmp(argv[0], "sync") == 0)
    {
        printf("//sync\n");
    }
    else
    {
        return 6;
    }

    return 6;//???????
}

int main()
{
    //initialized linked list here
    char* input = readline();
    int space_count = delimiter_count(input, ' ');
    
    while(input[0] == '\0' || my_strcmp(input, "quit") != 0) 
    {
        if (input_validation(input) == 0)
        {
            int string_count = delimiter_count(input, ' ') + 1;
            char** string_array = split_string(input, ' ');

            select_option(string_count, string_array);

            // printf("string_array [%d] = %s\n", 0, string_array[0]);
            int i = 0;
            while (i < string_count)
            {
                printf("string_array [%d] = %s\n", i, string_array[i]);
                i++;
            }
            //write commad to backup.txt file
            free_string_array(string_array, string_count);
        }
        else
        {   
            //print the error
            printf("Give me a good string please\n");
        }
        char* temp = input; //we make a temporay string to free everything stored at that location.
        free(temp);
        input = readline();
        space_count = delimiter_count(input, ' ');
    }

    free(input);

    return 0;
}