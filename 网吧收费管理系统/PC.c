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
			pc->startTime = NULL;
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
	if (NULL != p->user)
	{
		strcpy(user, p->user->masterName);
	}
	else
	{
		user[0] = '\0';
	}
	printf("\n%3s%9d |%19s |%19s |%19s% -3s\n"
		, isOption ? getAttri("L") : getAttri("NL"), p->id, p->type, user, prTime(p->startTime, TIME), isOption ? getAttri("R") : getAttri("NR"));
}

//上机
int loginPC(int type, char *text, pPC p) {
	int x = 16;
	gotoxy(x, 6);
	printf("=================================================");
	gotoxy(x, 7);
	printf("|                                               |");
	gotoxy(x, 8);
	printf("|                请输入上机会员卡号             |");
	gotoxy(x, 9);
	printf("|                                               |");
	gotoxy(x, 10);
	printf("|        -------------------------------        |");
	gotoxy(x, 11);
	printf("|                                               |");
	gotoxy(x, 12);
	printf("|             卡号：___________                 |");
	gotoxy(x, 13);
	printf("|                                               |");
	gotoxy(x, 14);
	printf("|               %19s             |",text);
	gotoxy(x, 15);
	printf("|            ");
	OPTION_OK(1 == type);
	printf("        ");
	OPTION_CANCEL(2 == type);
	printf("            |");
	gotoxy(x, 16);
	printf("|                                               |");
	gotoxy(x, 17);
	printf("=================================================");
	char *in = (char *)malloc(sizeof(char) * 16);
	char *name;
	char *text2 = (char *)malloc(sizeof(char) * 24);
	text2[0] = '\0';
	static int id;
	key k;
	if (0==type)
	{
		k = input(36,12,in,0,NUM, NULL);
		id = stringToInt(in);
	}
	else
	{
		name = getCard(id)->masterName;
		strcpy(text2, "卡主：");
		strcat(text2, name);
	}
	k = isKey(getch());
	switch (k)
	{
	case down:
	case right:
	case tab:
		if (2 == type)
		{
			type = -1;
		}
		return loginPC(type + 1, text2, p);
	case left:
	case up:
		if (0 == type)
		{
			type = 3;
		}
		return loginPC(type-1,text2, p);
	case enter:
		switch (type)
		{
		case 0:
			name = getCard(id)->masterName;
			strcpy(text2, "卡主：");
			strcat(text2, name);
			return loginPC(1,text2,p);
		case 1:
			p->user = getCard(id);
			if (p->user!=NULL)
			{
				p->startTime = localtime(time(NULL));
				return 1;
			}
			return loginPC(type, "未知用户", p);
		case 2:
			return 0;
		default:
			break;
		}
	default:
		saveExit(type);
		break;
	}
	return 1;
}

//下机
void logoutPC(pPC p) {
	if (NULL != p && p->user != NULL)
	{
		p->user->balance -= results(p, p->user);
		p->user = NULL;
	}
}

//全部下机
void logoutPCAll() {
	int x = 16;
	gotoxy(x, 8);
	printf("=================================================");
	gotoxy(x, 9);
	printf("|                                               |");
	gotoxy(x, 10);
	printf("|        -------------------------------        |");
	gotoxy(x, 11);
	printf("|                                               |");
	gotoxy(x, 12);
	printf("|                                               |");
	gotoxy(x, 13);
	printf("|                                               |");
	gotoxy(x, 14);
	printf("=================================================");
	gotoxy(x + 15, 9);
	printf("    正在结算金额    ");
	gotoxy(x + 5, 12);
	int i = 0;
	pList list = getPCs();
	while (NULL!=list)
	{
		if (i>pcLength/40)
		{
			printf("#");
			i = 0;
		}
		i++;
		logoutPC(list->date.pc);
	}
}

//PC界面
int showPC(pPC p, int type) {
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
	printf("|      ");
	prOption("上机", 1 == type, 6);
	printf("        ");
	prOption("下机", 2 == type, 6);
	printf("        ");
	prOption("取消", 3 == type, 6);
	printf("       |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	switch (k)
	{
	case up:
	case left:
		type--;
		if (0>type)
		{
			type = 3;
		}
		showPC(p, type);
		break;
	case down:
	case right:
	case tab:
		type++;
		if (3<type)
		{
			type = 1;
		}
		showPC(p, type);
		break;
	case enter:
		if (1 == type)
		{
			loginPC(0, "" ,p);
		}
		else if(2 == type)
		{
			logoutPC(p);
			showPC(p, 1);
			return;
		}
		else if (3==type)
		{
			return;
		}
		break;
	default:
		break;
	}
}

//搜索条件
typedef struct Criteria
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
pList getListFromCriteria(pCriteriaPC criteria) {
	pList list = (pList)malloc(sizeof(List));
	list->last = NULL;
	list->next = NULL;
	pList o = list;
	pList p = getPCs();
	int isAdd = 0;
	char temp[32];
	while (NULL!=p)
	{
		switch (criteria->type)
		{
		case 0:
			if (!strcmp(criteria->PCType,"所有类型"))
			{
				isAdd = 1;
			}
			else if (!strcmp(criteria->PCType,p->date.pc->type))
			{
				isAdd = 1;
			}
			if (0==criteria->isUse)
			{
				isAdd = 1;
			}
			else if (1==criteria->isUse&&NULL!=p->date.pc->user)
			{
				isAdd = 1;
			}
			else if (2==criteria->isUse&&NULL==p->date.pc->user)
			{
				isAdd = 1;
			}
			break;
		case 1:
			if (NULL!=strstr(itoa(p->date.pc->id,temp,10),criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL!=strstr(p->date.pc->type,criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL!= p->date.pc->user && NULL != strstr(p->date.pc->user->masterName, criteria->Criteria))
			{
				isAdd = 1;
			}
			if (NULL != strstr(prTime(p->date.pc->startTime,TIME), criteria->Criteria))
			{
				isAdd = 1;
			}
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

			isAdd = 0;
			o = o->next;
			p = p->next;
		}
	}
	return list;
}

//搜索
pPC selectPC(int type, pCriteriaPC criteria,pPC p) {
	key k;
	pList pt = getPCtypeList();
	system("title 上/下机");
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n\n");
	printf("                       ============= 搜 索 =============                       \n\n");
	printf("                         搜索方式:");
	if (0==criteria->type)
	{
		printf("条件搜索\n\n");
		printf("                            电脑类型：");
		while (strcmp(criteria->PCType,pt->date.pcType->type)!=0&&pt->next!=NULL)
		{
			pt = pt->next;
		}
		if (NULL==pt->next)
		{
			pt = getPCtypeList();
		}
		printf("%s\n\n", pt->date.pcType->type);
		printf("                            当前状态：");
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
	}
	else if (1==criteria->type)
	{
		printf("模糊搜索\n\n");
		printf("                         含有的内容：");
		k = input(5, 39, criteria->Criteria, 0, NUM | LETTER | CHINESE | SYMBOL, NULL);
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
		case 1:
			break;
		default:
			break;
		}
		return getListFromCriteria(criteria);
	default:
		break;
	}
}

pList selectToPC() {
	return selectPC(0, getDefaultCriteriaPC(), getPCs());
}
