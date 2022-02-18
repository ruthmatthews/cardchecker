#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long int get_number(void);
long int get_digit(long int cardnumber, int digitnumber);
long int second_digit(long int cardnumber);
long int other_digit(long int cardnumber);
int count_digits(long int cardnumber);


int main(void)
{

    //Ask user for card number
    long int cardnumber;
    cardnumber = get_number();

    //Count the number of digits on the card
    int digits = count_digits(cardnumber);

    //If the card number is less than 13 digits, reject
    if (digits < 13)
    {
        printf("INVALID\n");
        exit(0);
    }

    //Save each individual digit as a variable
    //Digits counted from end of card number
    int digit1 = get_digit(cardnumber, 1);
    int digit2 = get_digit(cardnumber, 2);
    int digit3 = get_digit(cardnumber, 3);
    int digit4 = get_digit(cardnumber, 4);
    int digit5 = get_digit(cardnumber, 5);
    int digit6 = get_digit(cardnumber, 6);
    int digit7 = get_digit(cardnumber, 7);
    int digit8 = get_digit(cardnumber, 8);
    int digit9 = get_digit(cardnumber, 9);
    int digit10 = get_digit(cardnumber, 10);
    int digit11 = get_digit(cardnumber, 11);
    int digit12 = get_digit(cardnumber, 12);
    int digit13 = get_digit(cardnumber, 13);
    int digit14 = get_digit(cardnumber, 14);
    int digit15 = get_digit(cardnumber, 15);
    int digit16 = get_digit(cardnumber, 16);

    //Check card using Luhn's algorithm
    long int check = (second_digit(cardnumber) + other_digit(cardnumber)) % 10;

    //If Lunh's algorithm does not return 1, reject
    if (check != 0)
    {
        printf("INVALID\n");
        exit(0);
    }

    //If the card is 13 or 16 digits long and begins with a 4, assign card VISA
    if ((digits == 13 && digit13 == 4) || (digits == 16 && digit16 == 4))
    {
        printf("VISA\n");
    }
    //If the card is 15 digits long and begins 34 or 37, assign card AMEX
    else if (digits == 15 && digit15 == 3 && (digit14 == 4 || digit14 == 7))
    {
        printf("AMEX\n");
    }
    //If the card is 16 digits long and begins 51, 52, 53, 54, or 55 assign card MASATERCARD
    else if (digits == 16 && digit16 == 5 && digit15 > 0 && digit15 <= 5)
    {
        printf("MASTERCARD\n");
    }
    //Otherwise, reject
    else
    {
        printf("INVALID\n");
    }

}

//Function: ask user for number
long int get_number(void)
{
    long int answer;
    answer = get_long("Number: ");
    return answer;
}

//Function: count the digits in card number
int count_digits(long int cardnumber)
{
    int count = 0;
    do
    {
        cardnumber /= 10;
        ++count;
    }
    while (cardnumber != 0);
    return count;
}

//Function: save an individual digit of cardnumber as a variable
long int get_digit(long int cardnumber, int digitnumber)
{

    long int digit = cardnumber % (long int)pow(10, digitnumber);
    digit = digit - (cardnumber % (long int)pow(10, digitnumber - 1));
    digit = digit / (long int)pow(10, digitnumber - 1);
    return digit;
}

//Function: Luhn's algorithm part1
//Multiply each second digit, beginnng with penultimate digit, by 2, then sum the digits
long int second_digit(long int cardnumber)
{
    long int second_digits = 0;
    int n;
    for (n = 2; n <= 16; n += 2)
    {
        if (get_digit(cardnumber, n) < 5)
        {
            long int doubled_less = get_digit(cardnumber, n) * 2;
            second_digits = second_digits + doubled_less;
        }
        else
        {
            long int doubled_more = get_digit(cardnumber, n) * 2;
            long int broken_first = doubled_more % 10;
            long int broken_second = (doubled_more - broken_first) / 10;
            second_digits = second_digits + broken_first + broken_second;
        }
    }
    return second_digits;
}

//Function: Luhn's algorithm part2
//Sum the other digits in card number not used in Luhn's part1
long int other_digit(long int cardnumber)
{
    long int other_digits = 0;
    int i;
    for (i = 1; i <= 15; i += 2)
    {
        other_digits = other_digits + get_digit(cardnumber, i);
    }
    return other_digits;
}