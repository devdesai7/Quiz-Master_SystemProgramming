#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include "../include/HeaderFiles_Student.h"
#include "../include/HeaderFiles_ViewResult.h"

/*
Follwing Module allows the student to take up the Quiz , with the following Quiz Code given to them.

Concepts used in the modules are : 
Process Managment , String Manipulation, File IO ,Signals ,Pipes

*/

#define MAXCHAR 100
#define READ 0  //For Read end of the pipe
#define WRITE 1 //For Write end of the pipe
int pid;
void takeQuiz()
{

    char QuizCode[MAXCHAR] = "";
    char QuizValue[MAXCHAR] = "";

restartOp:

    printf("Your Roll Number is  %d \n", getRollNumber());
    printf("Please Enter One of the following Quiz Code :\n");
    viewQuizCode("../include/Files");
    scanf("%s", QuizCode);

    //Quiz Code List and Checker

    strcat(QuizValue, "../include/Files/");
    strcat(QuizValue, QuizCode);
    strcat(QuizValue, ".txt");
    bool valChecker = file_exist_checker(QuizValue);
    if (valChecker != true)
    {
        printf("Wrong Code Entered.Please Try again...");
        strcpy(QuizCode, "");
        strcpy(QuizValue, "");
        goto restartOp;
    }

    //Process Manager and Communication Function Call
    Question_Answer_Input_OutputCal(QuizCode);
}
int countFileLine(char *Filename)
{
    FILE *fp;
    int count_lines = 1;
    char c;

    fp = fopen(Filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file %s", Filename);
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count_lines = count_lines + 1;

    fclose(fp);
    return count_lines;
}
void readQuestion(char *filename, int linenum)
{
    FILE *fp = fopen(filename, "r");
    int jump = 0;
    int count = 0;
    if (fp != NULL)
    {
        char str[MAXCHAR];                          /* or other suitable maximum line size */
        while (fgets(str, sizeof(str), fp) != NULL) /* read a line */
        {
            if (count == linenum)
            {
                printf("%s", str);
                break;
            }
            else
            {
                count++;
            }
        }
        fclose(fp);
    }
}
void putMarks(char *filename, int marks, char *QuizCode)
{
    FILE *fp1;
    char temp[MAXCHAR] = "";
    fp1 = fopen(filename, "a");
    sprintf(temp, "%d", marks);
    fputs(temp, fp1);
    fputs("\n", fp1);
    fclose(fp1);

    FILE *fp2;
    char FilePath[MAXCHAR] = "../include/Files/GroupMarks/";
    strcat(FilePath, QuizCode);
    strcat(FilePath, ".txt");
    char roll[MAXCHAR] = "";
    fp2 = fopen(FilePath, "a");

    sprintf(roll, "%d", getRollNumber());
    fputs("Roll Number : ", fp2);
    fputs(roll, fp2);
    fputs(" has Scored ", fp2);
    fputs(temp, fp2);
    fputs(" marks ", fp2);

    fputs("\n", fp2);

    fclose(fp2);
}

void makeAnswerKey(char *filename)
{
    FILE *fp1;
    fp1 = fopen(filename, "w");
    fclose(fp1);
}

bool file_exist_checker(char *file_name)
{
    //  char filename[MAXCHAR] = "";
    //  strcat(filename, file_name);

    FILE *fp;
    if (fp = fopen(file_name, "r"))
    {
        fclose(fp);
        return true;
    }
    else
    {
        return false;
    }
}

void Question_Answer_Input_OutputCal(char *QuizCode)
{

    int fd1[2], fd2[2], bytesRead, status;
    int pid;
    pipe(fd1); // For fd1, Parent - writer, Child - reader
    pipe(fd2); // For fd2, Parent - reader, Child - writer

    char filename[MAXCHAR] = "../include/Files/";
    char filepath[MAXCHAR] = ""; //Question Paper File Path
    strcat(filepath, filename);
    strcat(filepath, QuizCode);
    strcat(filepath, ".txt");

    int len = countFileLine(filepath);

    if (fork() == 0) //Child will read the question and send the  answer to the parent
    {

        close(fd1[READ]);  /* Close unused end */
        close(fd2[WRITE]); /* Close unused end */
        int i = 0;
        char str[MAXCHAR] = "HELLO";
        char op[MAXCHAR] = "";
        for (int i = 0; i < len - 1; i += 2)
        {
            readQuestion(filepath, i);
            readQuestion(filepath, i + 1);
            //printf("%d", i);
            //PIPE sending answer to parent where answer key will be created

            printf("\nEnter Your Answer Please:");
            scanf(" %c", &op[0]);
            write(fd1[WRITE], op, 1);

            // wait(&status);
            char temp[MAXCHAR] = "";
            read(fd2[READ], temp, 30);
            printf("\n%s\n", temp);
        }
    }
    else //Parent will Compare the correct answer and create a grade for him, with StudentID_SubjectCode has filename ,with its option and marks
    {
        //wait(&status);
        int marks = 0;
        close(fd1[WRITE]); /* Close unused end */
        close(fd2[READ]);  /* Close unused end */

        //Creating Answer Record File for the student
        char StudentFilename[MAXCHAR] = "";
        char temp[MAXCHAR] = "";
        sprintf(temp, "%d", getRollNumber());
        strcat(temp, "_");
        strcat(temp, QuizCode);

        strcat(StudentFilename, filename);
        strcat(StudentFilename, "StudentAnswers/");
        strcat(StudentFilename, temp);
        strcat(StudentFilename, ".txt");

        char AnsKey[MAXCHAR] = "../include/Files/A";
        strcat(AnsKey, QuizCode);
        strcat(AnsKey, ".txt");

        //Code to ADD to make sure file already doest not exist
        //It checks that has student given the paper or not
        bool checker_test_given = file_exist_checker(StudentFilename);
        if (checker_test_given == true)
        {
            printf("\nSeems You have already Given taken the exam.Please Try Again...System is Being Exited.\n");
            int pidP = getpid();
            kill(pidP, SIGQUIT);
        }
        else
        {
            makeAnswerKey(StudentFilename);
        }
        int i = 0;
        char ans[MAXCHAR] = "";
        char str[MAXCHAR] = "";

        FILE *fpStudent;
        FILE *fpOrignal;
        while (read(fd1[READ], ans, 2)) //Reading answer from Parent which is entered by the user)
        {
            printf("You Selected Option %s \n", ans);

            fpStudent = fopen(StudentFilename, "a");
            fpOrignal = fopen(AnsKey, "r");

            //Adds the answers and marks to answer key
            {

                fputs(ans, fpStudent);
                fputs("\n", fpStudent);

                int count = 0;
                if (fpOrignal != NULL)
                {
                    while (fgets(str, sizeof(str), fpOrignal) != NULL)
                    {

                        if (count == i)
                        {

                            fclose(fpOrignal);

                            break;
                        }
                        else
                        {
                            count++;
                        }
                    }
                    //  printf("Correct ANS =%s , str=%s", ans, str);
                }
            }
            i++;

            if (toupper(ans[0]) == str[0])
            {
                marks++;
            }
            //printf("Marks %d = ", marks);
            write(fd2[WRITE], "\nYour Answer Has Been Recorded\n", 30);
            fclose(fpStudent);
        }

        //putMarkinTheFile
        putMarks(StudentFilename, marks, QuizCode);
        menu();
    }
}
