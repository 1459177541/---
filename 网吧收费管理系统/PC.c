#include"config.h"

pList pcList = NULL;
int pcLength = 0;

//��ʼ��
void initPCToArray() {
	prPrompt("��������", "�������ɵ����б�");
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
		while (NULL == getPCtypeList()->next)
		{
			prPrompt("����", "��ǰ�����ɹ�ģ\n�������ת�����ɹ�ģ");
			getch();
			scrollMenu(getPCtypeList(), d_pcType, 0);
		}
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
pCriteria getDefaultCriteriaPC() {
	pCriteria p = (pCriteria)malloc(sizeof(Criteria));
	p->type = condition;
	p->condition.pc.pcType = getPCtypeList()->date.pcType;
	p->condition.pc.isUse = C_PC_ALL;
	p->Criteria[0] = '\0';
	return p;
}

//������������б�
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
	prOption(" ȫ����� ", 0 == type, 16);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 ");
	prOption(" ��ǰ�ϻ� ", 1 == type, 16);
	printf("                |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                 ");
	prOption("��ǰ���û�", 2 == type, 16);
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

//ɸѡ
pList selectPC(int type, pCriteria criteria) {
	char *isUse = (char*)malloc(sizeof(char) * 16);
	isUse[0] = '\0';
	if (C_PC_ALL == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "ȫ�����");
	}
	else if (C_PC_IS == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "��ǰ�ϻ�");
	}
	else if (C_PC_NOT == criteria->condition.pc.isUse)
	{
		strcpy(isUse, "��ǰ���û�");
	}
	int x = 16;
	int y = 4;
	myCls();
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                      ɸѡ                     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|          %c�л���ʽ: %-15s           |", 0 == type ? '>' : ' ', condition == criteria->type?"��������":"ģ������");
	if (condition == criteria->type)
	{
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %cѡ���������: %-15s       |"
			, 1 == type ? '>' : ' ', criteria->condition.pc.pcType->type);
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %cѡ���ϻ����: %-15s       |", 2 == type ? '>' : ' ',isUse);
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
		printf("|              %c�����������������              |",1==type?'>':' ');
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
//�Ƿ����ϻ�
int hasLoginPC() {
	return NULL != loginPcList;
}

//��/�»�
HANDLE handle = NULL;
void logPC(pPC p) {
	if (NULL==getRateList()->next)
	{
		prPrompt("���棡����", "��ǰֻ��Ĭ�ϵļƷѷ���\n��enter��ǿ���ϻ�(���ܻᵼ��������)\n��escȡ���������������ת���Ʒѷ�������");
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
		//�ϻ�
		if (NULL==handle)
		{
			void startCheck();
			startCheck();
		}
		system("title ѡ���ϻ��û�");
		p->user = paginationMenu(getCards(), d_card, 0, 9)->date.card;
		system("title ��/�»�");
		if (NULL==p->user)
		{
			prPrompt("����", "��ǰδѡ���Ա��\n�������ȡ���ϻ�����");
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
		//�»�
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
			sprintf(other, "�Է��˻�����\n����ȡ%.2lfԪ\n�������ȷ��", money - p->user->balance/100.0);
			prPrompt("�»�",other);
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
				sprintf(body, "%d�ŵ�������\n���Զ��»�\n��������ر�", pl->date.pc->id);
				lock = 0;
				logPC(pl->date.pc);
				lock = 1;
				prPrompt("��ʾ", body);
				getch();
			}
			else if (money>=pl->date.pc->user->balance)
			{
				char body[96];
				sprintf(body, "%d�ŵ�������\n����%s�������Զ��»�\n��������ر�", pl->date.pc->id, getAttri("checkTime"));
				prPrompt("��ʾ", body);
				getch();
			}
			pl = next;
		}
		lock = 0;
		Sleep(iTime);
	}
	return NULL;
}

//��ʼִ�м��
void startCheck() {
	if (NULL == handle)
	{
		handle = CreateThread(NULL, 0, check, NULL, 0, NULL);
	}
}