#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulator_files/memory.h"
#include "simulator_files/func.h"

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

        char *pos;
        if ((pos = strchr(line, '\n')) != NULL)
            *pos = '\0';

        char *p;
        p = (char *)malloc(10 * sizeof(char));
        p = strtok(line, " ");

        char *opcode;
        opcode = (char *)malloc(10 * sizeof(char));
        strcpy(opcode, p);

        strcpy(memory[memaddress], opcode);
        memaddress++;

        /*
        //end of file
        if (p == NULL)
        {
            //printf("case null\n");//debug
            relocationCounter = memaddress;
            return startAddress;
        }
        else
        {
            //printf("case not null\n");//debug
            p = strtok(NULL, " ");
            //address
            if (p != NULL)
            {
                //printf("case not null\n");//debug
                //relative address
                if (strcmp(p, "0"))
                {
                    //printf("case relative address\n");//debug
                    fgets(line, 1000, objfile);
                    p = strtok(line, " ");
                    p = strtok(NULL, " ");
                    char *opcode0;
                    strcpy(opcode0, p);
                    strcat(opcode0, opcode);
                    char *addressHex = opcode0;

                    //loading lower address
                    memory[memaddress][0] = addressHex[2];
                    memory[memaddress][1] = addressHex[3];

                    memaddress++;

                    //loading higher address
                    memory[memaddress][0] = addressHex[0];
                    memory[memaddress][1] = addressHex[1];
                }
                //absolute address
                else if (strcmp(p, "1"))
                {
                    //printf("case absolute address\n");//debug
                    fgets(line, 1000, objfile);
                    p = strtok(line, " ");
                    p = strtok(NULL, " ");
                    char *opcode0;
                    strcpy(opcode0, p);
                    strcat(opcode0, opcode);
                    int address = hex_decimal(opcode0);

                    //relocating absolute addresses
                    address += relocationCounter;
                    char *addressHex = decimal_hex(address);

                    //loading lower address
                    memory[memaddress][0] = addressHex[2];
                    memory[memaddress][1] = addressHex[3];

                    memaddress++;

                    //loading higher address
                    memory[memaddress][0] = addressHex[0];
                    memory[memaddress][1] = addressHex[1];
                }
            }
            //not an address
            else
            {
                //printf("case opcode\n");//debug
                strcpy(memory[memaddress], opcode);
                memaddress++;
            }
        }
        */
    }
    relocationCounter = memaddress;

    for (int i = startAddress; i < relocationCounter; i++)
        memory[i];

    return startAddress;
}

//runs the program
int run(int startAddress)
{
    pc = startAddress;
    while (1)
    {
        int returncode = function(memory[pc]);
        if(returncode == 0)
        {
            return 0;
        }
        readnext();
    }
}

int main(int argc, char *argv[])
{

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

    printf("Simulation started\n"); //debug

    int startAddress = loader(objfile);

    for (int i = 0; i < 8; i++)
        printf("%s\n", memory[i]);
    printf("-------------------------\n");

    run(startAddress);

    fclose(objfile);

    printf("fuck\n");
    //printf("%d\n",hex_decimal("2000"));
    printf("%d\n",acc);
    printf("%s\n",memory[hex_decimal("2000")]);
    printf("funk\n");

    return 0;
}