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
void editPCtype(int type, pList p) {
	char* typeName = (char*)malloc(16 * sizeof(char));
	char* num = (char*)malloc(16 * sizeof(char));
	char* startID = (char*)malloc(16 * sizeof(char));
	typeName[0] = '\0';
	num[0] = '\0';
	startID[0] = '\0';
	if (0 != type)
	{
		strcpy(typeName, p->date.pcType->type);
	}
	if (1 != type)
	{
		strcpy(num, intToString(p->date.pcType->num));
	}
	if (2 != type)
	{
		strcpy(startID, intToString(p->date.pcType->startId));
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
	printf("|          ");
	OPTION_OK(3 == type);
	printf("        ");
	OPTION_CANCEL(4 == type);
	printf("          |");
	gotoxy(x, 15);
	printf("|                                               |");
	gotoxy(x, 16);
	printf("=================================================");
	free(typeName);
	free(num);
	free(startID);
	if (4 == type)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			editPCtype(2, p);
			return;
		case down:
		case tab:
			editPCtype(0, p);
			return;
		case enter:
			p->last->next = p->next;
			if (NULL!=p->next)
			{
				p->next->last = p->last;
			}
			free(p);
			return;
		default:
			break;
		}
		return editPCtype(0, p);
	}

	key key;
	char *in = (char*)malloc(sizeof(char) * 16);
	in[0] = '\0';
	if (0 == type)
	{
		key = input(x + 27, 8, p->date.pcType->type, 0, NUM | LETTER | CHINESE, NULL);
	}
	else if (1 == type)
	{
		length -= p->date.pcType->num;
		key = input(x + 27, 10, in, 0, INTER, NULL);
		p->date.pcType->num = '\0' == in[0] ? p->date.pcType->num : stringToInt(in);
		length += p->date.pcType->num;
	}
	else
	{
		key = input(x + 27, 12, in, 0, INTER, NULL);
		p->date.pcType->startId = '\0' == in[0] ? p->date.pcType->startId : stringToInt(in);
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

/*********************************************************
 * 已废弃
 *********************************************************
//设置网吧电脑类型
void setPCType(int type) {
	int length = 0;
	int number = 0;
	pList q = getPCtypeList();
	pList op;
	while (length<type - 10 && NULL != q)
	{
		length++;
		q = q->next;
	}
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n\n                                 请设置您的网吧规模\n\n");
	printf("                  ================================================            \n");
	printf("                    类型         |      数量      |    起始编号               \n");
	if (0 != length)
	{
		printf("                      ++++++     |     ++++++     |    ++++++                \n");
	}
	else
	{
		printf("                                 |                |                          \n");
	}
	int pr = 0;
	while (NULL != q->next)
	{
		q = q->next;
		length++;
		number = q->date->num + q->date->startId;
		if (length == type)
		{
			op = q;
		}
		if (pr<10)
		{
			pr++;
			prPCtype(q->date, length == type);
		}
		else {
			break;
		}
	}
	for (int i = pr; i < 10; i++)
	{
		printf("                                 |                |                          \n");
	}
	if ((NULL != q && type >= 0) || (10 < length && type < 0))
	{
		printf("                      ++++++     |     ++++++     |    ++++++                \n");
	}
	else
	{
		printf("                                 |                |                          \n");
	}
	printf("                  ================================================            \n");
	if (0 == length && 1 == type)
	{
		type = 0;
	}
	printf("\n                         ");
	prOption("  新建  ", 0 == type, 13);
	printf("         ");
	prOption("  完成  ", -1 == type, 13);
	printf("                  ");
	while (1)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			if (0 == type)
			{
				if (0 == length)
				{
					setPCType(-1);
				}
				else
				{
					setPCType(length + 1);
				}
			}
			else if (-1 == type)
			{
				setPCType(0);
			}
			else if (1 == type)
			{
				setPCType(-1);
			}
			else
			{
				setPCType(type - 1);
			}
			return;
			break;
		case down:
		case tab:
			if (0 == type)
			{
				setPCType(-1);
			}
			else if (-1 == type)
			{
				if (0 == length)
				{
					setPCType(0);
				}
				else
				{
					setPCType(1);
				}
			}
			else if (length == type)
			{
				setPCType(0);
			}
			else
			{
				setPCType(type + 1);
			}
			return;
		case enter:
			if (0 == type)
			{
				pPCtype p = (pPCtype)malloc(sizeof(PCtype));
				p->startId = number;
				p->num = 0;
				p->type[0] = '\0';
				while (NULL != q->next)
				{
					q = q->next;
				}
				pList pl = (pList)malloc(sizeof(PCtypeList));
				pl->last = q;
				pl->next = NULL;
				pl->date = p;
				q->next = pl;
				editPCtype(0, pl);
				setPCType(type);
				return;
			}
			else if (-1 == type)
			{
				return;
			}
			else
			{
				editPCtype(0, op);
				setPCType(type);
				return;
			}
			break;
		case esc:
		{
			return;
		}
		break;
		default:
			break;
		}
	}
}

//保存
void savePCtype() {
	if (NULL == getPCtypeList())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\pc", "wb")))
	{
		return;
	}
	pList p = getPCtypeList();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(PCtype), 1, fp))
		{
			p = p->next;

		}
	}
}
*/
