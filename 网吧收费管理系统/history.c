#include"config.h"

pList historyLists = NULL;
pList historyFinal = NULL;
int HistoryLength = 0;
int initHistory() {
	prPrompt("正在加载", "正在加载历史记录");
	FILE *fp = NULL;
	if (NULL == (fp = fopen("data\\history", "rb")))
	{
		return 1;
	}
	pHistory p = (pHistory)malloc(sizeof(history));
	if (NULL == historyLists)
	{
		if (fread(p, sizeof(history), 1, fp)>0)
		{
			historyLists = (pList)malloc(sizeof(List));
			historyLists->next = NULL;
			historyLists->last = NULL;
			historyLists->type = d_history;
			historyLists->date.history = p;
		}
		else
		{
			free(historyLists);
			free(p);
			fclose(fp);
			return 1;
		}
	}
	pList o = (pList)malloc(sizeof(List));
	pList q = historyLists;
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
			historyLists = (pList)malloc(sizeof(List));
			historyLists->next = NULL;
			historyLists->last = NULL;
			historyLists->date.history = NULL;
			historyLists->type = d_history;
			historyFinal = NULL;
		}
	}
	return historyLists;
}

char *getHistoryType(historyType p) {
	char* type = (char*)malloc(16 * sizeof(char));
	switch (p)
	{
	case ALL_T:
		strcpy(type, "全部");
		break;
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
	case RECHARGE_T:
		strcpy(type, "充值");
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
	splitString(asctime(&(p->time)), textTime1, 0, 32);
	if (strlen(asctime(&(p->time)))>32)
	{
		splitString(asctime(&(p->time)), textTime2, 33, 64);
	}
	splitString(p->text, text1, 0, 32);
	if (strlen(p->text)>32)
	{
		splitString(p->text, text2, 33, 64);
	}
	if (strlen(p->text)>64)
	{
		splitString(p->text, text3, 65, 96);
	}
	int x = 8;
	int y = 4;
	gotoxy(x, y++);
	printf("=========================================================");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               类型: %-24s          |", getHistoryType(p->type));
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|             操作人: %-22s            |", p->editor);
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               时间: %4d年%2d月%2d日 %2d时%2d分%2d秒       |"
		, p->time.tm_year + 1900, p->time.tm_mon + 1, p->time.tm_mday
		, p->time.tm_hour, p->time.tm_min, p->time.tm_sec
		);
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               详细:%-32s   |", text1);
	gotoxy(x, y++);
	printf("|                    %-32s   |", text2);
	gotoxy(x, y++);
	printf("|                    %-32s   |", text3);
	gotoxy(x, y++);
	printf("|                                                       |");
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

void addHistory(historyType type, date date, double other) {
	char * prPower(int power);
	pList pl = NULL;
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
		historyFinal = historyFinal->next;
	}
	pHistory d = (pHistory)malloc(sizeof(history));
	pl->date.history = d;
	time_t timer = time(NULL);
	pTm tt = localtime(&timer);
	d->time = *tt;
	strcpy(d->editor, getUser()->name);
	d->money = other;
	d->type = type;
	switch (type)
	{
	case C_ADMIN_T:
		sprintf(d->text, "新建管理员: %-16s 权限: %-40s ", date.admin->name, prPower(date.admin->power));
		break;
	case D_ADMIN_T:
		sprintf(d->text, "删除管理员: %-16s", date.admin->name);
		break;
	case U_ADMIN_T:
		sprintf(d->text, "修改管理员信息: %-16s", date.admin->name);
		break;
	case C_RATE_T:
		sprintf(d->text, "新建计费方案: %-16s 对于 %s 在 %s 上机适用", date.rate->rule, date.rate->card, date.rate->pc);
		break;
	case D_RATE_T:
		sprintf(d->text, "删除计费方案: %s", date.rate->rule);
		break;
	case U_RATE_T:
		sprintf(d->text, "修改计费方案: %s", date.rate->rule);
		break;
	case C_CARD_T:
		sprintf(d->text, "开户: %s(证件号: %s)，开通%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case D_CARD_T:
		sprintf(d->text, "注销: %s(证件号: %s)，注销%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case U_CARD_T:
		sprintf(d->text, "修改: %s(证件号: %s)", date.card->masterName, date.card->idcardNum);
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
		sprintf(d->text, "新增会员卡类型%s，售价: %.2lf", date.cardType->name, date.cardType->price/100.0);
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
		sprintf(d->text, "用户: %16d 在 %16s 类型 %16d 电脑下机, 消费%5.2lf元", date.pc->user->id, date.pc->type, date.pc->id, other);
		break;
	case RECHARGE_T:
		sprintf(d->text, "用户: %16d 充值了 %16lf 元", date.card->id, other);
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
	printf("\n%5s%16s |%15s  | %4d年%2d月%2d日 %2d时%2d分%2d秒 %-5s"
		, isOption ? getAttri("L") : getAttri("NL"), getHistoryType(p->type), p->editor
		, p->time.tm_year+1900, p->time.tm_mon+1, p->time.tm_mday
		, p->time.tm_hour, p->time.tm_min, p->time.tm_sec
		, isOption ? getAttri("R") : getAttri("NR"));
}

//搜索条件
typedef struct
{
	int type;
	historyType hType;
	char editor[16];
	char Criteria[16];
}CriteriaHistory, *pCriteriaHistory;
pCriteriaHistory getDefaultCriteriaHistory() {
	pCriteriaHistory p = (pCriteriaHistory)malloc(sizeof(CriteriaHistory));
	p->type = 0;
	p->hType = ALL_T;
	strcpy(p->editor, "所有管理员");
	p->Criteria[0] = '\0';
	return p;
}

//依据条件获得列表
pList getListFromHistoryCriteria(pCriteriaHistory criteria) {
	pList list = (pList)malloc(sizeof(List));
	list->last = NULL;
	list->next = NULL;
	pList o = list;
	pList p = getPCs();
	int isAdd = 0;
	while (NULL != p)
	{
		switch (criteria->type)
		{
		case 0:
			isAdd = 1;
			if (0 != strcmp(criteria->editor, "所有管理员"))
			{
				if (0 != strcmp(criteria->editor, p->date.history->editor))
				{
					isAdd = 0;
				}
			}
			if (ALL_T != criteria->hType)
			{
				if (criteria->hType != p->type)
				{
					isAdd = 0;
				}
			}
			break;
		case 1:
			isAdd = 0;
			char *time = (char*)malloc(sizeof(char) * 64);
			sprintf(time, "%4d年%2d月%2d日 %2d时%2d分%2d秒"
				, p->date.history->time.tm_year + 1900, p->date.history->time.tm_mon + 1, p->date.history->time.tm_mday
				, p->date.history->time.tm_hour, p->date.history->time.tm_min, p->date.history->time.tm_sec);
			if (NULL != strstr(getHistoryType(p->date.history->type),criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(p->date.history->editor,criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(p->date.history->text, criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(time, criteria->Criteria))
			{
				isAdd = 1;
			}
			free(time);
			break;
		default:
			break;
		}
		if (isAdd)
		{
			pList q = (pList)malloc(sizeof(List));
			q->next = NULL;
			q->last = o;
			q->date = p->date;
			o->next = q;
			o = o->next;
		}
		p = p->next;
	}
	return list->next;
}

//筛选
pList selectHistory(int type, pCriteriaHistory criteria, pList p) {
	key k;
	historyType ht = ALL_T;
	pList admin = getAdminHead();
	system("title 筛选");
	system("mode con cols=80 lines=24");
	myCls();
	printf("\n\n");
	printf("                       ============= 筛 选 =============                       \n\n");
	printf("                            %c方式:", 0 == type ? '>' : ' ');
	if (0 == criteria->type)
	{
		printf("条件搜索\n\n");
		printf("                           %c操作人：", 1 == type ? '>' : ' ');
		while (strcmp(criteria->editor, admin->date.admin->name) != 0 && admin->next != NULL)
		{
			admin = admin->next;
		}
		if (NULL == admin->next)
		{
			admin = getAdminHead();
		}
		printf(admin->date.admin->name);
		printf("                           %c类型：", 2 == type ? '>' : ' ');
		while ( ht != criteria->hType && FINAL_T != criteria->hType)
		{
			ht = (historyType)((int)ht + 1);
		}
		if (FINAL_T == ht)
		{
			ht = ALL_T;
		}
		printf(getHistoryType(ht));
		printf("\n\n");
		printf("                                ");
		OPTION_OK(3 == type);
		k = isKey(getch());
	}
	else if (1 == criteria->type)
	{
		printf("模糊搜索\n\n");
		printf("                         %c含有的内容：", 1 == type ? '>' : ' ');
		k = input(5, 39, criteria->Criteria, 0, NUM | LETTER | CHINESE | SYMBOL, NULL);
		printf("\n\n");
		printf("                                ");
		OPTION_OK(2 == type);
	}
	else
	{
		k = isKey(getch());
	}
	switch (k)
	{
	case esc:
		return p;
	case left:
		if (0 == type)
		{
			criteria->type--;
			if (0>criteria->type)
			{
				criteria->type = 1;
			}
			return selectHistory(type, criteria, p);
		}
		if (criteria->type == 0)
		{
			switch (type)
			{
			case 1:
			{
				if (NULL != admin->last)
				{
					strcpy(criteria->editor, admin->last->date.admin->name);
				}
				return selectHistory(type, criteria, p);
			}
			case 2:
				if (ALL_T!=criteria->hType)
				{
					criteria->hType = (historyType)((int)criteria->hType - 1);
				}
				break;
			default:
				break;
			}
			return selectHistory(type, criteria, p);
		}
	case up:
		type--;
		if (type<0)
		{
			switch (criteria->type)
			{
			case 0:
				type = 3;
				break;
			case 1:
			case 2:
				type = 2;
				break;
			default:
				break;
			}
		}
		return selectHistory(type, criteria, p);
	case right:
		if (0 == type)
		{
			criteria->type++;
			if (1<criteria->type)
			{
				criteria->type = 0;
			}
			return selectHistory(type, criteria, p);
		}
		if (criteria->type == 0)
		{
			switch (type)
			{
			case 1:
			{
				if (NULL != admin->next)
				{
					strcpy(criteria->editor, admin->next->date.admin->name);
				}
				return selectHistory(type, criteria, p);
			}
			case 2:
				if (FINAL_T != criteria->hType)
				{
					criteria->hType = (historyType)((int)criteria->hType + 1);
				}
				break;
			default:
				break;
			}
			return selectHistory(type, criteria, p);
		}
	case down:
		type++;
		if (criteria->type == 0 && type>3)
		{
			type = 0;
		}
		else if (criteria->type != 0 && type>2)
		{
			type = 0;
		}
		return selectHistory(type, criteria, p);
	case enter:
		switch (criteria->type)
		{
		case 0:
			if (3 != type)
			{
				type = 3;
				return selectHistory(type, criteria, p);
			}
			break;
		case 1:
			if (2 != type)
			{
				type = 2;
				return selectHistory(type, criteria, p);
			}
			break;
		default:
			break;
		}
		return getListFromHistoryCriteria(criteria);
	default:
		return selectHistory(type, criteria, p);
	}
}

pList selectToHistory() {
	return selectHistory(0, getDefaultCriteriaHistory(), getHistorys());
}
