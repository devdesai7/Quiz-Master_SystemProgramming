#include <stdio.h>
#include <stdlib.h>
#include "../include/HeaderFiles_Faculty.h"

/*
Follwing is Menu Option for Faculty Module, which will give it options to redirect desired output.
Here the function are being called from different C files , which declared in above given header file.Which will help us
to make the code more readable.
*/
void menu()
{

    system("clear");
    int op;
    printf("WELCOEM FACULTY\n");
    printf("Please Enter One of the following Options : \n");
    printf("1.Enter a Quiz \n");
    printf("2.Delete a Quiz \n");
    printf("3.Get Result a Quiz \n");
    printf("4.Exit \n");

    scanf("%d", &op);

    if (op == 1)
    {
        EnterQuiz();
    }
    else if (op == 2)
    {
        delete_quiz();
    }
    else if(op ==3)
    {
        GroupMarks();
    }

    else if (op == 4)
    {
        system("clear");
        printf("THANK YOU FOR USING QUIZ MASTER\n");
        exit(0);
    }
    else
    {
        printf("Inappropriate Option was Choosen.Systen Exited");

    }
}
int main()
{

    menu();
}
