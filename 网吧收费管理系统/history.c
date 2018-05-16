#include"config.h"

pList historyLists = NULL;
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
	if (NULL==historyLists->date.history)
	{
		pl = historyLists;
	}
	else
	{
		pl = (pList)malloc(sizeof(List));
		pl->type = d_history;
		pl->next = historyLists;
		pl->last = NULL;
		historyLists->last = pl;
		historyLists = pl;
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
pCriteria getDefaultCriteriaHistory() {
	pCriteria p = (pCriteria)malloc(sizeof(Criteria));
	p->type = condition;
	p->condition.history.editor = getAdminHead()->date.admin;
	p->condition.history.historyType = ALL_T;
	p->Criteria[0] = '\0';
	return p;
}

//依据条件获得列表
pList getListFromHistoryCriteria(pCriteria criteria) {
	pList list = (pList)malloc(sizeof(List));
	list->last = NULL;
	list->next = NULL;
	pList o = list;
	pList p = getHistorys();
	int isAdd = 0;
	while (NULL != p)
	{
		switch (criteria->type)
		{
		case 0:
			isAdd = 1;
			if (0 != strcmp(criteria->condition.history.editor->name,getAdminHead()->date.admin->name))
			{
				if (0 != strcmp(criteria->condition.history.editor->name, p->date.admin->name))
				{
					isAdd = 0;
				}
			}
			if (ALL_T != criteria->condition.history.historyType)
			{
				if (criteria->condition.history.historyType != p->date.history->type)
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
			q->type = p->type;
			o->next = q;
			o = o->next;
		}
		p = p->next;
	}
	return list->next;
}

//筛选
void setHistoryFormCriteria(pCriteria p, int type) {
	int x = 12;
	int y = 0;
	gotoxy(x, y++);
	printf("=========================================================");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("     全部     ", 0 == type, 22);
	printf("     ");
	prOption("     充值     ", 1 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("     上机     ", 2 == type, 22);
	printf("     ");
	prOption("     下机     ", 3 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("新增会员卡类型", 4 == type, 22);
	printf("     ");
	prOption("删除会员卡类型", 5 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("修改会员卡类型", 6 == type, 22);
	printf("     ");
	prOption(" 新建计费标准 ", 7 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption(" 删除计费标准 ", 8 == type, 22);
	printf("     ");
	prOption(" 修改计费标准 ", 9 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  创建管理员  ", 10 == type, 22);
	printf("     ");
	prOption("  删除管理员  ", 11 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  修改管理员  ", 12 == type, 22);
	printf("     ");
	prOption("  注册会员卡  ", 13 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  注销会员卡  ", 14 == type, 22);
	printf("     ");
	prOption("修改会员卡信息", 15 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption(" 新增电脑类型 ", 16 == type, 22);
	printf("     ");
	prOption(" 删除电脑类型 ", 17 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|                   ");
	prOption(" 修改电脑类型 ", 18 == type, 22);
	printf("                   |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("=========================================================");
	key k = isKey(getch());
	switch (k)
	{
	case up:
		type -= 2;
		if (0>type)
		{
			type = 18;
		}
		break;
	case down:
		type += 2;
		if (19==type)
		{
			type = 18;
		}
		else if (20 == type)
		{
			type = 0;
		}
		break;
	case left:
		type--;
		if (0>type)
		{
			type = 18;
		}
		break;
	case right:
		type++;
		if (18<type)
		{
			type = 0;
		}
		break;
	case enter:
		switch (type)
		{
		case 0:
			p->condition.history.historyType = ALL_T;
			return;
		case 1:
			p->condition.history.historyType = RECHARGE_T;
			return;
		case 2:
			p->condition.history.historyType = UP_T;
			return;
		case 3:
			p->condition.history.historyType = DOWN_T;
			return;
		case 4:
			p->condition.history.historyType = C_CARD_TYPE_T;
			return;
		case 5:
			p->condition.history.historyType = D_CARD_TYPE_T;
			return;
		case 6:
			p->condition.history.historyType = U_CARD_TYPE_T;
			return;
		case 7:
			p->condition.history.historyType = C_RATE_T;
			return;
		case 8:
			p->condition.history.historyType = D_RATE_T;
			return;
		case 9:
			p->condition.history.historyType = U_RATE_T;
			return;
		case 10:
			p->condition.history.historyType = C_ADMIN_T;
			return;
		case 11:
			p->condition.history.historyType = D_ADMIN_T;
			return;
		case 12:
			p->condition.history.historyType = U_ADMIN_T;
			return;
		case 13:
			p->condition.history.historyType = D_CARD_T;
			return;
		case 14:
			p->condition.history.historyType = U_CARD_T;
			return;
		case 15:
			p->condition.history.historyType = U_CARD_T;
			return;
		case 16:
			p->condition.history.historyType = C_PC_TYPE_T;
			return;
		case 17:
			p->condition.history.historyType = D_PC_TYPE_T;
			return;
		case 18:
			p->condition.history.historyType = U_PC_TYPE_T;
			return;
		default:
			break;
		}
	default:
		break;
	}
	setHistoryFormCriteria(p, type);
	return ;
}

//筛选
pList selectHistory(int type, pCriteria criteria) {
	char *historyType = getHistoryType(criteria->condition.history.historyType);
	int x = 16;
	int y = 4;
	myCls();
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                      筛选                     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|          %c切换方式: %-15s           |", 0 == type ? '>' : ' ', condition == criteria->type ? "条件搜索" : "模糊搜索");
	if (condition == criteria->type)
	{
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %c选择记录类型: %-15s       |", 1 == type ? '>' : ' ', historyType);
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|            %c选择记录人: %-15s       |"
			, 2 == type ? '>' : ' ', criteria->condition.history.editor->name);
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|                      ");
		OPTION_OK(3 == type);
		printf("                  |");
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("=================================================");
		key k = isKey(getch());
		switch (k)
		{
		case down:
			type++;
			if (3 < type)
			{
				type = 0;
			}
			break;
		case up:
			type--;
			if (0>type)
			{
				type = 3;
			}
			break;
		case enter:
			switch (type)
			{
			case 0:
				criteria->type = fuzzy;
				break;
			case 1:
				setHistoryFormCriteria(criteria, 0);
				break;
			case 2:
			{
				pList editor = scrollMenu(getAdminHead(), d_admin, 4);
				criteria->condition.history.editor = editor->date.admin;
				break;
			}
			case 3:
				return getListFromHistoryCriteria(criteria);
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|              %c请输入待搜索的内容              |", 1 == type ? '>' : ' ');
		gotoxy(x, y++);
		printf("|                                               |");//12
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
		key k;
		if (1 == type)
		{
			k = input(x + 16, 12, criteria->Criteria, 0, NUM | SYMBOL | LETTER | CHINESE, NULL);
		}
		else
		{
			k = isKey(getch());
		}
		switch (k)
		{
		case up:
			type++;
			if (2 < type)
			{
				type = 0;
			}
			break;
		case down:
			type--;
			if (0>type)
			{
				type = 2;
			}
			break;
		case enter:
			switch (type)
			{
			case 0:
				criteria->type = condition;
				break;
			case 1:
				type = 2;
				break;
			case 2:
				return getListFromHistoryCriteria(criteria);
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	return selectHistory(type, criteria);
}

pList selectToHistory() {
	return selectHistory(0, getDefaultCriteriaHistory());
}
