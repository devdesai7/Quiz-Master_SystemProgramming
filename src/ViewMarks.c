#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include "../include/HeaderFiles_Faculty.h"

#define MAXCHAR 100
/*
Folling Module shows the Marks in a group as Suject Code is entere by the faculty

Concepts used in the  modules are : 
It uses of Directory Header File and demonstrates how Unbuffered IO is used
*/

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
void getSujectMarks(char *Qcode)
{
    char file_path[MAXCHAR] = "../include/Files/GroupMarks/";
    strcat(file_path, Qcode);
    strcat(file_path, ".txt");
    int fd;

    fd = open(file_path, O_RDWR);
    char str[MAXCHAR] = "";
    printf("\n");
    while (read(fd, str, sizeof(str)))
    {
        printf("%s ", str);
    }
}

void GroupMarks()
{
    system("clear");
    printf("Welcome Faculty, You about to View Marks of Quizs given by Students \nPlease Follow the Steps Carefully\n\n");

    char Qcode[MAXCHAR] = "";
    char pathChecker[MAXCHAR] = "";
    reQcode:

    printf("Following are Quiz Code:\n\n");
    viewQuizCode("../include/Files/GroupMarks/");
    printf("\nEnter Code to See result:");
    scanf("%s", Qcode);
    strcat(pathChecker, "GroupMarks/");
    strcat(pathChecker, Qcode);
    strcat(pathChecker, ".txt");
    bool checker = file_exist_checker(pathChecker);
    if (checker != true)
    {
        strcpy(pathChecker, "");
        strcpy(Qcode, "");
        printf("Wrong Code , Please Try Again\n");
        goto reQcode;
    }

    getSujectMarks(Qcode);
    int num;
    printf("\nPress 1 to Retry or 2 to go Back ");
    scanf("%d", &num);
    if (num == 1)
    {
        GroupMarks();
    }
    else
    {
        menu();
    }
}