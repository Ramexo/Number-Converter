#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

// This is a number system converters, it converts from one number system to another.

/*Now I know someoen will read this and say, Yo mate "You didnt need to this like this"
or they would say that there is easier option and that someone allready did this. But to them I say
I dont care. This project was made for me to learn all the functions and syntax.
When I read through this code I see as each day passed I improved on the way that code is writter.

If you happent to read this first I want to say thanks and you are awesome, and if you want to modify this code
go right ahead. Second thing this code is not efficiant I can tell you that much,
but making this small project tought me a lot about C. If you want to offer me feedback I guess you can find me
at programmers hideout on discord, my online name is ussualy Ramex.*/

// octal checker and binary checker need more work to complete, its something around indexing and loops.

// Reserved for prototypes
void dectohex(double num);
void dectooctal(double num);
void dectobin(double num);
int bintodec(int bin, int multi);
int octaltodec(int octal, int multi);
int hextodec(char hex, int multi);
int hexchecker(char *hex);
int decchecker(int num);

int num;
int main(void)
{
    int loop = 0;

    while (loop == 0)
    {
        int option;
        printf("\nFrom what number system are you converting: \n");
        printf("For decimal numbers insert 1, \nfor hexidecimal insert 2, \nfor octal insert 3, \nfor binary insert 4, \n");
        printf("To close the software insert 0\n OPTION: ");
        scanf(" %d", &option);
        // If you insert an illegal number program closes
        if (option > 4 || option < 0)
        {
            printf("\n\nIllegal option\n");
            option = 0;
        }
        // Decimal to other num system conversion
        if (option == 1)
        {
            printf("\nInsert decimal number to convert: ");
            scanf(" %d", &num);
            // Checks if number is allowed
            int legal = decchecker(num);
            if (legal != 0)
            {
                printf("illegal number\n");
            }
            if (legal == 0)
            {
                if (num != 0)
                {
                    dectohex(num);
                    dectooctal(num);
                    dectobin(num);
                }
                else
                {
                    printf("number 0 is allways converted to 0");
                }
            }
        }
        //------------------------------------
        if (option == 4)
        {
            // BINARY TO DECIMAL
            int binary;
            printf("Insert binary number: ");
            scanf(" %d", &binary);
            int dig = log10(binary) + 1;
            int *arr2 = malloc(dig * sizeof(int));
            int n = binary;

            // Sepperates numbers in to an array
            for (int i = dig - 1; i >= 0; i--)
            {
                double a = n * 0.1;
                int b = a;
                double c = a - b;
                int temp;
                temp = c * 10;
                arr2[i] = temp;
                // printf("%d", arr2[i]);
                n = b;
            }
            printf("\n");
            // dynamicly allocated array that stores decimal numbers
            int *dec_array = malloc(dig * sizeof(int));
            int multi1 = dig - 1;
            int legal = 0;

            for (int i = 0; i < dig; i++)
            {
                // Checks if you added non binary number you sneaky bastard
                if (arr2[i] < 0 || arr2[i] > 1)
                {
                    legal = 1;
                }
            }

            if (legal == 1)
            {
                printf("illegal number, reseting \n");
            }
            if (legal == 0)
            {
                for (int i = 0; i < dig; i++)
                {
                    // Converts binary numbers to decimal numbers, find the function on the bottom.
                    dec_array[i] = bintodec(arr2[i], multi1);
                    // Multiplier
                    multi1--;
                }
                printf("\n");
                int sum = 0;
                for (int i = 0; i < dig; i++)
                {
                    // sums up all decimal numbers to give you the answer you so despratly seek
                    sum = sum + dec_array[i];
                }
                printf("Decimal number is: %i\n", sum);
                // Binary to others
                // Uses decimal number you got previusly to convert it to other numbering systems.
                dectohex(sum);
                dectooctal(sum);

                printf("\n\n");
                // Frees the memory, no need to be greedy
                free(arr2);
                free(dec_array);
            }
        }
        //-----------------------------

        // OCTAL TO DECIMAL
        //------------------------------------
        if (option == 3)
        {
            printf("insert octal number to convert: ");
            scanf(" %d", &num);

            int dig = log10(num) + 1;
            // Dynamicly allocated arrays
            int *tarr1 = malloc(dig * sizeof(int));
            int *final = malloc(dig * sizeof(int));
            int multi = dig - 1;

            int legal;

            // seperates numbers to an array using MATH
            for (int i = 0; i < dig; i++)
            {
                double a = num * 0.1;
                int b = a;
                double c = a - b;
                int temp;
                temp = c * 10;
                tarr1[i] = temp;
                num = b;
            }
            int indexo = 0;
            // checks if you sneaked in a number that is not in octal system
            for (int i = 0; i < dig; i++)
            {
                if (tarr1[i] < 0 || tarr1[i] > 7)
                {
                    legal = 1;
                }
            }
            if (legal == 1)
            {
                printf("illegal number, software reseting\n");
            }
            if (legal == 0)
            {
                for (int i = dig - 1; i >= 0; i--)
                {
                    // Converts octal numbers to decimal numbers
                    final[indexo] = octaltodec(tarr1[i], multi);
                    multi--;
                    indexo++;
                }
                printf("\n");
                int sum = 0;
                for (int i = 0; i < dig; i++)
                {
                    // adds up all numbers in the array to give you the result
                    sum = sum + final[i];
                }
                printf("Decimal number is: %d\n", sum);
                // frees the dynamicly allocated arrays, we dont need them no more
                free(tarr1);
                free(final);
                // using decimal number to get other values
                dectohex(sum);
                dectobin(sum);
                printf("\n");
                indexo = 0;
            }
        }
        //-----------------------

        // HEXIDECIMAL TO TO DECIMAL
        //---------------------------
        if (option == 2)
        {
            printf("Insert hexidecimal number: ");
            char num[100];
            scanf(" %s", &num);
            int n = strlen(num);

            for (int i = 0; i < n; i++)
            {
                // Makes sure that you dont add non capital letters, code is sensitive like that
                num[i] = toupper(num[i]);
            }
            int final;
            int mult = n - 1;
            int sum = 0;
            // Checks if the number is hexidecimal, if not you borked
            int check = hexchecker(num);
            if (check != 0)
            {
                // Yup it aint hexidecimal, now you get this monstrosity
                printf("\n ILLEGAL NUMBER, SOFTWARE RESETING\n");
            }
            if (check == 0)
            {
                for (int i = 0; i < n; i++)
                {
                    // If all things are good, converts the hexidecimal number to decimal
                    final = hextodec(num[i], mult);
                    mult--;
                    // adds up all the numbers
                    sum = sum + final;
                }
                printf("Decimal number is: %d\n", sum);
                // Hexidecimal to others using Decimal number
                dectobin(sum);
                dectooctal(sum);
                printf("\n\n");
            }
        }
        //----------------------------
        // END THE LOOP, CLOSE PROGRAM
        //------------------------
        if (option == 0)
        {
            // If you accidently ran this software you can close it.
            printf("\nSoftware terminated\n");
            loop++;
        }
        //-----------------------
    }
}

void dectohex(double num)
{
    double remain, temp;
    int remainder, final;

    // Array of hexidecimal numbers
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    // Array used to store final score, char 'g' is used as empty space so there is no junk,
    char finals[20] = {'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'};
    int x = 0;

    // While loop that will use math to get remainders which are used to convert dec to hex numbers
    while (num != 0)
    {
        remain = num / 16;
        remainder = remain;
        temp = remain - remainder;

        final = temp * 16;

        num = remainder;

        // Final array, that can be flipped.
        finals[x] = hex[final];
        x++;
    }

    printf("Hexidecimal number is: ");
    // Flipts the "finals" array
    for (int i = 19; i >= 0; i--)
    {
        // Compares 2 characters in arrays then prints it out.
        for (int j = 0; j <= 16; j++)
        {
            if (finals[i] == hex[j])
            {
                printf("%c", finals[i]);
            }
        }
    }
    printf("\n");
}

void dectooctal(double num)
{
    double remain, temp;
    int remainder, final;
    int sum = 0;

    int octal[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int finals[20] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    int x = 0;

    while (num != 0)
    {
        // Uses math to convert decimal number to octal number
        remain = num / 8;
        remainder = remain;
        temp = remain - remainder;

        final = temp * 8;

        num = remainder;

        // Final array, that can be flipped.
        finals[x] = octal[final];
        x++;
    }
    printf("Octal number is: ");
    // this for loop flips the array
    for (int i = 19; i >= 0; i--)
    {
        // Compares 2 numbers in arrays then prints it out.
        for (int j = 0; j <= 7; j++)
        {
            if (finals[i] == octal[j])
            {
                printf("%d", finals[i]);
            }
        }
    }
    printf("\n");
}

void dectobin(double num)
{
    double remain, temp;
    int remainder, final;
    int x = 0;

    int bin[2] = {0, 1};
    int finals[20] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    while (num != 0)
    {   
        // Uses math to convert decimal number to binary
        remain = num / 2;
        remainder = remain;
        temp = remain - remainder;

        final = temp * 2;

        num = remainder;

        // Final array, that can be flipped.
        finals[x] = bin[final];
        x++;
    }
    printf("Binary number is: ");
    for (int i = 19; i >= 0; i--)
    {
        // Compares 2 numbers in arrays then prints it out.
        for (int j = 0; j <= 1; j++)
        {
            if (finals[i] == bin[j])
            {
                printf("%d", finals[i]);
            }
        }
    }
    printf("\n");
}

int bintodec(int bin, int multi)
{
    // Using math to turn binary numbers to decimal
    bin = bin * pow(2, multi);
    return bin;
}

int octaltodec(int octal, int multi)
{
    // using math to turn octal numbers to decimal
    octal = octal * pow(8, multi);
    return octal;
}

int hextodec(char hex, int multi)
{
    char hexp[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int hexnum[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int num;
    // hex = toupper(hex);
    // Compares 2 numbers if they are legal or not then converts them to decimal
    for (int i = 0; i < 17; i++)
    {
        if (hex == hexp[i])
        {
            num = hexnum[i];
            // converts to decimal using math
            num = num * pow(16, multi);
        }
    }

    return num;
}

int decchecker(int num)
{
    int legal = 0;
    // using basic if statement to check if number is negative or not
    if (num < 0)
    {
        legal = 1;
    }
    return legal;
}

int hexchecker(char *hex)
{
    char hexp[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int n = strlen(hex);
    int legal = 0;
    int index = 0;

    // checks if there is a non hex number in a string.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (hex[i] == hexp[j])
            {
                j = 16;
                index++;
            }
        }
    }
    if (index != n)
    {
        legal = 1;
    }
    index = 0;
    return legal;
}