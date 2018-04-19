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

void addHistory(historyType type, pPC pp, pCard pc, pRate pr,pAdmin pa) {
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


/*********************************************************
 * 已废弃
 *********************************************************
//History主菜单
void HistoryMenu(pHistoryList historyList, int page, int option) {
	pHistoryList p = getHistorys();
	if (10 >= option)
	{
		page += option / 10;
		option %= 10;
	}
	pHistory op = NULL;
	for (int i = 0; i < page * 10 && p != NULL; i++)
	{
		p = p->next;
	}
	int length = 0;
	system("title 会员卡管理");
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n                                                 ");
	prOption("搜 索", -1 == option, 9);
	printf("\n          操作类型     |     操作人     |                时间               \n");
	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			length++;
			prHistory(p->date, i == option);
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
		HistoryMenu(historyList, page, in - '0');
		return;
	case up:
		option--;
		if (-6 >= option)
		{
			option = length - 1;
		}
		HistoryMenu(historyList, page, option);
		return;
	case down:
		option++;
		if (length <= option)
		{
			option = -5;
		}
		HistoryMenu(historyList, page, option);
		return;
	case tab:
		if (0 <= option)
		{
			HistoryMenu(historyList, page, -5);
		}
		else
		{
			HistoryMenu(historyList, page, 0);
		}
		return;
	case left:
		if (option<0)
		{
			if (-4 == option)
			{
				HistoryMenu(historyList, page, 9);
			}
			else {
				HistoryMenu(historyList, page, option - 5);
			}
		}
		else if (0 != page)
		{
			HistoryMenu(historyList, page - 1, option);
		}
		else
		{
			HistoryMenu(historyList, page, option);
		}
		return;
	case right:
		if (option<0)
		{
			HistoryMenu(historyList, page, option + 1);
		}
		else if (page > HistoryLength / 10 - 1) {
			HistoryMenu(historyList, page, option);
		}
		else
		{
			HistoryMenu(historyList, page + 1, option);
		}
		return;
	case enter:
		if (-1 == option)
		{
			/////////////////////
		}
		else if (-6 == option)
		{
			HistoryMenu(historyList, 0, option);
		}
		else if (-5 == option)
		{
			HistoryMenu(historyList, page - 1, option);
		}
		else if (-4 == option)
		{
			HistoryMenu(historyList, page + 1, option);
		}
		else if (-3 == option)
		{
			HistoryMenu(historyList, HistoryLength / 10, option);
		}
		else
		{
			HistoryMenu(historyList, page, option);
		}
		break;
	case esc:
		return;
	default:
		break;
	}
}

//保存
void saveHistory() {
	if (NULL == getHistorys())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\history", "wb")))
	{
		return;
	}
	pHistoryList p = getHistorys();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(history), 1, fp))
		{
			p = p->next;
		}
	}
}
*/
