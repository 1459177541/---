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
	if (NULL != p->user)
	{
		strcpy(user, p->user->masterName);
	}
	else
	{
		user[0] = '\0';
	}
	printf("\n%3s%9d |%19s |%19s |%19s% -3s"
		, isOption ? getAttri("L") : getAttri("NL"), p->id, p->type, user, prTime(p->startTime, TIME), isOption ? getAttri("R") : getAttri("NR"));
}


//��/�»�
void logPC(pPC p) {
	if (NULL!=p->user)
	{
		p->user = paginationMenu(getCards(), d_card, 0, 0)->date.card;
	}
	else
	{
		p->user->balance -= results(p, p->user);
		p->user = NULL;
	}
}

//ȫ���»�
void logoutPCAll() {
	int x = 16;
	int y = 8;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x + 15, 9);
	printf("    ���ڽ�����    ");
	gotoxy(x + 5, 12);
	int i = 0;
	pList list = getPCs();
	while (NULL!=list && d_pc == list->type)
	{
		if (i>pcLength/40)
		{
			printf("#");
			i = 0;
		}
		i++;
		logPC(list->date.pc);
		list = list->next;
	}
}

//PC����
int showPC(pPC p) {
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
	char temp[32];
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
			o = o->next;
		}
		p = p->next;
	}
	return list->next;
}

//ɸѡ
pList selectPC(int type, pCriteriaPC criteria,pList p) {
	key k;
	pList pt = getPCtypeList();
	system("title ɸѡ");
	system("cls");
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
