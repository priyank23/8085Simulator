#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define size 250

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
	INSERT("MOVE_B_M","46");
	INSERT("MOV_C_A","4F");
	INSERT("MOV_C_B","48");
	INSERT("MOV_C_C","49");
	INSERT("MOV_C_D","4A");
	INSERT("MOV_C_E","4B");
	INSERT("MOV_C_H","4C");
	INSERT("MOV_C_L","4D");
	INSERT("MOV_C_M","4E");
	INSERT("MOV_D_A","57");
	INSERT("MOV_D_B","50");
	INSERT("MOV_D_C","51");
	INSERT("MOV_D_D","52");
	INSERT("MOV_D_E","53");
	INSERT("MOV_D_H","54");
	INSERT("MOV_D_L","55");
	INSERT("MOV_D_M","56");
	INSERT("MOVE_E_A","5F");
	INSERT("MOV_E_B","58");
	INSERT("MOV_E_C","59");
	INSERT("MOV_E_D","5A");
	INSERT("MOV_E_E","5B");
	INSERT("MOV_E_H","5C");
	INSERT("MOV_E_L","5D");
	INSERT("MOV_E_M","5E");
	INSERT("MOV_H_A","67");
	INSERT("MOV_H_B","60");
	INSERT("MOV_H_C","61");
	INSERT("MOV_H_D","62");
	INSERT("MOV_H_E","63");
	INSERT("MOV_H_H","64");
	INSERT("MOV_H_L","65");
	INSERT("MOV_H_M","66");
	INSERT("MOV_L_A","6F");
	INSERT("MOV_L_B","68");
	INSERT("MOV_L_C","69");
	INSERT("MOV_L_D","6A");
	INSERT("MOV_L_E","6B");
	INSERT("MOV_L_H","6C");
	INSERT("MOV_L_L","6D");
	INSERT("MOV_L_M","6E");
	INSERT("MOV_M_A","77");
	INSERT("MOV_M_B","70");
	INSERT("MOV_M_C","71");
	INSERT("MOV_M_D","72");
	INSERT("MOV_M_E","73");
	INSERT("MOV_M_H","74");
	INSERT("MOV_M_L","75");
	INSERT("MVI_A","3E");
	INSERT("MVI_B","06");
	INSERT("MVI_C","0E");
	INSERT("MVI_D","16");
	INSERT("MVI_E","1E");
	INSERT("MVI_H","26");
	INSERT("MVI_L","2E");
	INSERT("MVI_M","36");
	INSERT("NOP","00");
	INSERT("ORA_A","B7");
	INSERT("ORA_B","B0");
	INSERT("ORA_C","B1");
	INSERT("ORA_D","B2");
	INSERT("ORA_E","B3");
	INSERT("ORA_H","B4");
	INSERT("ORA_L","B5");
	INSERT("ORA_M","B6");
	INSERT("ORI","F6");
	INSERT("OUT","D3");
	INSERT("PHCL","E9");
	INSERT("POP_B","C1");
	INSERT("POP_D","D1");
	INSERT("POP_H","E1");
	INSERT("POP_PSW","F1");
	INSERT("PUSH_B","C5");
	INSERT("PUSH_D","D5");
	INSERT("PUSH_H","E5");
	INSERT("PUSH_PSW","F5");
	INSERT("RAL","17");
	INSERT("RAR","1F");
	INSERT("RC","D8");
	INSERT("RET","C9");
	INSERT("RIM","20");
	INSERT("RLC","07");
	INSERT("RM","F8");
	INSERT("RNC","D0");
	INSERT("RNZ","C0");
	INSERT("RP","F0");
	INSERT("RPE","E8");
	INSERT("RPO","E0");
	INSERT("RRC","0F");
	INSERT("RST_0","C7");
	INSERT("RST_1","CF");
	INSERT("RST_2","D7");
	INSERT("RST_3","DF");
	INSERT("RST_4","E7");
	INSERT("RST_5","EF");
	INSERT("RST_6","F7");
	INSERT("RST_7","FF");
	INSERT("RZ","C8");
	INSERT("SBB_A","9F");
	INSERT("SBB_B","98");
	INSERT("SBB_C","99");
	INSERT("SBB_D","9A");
	INSERT("SBB_E","9B");
	INSERT("SBB_H","9C");
	INSERT("SBB_L","9D");
	INSERT("SBB_M","9E");
	INSERT("SBI","DE");
	INSERT("SHLD","22");
	INSERT("SIM","30");
	INSERT("SPHL","F9");
	INSERT("STA","32");
	INSERT("STAX_B","02");
	INSERT("STAX_D","12");
	INSERT("STC","37");
	INSERT("SUB_A","97");
	INSERT("SUB_B","90");
	INSERT("SUB_C","91");
	INSERT("SUB_D","92");
	INSERT("SUB_E","93");
	INSERT("SUB_H","94");
	INSERT("SUB_L","95");
	INSERT("SUB_M","96");
	INSERT("SUI","D6");
	INSERT("XCHG","EB");
	INSERT("XRA_A","AF");
	INSERT("XRA_B","A8");
	INSERT("XRA_C","A9");
	INSERT("XRA_D","AA");
	INSERT("XRA_E","AB");
	INSERT("XRA_H","AC");
	INSERT("XRA_L","AD");
	INSERT("XRA_M","AE");
	INSERT("XRI","EE");
	INSERT("XTHL","E3");



	
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
