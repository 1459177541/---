#include"config.h"
pList cardTypeLists = NULL;

//��ʼ��
int initCardType() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\cardType", "rb")))
	{
		return 1;
	}
	pCardType p = (pCardType)malloc(sizeof(cardType));
	if (NULL==cardTypeLists && fread(p,sizeof(cardType),1,fp)>0)
	{
		cardTypeLists = (pList)malloc(sizeof(pList));
		cardTypeLists->next = NULL;
		cardTypeLists->last = NULL;
		cardTypeLists->date.cardType = p;
	}
	pList q = cardTypeLists;
	pList o = (pList)malloc(sizeof(List));
	while (fread(p, sizeof(cardType), 1, fp)>0)
	{
		o->type = d_cardType;
		o->date.cardType = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pCardType)malloc(sizeof(cardType));
		o = (pList)malloc(sizeof(List));
	}
	return 0;
}

//�õ��б�
pList getCardTypeList() {
	if (NULL == cardTypeLists)
	{
		if (initCardType())
		{
			cardTypeLists = (pList)malloc(sizeof(List));
			cardTypeLists->last = NULL;
			cardTypeLists->next = NULL;
			pCardType cardTypeHeard = (pCardType)malloc(sizeof(cardType));
			strcpy(cardTypeHeard->name, "��������");
			cardTypeHeard->price = 0;
			cardTypeLists->date.cardType = cardTypeHeard;
		}
	}
	return cardTypeLists;
}

//���
void prCardType(pCardType p, int isOption) {
	printf("            %6s%18s     |%7.2lf              %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), p->name, p->price, isOption ? getAttri("R") : getAttri("NR"));
}

//�޸Ļ�Ա������
void editCardType(int type, pCardType p) {
	char* typeName = (char*)malloc(16 * sizeof(char));
	char* num = (char*)malloc(16 * sizeof(char));
	typeName[0] = '\0';
	num[0] = '\0';
	if (0 != type)
	{
		strcpy(typeName, p->name);
	}
	if (1 != type)
	{
		sprintf(num, "%.2lf", p->price);
	}
	int x = 16;
	gotoxy(x, 7);
	printf("=================================================");
	gotoxy(x, 8);
	printf("|                                               |");
	gotoxy(x, 9);
	printf("|              ��Ա�����ƣ�%-21s|", typeName);
	gotoxy(x, 10);
	printf("|                                               |");
	gotoxy(x, 11);
	printf("|                ��    ��%-21s|", num);
	gotoxy(x, 12);
	printf("|                                               |");
	gotoxy(x, 13);
	printf("|                      ");
	OPTION_OK(3 == type);
	printf("                  |");
	gotoxy(x, 14);
	printf("|                                               |");
	gotoxy(x, 15);
	printf("=================================================");
	gotoxy(x, 16);
	free(typeName);
	free(num);

	key key;
	if (0 == type)
	{
		key = input(x + 27, 9, p->name, 0, NUM | LETTER | CHINESE, NULL);
	}
	else
	{
		char *in = (char *)malloc(sizeof(char) * 16);
		key = input(x + 27, 11, in, 0, NUM, NULL);
		p->price = '\0' == in[0] ? p->price : atof(in);
		free(in);
	}
	switch (key)
	{
	case up:
		if (1 == type)
		{
			editCardType(3, p);
		}
		else {
			editCardType(type - 1, p);
		}
		break;
	case down:
	case tab:
		if (3 == type)
		{
			editCardType(0, p);
		}
		else {
			editCardType(type + 1, p);
		}
		break;
	case enter:
		break;
	default:
		editCardType(type, p);
		break;
	}
}

/*********************************************************
 * �ѷ���
 *********************************************************
//���û�Ա������
void setCardType(int type) {
	int length = 0;
	pList q = getList();
	pList op = q;
	while (length<type - 10 && NULL != q)
	{
		length++;
		q = q->next;
	}
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n\n                             �������������ɻ�Ա������\n\n");
	printf("                  ================================================            \n");
	printf("                        ��Ա������       |     �۸�           \n");
	if (0 != length)
	{
		printf("                              ++++++     |     ++++++               \n");
	}
	else
	{
		printf("                                         |                                  \n");
	}
	int pr = 0;
	while (NULL != q->next)
	{
		length++;
		q = q->next;
		if (length == type)
		{
			op = q;
		}
		if (pr<10)
		{
			pr++;
			prCardType(q->date, length == type);
		}
		else {
			break;
		}
	}
	for (int i = pr; i < 10; i++)
	{
		printf("                                         |                                 \n");
	}
	if ((NULL != q && type >= 0) || (10 < length && type < 0))
	{
		printf("                              ++++++     |     ++++++               \n");
	}
	else
	{
		printf("                                         |                                 \n");
	}
	printf("                  ================================================            \n");
	if (0 == length && 1 == type)
	{
		type = 0;
	}
	printf("\n           	                  ");
	prOption("  �½�  ", 0 == type, 13);
	printf("\n           	                  ");
	prOption("  ���  ", -1 == type, 13);
	printf("\n           	                  ");
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
					setCardType(-1);
				}
				else
				{
					setCardType(length);
				}
			}
			else if (-1 == type)
			{
				setCardType(0);
			}
			else if (1 == type)
			{
				setCardType(-1);
			}
			else
			{
				setCardType(type - 1);
			}
			return;
			break;
		case down:
		case tab:
			if (0 == type)
			{
				setCardType(-1);
			}
			else if (-1 == type)
			{
				if (0 == length)
				{
					setCardType(0);
				}
				else
				{
					setCardType(1);
				}
			}
			else if (length == type)
			{
				setCardType(0);
			}
			else
			{
				setCardType(type + 1);
			}
			return;
		case enter:
			if (0 == type)
			{
				pCardType p = (pCardType)malloc(sizeof(cardType));
				p->name[0] = '\0';
				p->price = 0;
				while (NULL != q->next)
				{
					q = q->next;
				}
				pList pl = (pList)malloc(sizeof(cardTypeList));
				pl->last = q;
				pl->next = NULL;
				pl->date = p;
				q->next = pl;
				editCardType(0, pl);
				setCardType(type);
				return;
			}
			else if (-1 == type)
			{
				return;
			}
			else
			{
				editCardType(0, op);
				setCardType(type);
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

//����
void saveCardType() {
	if (NULL == getList())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\cardType", "wb")))
	{
		return;
	}
	pList p = getList();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(cardType), 1, fp))
		{
			p = p->next;

		}
	}
}
*/
