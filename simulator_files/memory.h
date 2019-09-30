#include <stdio.h>
#include <stdlib.h>

int acc = 0;
int regA;
int regB;
int regC;
int regD;
int regE;
int regH;
int regL;
int mem;
char memory[10000][3];
int relocationCounter;
int pc;
int flagC = 0;
int flagZ = 0;
int flagS = 0;
int flagP = 0;

struct Stack
{
    int stack[1000];
    int head;
} systemStack;

// Structure for system stack
void systemStackPush(int val)
{
    if (systemStack.head >= 1000)
    {
        printf("System stack overflow!\n");
        exit(0);
    }
    systemStack.stack[++(systemStack.head)] = val;
}
int systemStackPop()
{
    if (systemStack.head == 0)
    {
        printf("System stack underflow!\n");
        exit(0);
    }
    return systemStack.stack[(systemStack.head)--];
}
int systemStackTop()
{
    if (systemStack.head == -1)
    {
        printf("System stack underflow!\n");
        exit(0);
    }
    return systemStack.stack[systemStack.head];
}

//initialize the machine
void initializeMachine()
{
    relocationCounter = 0;
    pc = 0;
    flagC = 0;
    flagZ = 0;
}

//returns the current opcode and increments the pc
char *readnext()
{
    return memory[++pc];
}