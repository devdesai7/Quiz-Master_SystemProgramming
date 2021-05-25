#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include "../include/HeaderFiles_Faculty.h"

/*
Following Module uses concept of using Process Management , FILE IO , Signals  ,String Manipulation.
Where Signals are used to Manipulate the Processes, and are being called according to need.
*/
#define MAXCHAR 100
char temp_file_name[MAXCHAR] = "";
int Qpid, QchildID, status;
int x = 1;
int iSignal = 0, numSignal;

void Redirecting_Message()
{
    int i = 0;
    for (i = 0; i <= 10000; i++)
    {
        printf("\rRedirecting...Please Wait...(%d)", i / 100);
        sleep(0.1);
    }
    printf("\n");
}
static void signal_handler(int signo)
{
    switch (signo)
    {
    case SIGUSR1:
    {
        if (Qpid == getpid()) //For Parent
        {

            Write_File_Line_withQuestion(temp_file_name);
            printf("\n");
        }
        break;
    }
    case SIGUSR2:
    {

        if (QchildID != getpid()) //For Child
        {
            iSignal++;
            Write_File_Line_withAnswers(temp_file_name);
            //  printf("isignal %d ,numSignal %d",iSignal,numSignal);

            if (iSignal == numSignal)
            {
                  strcpy(temp_file_name,"");
                 x=1;
                iSignal = 0;
                system("clear");
                printf("Quiz Created Successfully.Please Wait\n");

                Redirecting_Message();
                sleep(2);
                menu();
            }
            printf("\n");
        }
        break;
    }
    default:
        break;
    }
    return;
}

bool File_Value_checker(char *file_name, char *value)
{
    FILE *fp;

    char str[MAXCHAR] = "";
    char filename[] = "../include/Files/";
    strcat(filename, file_name);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s .Please check, the Directory,File must be Deleted.", filename);
        return false;
    }
    bool rVal = false;
    while (!feof(fp))
    {
        fscanf(fp, "%s%*[^\n]", str);

        if (strcmp(str, value) == 0)
        {
            rVal = true;
            break;
        }
        else
        {
            rVal = false;
        }
    }
    fclose(fp);
    return rVal;
}
bool file_exist_checker(char *file_name)
{
    char filename[MAXCHAR] = "../include/Files/";
    strcat(filename, file_name);

    FILE *fp;
    if (fp = fopen(filename, "r"))
    {
        fclose(fp);
        return true;
    }
    else
    {
        return false;
    }
}
void File_data_get_by_line(char *file_name)
{

    FILE *fp;
    char str[MAXCHAR] = "";
    char filename[] = "../include/Files/";
    strcat(filename, file_name);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s .Please check, the Directory,File must be Deleted.", filename);
        return;
    }

    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
}
void Write_File_Line_withAnswers(char *file_name)
{
    FILE *fp1;
    char Question[MAXCHAR] = "";
    char Options[MAXCHAR] = "";

    char str[MAXCHAR] = "";
    char temp;
    char alpha;
    char addOn[] = "";
    //A stands for Answer
    char filename[] = "../include/Files/A";
    strcat(filename, file_name);
    fp1 = fopen(filename, "a");
    //strcat(addOn,);

    printf("Enter Correct Option for Question %d: ", x - 1);
    scanf(" %c", &alpha);
    //   fputs(".",fp1);

    fputc(toupper(alpha), fp1);
    fputs("\n", fp1);

    fclose(fp1);
}
void Write_File_Line_withQuestion(char *file_name)
{
    FILE *fp;
    char Question[MAXCHAR] = "";
    char Options[MAXCHAR] = "";

    char str[MAXCHAR] = "";
    char temp;

    char filename[] = "../include/Files/";
    strcat(filename, file_name);
    fp = fopen(filename, "a");

    //For Entering Questions
    printf("Enter Question %d: ", x);
    scanf("%c", &temp); // temp statement to clear buffer
    scanf("%[^\n]", Question);
    fputs(Question, fp);
    fputs("\n", fp);

    //For Entering Options
    int num;
    printf("Enter Number of options for question %d: ", x);
    scanf("%d", &num);
    char alpha = 'A';
    for (int i = 0; i < num; i++)
    {
        printf("Enter Option %c.", alpha);
        scanf("%c", &temp); // temp statement to clear buffer
        scanf("%[^\n]", Options);
        fputc(alpha, fp);
        fputs(". ", fp);
        fputs(Options, fp);
        fputs(" ", fp);
        alpha++;
    }
    fputs("\n", fp);

    x++;
    fclose(fp);
    kill(Qpid, SIGUSR2); //For using Child
}
void GroupAnsFileMaker(char * filename)
{
    FILE *fp1;
    char file_name[MAXCHAR]="";
    strcat(file_name,"../include/Files/GroupMarks/");
    strcat(file_name,filename);
    fp1 = fopen(file_name, "w");
    fclose(fp1);
}
void EnterQuiz()
{
    char in[MAXCHAR] = "";
    char inQC[MAXCHAR] = "";
    int num;

    system("clear");
    printf("Welcome Faculty, You are about to Make a Quiz\nPlease Follow the Steps Carefully\n\n");
    printf("Please Select a Subject (Use Suject Code as Same Below)\n");
    char *temp = "Subject.txt";

    File_data_get_by_line(temp);

Subject_Code:

    printf("Enter the Subject Code : ");
    scanf("%s", in);

    bool checker_exist = File_Value_checker(temp, in); //Checks if value is entered correct or not

    if (checker_exist != true)
    {
        printf("Enter Correct Code Following Code is not present in directory.Contact admin. \n");
        strcpy(in,"");
        goto Subject_Code;
    }

    printf("Enter Quiz Code (Quiz Should be Unique and Should not Repeat for the same subject): ");
    scanf("%s", inQC);

    printf("Enter Number of Questions you want to set    : ");
    scanf("%d", &num);

    strcat(temp_file_name, in);
    strcat(temp_file_name, "_");
    strcat(temp_file_name, inQC);
    strcat(temp_file_name, ".txt");
    GroupAnsFileMaker(temp_file_name);
    bool checker_file = file_exist_checker(temp_file_name); //Check if file exist or not
    if (checker_file == true)
    {
        printf("File Already Exist , Please enter New File name \n");

        strcpy(temp_file_name, "");
        goto Subject_Code;
    }

    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
    {
        printf("Parent: Unable to create handler for SIGUSR1\n");
    }

    if (signal(SIGUSR2, signal_handler) == SIG_ERR)
    {
        printf("Parent: Unable to create handler for SIGUSR2\n");
    }
    Qpid = getpid();
    QchildID = fork();
    numSignal = num;
    for (int i = 1; i < numSignal; i++)
    {

        kill(Qpid, SIGUSR1); //For using parent
    }
  
}
