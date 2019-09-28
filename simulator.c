#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DEBUG

void parseFile(FILE *objfile)
{
    while(!feof(objfile))
    {
        char *line;
        line = (char*) malloc(1000*sizeof(char));
        fgets(line,1000,objfile);
        printf("%s",line);
    }

    return;
}

int main(int argc, char *argv[])
{
    //checking for incorrect input
    #ifdef DEBUG
        printf("argc = %d\n", argc);
        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
    #endif

    if (argc != 2)
    {
        printf("Please Enter object file as argument\n");
        exit(0);
    }

    //objfilename contains the objectcode file path
    char *objfilename = argv[1];

    FILE *objfile = fopen(objfilename, "r");

    //check if file doesnot exit
    if (objfile == NULL)
    {
        printf("File not found!\n");
        exit(0);
    }

    parseFile(objfile);

    fclose(objfile);

    return 0;
}