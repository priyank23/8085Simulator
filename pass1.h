#include "hash_fn.h"
#include "symtab.h"
#include "macroProcessor.h"
void pass1(char *file)
{
    pass1Macro(file);
    printf("Running pass1...\n");
    createOptab();
    FILE *input;
    FILE *output,*inter;
    input=fopen("Code_after_macroprocessor_pass.txt","r");
    inter=fopen("inter.txt","w");
    
    output=fopen("symTab.txt","w");
    char *line=(char*)malloc(50);
    fgets(line,50,input);
    line[strlen(line)-1] = '\0';

    tokenize(line);
    while(strcmp(label,"START")!=0 && strcmp(label,"start")!=0)
    {
        fgets(line,50,input);
        line[strlen(line)-1] = '\0';
        tokenize(line);
        locctr=1;
    }
    fprintf(inter,"%s\n",line);
    // fgets(line,50,input);
    // tokenize(line);
    while(strcmp(label,"END")!=0)
    {
        // line='\0';
        fgets(line,50,input);
        tokenize(line);
        if(label[0]==';')
            continue;
        if(label[0]!='\0')
        {
            int add=search2(label);
            if(add!=-1)
            {
                printf("Error1!!");
                return;
            }
            else
            {
                INSERT2(label,locctr);
                fprintf(output,"%s\t%d\n",label,locctr);
            }
            // convert mov a,b ==> mov_a_b
            
        }
        char* ch;
        if(opcode[0]!='\0')
        {
            ch=search(opcode);
            if(ch!="NULL")
            {
                locctr++;    
            }
            else 
            {
            //    printf("Error2!!");
            //   return;
            }
            if(operand[0]!='\0')
            {
                locctr++;
                if(strlen(operand)>3) locctr++;
            }
        }
        fprintf(inter,"%s\n",line);
    }
    fprintf(output,"program Length=%d bytes",locctr);
    fclose(input);
    fclose(output);
    fclose(inter);
    printf("pass1 done!!\n");
}
/*
int main()
{
    pass1();
    return 0;
}*/