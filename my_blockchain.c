#include "my_blockchain.h"


//readline
//read a character
//combine into the return_string
//continue reading characters until read "\n"
//return return_str



char* readline()
{
    char* str = "\0";
    char* character = malloc(sizeof(char));
    int characters_read = read(0, character, 1);
    // printf("the character is %s\n", character);
    // printf("the value of character is %d\n", character[0]);

    while (character[0] != '\n')
    {
        str = combine_strings(str, character);
        int characters_read = read(0, character, 1);
        // printf("the character is %s\n", character);
        // printf("the value of character is %d\n", character[0]);
        // printf("str is %s\n", str);
        // if(my_strcmp("\n", character) == 0)
        // {
        //     break;
        // }
    }
    return str; //if no characters are passed, str == \0
}

int input_validation(char* )
{
    //space_validator
}

int main()
{
    char* input = readline();
    int space_count = delimiter_count(input, ' ');
    

    while(input[0] == '\0' || my_strcmp(input, "quit") != 0) 
    {
        char** string_array = split_string(input, ' ');
        // printf("string_array [%d] = %s\n", 0, string_array[0]);
        int i = 0;
        while (i < space_count + 1)
        {
            printf(" [%d] = \n", i);
            free(string_array[i]);
            i++;
        }
        free(string_array);
        input = readline();
        space_count = delimiter_count(input, ' ');
    }

    free(input);

    return 0;
}