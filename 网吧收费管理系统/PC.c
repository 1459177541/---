#include"config.h"

pList pcList = NULL;
int pcLength = 0;

//初始化
void initPCToArray() {
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
typedef struct
{
	int type;
	char PCType[16];
	int isUse;
	char Criteria[16];
}CriteriaPC,* pCriteriaPC;
pCriteriaPC getDefaultCriteriaPC() {
	pCriteriaPC p = (pCriteriaPC)malloc(sizeof(CriteriaPC));
	p->type = 0;
	p->isUse = 0;
	strcpy(p->PCType, getPCtypeList()->date.pc->type);
	p->Criteria[0] = '\0';
	return p;
}

//依据条件获得列表
pList getListFromPcCriteria(pCriteriaPC criteria) {
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
			if (0 != strcmp(criteria->PCType,"所有类型"))
			{
				if (0!=strcmp(criteria->PCType,p->date.pc->type))
				{
					isAdd = 0;
				}
			}
			if (0 != criteria->isUse)
			{
				if (1 != criteria->isUse&&NULL != p->date.pc->user)
				{
					isAdd = 0;
				}
				else if (2 != criteria->isUse&&NULL == p->date.pc->user)
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
			o->next = q;
			o = o->next;
		}
		p = p->next;
	}
	free(temp);
	return list->next;
}

//筛选
pList selectPC(int type, pCriteriaPC criteria,pList p) {
	key k;
	pList pt = getPCtypeList();
	system("title 筛选");
	myCls();
	system("mode con cols=80 lines=24");
	printf("\n\n");
	printf("                       ============= 筛 选 =============                       \n\n");
	printf("                            %c方式:", 0 == type ? '>' : ' ');
	if (0==criteria->type)
	{
		printf("条件搜索\n\n");
		printf("                           %c电脑类型：",1==type?'>':' ');
		while (strcmp(criteria->PCType,pt->date.pcType->type)!=0&&pt->next!=NULL)
		{
			pt = pt->next;
		}
		if (NULL==pt->next)
		{
			pt = getPCtypeList();
		}
		printf("%s\n\n", pt->date.pcType->type);
		printf("                          %c 当前状态：", 2 == type ? '>' : ' ');
		switch (criteria->isUse)
		{
		case 0:
			printf("全部");
			break;
		case 1:
			printf("已有上机");
			break;
		case 2:
			printf("未有上机");
			break;
		default:
			break;
		}
		printf("\n\n");
		printf("                                ");
		OPTION_OK(3 == type);
		k = isKey(getch());
	}
	else if (1==criteria->type)
	{
		printf("模糊搜索\n\n");
		printf("                       %c 含有的内容：", 1 == type ? '>' : ' ');
		k = input(5, 39, criteria->Criteria, 0, NUM | LETTER | CHINESE | SYMBOL, NULL);
		printf("\n\n");
		printf("                                ");
		OPTION_OK(2 == type);
	}
	switch (k)
	{
	case esc:
		return p;
	case left:
		if (0==type)
		{
			criteria->type--;
			if (0>criteria->type)
			{
				criteria->type = 1;
			}
			return selectPC(type, criteria, p);
		}
		if (criteria->type==0)
		{
			switch (type)
			{
			case 1:
			{
				if (NULL != pt->last)
				{
					strcpy(criteria->PCType, pt->last->date.pcType->type);
				}
				return selectPC(type, criteria, p);
			}
			case 2:
				criteria->isUse--;
				if (0>criteria->isUse)
				{
					criteria->isUse = 2;
				}
				break;
			default:
				break;
			}
			return selectPC(type, criteria, p);
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
		return selectPC(type, criteria, p);
	case right:
		if (0 == type)
		{
			criteria->type++;
			if (1<criteria->type)
			{
				criteria->type = 0;
			}
			return selectPC(type, criteria, p);
		}
		if (criteria->type == 0)
		{
			switch (type)
			{
			case 1:
			{
				if (NULL!=pt->next)
				{
					strcpy(criteria->PCType, pt->next->date.pcType->type);
				}
				return selectPC(type, criteria, p);
			}
			case 2:
				criteria->isUse--;
				if (0>criteria->isUse)
				{
					criteria->isUse = 2;
				}
				break;
			default:
				break;
			}
			return selectPC(type, criteria, p);
		}
	case down:
		type++;
		if (criteria->type==0&&type>3)
		{
			type = 0;
		}
		else if(criteria->type!=0&&type>2)
		{
			type = 0;
		}
		return selectPC(type, criteria, p);
	case enter:
		switch (criteria->type)
		{
		case 0:
			if (3!=type)
			{
				type = 3;
				return selectPC(type, criteria, p);
			}
			break;
		case 1:
			if (2!=type)
			{
				type = 2;
				return selectPC(type, criteria, p);
			}
			break;
		default:
			break;
		}
		return getListFromPcCriteria(criteria);
	default:
		return selectPC(type, criteria, p);
	}
}

pList selectToPC() {
	return selectPC(0, getDefaultCriteriaPC(), getPCs());
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
void logPC(pPC p) {
	while (lock)
	{
		Sleep(100);
	}
	lock = 1;
	date d;
	d.pc = p;
	if (NULL == p->user)
	{
		p->user = paginationMenu(getCards(), d_card, 0, 9)->date.card;
		addHistory(UP_T, d, 0);
		if (hasLoginPC)
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
		time_t now = time(NULL);
		time_t time = now - mktime(&(p->startTime));
		double money = results(p, p->user, localtime(&time));
		if (p->user->balance>money)
		{
			p->user->balance -= money;
		}
		else
		{
			char other[16];
			sprintf(other, "对方账户余额不足\n请收取%.2ld元\n按任意键确认", money - p->user->balance);
			prPrompt("下机",other);
			p->user->balance = 0;
		}
		p->user = NULL;
		addHistory(DOWN_T, d, money);
		pList pl = loginPcList;
		while (pl!=NULL && pl->date.pc!=p)
		{
			pl = pl->next;
		}
		if (NULL==pl->last)
		{
			loginPcList = loginPcList->next;
			loginPcList->last = NULL;
		}
		else if (NULL==pl->next)
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
void check() {
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
		while (pl!=NULL)
		{
			time_t time_t = time(NULL) - mktime(&(pl->date.pc->startTime));
			double money = results(pl->date.pc, pl->date.pc->user, localtime(time_t + iTime));
			double money2 = results(pl->date.pc, pl->date.pc->user, localtime(time_t));
			if (money2>pl->date.pc->user->balance)
			{
				logPC(pl->date.pc);
				char body[32];
				sprintf(body, "%d号电脑余额不足\n已自动下机\n按任意键关闭", pl->date.pc->id);
				prPrompt("提示", body);
				getch();
			}
			else if (money>pl->date.pc->user->balance)
			{
				char body[32];
				sprintf(body, "%d号电脑余额不足\n将在%s分钟内自动下机\n按任意键关闭", pl->date.pc->id, getAttri("checkTime"));
				prPrompt("提示", body);
				getch();
			}
			pl = pl->next;
		}
		lock = 0;
		Sleep(iTime);
	}
}

//开始执行检查
void startCheck() {
//	CreateThread(NULL, 0, check, NULL, 0, NULL);
}