#include"config.h"

pList cardLists = NULL;
int CardLength = 0;
int initCard() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\card", "rb")))
	{
		return 1;
	}
	if (NULL== cardLists)
	{
		cardLists = (pList)malloc(sizeof(List));
		cardLists->next = NULL;
		cardLists->last = NULL;
		cardLists->date.card = NULL;
	}
	pList o = (pList)malloc(sizeof(List));
	pCard p = (pCard)malloc(sizeof(card));
	pList q = cardLists;
	q->date.card = p;
	q->type = d_card;
	while (fread(p, sizeof(card), 1, fp)>0)
	{
		o->type = d_card;
		o->date.card = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pCard)malloc(sizeof(card));
		o = (pList)malloc(sizeof(List));
	}
	return 0;
}

pList getCards() {
	if (NULL== cardLists)
	{
		if (initCard())
		{
			/*
			cardLists = (pCard)malloc(sizeof(card));
			cardLists->next = NULL;
			cardLists->last = NULL;
			cardLists->date = NULL;
			*/
			return NULL;
		}
	}
	return cardLists;
}

pCard getCard(int id) {
	pList p = getCards();
	while (NULL!=p)
	{
		if (id==p->date.card->id)
		{
			return p->date.card;
		}
	}
	return NULL;
}

void prCard(pCard p, int isOption) {
	printf("%6s%19d |%19s |%19s |%13.2lf %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), p->id, p->type, p->masterName, p->balance, isOption ? getAttri("R") : getAttri("NR"));
}

int showCard(pCard p, int type,char * text, char *password, char *password2) {
	char* balance = (char*)malloc(16 * sizeof(char));
	balance[0] = '\0';
	if (5 != type)
	{
		sprintf(balance, "%.2lf", p->balance);
	}
	int x = 16;
	int y = 2;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                      id��%-21s|", 0 == type ? "" : itoa(p->id, NULL, 10));
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    ���ͣ�%-21s|", 1 == type ? "" : p->type);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                  �û�����%-21s|", 2 == type ? "" : p->masterName);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    ���룺%-21s|", "");
	gotoxy(x + 27, y - 1); printfPassword(password);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                �ٴ����룺%-21s|", "");
	gotoxy(x + 27, y - 1);
	printfPassword(password2);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    ��%-21s|", balance);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    %10s                 |",text);
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(6 == type);
	printf("                  |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	free(balance);

	key k;
	switch (type)
	{
	case 0:
	{
		char * temp = (char*)malloc(16 * sizeof(char));
		temp[0] = '\0';
		k = input(x + 27, 5, temp, 0, INTER, NULL);
		if ('\0'!=temp)
		{
			p->id = atoi(temp);
		}
		free(temp);
		break;
	}
	case 1:
		k = input(x + 27, 5, p->type, 0, NUM | LETTER | CHINESE, NULL);
		break;
	case 2:
		k = input(x + 27, 5, p->masterName, 0, LETTER | CHINESE, NULL);
		break;
	case 3:
		k = input(x + 27, 5, password, 0, INTER, NULL);
		break;
	case 4:
		k = input(x + 27, 5, password2, 0, INTER, NULL);
		break;
	case 5:
	{
		char * temp = (char*)malloc(16 * sizeof(char));
		temp[0] = '\0';
		k = input(x + 27, 5, temp, 0, NUM, NULL);
		if ('\0' != temp)
		{
			p->balance = atof(temp);
		}
		free(temp);
		break;
	}
	default:
		break;
	}
	switch (k)
	{
	case up:
		if (0 == type)
		{
			showCard(7, p, text, password, password2);
		}
		else {
			showCard(type-1, p, text, password, password2);
		}
		break;
	case down:
	case tab:
		if (7 == type)
		{
			showCard(0, p, text, password, password2);
		}
		else {
			showCard(type+1, p, text, password, password2);
		}
		break;
	case enter:
		if (6 == type)
		{
			if ('\0' == password[0] || '\0' == password2[0])
			{
				password[0] = '\0';
				password2[0] = '\0';
				showCard(type, p, "[     err:����������     ]", password, password2);
				return;
			}
			if (0 == strcmp(password, password2))
			{
				strcpy(p->password, password);
				strcpy(password, "***************");
				strcpy(password2, "***************");
				free(password);
				free(password2);
				return;
			}
			else
			{
				password[0] = '\0';
				password2[0] = '\0';
				showCard(type, p, "[err:������������벻һ��]", password, password2);
				return;
			}
		}
		else
		{
			showCard(6, p, text, password, password2);
		}
		break;
	default:
		showCard(type, p, text, password, password2);
		break;
	}
}
