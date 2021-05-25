#include <stdio.h>
#include <stdlib.h>
#include "../include/HeaderFiles_Student.h"
#include "../include/HeaderFiles_ViewResult.h"
/*
Following Module is the Menu Option for Student,, which will give it options to redirect desired output.
Here the function are being called from different C files , which declared in above given header file.Which will help us
to make the code more readable.
*/
static int roll;
void setRollNumber(int rollno)
{
    roll = rollno;
}
int getRollNumber()
{
    return roll;
}
void menu()
{
    system("clear");
    printf("Welcome to QUIZ MASTER \n\n");
    int rollno, option;
    printf("Enter Your Roll Number :");
    scanf("%d", &rollno);
    setRollNumber(rollno);
    printf("\nWelcome to Quiz Master %d \n", getRollNumber());
    printf("Please Choose one of the following Options:\n");
    printf("1.Take Up A Quiz \n");
    printf("2.View Results \n");
    printf("3.Exit\n");
    scanf("%d", &option);

    if (option == 1)
    {
        takeQuiz();
    }
    else if (option == 2)
    {
        view_result_student();
    }
    else if (option == 3)
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