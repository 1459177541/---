#include"config.h"
pList cardTypeLists = NULL;

//初始化
int initCardType() {
	prPrompt("正在加载", "正在加载会员卡类型");
	FILE *fp = NULL;
	if (NULL == (fp = fopen("data\\cardType", "rb")))
	{
		return 1;
	}
	pCardType t = (pCardType)malloc(sizeof(cardType));
	if (NULL==cardTypeLists)
	{
		if (fread(t,sizeof(cardType),1,fp)>0)
		{
			cardTypeLists = (pList)malloc(sizeof(pList));
			cardTypeLists->next = NULL;
			cardTypeLists->last = NULL;
			cardTypeLists->type = d_cardType;
			cardTypeLists->data.cardType = t;
		}
		else
		{
			free(t);
			fclose(fp);
			return 1;
		}
	}
	pList q = cardTypeLists;
	pList o = (pList)malloc(sizeof(List));
	pCardType p = (pCardType)malloc(sizeof(cardType));
	while (fread(p, sizeof(cardType), 1, fp)>0)
	{
		o->type = d_cardType;
		o->data.cardType = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pCardType)malloc(sizeof(cardType));
		o = (pList)malloc(sizeof(List));
	}
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

//得到列表
pList getCardTypeList() {
	if (NULL == cardTypeLists)
	{
		if (initCardType())
		{
			pCardType cardTypeHeard = (pCardType)malloc(sizeof(cardType));
			strcpy(cardTypeHeard->name, "所有类型");
			cardTypeHeard->price = 0;
			cardTypeLists = (pList)malloc(sizeof(List));
			cardTypeLists->type = d_cardType;
			cardTypeLists->last = NULL;
			cardTypeLists->next = NULL;
			cardTypeLists->data.cardType = cardTypeHeard;
		}
	}
	return cardTypeLists;
}

//输出
void prCardType(pCardType p) {
	printf("            %24s     |%13.2lf              \n", p->name, p->price/100.0);
}

//修改会员卡类型
void editCardType(int type, pCardType p) {
	char* num = (char*)malloc(16 * sizeof(char));
	num[0] = '\0';
	if (1 != type)
	{
		sprintf(num, "%.2lf", p->price/100.0);
	}
	int x = 16;
	int y = 7;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|              会员卡名称：%-21s|", 0 == type ? "":p->name);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                价    格：%-21s|", num);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(2 == type);
	printf("                  |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	free(num);

	key key;
	if (0 == type)
	{
		key = input(x + 27, 9, p->name, 0, NUM | LETTER | CHINESE, NULL);
	}
	else if(1 == type)
	{
		char *in = (char *)malloc(sizeof(char) * 16);
		in[0] = '\0';
		key = input(x + 27, 11, in, 0, NUM, NULL);
		p->price = '\0' == in[0] ? p->price : (int)(atof(in)*100);
		free(in);
	}
	else
	{
		key = isKey(getch());
	}
	switch (key)
	{
	case up:
		if (1 == type)
		{
			editCardType(2, p);
		}
		else {
			editCardType(type - 1, p);
		}
		break;
	case down:
	case tab:
		if (2 == type)
		{
			editCardType(0, p);
		}
		else {
			editCardType(type + 1, p);
		}
		break;
	case enter:
		if (2!=type)
		{
			editCardType(2, p);
			return;
		}
		pList q = getPCtypeList();
		while (NULL != q)
		{
			if (p == q->data.cardType)
			{
				q = q->next;
				continue;
			}
			if (0 == strcmp(p->name, q->data.cardType->name))
			{
				prPrompt("警告！", "已存在该类型\n按任意键继续");
				getch();
				editCardType(0, p);
				return;
			}
			q = q->next;
		}
		return;
	default:
		editCardType(type, p);
		break;
	}
}

//新建
pList newCardType(pList list) {
	pList q = list;
	while (NULL != q->next)
	{
		q = q->next;
	}
	pCardType p = (pCardType)malloc(sizeof(cardType));
	p->name[0] = '\0';
	p->price = 0;
	pList pl = (pList)malloc(sizeof(List));
	pl->last = q;
	pl->next = NULL;
	pl->data.cardType = p;
	pl->type = d_cardType;
	q->next = pl;
	editCardType(0, p);
	addHistory(C_CARD_TYPE_T, pl->data, 0);
	return list;
}