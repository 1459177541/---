#include"config.h"
pList pcTypeList = NULL;

//初始化
int length = 0;
int initPCType() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\pc", "rb")))
	{
		return 1;
	}
	pPCtype p = (pPCtype)malloc(sizeof(PCtype));
	if (NULL==pcTypeList && fread(p, sizeof(PCtype), 1, fp)>0)
	{
		pcTypeList = (pList)malloc(sizeof(List));
		pcTypeList->next = NULL;
		pcTypeList->last = NULL;
		pcTypeList->date.pcType = p;
	}
	pList q = pcTypeList;
	pList o = (pList)malloc(sizeof(List));
	while (fread(p, sizeof(PCtype), 1, fp)>0)
	{
		length += p->num;
		o->type = d_pcType;
		o->date.pcType = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pPCtype)malloc(sizeof(PCtype));
		o = (pList)malloc(sizeof(List));
	}
	return 0;
}

//得到列表
pList getPCtypeList() {
	if (NULL == pcTypeList)
	{
		if (initPCType())
		{
			pcTypeList = (pList)malloc(sizeof(List));
			pcTypeList->last = NULL;
			pcTypeList->next = NULL;
			pPCtype pctype = (pPCtype)malloc(sizeof(PCtype));
			strcpy(pctype->type, "所有类型");
			pctype->num = 0;
			pctype->startId = 0;
			pcTypeList->date.pcType = pctype;
		}
	}
	return pcTypeList;
}

//输出
void prPCtype(pPCtype p, int isOption) {
	printf("     %6s%18s    |%12d    |%12d    %-6s   \n"
		, isOption ? getAttri("L") : getAttri("NL"), p->type, p->num, p->startId, isOption ? getAttri("R") : getAttri("NR"));
}

//修改电脑类型
void editPCtype(int type, pPCtype p) {
	char* typeName = (char*)malloc(16 * sizeof(char));
	char* num = (char*)malloc(16 * sizeof(char));
	char* startID = (char*)malloc(16 * sizeof(char));
	typeName[0] = '\0';
	num[0] = '\0';
	startID[0] = '\0';
	if (0 != type)
	{
		strcpy(typeName, p->type);
	}
	if (1 != type)
	{
		strcpy(num, intToString(p->num));
	}
	if (2 != type)
	{
		strcpy(startID, intToString(p->startId));
	}
	int x = 16;
	gotoxy(x, 6);
	printf("=================================================");
	gotoxy(x, 7);
	printf("|                                               |");
	gotoxy(x, 8);
	printf("|                类型名称：%-21s|", typeName);
	gotoxy(x, 9);
	printf("|                                               |");
	gotoxy(x, 10);
	printf("|                数    量：%-21s|", num);
	gotoxy(x, 11);
	printf("|                                               |");
	gotoxy(x, 12);
	printf("|                起始编号：%-21s|", startID);
	gotoxy(x, 13);
	printf("|                                               |");
	gotoxy(x, 14);
	printf("|                      ");
	OPTION_OK(3 == type);
	printf("                  |");
	gotoxy(x, 15);
	printf("|                                               |");
	gotoxy(x, 16);
	printf("=================================================");
	free(typeName);
	free(num);
	free(startID);

	key key;
	char *in = (char*)malloc(sizeof(char) * 16);
	in[0] = '\0';
	if (0 == type)
	{
		key = input(x + 27, 8, p->type, 0, NUM | LETTER | CHINESE, NULL);
	}
	else if (1 == type)
	{
		length -= p->num;
		key = input(x + 27, 10, in, 0, INTER, NULL);
		p->num = '\0' == in[0] ? p->num : stringToInt(in);
		length += p->num;
		getPCtypeList()->date.pcType->num = length;
	}
	else
	{
		key = input(x + 27, 12, in, 0, INTER, NULL);
		p->startId = '\0' == in[0] ? p->startId : stringToInt(in);
	}
	free(in);
	switch (key)
	{
	case up:
		if (0 == type)
		{
			editPCtype(4, p);
		}
		else {
			editPCtype(type - 1, p);
		}
		break;
	case down:
	case tab:
		if (4 == type)
		{
			editPCtype(0, p);
		}
		else {
			editPCtype(type + 1, p);
		}
		break;
	case enter:
		if (3 != type)
		{
			editPCtype(3, p);
		}
		return 0;
	default:
		editPCtype(type, p);
		break;
	}
}
