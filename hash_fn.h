#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define size 200

typedef struct opcodeItem
{
	char mn[20];
	char code[4];

}opcodeItem;

opcodeItem* optab[size];

int hashcode(char ch[])
{
	int total = 0;
	int p;

	for (int k=0;k<=strlen(ch);k++)
	{
		total+=(int)ch[k];
	}
	total = total%size;
	p=total;

	return p;
}

void INSERT(char ch[],char cd[])
{
	
	opcodeItem *item = (opcodeItem*)malloc(sizeof(opcodeItem));
	strcpy(item->mn,ch);
	strcpy(item->code,cd);

	int h_code = hashcode(ch);

	while(optab[h_code]!=NULL)
	{
		++h_code;
		h_code %=size;
	}

	optab[h_code] = item;


}

char* search(char ch[])
{
	int h_code = hashcode(ch);
	while(optab[h_code]!=NULL)
	{
		if(strcmp(optab[h_code]->mn,ch)==0)
			return optab[h_code]->code;

		++h_code;
		h_code %= size;
		if (optab[h_code]==NULL)
			return "NULL";
	}
}



void createOptab()
{
	INSERT("ACI","CE");
	INSERT("ADC_A","8F");
	INSERT("ADC_B","88");
	INSERT("ADC_C","89");
	INSERT("ADC_D","8A");
	INSERT("ADC_E","8B");
	INSERT("ADC_H","8C");
	INSERT("ADC_L","8D");
	INSERT("ADC_M","8E");
	INSERT("ADD_A","87");
	INSERT("ADD_B","80");
	INSERT("ADD_C","81");
	INSERT("ADD_D","82");
	INSERT("ADD_E","83");
	INSERT("ADD_H","84");
	INSERT("ADD_L","85");
	INSERT("ADD_M","86");
	INSERT("ADI","C6");
	INSERT("ANA_A","A7");
	INSERT("ANA_B","A0");
	INSERT("ANA_C","A1");
	INSERT("ANA_D","A2");
	INSERT("ANA_E","A3");
	INSERT("ANA_H","A4");
	INSERT("ANA_L","A5");
	INSERT("ANA_M","A6");
	INSERT("ANI","E6");
	INSERT("CALL","CD");
	INSERT("CC","DC");
	INSERT("CM","FC");
	INSERT("CMA","2F");
	INSERT("CMC","3F");
	INSERT("CMP_A","BF");
	INSERT("CMP_B","B8");
	INSERT("CMP_C","B9");
	INSERT("CMP_D","BA");
	INSERT("CMP_E","BB");
	INSERT("CMP_H","BC");
	INSERT("CMP_L","BD");
	INSERT("CMP_M","BE");
	INSERT("CNC","D4");
	INSERT("CNZ","C4");
	INSERT("CP","F4");
	INSERT("CPE","EC");
	INSERT("CPI","FE");
	INSERT("CPO","E4");
	INSERT("CZ","CC");
	INSERT("DAA","27");
	INSERT("DAD_B","09");
	INSERT("DAD_H","19");
	INSERT("DAD_SP","39");
	INSERT("DCR_A","3D");
	INSERT("DCR_B","05");
	INSERT("DCR_C","0D");
	INSERT("DCR_D","15");
	INSERT("DCR_E","1D");
	INSERT("DCR_H","25");
	INSERT("DCR_L","2D");
	INSERT("DCR_M","35");
	INSERT("DCX_B","0B");
	INSERT("DCX_D","1B");
	INSERT("DCX_H","2B");
	INSERT("DCX_SP","3B");
	INSERT("DI","F3");
	INSERT("EI","FB");
	INSERT("HLT","76");
	INSERT("IN","DB");
	INSERT("INR_A","3C");
	INSERT("INR_B","04");
	INSERT("INR_C","0C");
	INSERT("INR_D","14");
	INSERT("INR_E","1C");
	INSERT("INR_H","24");
	INSERT("INR_L","2C");
	INSERT("INR_M","34");
	INSERT("INX_B","03");
	INSERT("INX_D","13");
	INSERT("INX_H","23");
	INSERT("INX_SP","33");
	INSERT("JC","DA");
	INSERT("JM","FA");
	INSERT("JMP","C3");
	INSERT("JNC","D2");
	INSERT("JNZ","C2");
	INSERT("JP","F2");
	INSERT("JPE","EA");
	INSERT("JPO","E2");
	INSERT("JZ","CA");
	INSERT("LDA","3A");
	INSERT("LDAX_B","0A");
	INSERT("LDAX_D","1A");
	INSERT("LHLD","2A");
	INSERT("LXI_B","01");
	INSERT("LXI_D","11");
	INSERT("LXI_H","21");
	INSERT("LXI_SP","31");
	INSERT("MOV_A_A","7F");
	INSERT("MOV_A_B","78");
	INSERT("MOV_A_C","79");
	INSERT("MOV_A_D","7A");
	INSERT("MOV_A_E","7B");
	INSERT("MOV_A_H","7C");
	INSERT("MOV_A_L","7D");
	INSERT("MOV_A_M","7E");
	INSERT("MOV_B_A","47");
	INSERT("MOV_B_B","40");
	INSERT("MOV_B_C","41");
	INSERT("MOV_B_D","42");
	INSERT("MOV_B_E","43");
	INSERT("MOV_B_H","44");
	INSERT("MOV_B_L","45");
	INSERT("MOV_B_M","46");


	
}

/*

int main()
{
createOptab();
char *ch=search("sbfjsbbj");

printf("String is %s",ch);

return 0;
}

*/
