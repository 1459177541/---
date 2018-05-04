#include"config.h"

pList pcList = NULL;
int pcLength = 0;

//��ʼ��
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

//���ȫ��PC�б�
pList getPCs() {
	if (NULL == pcList)
	{
		initPCToArray();
	}
	return pcList;
}

//���PC��Ϣ���б�
void prPC(pPC p, int isOption) {
	char *user = (char *)malloc(16 * sizeof(char));
	char *time = (char *)malloc(16 * sizeof(char));
	if (NULL != p->user)
	{
		strcpy(user, p->user->masterName);
		sprintf(time, "%2d�� %2dʱ%2d��", p->startTime.tm_mday, p->startTime.tm_hour, p->startTime.tm_min);
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

//PC����
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
	printf("|                 ����: %-24s|", p->type);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|              ��ǰ�û�: %-23s|", name);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                ");
	prOption("���",1, 6);
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

//��������
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

//������������б�
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
			if (0 != strcmp(criteria->PCType,"��������"))
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
				sprintf(time, "%2d�� %2dʱ%2d��"
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

//ɸѡ
pList selectPC(int type, pCriteriaPC criteria,pList p) {
	key k;
	pList pt = getPCtypeList();
	system("title ɸѡ");
	myCls();
	system("mode con cols=80 lines=24");
	printf("\n\n");
	printf("                       ============= ɸ ѡ =============                       \n\n");
	printf("                            %c��ʽ:", 0 == type ? '>' : ' ');
	if (0==criteria->type)
	{
		printf("��������\n\n");
		printf("                           %c�������ͣ�",1==type?'>':' ');
		while (strcmp(criteria->PCType,pt->date.pcType->type)!=0&&pt->next!=NULL)
		{
			pt = pt->next;
		}
		if (NULL==pt->next)
		{
			pt = getPCtypeList();
		}
		printf("%s\n\n", pt->date.pcType->type);
		printf("                          %c ��ǰ״̬��", 2 == type ? '>' : ' ');
		switch (criteria->isUse)
		{
		case 0:
			printf("ȫ��");
			break;
		case 1:
			printf("�����ϻ�");
			break;
		case 2:
			printf("δ���ϻ�");
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
		printf("ģ������\n\n");
		printf("                       %c ���е����ݣ�", 1 == type ? '>' : ' ');
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
//�Ƿ����ϻ�
int hasLoginPC() {
	return NULL != loginPcList;
}

//��/�»�
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
			sprintf(other, "�Է��˻�����\n����ȡ%.2ldԪ\n�������ȷ��", money - p->user->balance);
			prPrompt("�»�",other);
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

//ȫ���»�
void logoutPCAll() {
	prPrompt("���ڽ�����", "");
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

//����ϻ����
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
				sprintf(body, "%d�ŵ�������\n���Զ��»�\n��������ر�", pl->date.pc->id);
				prPrompt("��ʾ", body);
				getch();
			}
			else if (money>pl->date.pc->user->balance)
			{
				char body[32];
				sprintf(body, "%d�ŵ�������\n����%s�������Զ��»�\n��������ر�", pl->date.pc->id, getAttri("checkTime"));
				prPrompt("��ʾ", body);
				getch();
			}
			pl = pl->next;
		}
		lock = 0;
		Sleep(iTime);
	}
}

//��ʼִ�м��
void startCheck() {
//	CreateThread(NULL, 0, check, NULL, 0, NULL);
}