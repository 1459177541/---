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
	historyFinal = q->last;
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

void addHistory(historyType type, date date) {
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
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (type)
	{
	case C_ADMIN_T:

		break;
	case D_ADMIN_T:

		break;
	case U_ADMIN_T:

		break;
	case C_RATE_T:

		break;
	case D_RATE_T:

		break;
	case U_RATE_T:

		break;
	case C_CARD_T:

		break;
	case D_CARD_T:

		break;
	case U_CARD_T:

		break;
	case C_PC_TYPE_T:

		break;
	case D_PC_TYPE_T:

		break;
	case U_PC_TYPE_T:

		break;
	case C_CARD_TYPE_T:

		break;
	case D_CARD_TYPE_T:

		break;
	case U_CARD_TYPE_T:

		break;
	case UP_T:

		break;
	case DOWN_T:

		break;
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
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
	printf("%6s%16s |%15s  |%19s %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), type, p->editor, p->time, isOption ? getAttri("R") : getAttri("NR"));
}
