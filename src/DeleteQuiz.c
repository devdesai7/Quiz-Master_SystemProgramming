#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../include/HeaderFiles_Faculty.h"

/*
Following Module uses concept of using Libary Function ,File IO and using it properties as well using Directory properties.
Where we use inbuild libary function, inorder to achieve the task.
*/
#define MAXCHAR 100

void remove_file()
{

  int removeQuestion, removeAnswer;

  char filename[MAXCHAR] = "../include/Files/";
  char file_name_Question[MAXCHAR] = "";
  char file_name_Answer[MAXCHAR] = "";
  char file_name[MAXCHAR] = "";
  //Stduent Answer Key will not be deleted as that must remain in existence
  printf("Enter File Name(with .txt) :  ");
  scanf("%s", file_name);

  //Concating  Question File Name
  strcat(file_name_Question, filename);
  strcat(file_name_Question, file_name);
  //Concating  Answer File Name
  strcat(file_name_Answer, filename);
  strcat(file_name_Answer, "A");
  strcat(file_name_Answer, file_name);

  removeQuestion = remove(file_name_Question);
  removeAnswer = remove(file_name_Answer);
  if (removeQuestion == 0 && removeAnswer == 0)
  {

    printf("Both Question Paper and Key files are  deleted successfully \n");
    sleep(2);
    }
  else
  {
    printf("Error:Something Went Wrong unable to delete the file.Please try Again \n");
    sleep(2);
  }
}

void rename_file()
{
  //Naming Convention is being checked by the function call
  //Renaming will also change the answer key filename
  int renameQuestion, renameAnswer;

  char filename[MAXCHAR] = "../include/Files/";
  char file_rename_Question_oldValue[MAXCHAR] = "";
  char file_rename_Question_newValue[MAXCHAR] = "";

  char file_rename_Answer_oldValue[MAXCHAR] = "";
  char file_rename_Answer_newValue[MAXCHAR] = "";

  char file_rename_old[MAXCHAR] = "";
  char file_rename_new[MAXCHAR] = "";
  char file_rename_new_code[MAXCHAR] = "";

reenter_name:

  //Answer Key will not be deleted as that must remain in existence
  printf("Enter File Name (OLD)(Including.txt)): ");
  scanf("%s", file_rename_old);
  printf("Enter File Name Subject Code (NEW):  ");
  scanf("%s", file_rename_new);
  printf("Enter File Name Quiz Code (NEW):  ");
  scanf("%s", file_rename_new_code);

  //Concating  Question old File Name
  strcat(file_rename_Question_oldValue, filename);
  strcat(file_rename_Question_oldValue, file_rename_old);

  //Concating Question New File New
  strcat(file_rename_Question_newValue, filename);
  strcat(file_rename_Question_newValue, file_rename_new);
  strcat(file_rename_Question_newValue, "_");
  strcat(file_rename_Question_newValue, file_rename_new_code);
  strcat(file_rename_Question_newValue, ".txt");

  //Checking New Name File is valid or not According to given standards used while creating the Quiz
  bool checker_exist = File_Value_checker("Subject.txt", file_rename_new); //Checks if value is entered correct or not
  if (checker_exist != true)
  {
    printf("\n Enter Correct Code .Following Code is not present in directory.Contact admin. \n");
    strcpy(file_rename_Question_oldValue, "");
    strcpy(file_rename_Question_newValue, "");
    goto reenter_name;
  }

  //Renaming it Question File
  renameQuestion = rename(file_rename_Question_oldValue, file_rename_Question_newValue);

  //Concating  Answer old File Name
  strcat(file_rename_Answer_oldValue, filename);
  strcat(file_rename_Answer_oldValue, "A");
  strcat(file_rename_Answer_oldValue, file_rename_old);

  //Concating  Answer New File Name
  strcat(file_rename_Answer_newValue, filename);
  strcat(file_rename_Answer_newValue, "A");
  strcat(file_rename_Answer_newValue, file_rename_new);
  strcat(file_rename_Answer_newValue, "_");
  strcat(file_rename_Answer_newValue, file_rename_new_code);
  strcat(file_rename_Answer_newValue, ".txt");

  renameAnswer = rename(file_rename_Answer_oldValue, file_rename_Answer_newValue);

  if (renameQuestion == 0 && renameAnswer == 0)
  {
    printf("Both Question Paper and Answer Key files are renamed successfully \n");
    sleep(2);

  }
  else
  {
    printf("Error:Something Went Wrong unable to delete the file.Please Check the files name properly\n");
    sleep(2);

  }
}
void file_data(char *file_path) // Shows when was last file updated
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
        strcat(path, file_path);
        strcat(path, "/");
        strcat(path, dir->d_name);
        stat(path, &attr);

        printf("%s \t", dir->d_name);
        printf("Last modified time: %s", ctime(&attr.st_mtime));

        strcpy(path, "");
      }
    }
    closedir(d);
  }
  printf("\n");
}
void delete_quiz()
{
  while (1)
  {
    system("clear");
    printf("Welcome Faculty, You are in Delete/Rename Page \nPlease Follow the Steps Carefully\n\n");

    printf("Follwing are the List of Files Present in Directory: \n");
    file_data("../include/Files");
    printf("Please Enter One of the following Options : \n");
    printf("1.Delete the Quiz  \n");
    printf("2.Rename the Quiz  \n");
    printf("3.Go Back \n");

    int opt;
    scanf("%d", &opt);

    if (opt == 1)
    {
      remove_file();
    }
    else if (opt == 2)
    {
      rename_file();
    }
    else if (opt == 3)
    {
      break;
    }
  }
  menu();
}