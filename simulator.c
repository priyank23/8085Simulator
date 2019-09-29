#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulator_files/memory.h"
//#define DEBUG

//conversion----------------------------------------

int hex_decimal(char *hexVal)//hex->decimal
{
	int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
}
char * decimal_hex(int decimalNumber)//decimal->hex
{
	char *ch="00000";
	int quotient = decimalNumber;
	int temp;
	int i=0;
    while(quotient!=0)
    {
    	if(i>4)
    		break;
    	temp = quotient % 16;

      //To convert integer into character
    	if( temp < 10)
    		temp =temp + 48;
    	else
    		temp = temp + 55;

    	ch[i++]= temp;
    	quotient = quotient / 16;
    }
    return ch;
}
int * decToBinary(int n)//Decimal->Binary
{ 
    // array to store binary number 
    int binaryNum[32]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    }
    return binaryNum;
} 

//--------------------------------------------------


//reads the object code from the file and loads it into the memory
int loader(FILE *objfile)
{
    int startAddress = relocationCounter;
    int memaddress = relocationCounter;
    while (!feof(objfile))
    {
        char *line;
        line = (char *)malloc(1000 * sizeof(char));
        fgets(line, 1000, objfile);

        char *p = strtok(line, " ");
        p = strtok(NULL, " ");

        //end of file
        if (p == NULL)
        {
            relocationCounter = memaddress;
            return startAddress;
        }
        else
        {
            char *opcode;
            strcpy(opcode, p);

            p = strtok(NULL, " ");
            //address
            if (p != NULL)
            {
                //relative address
                if(strcmp(p,"0"))
                {
                    fgets(line, 1000,objfile);
                    p = strtok(line," ");
                    p = strtok(NULL," ");
                    char *opcode0;
                    strcpy(opcode0,p);
                    strcat(opcode0,opcode);
                    char *addressHex = opcode0;

                    //loading lower address
                    memory[memaddress][0]=addressHex[2];
                    memory[memaddress][1]=addressHex[3];

                    memaddress++;

                    //loading higher address
                    memory[memaddress][0]=addressHex[0];
                    memory[memaddress][1]=addressHex[1];
                }
                //absolute address
                else if(strcmp(p,"1"))
                {
                    fgets(line, 1000,objfile);
                    p = strtok(line," ");
                    p = strtok(NULL," ");
                    char *opcode0;
                    strcpy(opcode0,p);
                    strcat(opcode0,opcode);
                    int address = hex_decimal(opcode0);
                    
                    //relocating absolute addresses
                    address += relocationCounter;
                    char *addressHex = decimal_hex(address);

                    //loading lower address
                    memory[memaddress][0]=addressHex[2];
                    memory[memaddress][1]=addressHex[3];

                    memaddress++;

                    //loading higher address
                    memory[memaddress][0]=addressHex[0];
                    memory[memaddress][1]=addressHex[1];
                }
            }
            //not an address
            else
            {
                strcpy(memory[memaddress],opcode);
                memaddress++;
            }
        }
    }
    relocationCounter = memaddress;
    return startAddress;
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

    initializeMachine();

    int startAddress = loader(objfile);

    fclose(objfile);

    return 0;
}