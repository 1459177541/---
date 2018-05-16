#include"config.h"

pList pcList = NULL;
int pcLength = 0;

//初始化
void initPCToArray() {
	prPrompt("正在生成", "正在生成电脑列表");
	if (NULL==getPCtypeList() || NULL==getPCtypeList()->next)
	{
		pcList = NULL;
		return;
	}
	if (NULL==pcList )
	{
		pcList = (pList)malloc(sizeof(List));
		pcList->last = NULL;
		pcList->next = NULL;
		pcList->date.pc = NULL;
		pcList->type = d_pc;
	}
	pList pcTypeList = getPCtypeList()->next;
	pList p = pcList;
	pList q;
	while (NULL!=pcTypeList)
	{
		pPCtype pcType = pcTypeList->date.pcType;
		for (int i = 0; i < pcType->num; i++)
		{
			pPC pc = (pPC)malloc(sizeof(PC));
			pc->id = pcType->startId + i;
			pc->user = NULL;
			strcpy(pc->type, pcTypeList->date.pcType->type);
			q = (pList)malloc(sizeof(List));
			q->type = d_pc;
			q->last = p;
			q->next = NULL;
			q->date.pc = pc;
			p->next = q;
			p = p->next;
			pcLength++;
		}
		pcTypeList = pcTypeList->next;
	}
	pList t = pcList;
	pcList = pcList->next;
	pcList->last = NULL;
	free(t);
	return;
}

//获得全部PC列表
pList getPCs() {
	if (NULL == pcList)
	{
		while (NULL == getPCtypeList()->next)
		{
			prPrompt("警告", "当前无网吧规模\n按任意键转到网吧规模");
			getch();
			scrollMenu(getPCtypeList(), d_pcType, 0);
		}
		initPCToArray();
	}
	return pcList;
}

//输出PC信息（列表）
void prPC(pPC p, int isOption) {
	char *user = (char *)malloc(16 * sizeof(char));
	char *time = (char *)malloc(16 * sizeof(char));
	if (NULL != p->user)
	{
		strcpy(user, p->user->masterName);
		sprintf(time, "%2d日 %2d时%2d分", p->startTime.tm_mday, p->startTime.tm_hour, p->startTime.tm_min);
	}
	else
	{
		time[0] = '\0';
		user[0] = '\0';
	}
	printf("\n%3s%9d |%19s |%19s |%19s% -3s"
		, isOption ? getAttri("L") : getAttri("NL"), p->id, p->type, user, time, isOption ? getAttri("R") : getAttri("NR"));
	free(user);
	free(time);
}

//PC界面
void showPC(pPC p) {
	char name[16] = "";
	if (NULL!=p->user)
	{
		strcpy(name, p->user->masterName);
	}
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                  id: %-25d|", p->id);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 类型: %-24s|", p->type);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|              当前用户: %-23s|", name);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                ");
	prOption("完成",1, 6);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	if (enter == k)
	{
		return;
	}
	else
	{
		showPC(p);
	}
}

//搜索条件
pCriteria getDefaultCriteriaPC() {
	pCriteria p = (pCriteria)malloc(sizeof(Criteria));
	p->type = condition;
	p->condition.pc.pcType = getPCtypeList()->date.pcType;
	p->condition.pc.isUse = C_PC_ALL;
	p->Criteria[0] = '\0';
	return p;
}

//依据条件获得列表
pList getListFromPcCriteria(pCriteria criteria) {
	pList list = (pList)malloc(sizeof(List));
	list->last = NULL;
	list->next = NULL;
	pList o = list;
	pList p = getPCs();
	int isAdd;
	char *temp = (char*)malloc(sizeof(char) * 32);
	while (NULL!=p)
	{
		switch (criteria->type)
		{
		case 0:
			isAdd = 1;
			if (0 != strcmp(criteria->condition.pc.pcType->type, getPCtypeList()->date.pcType))
			{
				if (0 != strcmp(criteria->condition.pc.pcType->type, p->date.pcType))
				{
					isAdd = 0;
				}
			}
			if (C_PC_ALL != criteria->condition.pc.isUse)
			{
				if (C_PC_IS != criteria->condition.pc.isUse && NULL != p->date.pc->user)
				{
					isAdd = 0;
				}
				else if (C_PC_NOT != criteria->condition.pc.isUse && NULL == p->date.pc->user)
				{
					isAdd = 0;
				}
			}
			break;
		case 1:
			isAdd = 0;
			char *user = (char *)malloc(16 * sizeof(char));
			char *time = (char *)malloc(16 * sizeof(char));
			if (NULL != p->date.pc->user)
			{
				strcpy(user, p->date.pc->user->masterName);
				sprintf(time, "%2d日 %2d时%2d分"
					, p->date.pc->startTime.tm_mday, p->date.pc->startTime.tm_hour, p->date.pc->startTime.tm_min);
			}
			else
			{
				time[0] = '\0';
				user[0] = '\0';
			}
			if (NULL!=strstr(itoa(p->date.pc->id,temp,10),criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL!=strstr(p->date.pc->type,criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(user, criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(time, criteria->Criteria))
			{
				isAdd = 1;
			}
			free(user);
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
	free(temp);
	pList ret = list->next;
	ret->last = NULL;
	free(list);
	return ret;
}

void setIsUseFormCriteria(pCriteria p, int type) {
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 ");
	prOption(" 全部情况 ", 0 == type, 16);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 ");
	prOption(" 当前上机 ", 1 == type, 16);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 ");
	prOption("当前无用户", 2 == type, 16);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	switch (k)
	{
	case up:
		type--;
		if (0>type)
		{
			type = 2;
		}
		break;
	case down:
		type++;
		if (2<type)
		{
			type = 0;
		}
		break;
	case enter:
		switch (type)
		{
		case 0:
			p->condition.pc.isUse = C_PC_ALL;
			return;
		case 1:
			p->condition.pc.isUse = C_PC_IS;
			return;
		case 2:
			p->condition.pc.isUse = C_PC_NOT;
			return;
		default:
			break;
		}
	default:
		break;
	}
	return setIsUseFormCriteria(p, type);
}

//筛选
pList selectPC(int type, pCriteria criteria) {
	char *isUse = (char*)malloc(sizeof(char) * 16);
	isUse[0] = '\0';
	if (C_PC_ALL == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "全部情况");
	}
	else if (C_PC_IS == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "当前上机");
	}
	else if (C_PC_NOT == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "当前无用户");
	}
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
	printf("|          %c切换方式: %-15s           |", 0 == type ? '>' : ' ', condition == criteria->type?"条件搜索":"模糊搜索");
	if (condition == criteria->type)
	{
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %c选择电脑类型: %-15s       |"
			, 1 == type ? '>' : ' ', criteria->condition.pc.pcType->type);
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %c选择上机情况: %-15s       |", 2 == type ? '>' : ' ',isUse);
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
			{
				pList pcType = scrollMenu(getPCtypeList(), d_pcType, 4);
				criteria->condition.pc.pcType = pcType->date.pcType;
				break;
			}
			case 2:
				setIsUseFormCriteria(criteria,0);
				break;
			case 3:
				return getListFromPcCriteria(criteria);
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
		printf("|              %c请输入待搜索的内容              |",1==type?'>':' ');
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
		if (1==type)
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
				return getListFromPcCriteria(criteria);
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	return selectPC(type, criteria);
}

pList selectToPC() {
	return selectPC(0, getDefaultCriteriaPC());
}

pList loginPcList = NULL;
pList loginPcListFinal = NULL;
int loginPcNum = 0;
int lock = 0;
//是否有上机
int hasLoginPC() {
	return NULL != loginPcList;
}

//上/下机
HANDLE handle = NULL;
void logPC(pPC p) {
	if (NULL==getRateList()->next)
	{
		prPrompt("警告！！！", "当前只有默认的计费方案\n按enter键强制上机(可能会导致无收入)\n按esc取消，按其他任意键转到计费方案管理");
		key k = isKey(getch());
		switch (k)
		{
		case enter:
			break;
		case esc:
			return;
		default:
			scrollMenu(getRateList(), d_rate, 0);
			break;
		}
	}
	while (lock)
	{
		Sleep(100);
	}
	lock = 1;
	date d;
	d.pc = p;
	if (NULL == p->user)
	{
		//上机
		if (NULL==handle)
		{
			void startCheck();
			startCheck();
		}
		system("title 选择上机用户");
		p->user = paginationMenu(getCards(), d_card, 0, 9)->date.card;
		system("title 上/下机");
		if (NULL==p->user)
		{
			prPrompt("警告", "当前未选择会员卡\n按任意键取消上机操作");
			getch();
			lock = 0;
			return;
		}
		time_t timer = time(NULL);
		pTm tt = localtime(&timer);
		p->startTime = *tt;
		addHistory(UP_T, d, 0);
		if (hasLoginPC())
		{
			pList pl = (pList)malloc(sizeof(List));
			pl->next = NULL;
			pl->last = loginPcListFinal;
			pl->type = d_pc;
			pl->date.pc = p;
			loginPcListFinal->next = pl;
		}
		else
		{
			loginPcList = (pList)malloc(sizeof(List));
			loginPcList->last = NULL;
			loginPcList->next = NULL;
			loginPcList->type = d_pc;
			loginPcList->date.pc = p;
			loginPcListFinal = loginPcList;
		}
		loginPcNum++;
	}
	else
	{
		//下机
		time_t now = time(NULL);
		time_t time = now - mktime(&(p->startTime));
		double money = results(p, p->user, localtime(&time));
		if (p->user->balance>=money)
		{
			p->user->balance -= money;
		}
		else
		{
			char other[16];
			sprintf(other, "对方账户余额不足\n请收取%.2lf元\n按任意键确认", money - p->user->balance/100.0);
			prPrompt("下机",other);
			getch();
			p->user->balance = 0;
		}
		addHistory(DOWN_T, d, money);
		p->user = NULL;
		pList pl = loginPcList;
		while (pl!=NULL && pl->date.pc!=p)
		{
			pl = pl->next;
		}
		if (loginPcList == pl)
		{
			loginPcList = loginPcList->next;
			if (NULL!=loginPcList)
			{
				loginPcList->last = NULL;
			}
		}
		else if (loginPcListFinal == pl)
		{
			loginPcListFinal = loginPcListFinal->last;
			loginPcListFinal->next = NULL;
		}
		else
		{
			pl->last->next = pl->next;
			pl->next->last = pl->last;
		}
		pl->date.pc = NULL;
		free(pl);
		loginPcNum--;
	}
	lock = 0;
}

//全部下机
void logoutPCAll() {
	prPrompt("正在结算金额", "");
	gotoxy(21, 12);
	int i = 0;
	pList list = loginPcList;
	while (hasLoginPC())
	{
		if (i>loginPcNum / 40)
		{
			printf("#");
			i = 0;
		}
		i++;
		pList p = list->next;
		if (NULL != list->date.pc->user)
		{
			logPC(list->date.pc);
		}
		list = p;
	}
}

//检查上机余额
DWORD WINAPI check(LPVOID pM) {
	int iTime = atoi(getAttri("checkTime")) * 60 * 1000;
	while (1)
	{
		while (lock)
		{
			Sleep(500);
		}
		lock = 1;
		if (NULL == loginPcList)
		{
			lock = 0;
			Sleep(iTime);
			continue;
		}
		pList pl = loginPcList;
		pList next;
		while (pl != NULL)
		{
			next = pl->next;
			time_t time_t1 = time(NULL) - mktime(&(pl->date.pc->startTime)) + iTime/1000;
			time_t time_t2 = time(NULL) - mktime(&(pl->date.pc->startTime));
			double money = results(pl->date.pc, pl->date.pc->user, localtime(&time_t1));
			double money2 = results(pl->date.pc, pl->date.pc->user, localtime(&time_t2));
			if (money2>=pl->date.pc->user->balance)
			{
				char body[96];
				sprintf(body, "%d号电脑余额不足\n已自动下机\n按任意键关闭", pl->date.pc->id);
				lock = 0;
				logPC(pl->date.pc);
				lock = 1;
				prPrompt("提示", body);
				getch();
			}
			else if (money>=pl->date.pc->user->balance)
			{
				char body[96];
				sprintf(body, "%d号电脑余额不足\n将在%s分钟内自动下机\n按任意键关闭", pl->date.pc->id, getAttri("checkTime"));
				prPrompt("提示", body);
				getch();
			}
			pl = next;
		}
		lock = 0;
		Sleep(iTime);
	}
	return NULL;
}

//开始执行检查
void startCheck() {
	if (NULL == handle)
	{
		handle = CreateThread(NULL, 0, check, NULL, 0, NULL);
	}
}