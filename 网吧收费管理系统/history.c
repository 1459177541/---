#include"config.h"

pList historyLists = NULL;
pList historyFinal = NULL;
int HistoryLength = 0;
int initHistory() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\history", "rb")))
	{
		return 1;
	}
	if (NULL == historyLists)
	{
		historyLists = (pList)malloc(sizeof(List));
		historyLists->next = NULL;
		historyLists->last = NULL;
	}
	pList o = (pList)malloc(sizeof(List));
	pHistory p = (pHistory)malloc(sizeof(history));
	pList q = historyLists;
	q->type = d_history;
	q->date.history = p;
	p = (pHistory)malloc(sizeof(history));
	while (fread(p, sizeof(history), 1, fp)>0)
	{
		o->date.history = p;
		o->type = d_history;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pHistory)malloc(sizeof(history));
		o = (pList)malloc(sizeof(List));
	}
	historyFinal = q;
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

pList getHistorys() {
	if (NULL == historyLists)
	{
		if (initHistory())
		{
			historyLists = (pHistory)malloc(sizeof(history));
			historyLists->next = NULL;
			historyLists->last = NULL;
			historyLists->type = d_history;
			return NULL;
		}
	}
	return historyLists;
}

char *getHistoryType(pHistory p) {
	char type[15];
	switch (p->type)
	{
	case C_ADMIN_T:
		strcpy(type, "创建管理员");
		break;
	case D_ADMIN_T:
		strcpy(type, "删除管理员");
		break;
	case U_ADMIN_T:
		strcpy(type, "修改管理员");
		break;
	case C_RATE_T:
		strcpy(type, "新建计费标准");
		break;
	case D_RATE_T:
		strcpy(type, "删除计费标准");
		break;
	case U_RATE_T:
		strcpy(type, "修改计费标准");
		break;
	case C_CARD_T:
		strcpy(type, "注册会员卡");
		break;
	case D_CARD_T:
		strcpy(type, "注销会员卡");
		break;
	case U_CARD_T:
		strcpy(type, "修改会员卡信息");
		break;
	case C_PC_TYPE_T:
		strcpy(type, "新增电脑类型");
		break;
	case D_PC_TYPE_T:
		strcpy(type, "删除电脑类型");
		break;
	case U_PC_TYPE_T:
		strcpy(type, "修改电脑类型");
		break;
	case C_CARD_TYPE_T:
		strcpy(type, "新增会员卡类型");
		break;
	case D_CARD_TYPE_T:
		strcpy(type, "删除会员卡类型");
		break;
	case U_CARD_TYPE_T:
		strcpy(type, "修改会员卡类型");
		break;
	case UP_T:
		strcpy(type, "上机");
		break;
	case DOWN_T:
		strcpy(type, "下机");
		break;
	default:
		strcpy(type, "ERROR");
		break;
	}
	return type;
}

void showHistory(pHistory p) {
	char *textTime1 = (char *)malloc(sizeof(char) * 33);
	char *textTime2 = (char *)malloc(sizeof(char) * 33);
	char *text1 = (char *)malloc(sizeof(char) * 33);
	char *text2 = (char *)malloc(sizeof(char) * 33);
	char *text3 = (char *)malloc(sizeof(char) * 33);
	textTime1[0] = '\0';
	textTime2[0] = '\0';
	text1[0] = '\0';
	text2[0] = '\0';
	text3[0] = '\0';
	splitString(p->time, textTime1, 0, 32);
	splitString(p->time, textTime2, 33, 64);
	splitString(p->text, text1, 0, 32);
	splitString(p->text, text1, 33, 64);
	splitString(p->text, text1, 65, 96);
	int x = 8;
	int y = 1;
	gotoxy(x, y++);
	printf("=========================================================");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               类型: %-24s             |", getHistoryType(p));
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|             操作人: %-22s             |", p->editor);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               时间: %-32s         |", textTime1);
	gotoxy(x, y++);
	printf("|                    %-32s         |", textTime2);
	gotoxy(x, y++);
	printf("|                                                   |");
	gotoxy(x, y++);
	printf("|               详细:%-32s         |", text1);
	gotoxy(x, y++);
	printf("|                    %-32s         |", text2);
	gotoxy(x, y++);
	printf("|                    %-32s         |", text3);
	gotoxy(x, y++);
	printf("|                                                   |");
	gotoxy(x, y++);
	printf("|            -------------------------------            |");
	gotoxy(x, y++);
	printf("|                          ");
	OPTION_OK(1);
	printf("                      |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("=========================================================");
	while (enter != isKey(getch()))	{}
	free(text3);
	free(text2);
	free(text1);
	free(textTime2);
	free(textTime1);
}

void addHistory(historyType type, date date, void* other) {
	char * prPower(int power);
	pList pl;
	if (NULL==historyFinal)
	{
		historyFinal = getHistorys();
		pl = historyFinal;
	}
	else
	{
		pl = (pList)malloc(sizeof(List));
		pl->type = d_history;
		pl->last = historyFinal;
		pl->next = NULL;
		historyFinal->next = pl;
	}
	pHistory d = (pHistory)malloc(sizeof(history));
	strcpy(d->editor, getUser()->name);
	strcpy(d->time, prTime(localtime(NULL),DATE|TIME));
	switch (type)
	{
	case C_ADMIN_T:
		sprintf(d->text, "新建管理员: %-16s 权限: %-40s ", date.admin->name, prPower(date.admin->power));
		break;
	case D_ADMIN_T:
		sprintf(d->text, "删除管理员: %-16s", date.admin->name);
		break;
	case U_ADMIN_T:
		sprintf(d->text, "修改管理员信息: %-16s --> %-16s ", date.admin->name);
		break;
	case C_RATE_T:
		sprintf(d->text, "新建计费方案: %-16s 对于 %s 在 %s 上机适用", date.rate->rule, date.rate->card, date.rate->pc);
		break;
	case D_RATE_T:
		sprintf(d->text, "删除计费方案: %s", date.rate->rule);
		break;
	case U_RATE_T:
		sprintf(d->text, "修改计费方案: %s --> %s", date.rate->rule);
		break;
	case C_CARD_T:
		sprintf(d->text, "开户: %s(证件号: %s)，开通%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case D_CARD_T:
		sprintf(d->text, "注销: %s(证件号: %s)，注销%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case U_CARD_T:
		sprintf(d->text, "修改: %s(证件号: %s)，注销%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case C_PC_TYPE_T:
		sprintf(d->text, "新增电脑类型%s %d台，编号: %d~%d", date.pcType->type, date.pcType->num, date.pcType->startId, date.pcType->startId + date.pcType->num);
		break;
	case D_PC_TYPE_T:
		sprintf(d->text, "删除%s类型电脑", date.pcType->type);
		break;
	case U_PC_TYPE_T:
		sprintf(d->text, "修改%s类型电脑", date.pcType->type);
		break;
	case C_CARD_TYPE_T:
		sprintf(d->text, "新增会员卡类型%s，售价: %lf", date.cardType->name, date.cardType->price);
		break;
	case D_CARD_TYPE_T:
		sprintf(d->text, "删除会员卡类型%s", date.cardType->name);
		break;
	case U_CARD_TYPE_T:
		sprintf(d->text, "修改类型%s的会员卡", date.cardType->name);
		break;
	case UP_T:
		sprintf(d->text, "用户: %16d 在 %s 类型 %d 电脑上机", date.pc->user->id, date.pc->type, date.pc->id);
		break;
	case DOWN_T:
		sprintf(d->text, "用户: %16d 在 %16s 类型 %16d 电脑下机, 消费%5lf元", date.pc->user->id, date.pc->type, date.pc->id, (double*)other);
		break;
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
	printf("%6s%16s |%15s  |%19s %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), getHistoryType(p), p->editor, p->time, isOption ? getAttri("R") : getAttri("NR"));
}
