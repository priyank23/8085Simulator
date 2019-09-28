#include "pass1.h"

void pass2()
{
    pass1();
    FILE *input;
    FILE *output;
    input=fopen("code.txt","r");
    output=fopen("code.obj","w");
    char *line=(char*)malloc(50);

    fgets(line,50,input);
    tokenize(line);
    if(strcmp(label,"START")==0)
    {
        fprintf(output,"\n");
    }
    fgets(line,50,input);
    tokenize(line);
    int i=1;
    while(strcmp(label,"END")!=0)
    {
        printf("iter: %d\n",i++);
        printf("%s\n%s\n%s\n",label,opcode,operand);
        if(strcmp(label,";")==0) continue;
        char *OP=search(opcode);
        printf("%s\n",OP);
        if(OP!="NULL")
        {
            fprintf(output,"%s\n",OP);
            if(operand[0]!='\0')
            {
                if(search2(operand)==-1)
                {
                    int lenop=strlen(operand);
                    printf("%d",lenop);
                    if(lenop<=3)
                    {
                        fprintf(output,"%s\n",operand);
                    }
                    else
                    {
                        fprintf(output,"%c%c\t1\n",operand[2],operand[3]);
                        fprintf(output,"%c%c\t1\n",operand[0],operand[1]);
                    }
                }
                else
                {
                    int var=search2(operand);
                    printf("%d\n",var);
                    if(var<=9)
                    {
                        fprintf(output,"0%d\t0\n00\t0\n",var);
                    }
                    else if(var<100)
                    {
                        char* l;
                        l=(char*)malloc(5);
                        decToHexa(var,l);
                        if(strlen(l)<3)
                        {
                            fprintf(output,"0%s\t0\n00\t0\n",l);
                        }
                        else fprintf(output,"%s\t0\n00\t0\n",l);
                    }
                    else
                    {
                        char *l,*h;
                        l=(char*)malloc(5);
                        h=(char*)malloc(5);
                        printf("X");
                        decToHexa(var%100,l);
                        printf("X");
                        decToHexa(var/100,h);
                        if(strlen(l)<3)
                        {
                            fprintf(output,"0%s\t0\n",l);
                        }
                        else fprintf(output,"%s\t0\n",l);
                        if(strlen(h)<3)
                        {
                            fprintf(output,"0%s\t0\n",h);
                        }
                        else fprintf(output,"%s\t0\n",h);
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
            fprintf(output,"0\n");
                printf("ERROR2!!");
        }
        fgets(line,50,input);
        tokenize(line);
    }
    fclose(input);
    fclose(output);
}

int main()
{
    pass2();
    return 0;
}