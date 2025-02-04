#include "pass1.h"

void pass2(char *file)
{
    pass1(file);
    printf("Running pass2 of Assembler...\n");
    FILE *input;
    FILE *output;
    input=fopen("inter.txt","r");
    // input=fopen(file,"r");
    file[strlen(file)-3]='o';
    file[strlen(file)-2]='b';
    file[strlen(file)-1]='j';
    file[strlen(file)]='\0';
    char *fileOut=(char*)malloc(20);
    strcpy(fileOut,file);
    output=fopen(fileOut,"w");
    char *line=(char*)malloc(50);

    fgets(line,50,input);
    tokenize(line);
    while(strcmp(label,"START")!=0)
    {
        fgets(line,50,input);
        line[strlen(line)-1] = '\0';
        tokenize(line);
    }
   // fprintf(output,"\n");
    
    // int i=1;
    while(strcmp(label,"END")!=0)
    {
        fgets(line,50,input);
        tokenize(line);
        if(strcmp(label,"END")==0) break;
        // printf("iter: %d\n",i++);
        // printf("%s\n%s\n%s\n",label,opcode,operand);
        if(label[0]==';') continue;
        char *OP=search(opcode);
        // printf("%s\n",OP);
        if(OP!="NULL")
        {
            fprintf(output,"\n%s",OP);
            if(operand[0]!='\0')
            {
                if(search2(operand)==-1)
                {
                    int lenop=strlen(operand);
                    // printf("%d",lenop);
                    if(lenop<=3)
                    {
                        fprintf(output,"\n%s",operand);
                    }
                    else
                    {
                        fprintf(output,"\n%c%c 1",operand[2],operand[3]);
                        fprintf(output,"\n%c%c 1",operand[0],operand[1]);
                    }
                }
                else
                {
                    int var=search2(operand);
                    // printf("%d\n",var);
                    if(var<=9)
                    {
                        fprintf(output,"\n0%d 0\n00 0",var);
                    }
                    else if(var<100)
                    {
                        char* l;
                        l=(char*)malloc(5);
                        decToHexa(var,l);
                        if(strlen(l)<2)
                        {
                            fprintf(output,"\n0%s 0\n00 0",l);
                        }
                        else fprintf(output,"\n%s 0\n00 0",l);
                    }
                    else
                    {
                        char *l,*h;
                        l=(char*)malloc(5);
                        h=(char*)malloc(5);
                        // printf("X");
                        decToHexa(var%100,l);
                        // printf("X");
                        decToHexa(var/100,h);
                        if(strlen(l)<3)
                        {
                            fprintf(output,"\n0%s 0",l);
                        }
                        else fprintf(output,"\n%s 0",l);
                        if(strlen(h)<3)
                        {
                            fprintf(output,"\n0%s 0",h);
                        }
                        else fprintf(output,"\n%s 0",h);
                    }
                }
            }
            else
            {
                //fprintf(output,"0\n");
                //assemble the object code instruction
            }
        }
        else{
            fprintf(output,"\n0");
                printf("ERROR2!!");
                return;
        }
        // fgets(line,50,input);
        // tokenize(line);
    }
    printf("Execution of pass2 of Assembler Completed!\n");
    fclose(input);
    fclose(output);
}

int main(int argc,char **argv)
{
    pass2(argv[1]);
    return 0;
}