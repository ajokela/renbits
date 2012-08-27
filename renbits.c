#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AND "and"
#define OR "or"
#define XOR "xor"
#define TWIDDLE "twiddle"
#define RSHIFT "rshift"
#define LSHIFT "lshift"

void help()
{
    puts("================================================================================");
    printf("\tFun with binary and bitwise operations!\n");
    printf("USAGE:\n");
    printf("input a one line command in the format of <integer1> <(optional)operator name> <(optional)integer2>\n");
    printf("valid operators(not case sensitive):\n");
    printf("\tAND, OR, XOR, TWIDDLE, RSHIFT, LSHIFT\n");
    printf("\t&, |, ^, ~, >>, <<\n");
    printf("examples:\n\t3 and 9 (3 & 9)\n\t4 RSHIFT 1 (4 >> 1)\n\t810 TWIDDLE (810 ~)\n\t47 XOR 39 (47 ^ 39)\n");
    puts("================================================================================");
}


void dec_to_bin(long n){
    int num_of_bits;
    if(n < 128 && n >= -128) 
        num_of_bits = 8;
    else if(n < 32768 && n >= -32768)
        num_of_bits = 16;
    else if(n < 8388608 && n >= -8388608)
        num_of_bits = 24;
    else if(n < 2147483648 && n >= -2147483648)
        num_of_bits = 32;
    else{ // test min max bounds
        printf("Number out of bounds: %ld\n", n);
        exit(1);
    }
    int spaces = (num_of_bits / 4) - 1;
    int j = num_of_bits - 1;
    long check = 1;
    for(;j > 0; j--)
        check = check << 1;
    // malloc space for each binary digit, a '\0', and each space(' ')
    char *buff = malloc(sizeof(char) * (num_of_bits + 1 + spaces));
    int i = 0;
    while(check)
    {
        if ((i % 5) == 0)
            buff[i++] = ' ';
        if(n & check){
            buff[i++] = '1';
        }
        else
            buff[i++] = '0';
        check = check>>1;
    }
    buff[i]= '\0';

    printf("%40s -> %d-BIT integer: %ld", buff, num_of_bits, n);
    if(n >= 0 && n <= 255)
        printf(" char: %c", (int)n);
    printf("\n");
    free(buff);
}

void run_bitwise_operation(char *word, long num1,
                         long num2, int num_of_args){
    long result = 0;
    char *opname;
    int shift = 0;
    if (strcasecmp(word, AND) == 0 || strcasecmp(word, "&") == 0){
        result = num1 & num2;
        opname = "AND &";
    }
    else if (strcasecmp(word, OR) == 0 || strcasecmp(word, "|") == 0){
        result = num1 | num2;
        opname = "OR |";
    }
    else if (strcasecmp(word, XOR) == 0 || strcasecmp(word, "^") == 0){
        result = num1 ^ num2;
        opname = "XOR ^";
    }
    else if (strcasecmp(word, TWIDDLE) == 0 || strcasecmp(word, "~") == 0){
        result = ~num1; // check to see if this runs ok with useless second arg
        opname = "TWIDDLE ~";
    }
    else if (strcasecmp(word, RSHIFT) == 0 || strcasecmp(word, ">>") == 0){
        result = num1 >> num2;
        opname = "RSHIFT >>";
        shift = num2;
    }
    else if (strcasecmp(word, LSHIFT) == 0 || strcasecmp(word, "<<") == 0){
        result = num1 << num2;
        opname = "LSHIFT <<";
        shift = num2;
    }
    else{
        if(num_of_args > 1){
            printf("Unhandled bitwise operator word argument: %s\n", word);
            exit(1);
        }
    }

    dec_to_bin(num1);
    if (num_of_args == 3 && !shift)
        dec_to_bin(num2);
    if (num_of_args > 1){  
        if(shift)
            printf("%48s (%d)\n", opname, shift);
        else
            printf("%48s\n", opname);
        dec_to_bin(result);
    }
    
}

int has_third_argument(){
    char line[80];
    fgets(line, 80, stdin);
    printf("line: '%s'...", line);

    return 1;
}

int main(){
    help();
    long num1 = 0;
    long num2 = 0;
    char word[40];
    char buff[100];
    int num_of_args = 0;
    while(1){
        printf("(enter command or 'help'): ");
        fgets(buff, 80, stdin);
        if(strstr(buff, "help")){
            help();
            continue;
        }
        buff[strlen(buff) - 1] = '\0';
        //printf("input read: '%s'\n", buff);
        num_of_args = sscanf(buff, "%ld %s %ld", &num1, word, &num2);
        //printf("sscanf read %d args:\n", num_of_args);
        //printf("num1: %ld, num2: %ld, word: '%s'\n", num1, num2, word);
        if(num_of_args > 0){
            puts("================================================================================");
            run_bitwise_operation(word, num1, num2, num_of_args);
            puts("================================================================================");
        }
        else
            puts("Invalid input");
    }

    return 0;

}