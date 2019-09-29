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

int toString(char a[]) {
  int c, offset=0, n=0; 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }

  return n;
}
/*
int hexaToDec(char hexVal[]) 
{    
    int x = strlen(hexVal); 
      
    int base = 1; 
      
    int dec_val = 0; 
      
    for (int i=x-1; i>=0; i--) 
    {  
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 
*/
void decToHexa(int n,char hex[]) 
{    
    // char array to store hexadecimal number 
    char hexaDeciNum[100]; 
      
    // counter for hexadecimal number array 
    int i = 0; 
    while(n!=0) 
    {    
        // temporary variable to store remainder 
        int temp  = 0; 
          
        // storing remainder in temp variable. 
        temp = n % 16; 
          
        // check if temp < 10 
        if(temp < 10) 
        { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 
        else
        { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
          
        n = n/16; 
    } 
      int k=0;
    // printing hexadecimal number array in reverse order 
    for(int j=i-1; j>=0; j--) 
     { hex[k++]= hexaDeciNum[j];}
       hex[k]='\0'; 
} 

void tokenize(char* line)
{
    upper_string(line);
    strcpy(label,"\0");
    strcpy(opcode,"\0");
    strcpy(operand,"\0");
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
    if(label[ctr2-1]==':') label[ctr2-1]='\0';
    else label[ctr2]='\0';
    ctr2=0;
 //  if(label[0]!='\0') ctr++;
    while(line[ctr]!='\0')
    {
        if(line[ctr]==32 && ctr2 !=0)
        {
            if(line[ctr+1]>='0'&& line[ctr+1]<='9')
            break;
            else 
            {
                opcode[ctr2++]='\0';
                if(strcmp(opcode,"CALL")==0 || strcmp(opcode,"CNC")==0 || strcmp(opcode,"CNZ")==0 || strcmp(opcode,"CP")==0 || strcmp(opcode,"CPE")==0 || strcmp(opcode,"CPI")==0 || strcmp(opcode,"CPO")==0 || strcmp(opcode,"CZ")==0 || strcmp(opcode,"JC")==0 || strcmp(opcode,"JM")==0|| strcmp(opcode,"JMP")==0 || strcmp(opcode,"JNC")==0 || strcmp(opcode,"JNZ")==0 || strcmp(opcode,"JP")==0 || strcmp(opcode,"JPE")==0 || strcmp(opcode,"JPO")==0 || strcmp(opcode,"JZ")==0) break;
                ctr++;
                ctr2--;
                opcode[ctr2++]='_';
            };
        }
        else if(line[ctr]==','&&ctr2!=0) 
        {
            if(line[ctr+1]>='0'&& line[ctr+1]<='9')
            break;
            else {ctr++;opcode[ctr2++]='_';};
        }
        opcode[ctr2++]=line[ctr++];
    }
    opcode[ctr2]='\0';
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

    if(operand[0]!='\0')
    {
        if(operand[strlen(operand)-1]=='H')
        {
            operand[strlen(operand)-1]='\0';
            // int x=hexaToDec(operand);
            // itoa(x,operand,5);
            // sprintf(operand, "%d", x);
        }
        else
        {
            if(operand[0]<='9'&&operand[0]>='0')
            decToHexa(toString(operand),operand);
        }
    }
    if(strcmp(label,"\0")!=0) printf("%s\n",label);
    if(strcmp(opcode,"\0")!=0) printf("%s\n",opcode);
     if(strcmp(operand,"\0")!=0) printf("%s\n",operand);
}
void pass1(char *file)
{
    createOptab();
    FILE *input;
    FILE *output;
    input=fopen(file,"r");
    
    
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
    // fgets(line,50,input);
    // tokenize(line);
    while(strcmp(label,"END")!=0)
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