#include"config.h"

pList historyLists = NULL;
int HistoryLength = 0;
int initHistory() {
	prPrompt("���ڼ���", "���ڼ�����ʷ��¼");
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
		strcpy(type, "ȫ��");
		break;
	case C_ADMIN_T:
		strcpy(type, "��������Ա");
		break;
	case D_ADMIN_T:
		strcpy(type, "ɾ������Ա");
		break;
	case U_ADMIN_T:
		strcpy(type, "�޸Ĺ���Ա");
		break;
	case C_RATE_T:
		strcpy(type, "�½��Ʒѱ�׼");
		break;
	case D_RATE_T:
		strcpy(type, "ɾ���Ʒѱ�׼");
		break;
	case U_RATE_T:
		strcpy(type, "�޸ļƷѱ�׼");
		break;
	case C_CARD_T:
		strcpy(type, "ע���Ա��");
		break;
	case D_CARD_T:
		strcpy(type, "ע����Ա��");
		break;
	case U_CARD_T:
		strcpy(type, "�޸Ļ�Ա����Ϣ");
		break;
	case C_PC_TYPE_T:
		strcpy(type, "������������");
		break;
	case D_PC_TYPE_T:
		strcpy(type, "ɾ����������");
		break;
	case U_PC_TYPE_T:
		strcpy(type, "�޸ĵ�������");
		break;
	case C_CARD_TYPE_T:
		strcpy(type, "������Ա������");
		break;
	case D_CARD_TYPE_T:
		strcpy(type, "ɾ����Ա������");
		break;
	case U_CARD_TYPE_T:
		strcpy(type, "�޸Ļ�Ա������");
		break;
	case UP_T:
		strcpy(type, "�ϻ�");
		break;
	case DOWN_T:
		strcpy(type, "�»�");
		break;
	case RECHARGE_T:
		strcpy(type, "��ֵ");
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
	printf("|               ����: %-24s          |", getHistoryType(p->type));
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|             ������: %-22s            |", p->editor);
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               ʱ��: %4d��%2d��%2d�� %2dʱ%2d��%2d��       |"
		, p->time.tm_year + 1900, p->time.tm_mon + 1, p->time.tm_mday
		, p->time.tm_hour, p->time.tm_min, p->time.tm_sec
		);
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               ��ϸ:%-32s   |", text1);
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
		sprintf(d->text, "�½�����Ա: %-16s Ȩ��: %-40s ", date.admin->name, prPower(date.admin->power));
		break;
	case D_ADMIN_T:
		sprintf(d->text, "ɾ������Ա: %-16s", date.admin->name);
		break;
	case U_ADMIN_T:
		sprintf(d->text, "�޸Ĺ���Ա��Ϣ: %-16s", date.admin->name);
		break;
	case C_RATE_T:
		sprintf(d->text, "�½��Ʒѷ���: %-16s ���� %s �� %s �ϻ�����", date.rate->rule, date.rate->card, date.rate->pc);
		break;
	case D_RATE_T:
		sprintf(d->text, "ɾ���Ʒѷ���: %s", date.rate->rule);
		break;
	case U_RATE_T:
		sprintf(d->text, "�޸ļƷѷ���: %s", date.rate->rule);
		break;
	case C_CARD_T:
		sprintf(d->text, "����: %s(֤����: %s)����ͨ%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case D_CARD_T:
		sprintf(d->text, "ע��: %s(֤����: %s)��ע��%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case U_CARD_T:
		sprintf(d->text, "�޸�: %s(֤����: %s)", date.card->masterName, date.card->idcardNum);
		break;
	case C_PC_TYPE_T:
		sprintf(d->text, "������������%s %d̨�����: %d~%d", date.pcType->type, date.pcType->num, date.pcType->startId, date.pcType->startId + date.pcType->num);
		break;
	case D_PC_TYPE_T:
		sprintf(d->text, "ɾ��%s���͵���", date.pcType->type);
		break;
	case U_PC_TYPE_T:
		sprintf(d->text, "�޸�%s���͵���", date.pcType->type);
		break;
	case C_CARD_TYPE_T:
		sprintf(d->text, "������Ա������%s���ۼ�: %.2lf", date.cardType->name, date.cardType->price/100.0);
		break;
	case D_CARD_TYPE_T:
		sprintf(d->text, "ɾ����Ա������%s", date.cardType->name);
		break;
	case U_CARD_TYPE_T:
		sprintf(d->text, "�޸�����%s�Ļ�Ա��", date.cardType->name);
		break;
	case UP_T:
		sprintf(d->text, "�û�: %16d �� %s ���� %d �����ϻ�", date.pc->user->id, date.pc->type, date.pc->id);
		break;
	case DOWN_T:
		sprintf(d->text, "�û�: %16d �� %16s ���� %16d �����»�, ����%5.2lfԪ", date.pc->user->id, date.pc->type, date.pc->id, other);
		break;
	case RECHARGE_T:
		sprintf(d->text, "�û�: %16d ��ֵ�� %16lf Ԫ", date.card->id, other);
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
	printf("\n%5s%16s |%15s  | %4d��%2d��%2d�� %2dʱ%2d��%2d�� %-5s"
		, isOption ? getAttri("L") : getAttri("NL"), getHistoryType(p->type), p->editor
		, p->time.tm_year+1900, p->time.tm_mon+1, p->time.tm_mday
		, p->time.tm_hour, p->time.tm_min, p->time.tm_sec
		, isOption ? getAttri("R") : getAttri("NR"));
}

//��������
pCriteria getDefaultCriteriaHistory() {
	pCriteria p = (pCriteria)malloc(sizeof(Criteria));
	p->type = condition;
	p->condition.history.editor = getAdminHead()->date.admin;
	p->condition.history.historyType = ALL_T;
	p->Criteria[0] = '\0';
	return p;
}

//������������б�
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
			sprintf(time, "%4d��%2d��%2d�� %2dʱ%2d��%2d��"
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

//ɸѡ
void setHistoryFormCriteria(pCriteria p, int type) {
	int x = 12;
	int y = 0;
	gotoxy(x, y++);
	printf("=========================================================");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("     ȫ��     ", 0 == type, 22);
	printf("     ");
	prOption("     ��ֵ     ", 1 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("     �ϻ�     ", 2 == type, 22);
	printf("     ");
	prOption("     �»�     ", 3 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("������Ա������", 4 == type, 22);
	printf("     ");
	prOption("ɾ����Ա������", 5 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("�޸Ļ�Ա������", 6 == type, 22);
	printf("     ");
	prOption(" �½��Ʒѱ�׼ ", 7 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption(" ɾ���Ʒѱ�׼ ", 8 == type, 22);
	printf("     ");
	prOption(" �޸ļƷѱ�׼ ", 9 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  ��������Ա  ", 10 == type, 22);
	printf("     ");
	prOption("  ɾ������Ա  ", 11 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  �޸Ĺ���Ա  ", 12 == type, 22);
	printf("     ");
	prOption("  ע���Ա��  ", 13 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption("  ע����Ա��  ", 14 == type, 22);
	printf("     ");
	prOption("�޸Ļ�Ա����Ϣ", 15 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|     ");
	prOption(" ������������ ", 16 == type, 22);
	printf("     ");
	prOption(" ɾ���������� ", 17 == type, 22);
	printf("     |");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|                   ");
	prOption(" �޸ĵ������� ", 18 == type, 22);
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

//ɸѡ
pList selectHistory(int type, pCriteria criteria) {
	char *historyType = getHistoryType(criteria->condition.history.historyType);
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
	printf("|          %c�л���ʽ: %-15s           |", 0 == type ? '>' : ' ', condition == criteria->type ? "��������" : "ģ������");
	if (condition == criteria->type)
	{
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|          %cѡ���¼����: %-15s       |", 1 == type ? '>' : ' ', historyType);
		gotoxy(x, y++);
		printf("|                                               |");
		gotoxy(x, y++);
		printf("|            %cѡ���¼��: %-15s       |"
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
		printf("|              %c�����������������              |", 1 == type ? '>' : ' ');
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
