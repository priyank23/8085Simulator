#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char label[20],opcode[20],operand[20];
int locctr;
int prog_length;
char* mdt[100];
int cur_mdt_index=0;
char* line;
int mnt_index=-1;
char* name_mnt[100];
char* arg_name[100];
int num_of_params_mnt[100];
int mdt_start_index[100];
int mdt_end_index[100];

int search3(char name[])
{
    if(mnt_index==-1) return -1;

    for(int i=0;i<=mnt_index;i++)
    {
        if(strcmp(name,name_mnt[i])==0) return i;
    }
    return -1;
}
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
        if(num_of_tabs>0) break;
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
                if(line[ctr+2]!=',' && line[ctr+2]!='\0') break;
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
    // if(strcmp(label,"\0")!=0) printf("label:%s\n",label);
    // if(strcmp(opcode,"\0")!=0) printf("opcode:%s\n",opcode);
    //  if(strcmp(operand,"\0")!=0) printf("operand:%s\n",operand);
}

void tokenize2(char* line)
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
        if(num_of_tabs>0) break;
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
                if(line[ctr+2]!=',' && line[ctr+2]!='\0') break;
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

    /*if(operand[0]!='\0')
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
    }*/
    // if(strcmp(label,"\0")!=0) printf("label:%s\n",label);
    // if(strcmp(opcode,"\0")!=0) printf("opcode:%s\n",opcode);
    //  if(strcmp(operand,"\0")!=0) printf("operand:%s\n",operand);
}
void pass1Macro(char* file)
{
    printf("running one pass macro processor...\n");
    FILE* in=fopen(file,"r");
    FILE* out=fopen("Code_after_macroprocessor_pass.txt","w");
    
    line=(char*)malloc(50);
    fgets(line,50,in);
    line[strlen(line)-1] = '\0';
    tokenize2(line);

    while(strcmp(label,"START")!=0 && strcmp(label,"start")!=0)
    {
        if(strcmp(label,"MACRO")==0)
        {
            tokenize2(line);
            if(strcmp(operand,"\0")==0)   //entering details in mnt
            {
                num_of_params_mnt[++mnt_index]=0;
            }
            else num_of_params_mnt[++mnt_index]=1;
            arg_name[mnt_index]=(char*)malloc(50);
            strcpy(arg_name[mnt_index],operand);
            name_mnt[mnt_index]=(char*)malloc(50);
            strcpy(name_mnt[mnt_index],opcode);
            mdt_start_index[mnt_index]=cur_mdt_index;

            fgets(line,50,in);   //updating mdt
            line[strlen(line)-1] = '\0';
            tokenize2(line);
            while(strcmp(label,"MEND")!=0)
            {
                mdt[cur_mdt_index]=(char*)malloc(50);
                strcpy(mdt[cur_mdt_index++],line);
                fgets(line,50,in);  
                line[strlen(line)-1] = '\0';
                tokenize2(line);
            }
            mdt_end_index[mnt_index]=cur_mdt_index-1;
        }
        fgets(line,50,in);   //updating mdt
        line[strlen(line)-1] = '\0';
        tokenize2(line);
    }
    while(strcmp(label,"END")!=0)
    {
        int index=-1;
        if(strcmp(opcode,"\0")!=0)
        index=search3(opcode);
        if(index==-1)
        {
            fprintf(out,"%s\n",line);
        }
        else
        {
            // printf("%s %d\n",name_mnt[index],num_of_params_mnt[index]);
            char* argument=(char*)malloc(50);
            strcpy(argument,"\0");
            if(strcmp(operand,"\0")==0)
            {
                if(num_of_params_mnt[index]==1) printf("Error!\n");
                else
                {
                    int lno=mdt_start_index[index];
                    if(strcmp(label,"\0")!=0) 
                    {
                        fprintf(out,"%s: ",label);
                        tokenize2(mdt[lno++]);
                        if(strcmp(opcode,"\0")!=0) fprintf(out,"%s ",opcode);
                        if(strcmp(operand,"\0")!=0) fprintf(out,"%s",operand);
                        fprintf(out,"\n"); 
                    }
                    while(lno<=mdt_end_index[index])
                    fprintf(out,"%s\n",mdt[lno++]);   
                }
            }
            else
            {
                strcpy(argument,operand);
                // printf("argument:%s\n",argument);
                upper_string(argument);
                if(num_of_params_mnt[index]==0) printf("Error!\n");
                else
                {
                    int lno=mdt_start_index[index];

                    if(strcmp(label,"\0")!=0) 
                    {
                        fprintf(out,"%s: ",label);
                        tokenize2(mdt[lno++]);
                        if(strcmp(opcode,arg_name[index])==0) strcpy(opcode,argument);
                        if(strcmp(operand,arg_name[index])==0)
                        {
                            strcpy(operand,argument);
                        }
                        if(strcmp(opcode,"\0")!=0) fprintf(out,"%s ",opcode);
                        if(strcmp(operand,"\0")!=0) fprintf(out,"%s",operand);
                        fprintf(out,"\n"); 
                    }

                    while(lno<=mdt_end_index[index])
                    {
                        tokenize2(mdt[lno++]);
                        if(strcmp(opcode,arg_name[index])==0) strcpy(opcode,argument);
                        if(strcmp(operand,arg_name[index])==0)
                        {
                            strcpy(operand,argument);
                        }
                        if(strcmp(label,"\0")==0)
                        {
                            fprintf(out,"    ");
                        }
                        else fprintf(out,"%s: ",label);
                        if(strcmp(opcode,"\0")!=0)
                        fprintf(out,"%s",opcode);
                        if(strcmp(operand,"\0")!=0)
                        fprintf(out," %s",operand);
                        fprintf(out,"\n");
                    }
                }
            }
        }
        fgets(line,50,in);  
        tokenize2(line);
    }
    printf("Macro processor execution completed!\n");
    fprintf(out,"%s",line);
    fclose(in);
    fclose(out);
}
/*
int main()
{
    pass1Macro();
    return 0;
}*/