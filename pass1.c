#include "hash_fn.h"
#include "symtab.h"
char label[20],opcode[20],operand[20];
int locctr;
int prog_length;
void upper_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}
void tokenize(char* line)
{
    label[0]='\0';
    opcode[0]='\0';
    operand[0]='\0';
    line[strcspn(line, "\n")] = 0;
    int ctr=0,ctr2=0;
    int num_of_tabs=0;
    while(line[ctr]!='\0')
    {
        if(line[ctr]==32 && ctr2 ==0)
        {
            ctr++;
            num_of_tabs++;
            continue;
        }
        else if(line[ctr]==32) 
        {
            ctr++;
            break;
        }
        if(num_of_tabs>3) break;
        label[ctr2++]=line[ctr++];
    }
    label[ctr2-1]='\0';
    ctr2=0;
    if(label[0]!='\0') ctr++;
    while(line[ctr]!='\0')
    {
        if(line[ctr]==32 && ctr2 !=0)
        {
            opcode[ctr2++]='_';ctr++;
        }
        else if(line[ctr]==','&&ctr!=0) 
        {
            if(line[ctr+1]>='0'&& line[ctr+1]<='9')
            break;
            else {ctr++;opcode[ctr2++]='_';};
        }
        opcode[ctr2++]=line[ctr++];
    }
    opcode[ctr2]='\0';
    upper_string(opcode);
    ctr2=0;
    ctr++;
    while(line[ctr]!='\0')
    {
        if(line[ctr]==32 && ctr2 ==0)
        {
            continue;
        }
        else if(line[ctr]==32) break;
        operand[ctr2++]=line[ctr++];
    }
    operand[ctr2]='\0';

    if(opcode[0]=='J')
    {
        int i;
        for(i=4;opcode[i]!='\0';i++)
        {
            operand[i-4]=opcode[i];
        }
        operand[i-4]='\0';
        opcode[3]='\0';
    }
    // printf("%s\n",label);
    // printf("%s\n",opcode);
    //  if (operand!=NULL) printf("%s\n",operand);
}
void pass1()
{
    createOptab();
    FILE *input;
    FILE *output;
    input=fopen("code.txt","r");
    output=fopen("symTab.txt","w");
    char *line=(char*)malloc(50);
    fgets(line,50,input);
    line[strlen(line)-1] = '\0';

    tokenize(line);
    if(strcmp(label,"START")==0 || strcmp(label,"start")==0)
    {
        locctr=0;
    }
    else locctr=-1;
    // fgets(line,50,input);
    // tokenize(line);
    while(strcmp(label,"end")!=0)
    {
        // line='\0';
        fgets(line,50,input);
        tokenize(line);
        if(strcmp(label,";")==0)
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
                fprintf(output,"%s\t%x\n",label,locctr);
            }
            // convert mov a,b ==> mov_a_b
            char* ch;
            if(opcode[0]!='\0'){ ch=search(opcode);
            if(ch!="NULL")
            {
                locctr++;    
            }
            else 
            {
            //    printf("Error2!!");
             //   return;
            }
            if(operand!=NULL) locctr++;}
        }
        else
        {
            char *ch;
            if(opcode[0]!='\0'){ ch=search(opcode);
            if(ch!="NULL")
            {
                locctr++;    
            }
            else 
            {
              //  printf("Error!!");
              //  return;
            }
            if(operand!='\0') locctr++;}
        }
    }
    fprintf(output,"program Length=%d bytes",locctr);
    fclose(input);
    fclose(output);
}
/*
int main()
{
    pass1();
    return 0;
}*/