#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include "../include/HeaderFiles_Student.h"
#include "../include/HeaderFiles_ViewResult.h"
/*
Folloing Module Fetches the Score of the Student Marks and display it

Concepts used in the modules are : 
File IO , Directory Header Files ,Process Management,Pipes
*/

#define MAXCHAR 100
#define READ 0  //For Read end of the pipe
#define WRITE 1 //For Write end of the pipe

void viewQuizCode(char *file_path)
{
    DIR *d;
    struct dirent *dir;
    struct stat attr;

    char path[MAXCHAR] = "";
    d = opendir(file_path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {

            if (dir->d_type == DT_REG)
            {
                char temp[MAXCHAR] = "";
                strcat(temp, dir->d_name);
                if (temp[0] == 'A' || (strcmp(temp, "Subject.txt") == 0))
                {
                    //Do nothing
                }
                else
                {
                    printf("%s \t", dir->d_name);
                }
            }
        }
        closedir(d);
    }
    printf("\n");
}

void getMarks(char *Qcode)
{
    char pathanskey[MAXCHAR] = "";
    char temp[MAXCHAR] = "";
    sprintf(temp, "%d", getRollNumber());
    strcat(pathanskey, "../include/Files/StudentAnswers/");
    strcat(pathanskey, temp);
    strcat(pathanskey, "_");
    strcat(pathanskey, Qcode);
    strcat(pathanskey, ".txt");

    int fd[2], bytesRead, status;
    pipe(fd);
    if (fork() == 0) //Child
    {
        close(fd[READ]); // Close unused end
        int linenum = countFileLine(pathanskey) - 2;
        if (linenum == -2)
        {
            write(fd[WRITE], "No Data", 8);
        }
        printf("\nYour Marks for Quiz %s is ", Qcode);
        readQuestion(pathanskey, linenum);
    }
    else //Parent
    {
        close(fd[WRITE]); // Close unused end
        char str[MAXCHAR] = "";
        read(fd[READ], str, 8);
        if (strcmp(str, "No Data") == 0)
        {
            printf("\nPlease check the Quiz Code or you have not attempted the following Quiz\n");
        }
        wait(&status);
        int x;
        printf("Press 1 to Retry or 2 to Go Back to Menu \n");
        scanf("%d", &x);
        if (x == 1)
        {
            view_result_student();
        }
        else if (x == 2)
        {
            menu();
        }
    }
}

void view_result_student()
{
    system("clear");
    char Qcode[MAXCHAR] = "";
    printf("Welcome Roll Number %d \n\n", getRollNumber());
    printf("To view your marks , Please Enter one of the Folliwng are the Quiz Codes :\n");
    viewQuizCode("../include/Files");
    printf("Please Enter the Code for which you require the marks : ");
    scanf("%s", Qcode);
    getMarks(Qcode);
}
