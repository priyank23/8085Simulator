#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define len 200

typedef struct symmap
{
	char mn[20];
	int add;
}symmap;

symmap* symtab[len];

int hashcode2(char ch[])
{
	int total = 0;
	int p;

	for (int k=0;k<=strlen(ch);k++)
	{
		total+=(int)ch[k];
	}
	total = total%len;
	p=total;

	return p;
}

void INSERT2(char ch[],int cd)
{
    // printf("Insert in symtab");
	symmap *item = (symmap*)malloc(sizeof(symmap));
	strcpy(item->mn,ch);
	item->add=cd;

	int h_code = hashcode2(ch);

	while(symtab[h_code]!=NULL)
	{
		++h_code;
		h_code %=len;
	}

	symtab[h_code] = item;


}

int search2(char ch[])
{
	int h_code = hashcode2(ch);
	while(symtab[h_code]!=NULL)
	{
		if(strcmp(symtab[h_code]->mn,ch)==0)
			return symtab[h_code]->add;

		++h_code;
		h_code %= size;
		if (symtab[h_code]==NULL)
			return -1;
	}
    return -1;
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
