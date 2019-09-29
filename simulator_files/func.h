#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//strcat needs coorection at all occurences
//decimal_hex has garbage value 	


/*Assumption:
	1. All data is in decimal.
*/



//name->variable name
//accumator/A->acc
//B->regB
//C->regC
//D->regD
//E->regE
//H->regH
//L->regL
//M->mem (mem=memory[regH*1000+regL])



//pc->program counter(array index of current execution)
//memory[]->memory array


//--------------------FUNCTION-----------------------------//
//char * readnext()->reads next array location and shifts PC->PC+1





//-----------------------------------FLAG------------------------//
//flag->variable
//Carry flag->flagC
//Zero flag->flagZ
//Sign flag->flagS



//-------------------------------CONVERSION---------------------------------//
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
char * decimal_hex(int decimalNumber)//decimal->hex(2 character)
{
	char *ch;
	ch=(char *)malloc(2);
	//ch=(char *)malloc(2*sizeof(char));
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
    char *ch1;
    ch1=(char *)malloc(2);
    *(ch1+1)=*ch;
    *(ch1)=*(ch+1);
    return (char *)ch1;
}
int * decToBinary(int n)//Decimal->Binary(8 bit)//----------------------------------------------------------------------NEEDS  CORRECTION
{ 
    // array to store binary number 
    int binaryNum[8]; 
  	//binaryNum=(int *)malloc(1);
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    }
    while(i<8)
    {
    	binaryNum[i]=0;
    	i++;
    }
    int * bin=binaryNum;
    return bin;
}
int binToDec(int * n)
{
	int decimalNum=0;
	//int rem=0;
	for(int i=0;i<8;i++)
	{
		decimalNum=decimalNum+(*(n+i))*pow(2,7-i);
	}
    return decimalNum;
} 

//------------------MEM UPDATATION FUNTION--------------------//
//USE -> INX H,DCX H,LXI H
void update_mem()
{
	char *h=decimal_hex(regH);
	char *l=decimal_hex(regL);
	char hl[4];
	char H[2];
	H[0]=*h;
	H[1]=*(h+1);
	strcpy(hl,H);
	strcat(hl,l);
	int HL=hex_decimal(hl);
	mem=hex_decimal(memory[HL]);//not tried
}





//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//
void function(char *ch)
{
//-------------------------------ADD-----------------------------//
	if(strcmp(ch, "87")==0)//add A
	{
		acc+=acc;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "80")==0)//add B
	{
		acc+=regB;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "81")==0)//add C
	{
		acc+=regC;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "82")==0)//add D
	{
		acc+=regD;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "83")==0)//add E
	{
		acc+=regE;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "84")==0)//add H
	{
		acc+=regH;
		if(acc>255)
			acc=acc-256;
	}	else if(strcmp(ch, "85")==0)//add L
	{
		acc+=regL;
		if(acc>255)
			acc=acc-256;
	}
	else if(strcmp(ch, "88")==0)//add M
	{
		acc+=mem;
		if(acc>255)
			acc=acc-256;
	}
//----------------------------CMP--------------------------------//
	else if(strcmp(ch, "BF")==0)//CMP A
		flagZ=1;
	else if(strcmp(ch, "B8")==0)//CMP B
	{	
		if(acc>regB)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regB)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "B9")==0)//CMP C
	{	
		if(acc>regC)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regC)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "BA")==0)//CMP D
	{	
		if(acc>regD)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regD)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "BB")==0)//CMP E
	{	
		if(acc>regE)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regE)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "BC")==0)//CMP H
	{	
		if(acc>regH)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regH)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "BD")==0)//CMP L
	{	
		if(acc>regL)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<regL)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
	else if(strcmp(ch, "BE")==0)//CMP M
	{	
		if(acc>mem)
		{
			flagC=0;
			flagZ=0;
		}
		else if(acc<mem)
		{
			flagC=1;
		}
		else
			flagZ=1;
	}
//--------------------------DCR--------------------------------//
	else if(strcmp(ch, "3D")==0)//DCR A
	{
		acc--;
		if(acc<0)
		{
			flagS=1;
			acc=256+acc;
		}
	}
	else if(strcmp(ch, "05")==0)//DCR B
	{
		regB--;
		if(regB<0)
		{
			flagS=1;
			regB=256+regB;
		}
	}
	else if(strcmp(ch, "0D")==0)//DCR C
	{
		regC--;
		if(regC<0)
		{
			flagS=1;
			regC=256+regC;
		}
	}
	else if(strcmp(ch, "15")==0)//DCR D
	{
		regD--;
		if(regD<0)
		{
			flagS=1;
			regD=256+regD;
		}
	}
	else if(strcmp(ch, "1D")==0)//DCR E
	{
		regE--;
		if(regE<0)
		{
			flagS=1;
			regE=256+regE;
		}
	}
	else if(strcmp(ch,"25")==0)//DCR H
	{
		regH--;
		if(regH<0)
		{
			flagS=1;
			regH=256+regH;
		}
	}
	else if(strcmp(ch,"2D")==0)//DCR L
	{
		regL--;
		if(regL<0)
		{
			flagS=1;
			regL=256+regL;
		}
	}
	else if(strcmp(ch,"35")==0)//DCR M
	{
		mem--;
		if(mem<0)
		{
			flagS=1;
			mem=256+mem;
		}
	}
//-------------------------INR------------------------------------//
	else if(strcmp(ch, "3C")==0)//INR A
		acc++;
	else if(strcmp(ch, "04")==0)//INR B
		regB++;
	else if(strcmp(ch, "0C")==0)//INR C
		regC++;
	else if(strcmp(ch, "14")==0)//INR D
		regD++;
	else if(strcmp(ch, "1C")==0)//INR E
		regE++;
	else if(strcmp(ch,"24")==0)//INR H
		regH++;
	else if(strcmp(ch,"2C")==0)//INR L
		regL++;
	else if(strcmp(ch,"34")==0)//INR M
		mem++;
//-------------------------MOV A,X----------------------------------//
	else if(strcmp(ch, "7F")==0)//MOV A,A
		acc=acc;
	else if(strcmp(ch, "78")==0)//MOV A,B
		acc=regB;
	else if(strcmp(ch, "79")==0)//MOV A,C
		acc=regC;
	else if(strcmp(ch, "7A")==0)//MOV A,D
		acc=regD;
	else if(strcmp(ch, "7B")==0)//MOV A,E
		acc=regE;
	else if(strcmp(ch, "7C")==0)//MOV A,H
		acc=regH;
	else if(strcmp(ch, "7D")==0)//MOV A,L
		acc=regL;
	else if(strcmp(ch, "7E")==0)//MOV A,M
		acc=mem;
//------------------------MOV B,X-----------------------------//
	else if(strcmp(ch, "47")==0)//MOV B,A
		regB=acc;
	else if(strcmp(ch, "40")==0)//MOV B,B
		regB=regB;
	else if(strcmp(ch, "41")==0)//MOV B,C
		regB=regC;
	else if(strcmp(ch, "42")==0)//MOV B,D
		regB=regD;
	else if(strcmp(ch, "43")==0)//MOV B,E
		regB=regE;
	else if(strcmp(ch, "44")==0)//MOV B,H
		regB=regH;
	else if(strcmp(ch, "45")==0)//MOV B,L
		regB=regL;
	else if(strcmp(ch, "46")==0)//MOV B,M
		regB=mem;
//-----------------------MOV C,X--------------------------//
	else if(strcmp(ch, "4F")==0)//MOV C,A
		regC=acc;
	else if(strcmp(ch, "48")==0)//MOV C,B
		regC=regB;
	else if(strcmp(ch, "49")==0)//MOV C,C
		regC=regC;
	else if(strcmp(ch, "4A")==0)//MOV C,D
		regC=regD;
	else if(strcmp(ch, "4B")==0)//MOV C,E
		regC=regE;
	else if(strcmp(ch, "4C")==0)//MOV C,H
		regC=regH;
	else if(strcmp(ch, "4D")==0)//MOV C,L
		regC=regL;
	else if(strcmp(ch, "4E")==0)//MOV C,M
		regC=mem;
//-------------------------MOV D,X------------------------//
	else if(strcmp(ch, "57")==0)//MOV D,A
		regD=acc;
	else if(strcmp(ch, "50")==0)//MOV D,B
		regD=regB;
	else if(strcmp(ch, "51")==0)//MOV D,C
		regD=regC;
	else if(strcmp(ch, "52")==0)//MOV D,D
		regD=regD;
	else if(strcmp(ch, "53")==0)//MOV D,E
		regD=regE;
	else if(strcmp(ch, "54")==0)//MOV D,H
		regD=regH;
	else if(strcmp(ch, "55")==0)//MOV D,L
		regD=regL;
	else if(strcmp(ch, "56")==0)//MOV D,M
		regD=mem;
//----------------------------MOV E,X----------------------//
	else if(strcmp(ch, "5F")==0)//MOV E,A
		regE=acc;
	else if(strcmp(ch, "58")==0)//MOV E,B
		regE=regB;
	else if(strcmp(ch, "59")==0)//MOV E,C
		regE=regC;
	else if(strcmp(ch, "5A")==0)//MOV E,D
		regE=regD;
	else if(strcmp(ch, "5B")==0)//MOV E,E
		regE=regE;
	else if(strcmp(ch, "5C")==0)//MOV E,H
		regE=regH;
	else if(strcmp(ch, "5D")==0)//MOV E,L
		regE=regL;
	else if(strcmp(ch, "5E")==0)//MOV E,M
		regE=mem;
//-------------------------MOV H,X-------------------------//
	else if(strcmp(ch, "67")==0)//MOV H,A
		regH=acc;
	else if(strcmp(ch, "60")==0)//MOV H,B
		regH=regB;
	else if(strcmp(ch, "61")==0)//MOV H,C
		regH=regC;
	else if(strcmp(ch, "62")==0)//MOV H,D
		regH=regD;
	else if(strcmp(ch, "63")==0)//MOV H,E
		regH=regE;
	else if(strcmp(ch, "64")==0)//MOV H,H
		regH=regH;
	else if(strcmp(ch, "65")==0)//MOV H,L
		regH=regL;
	else if(strcmp(ch, "66")==0)//MOV H,M
		regH=mem;
//------------------------MOV L,X--------------------------//
	else if(strcmp(ch, "6F")==0)//MOV L,A
		regL=acc;
	else if(strcmp(ch, "68")==0)//MOV L,B
		regL=regB;
	else if(strcmp(ch, "69")==0)//MOV L,C
		regL=regC;
	else if(strcmp(ch, "6A")==0)//MOV L,D
		regL=regD;
	else if(strcmp(ch, "6B")==0)//MOV L,E
		regL=regE;
	else if(strcmp(ch, "6C")==0)//MOV L,H
		regL=regH;
	else if(strcmp(ch, "6D")==0)//MOV L,L
		regL=regL;
	else if(strcmp(ch, "6E")==0)//MOV L,M
		regL=mem;
//--------------------------MOV M,X--------------------------//
	else if(strcmp(ch, "67")==0)//MOV M,A
		mem=acc;
	else if(strcmp(ch, "60")==0)//MOV M,B
		mem=regB;
	else if(strcmp(ch, "61")==0)//MOV M,C
		mem=regC;
	else if(strcmp(ch, "62")==0)//MOV M,D
		mem=regD;
	else if(strcmp(ch, "63")==0)//MOV M,E
		mem=regE;
	else if(strcmp(ch, "64")==0)//MOV M,H
		mem=regH;
	else if(strcmp(ch, "65")==0)//MOV M,L
		mem=regL;
	else if(strcmp(ch, "66")==0)//MOV M,M
		mem=mem;
//---------------------ACI Data-----------------------//
	else if(strcmp(ch, "CE")==0)//ACI DATA
	{
		char *D=readnext();
		int d=hex_decimal(D);
		acc+=d;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
//-------------------------ADC X----------------------//
	else if(strcmp(ch, "8F")==0)//ADC A
	{
		acc+=acc;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "88")==0)//ADC B
	{
		acc+=regB;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "89")==0)//ADC C
	{
		acc+=regC;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "8A")==0)//ADC D
	{
		acc+=regD;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "8B")==0)//ADC E
	{
		acc+=regE;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "8C")==0)//ADC H
	{
		acc+=regH;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "8D")==0)//ADC L
	{
		acc+=regL;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
	else if(strcmp(ch, "8E")==0)//ADC M
	{
		acc+=mem;
		if(acc>255)
		{
			flagC=1;
			acc-=256;
		}
	}
//------------------------ADI Data-------------------//
	else if(strcmp(ch, "C6")==0)//ADI Data
	{
		char *D=readnext();
		int d=hex_decimal(D);
		acc+=d;
		if(acc>255)
			acc=acc-256;
	}
//-----------------------ANA X---------------------------//
	else if(strcmp(ch, "A7")==0)//ANA A
	{
		acc=(acc&acc);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A0")==0)//ANA B
	{
		acc=(acc&regB);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A1")==0)//ANA C
	{
		acc=(acc&regC);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A2")==0)//ANA D
	{
		acc=(acc&regD);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A3")==0)//ANA E
	{
		acc=(acc&regE);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A4")==0)//ANA H
	{
		acc=(acc&regH);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A5")==0)//ANA L
	{
		acc=(acc&regL);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
	else if(strcmp(ch, "A6")==0)//ANA M
	{
		acc=(acc&mem);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
//--------------------------ANI Data-----------------------------//
	else if(strcmp(ch, "E6")==0)//ANI DATA
	{
		char *D=readnext();
		int d=hex_decimal(D);
		acc=(acc&d);
		/*int * bin=decToBinary(acc);
		if(*(bin+7)==0)
			flagC=0;
		else
			flagC=1;
		if(*(bin+2)==0)
			flagZ=0;
		else
			flagZ=1;*/
	}
//------------------------CALL Label--------------------//
	else if(strcmcp(ch, "E6")==0)//CALL LABEL
	{
		char *D=readnext();
		//int d=hex_decimal(D);
		char *E=readnext();
		char de[4];
		char H[2];
		H[0]=*E;
		H[1]=*(E+1);
		strcpy(de,H);
		strcat(de,D);
		int e=hex_decimal(de);
		pc=e;//doubt
		//----------------------------------------------------------------------------------------------work not done//
	}
//------------------------DCX X----------------------//DCX SP not implemented
	else if(strmp(ch, "0B")==0)//DCX B
	{
		if(regC>0)
			regC--;
		else
		{
			regC=255;
			regB--;
		}
		if(regB==0 && regC==0)
			flagZ=1;
	}
	else if(strcmp(ch, "1B")==0)//DCX D
	{
		if(regE>0)
			regE--;
		else
		{
			regE=255;
			regD--;
		}
		if(regE==0 && regD==0)
			flagZ=1;
	}
	else if(strcmp(ch, "1B")==0)//DCX H
	{
		if(regL>0)
			regL--;
		else
		{
			regL=255;
			regH--;
		}
		if(regH==0 && regL==0)
			flagZ=1;
		update_mem();
	}
//---------------------------INX X-----------------------------//(INX SP not done)
	else if(strmp(ch, "0B")==0)//INX B
	{
		if(regC<255)
			regC++;
		else
		{
			regC=0;
			regB++;
		}
	}
	else if(strcmp(ch, "1B")==0)//INX D
	{
		if(regE<255)
			regE++;
		else
		{
			regE=0;
			regD++;
		}
	}
	else if(strcmp(ch, "1B")==0)//INX H
	{
		if(regL<255)
			regL++;
		else
		{
			regL=0;
			regH++;
		}
		update_mem();
	}
//--------------------------LDA Address----------------------//
	else if(strcmp(ch, "3A")==0)//LDA ADDRESS
	{
		char *D=readnext();
		char *E=readnext();
		char de[4];
		char H[2];
		H[0]=*E;
		H[1]=*(E+1);
		strcpy(de,H);
		strcat(de,D);
		int e=hex_decimal(de);
		//int temp=r*100+d;//doubt
		acc=hex_decimal(memory[e]);
	}
//--------------------------LDAX X------------------------------//
	else if(strcmp(ch, "0A")==0)//LDAX B
	{
		char *b=decimal_hex(regB);
		char *c=decimal_hex(regC);
		char bc[4];
		char H[2];
		H[0]=*b;
		H[1]=*(b+1);
		strcpy(bc,H);
		strcat(bc,c);
		int e=hex_decimal(bc);
		acc=hex_decimal(memory[e]);
	}
	else if(strcmp(ch, "1A")==0)//LDAX D
	{
		char *b=decimal_hex(regD);
		char *c=decimal_hex(regE);
		char bc[4];
		char H[2];
		H[0]=*b;
		H[1]=*(b+1);
		strcpy(bc,H);
		strcat(bc,c);
		int e=hex_decimal(bc);
		acc=hex_decimal(memory[e]);
	}
//-----------------------LHLD address------------------------//
	else if(strcmp(ch, "2A")==0)//LHLD ADDRESS
	{
		char *l=readnext();
		char *h=readnext();
		char hl[4];
		char H[2];
		H[0]=*h;
		H[1]=*(h+1);
		strcpy(hl,H);
		strcat(hl,l);
		int HL=hex_decimal(hl);
		regL=hex_decimal(memory[HL]);
		regH=hex_decimal(memory[HL+1]);
		//int H=hex_decimal(h);
		//int L=hex_decimal(l);
	}
//------------------------LXI X-----------------------------//(LXI SP not done)
	else if(strcmp(ch, "01")==0)//LXI B
	{
		char *c=readnext();
		char *b=readnext();
		regB=hex_decimal(b);
		regC=hex_decimal(c);
	}
	else if(strcmp(ch, "11")==0)//LXI D
	{
		char *c=readnext();
		char *b=readnext();
		regD=hex_decimal(b);
		regE=hex_decimal(c);
	}
	else if(strcmp(ch, "21")==0)//LXI H
	{
		char *c=readnext();
		char *b=readnext();
		regH=hex_decimal(b);
		regL=hex_decimal(c);
		update_mem();
	}
//----------------------MVI X,Data-------------------------------//
	else if(strcmp(ch, "3E")==0)//MVI A,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		acc=D;
	}
	else if(strcmp(ch, "06")==0)//MVI B,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regB=D;
	}
	else if(strcmp(ch, "0E")==0)//MVI C,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regC=D;
	}
	else if(strcmp(ch, "16")==0)//MVI D,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regD=D;
	}
	else if(strcmp(ch, "1E")==0)//MVI E,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regE=D;
	}
	else if(strcmp(ch, "26")==0)//MVI H,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regH=D;
	}
	else if(strcmp(ch, "2E")==0)//MVI L,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		regL=D;
	}
	else if(strcmp(ch, "36")==0)//MVI M,DATA
	{
		char *d=readnext();
		int D=hex_decimal(d);
		mem=D;
	}
//--------------------------NOP------------------------------//
	else if(strcmp(ch, "00")==0)//NOP
	{
		//Nothing
	}
//------------------------ORA X--------------------------------//
	else if(strcmp(ch, "B7")==0)//ORA A
	{
		acc=(acc|acc);
	}
	else if(strcmp(ch, "B0")==0)//ORA B
	{
		acc=(acc|regB);
	}
	else if(strcmp(ch, "B1")==0)//ORA C
	{
		acc=(acc|regC);
	}
	else if(strcmp(ch, "B2")==0)//ORA D
	{
		acc=(acc|regD);
	}
	else if(strcmp(ch, "B3")==0)//ORA E
	{
		acc=(acc|regE);
	}
	else if(strcmp(ch, "B4")==0)//ORA H
	{
		acc=(acc|regH);
	}
	else if(strcmp(ch, "B5")==0)//ORA L
	{
		acc=(acc|regL);
	}
	else if(strcmp(ch, "B6")==0)//ORA M
	{
		acc=(acc|mem);
	}
//-------------------------ORI Data----------------------//
	else if(strcmp(ch, "F6")==0)//ORA DATA
	{
		char *D=readnext();
		int d=hex_decimal(D);
		acc=(acc|d);
	}
//------------------------RAR------------------------------//
	else if(strcmp(ch, "1F")==0)//RAR
	{
		int * bin=decToBinary(acc);
		//flagC=0;
		int temp=*bin;
		for(int i=0;i<7;i++)
		{
			*(bin+i)=*(bin+i+1);
		}
		*(bin+7)=flagC;
		flagC=temp;
		int npl[8];
		for(int i=0;i<8;i++)
		{
			npl[7-i]=*(bin+i);
		}
		int p=binToDec(npl);
		acc=p;
	}
//-------------------------RAL-------------------------------//
	else if(strcmp(ch, "17")==0)//RAL
	{
		int * bin=decToBinary(acc);
		//flagC=0;
		int temp=*(bin+7);
		for(int i=0;i<7;i++)
		{
			*(bin+7-i)=*(bin+6-i);
		}
		*(bin)=flagC;
		flagC=temp;
		int npl[8];
		for(int i=0;i<8;i++)
		{
			npl[7-i]=*(bin+i);
		}
		int p=binToDec(npl);
		acc=p;
	}
//------------------------RRC-------------------------------//
	else if(strcmp(ch, "0F")==0)//RRC
	{
		int *bin=decToBinary(acc);
		int temp=*(bin);
		for(int i=0;i<7;i++)
		{
			*(bin+i)=*(bin+i+1);
		}
		*(bin+7)=temp;
		int npl[8];
		for(int i=0;i<8;i++)
		{
			npl[7-i]=*(bin+i);
		}
		int p=binToDec(npl);
		acc=p;
	}
//---------------------------RLC----------------------------//
	else if(strcmp(ch, "07")==0)//RLC
	{
		int * bin=decToBinary(acc);
		//flagC=0;
		int temp=*(bin+7);
		for(int i=0;i<7;i++)
		{
			*(bin+7-i)=*(bin+6-i);
		}
		*(bin)=temp;
		//flagC=temp;
		int npl[8];
		for(int i=0;i<8;i++)
		{
			npl[7-i]=*(bin+i);
		}
		int p=binToDec(npl);
		acc=p;
	}
//-------------------------RST 5--------------------------------//
	else if(strcmp(ch, "EF")==0)//RST 5
	{
		printf("%s","\n\nEnd of Program");
		break;
	}
//--------------------------STA Address-------------------------//Need to verify
	else if(strcmp(ch, "32")==0)//STA ADDRESS
	{
		char *l=readnext();
		char *h=readnext();
		char hl[4];
		char H[2];
		H[0]=*h;
		H[1]=*(h+1);
		strcpy(hl,H);
		strcat(hl,l);
		int HL=hex_decimal(hl);
		char * temp=decimal_hex(acc);
		memory[HL]=temp;
		//strcpy(memory[HL],temp);
	}
//-------------------------STAX X--------------------------------//
	else if(strcmp(ch, "02")==0)//STAX B
	{
		char *h=decimal_hex(regB);
		char *l=decimal_hex(regC);
		char hl[4];
		char H[2];
		H[0]=*h;
		H[1]=*(h+1);
		strcpy(hl,H);
		strcat(hl,l);
		int HL=hex_decimal(hl);
		char * temp=decimal_hex(acc);
		memory[HL]=temp;
	}
	else if(strcmp(ch, "12")==0)//STAX D
	{
		char *h=decimal_hex(regD);
		char *l=decimal_hex(regE);
		char hl[4];
		char H[2];
		H[0]=*h;
		H[1]=*(h+1);
		strcpy(hl,H);
		strcat(hl,l);
		int HL=hex_decimal(hl);
		char * temp=decimal_hex(acc);
		memory[HL]=temp;
	}
//--------------------------XRA X-----------------------------//
	else if(strcmp(ch, "AF")==0)//XRA A
	{
		acc=(acc^acc);
	}
	else if(strcmp(ch, "A8")==0)//XRA B
	{
		acc=(acc^regB);
	}
	else if(strcmp(ch, "A9")==0)//XRA C
	{
		acc=(acc^regC);
	}
	else if(strcmp(ch, "AA")==0)//XRA D
	{
		acc=(acc^regD);
	}
	else if(strcmp(ch, "AB")==0)//XRA E
	{
		acc=(acc^regE);
	}
	else if(strcmp(ch, "AC")==0)//XRA H
	{
		acc=(acc^regH);
	}
	else if(strcmp(ch, "AD")==0)//XRA L
	{
		acc=(acc^regL);
	}
	else if(strcmp(ch, "AE")==0)//XRA M
	{
		acc=(acc^mem);
	}
//-----------------------XRI Data-----------------------------//
	else if(strcmp(ch, "EE")==0)//XRI DATA
	{
		char *D=readnext();
		int d=hex_decimal(D);
		acc=(acc^d);
	}
//-------------------------SUB X-------------------------------//
	else if(strcmp(ch, "97")==0)//SUB A
	{
		acc=0;
	}
	else if(strcmp(ch, "90")==0)//SUB B
	{
		acc-=regB;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "91")==0)//SUB C
	{
		acc-=regC;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "92")==0)//SUB D
	{
		acc-=regD;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "93")==0)//SUB E
	{
		acc-=regE;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "94")==0)//SUB H
	{
		acc-=regH;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "95")==0)//SUB L
	{
		acc-=regL;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
	else if(strcmp(ch, "96")==0)//SUB M
	{
		acc-=mem;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
//----------------------------SUI Data-----------------------//
	else if(strcmp(ch, "90")==0)//SUB B
	{
		char *d=readnext();
		int D=hex_decimal(d);
		acc-=D;
		if(acc<0)
		{
			acc=256+acc;
			flagS=1;
		}
		else
			flagS=0;
	}
//--------------------------------------------------------//
	else
		printf("Error");
}
