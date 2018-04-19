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
	char* id = (char*)malloc(16 * sizeof(char));
	char* cardType = (char*)malloc(16 * sizeof(char));
	char* masterName = (char*)malloc(16 * sizeof(char));
	char* balance = (char*)malloc(16 * sizeof(char));
	id[0] = '\0';
	cardType[0] = '\0';
	masterName[0] = '\0';
	balance[0] = '\0';
	if (0 != type)
	{
		sprintf(id, "%d", p->id);
	}
	if (1 != type)
	{
		strcpy(cardType, p->type);
	}
	if (2 != type)
	{
		strcpy(masterName, p->masterName);
	}
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
	printf("|                      id：%-21s|", id);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    类型：%-21s|", cardType);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                  用户名：%-21s|", masterName);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    密码：%-21s|", "");
	gotoxy(x + 27, y - 1); printfPassword(password);
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
	printf("|          ");
	OPTION_OK(6 == type);
	printf("        ");
	OPTION_CANCEL(7 == type);
	printf("          |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, 16);
	free(id);
	free(cardType);
	free(masterName);
	free(balance);

	if (7 == type)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			return showCard(6, p, text, password,password2);
		case down:
		case tab:
			return showCard(0, p, text, password, password2);
		case enter:
			return 1;
		default:
			break;
		}
		return showCard(type, p, text, password, password2);
	}

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
				showCard(type, p, "[     err:请输入密码     ]", password, password2);
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
				showCard(type, p, "[err:两次输入的密码不一样]", password, password2);
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

/*********************************************************
 * 已废弃
 *********************************************************
//Card主菜单
void CardMenu(pList cardList, int page, int option) {
	pList p = getCards();
	if (10 >= option)
	{
		page += option / 10;
		option %= 10;
	}
	pCard op = NULL;
	for (int i = 0; i < page * 10 && p != NULL; i++)
	{
		p = p->next;
	}
	int length = 0;
	system("title 会员卡管理");
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n                                                 ");
	prOption("新 建", -2 == option, 9);
	prOption("搜 索", -1 == option, 9);
	printf("\n          id         |        类型        |       用户名       |      余额    \n");
	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			length++;
			prCard(p->date, i == option);
			if (i == option)
			{
				op = p->date;
			}
			p = p->next;
		}
		else {
			printf("\n\n");
		}
	}
	printf("\n                     ");
	prOption("首  页", option == -6, 9);
	printf("   ");
	prOption("上一页", option == -5, 9);
	printf("   ");
	prOption("下一页", option == -4, 9);
	printf("   ");
	prOption("尾  页", option == -3, 9);
	printf("   ");
	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case number:
		CardMenu(cardList, page, in - '0');
		return;
	case up:
		option--;
		if (-6 >= option)
		{
			option = length - 1;
		}
		CardMenu(cardList, page, option);
		return;
	case down:
		option++;
		if (length <= option)
		{
			option = -5;
		}
		CardMenu(cardList, page, option);
		return;
	case tab:
		if (0 <= option)
		{
			CardMenu(cardList, page, -5);
		}
		else
		{
			CardMenu(cardList, page, 0);
		}
		return;
	case left:
		if (option<0)
		{
			if (-4 == option)
			{
				CardMenu(cardList, page, 9);
			}
			else {
				CardMenu(cardList, page, option - 5);
			}
		}
		else if (0 != page)
		{
			CardMenu(cardList, page - 1, option);
		}
		else
		{
			CardMenu(cardList, page, option);
		}
		return;
	case right:
		if (option<0)
		{
			CardMenu(cardList, page, option + 1);
		}
		else if (page > CardLength / 10 - 1) {
			CardMenu(cardList, page, option);
		}
		else
		{
			CardMenu(cardList, page + 1, option);
		}
		return;
	case enter:
		if (-1 == option)
		{
			/////////////////////
		}
		else if (-2 == option)
		{
			while (NULL!=p)
			{
				p = p->next;
			}
			pCard o = (pCard)malloc(sizeof(card));
			o->balance = 0;
			o->id = 0;
			o->idcardNum[0] = '\0';
			o->masterName[0] = '\0';
			o->password[0] = '\0';
			o->type[0] = '\0';
			pList q = (pList)malloc(sizeof(cardList));
			q->last = p;
			q->next = NULL;
			p->next = q;
			char *pass1 = (char *)malloc(sizeof(char) * 16);
			char *pass2 = (char *)malloc(sizeof(char) * 16);
			pass1[0] = '\0';
			pass2[0] = '\0';
			showCard(p, 1, "",pass1, pass2);
		}
		else if (-6 == option)
		{
			CardMenu(cardList, 0, option);
		}
		else if (-5 == option)
		{
			CardMenu(cardList, page - 1, option);
		}
		else if (-4 == option)
		{
			CardMenu(cardList, page + 1, option);
		}
		else if (-3 == option)
		{
			CardMenu(cardList, CardLength / 10, option);
		}
		else
		{
			char *pass1 = (char *)malloc(sizeof(char) * 16);
			char *pass2 = (char *)malloc(sizeof(char) * 16);
			pass1[0] = '\0';
			pass2[0] = '\0';
			showCard(op, 1, "", pass1, pass2);
		}
		break;
	case esc:
		return;
	default:
		break;
	}
}

//保存
void saveCard() {
	if (NULL == getCards())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\card", "wb")))
	{
		return;
	}
	pList p = getCards();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(card), 1, fp))
		{
			p = p->next;
		}
	}
}
*/