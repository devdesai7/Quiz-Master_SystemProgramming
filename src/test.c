#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 100
void test(char* file_name)
{
    printf("%s",file_name);
    FILE *fp;
    char str[MAXCHAR]="";
    char filename[] = "../include/";
    strcat(filename,file_name);
   
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return ;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    	fclose(fp);

}
