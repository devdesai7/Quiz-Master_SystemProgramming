#include <stdio.h>
#include <unistd.h>
/*
Following module is Main Menu of the system , where it will choosen either you are a faculty or a student and accordingly 
the program will run.

Concepts used in the  modules are : 
use of exec() command where it will replace it process with desired process seleted by the user.
*/
int main(int argc, char *argv[])
{
	int n;
	printf("WELCOME TO QUIZ MASTER\n");
	printf("Enter one of the Following Option :\n");
	printf("Are you a ? \n");
	printf("1.Faculty \n2.Sutdent\n");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
	{
		char *args[] = {"../bin/FacultyRunable", NULL};
		execvp(args[0], &args[0]);
		break;
	}
	case 2:
	{
		char *args[] = {"../bin/StudentRunable", NULL};
		execvp(args[0], &args[0]);
	}
	break;
	defualt:
		{
			printf("Inappropriate Option was Choosen.Systen Exited");
		}
		break;
	}
}
