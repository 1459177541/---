#include"config.h"

int maxCardId = 1;
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
	p = (pCard)malloc(sizeof(card));;
	while (fread(p, sizeof(card), 1, fp)>0)
	{
		if (p->id>maxCardId)
		{
			maxCardId = p->id;
		}
		o->type = d_card;
		o->date.card = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pCard)malloc(sizeof(card));
		o = (pList)malloc(sizeof(List));
	}
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

pList getCards() {
	if (NULL== cardLists)
	{
		if (initCard())
		{
			cardLists = (pList)malloc(sizeof(List));
			cardLists->date.card = NULL;
			cardLists->last = NULL;
			cardLists->next = NULL;
			cardLists->type = d_card;
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
	printf("%3s%15d |%19s |%19s |%13.2lf %-3s"
		, isOption ? getAttri("L") : getAttri("NL"), p->id, p->type, p->masterName, p->balance, isOption ? getAttri("R") : getAttri("NR"));
}

int showCard(int type, pCard p,char * text, char *password, char *password2) {
	if (0 > p->id)
	{
		p->id = maxCardId;
		maxCardId++;
	}
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
	printf("|                      id：%-21d|", p->id);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                   %c类型：%-21s|",0==type?'>':' ', p->type);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                  用户名：%-21s|", 1 == type ? "" : p->masterName);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    密码：%-21s|", "");
	gotoxy(x + 27, y - 1); 
	printfPassword(password);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                再次输入：%-21s|", "");
	gotoxy(x + 27, y - 1);
	printfPassword(password2);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    余额：%-21s|", balance);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    %10s                 |",text);
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(5 == type);
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
		pList typeList = getCardTypeList();
		if ('\0'==p->type[0])
		{
			strcpy(p->type, typeList->date.cardType->name);
		}
		else
		{
			while (0!=strcmp(p->type,typeList->date.cardType->name) && NULL!=typeList->next)
			{
				typeList = typeList->next;
			}
			k = isKey(getch());
			switch (k)
			{
			case left:
				if (NULL!=typeList->last)
				{
					strcpy(p->type, typeList->last->date.cardType->name);
				}
				showCard(type, p, text, password, password2);
				return;
			case right:
				if (NULL != typeList->next)
				{
					strcpy(p->type, typeList->next->date.cardType->name);
				}
				showCard(type, p, text, password, password2);
				return;
			default:
				break;
			}
		}
		break;
	}
	case 1:
	{
		k = input(x + 27, 8, p->masterName, 0, NUM | LETTER | CHINESE, NULL);
		break;
	}
	case 2:
		k = input(x + 27, 10, password, 1, INTER | LETTER | SYMBOL, NULL);
		break;
	case 3:
		k = input(x + 27, 12, password2, 1, INTER | LETTER | SYMBOL, NULL);
		break;
	case 4:
	{
		char * temp = (char*)malloc(16 * sizeof(char));
		temp[0] = '\0';
		k = input(x + 27, 14, temp, 0, NUM, NULL);
		if ('\0' != temp)
		{
			p->balance = atof(temp);
		}
		break;
	}
	default:
		k = isKey(getch());
		break;
	}
	switch (k)
	{
	case up:
		if (0 == type)
		{
			showCard(5, p, text, password, password2);
		}
		else {
			showCard(type-1, p, text, password, password2);
		}
		break;
	case down:
	case tab:
		if (5 == type)
		{
			showCard(0, p, text, password, password2);
		}
		else {
			showCard(type+1, p, text, password, password2);
		}
		break;
	case enter:
		if (5 == type)
		{
			if ('\0' == password[0] || '\0' == password2[0])
			{
				password[0] = '\0';
				password2[0] = '\0';
				showCard(type, p, "[     err:请输入密码     ]", password, password2);
				return;
			}
			if (0 == strcmp(password, password2))
			{
				strcpy(p->password, password);
				return;
			}
			else
			{
				password[0] = '\0';
				password2[0] = '\0';
				showCard(type, p, "[err:两次输入的密码不一样]", password, password2);
				return;
			}
		}
		else
		{
			showCard(5, p, text, password, password2);
		}
		break;
	default:
		showCard(type, p, text, password, password2);
		break;
	}
}
