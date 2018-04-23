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
			historyLists = (pHistory)malloc(sizeof(history));
			historyLists->next = NULL;
			historyLists->last = NULL;
			historyLists->type = d_history;
			return NULL;
		}
	}
	return historyLists;
}

char *getHistoryType(pHistory p) {
	char type[15];
	switch (p->type)
	{
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
	splitString(p->time, textTime1, 0, 32);
	splitString(p->time, textTime2, 33, 64);
	splitString(p->text, text1, 0, 32);
	splitString(p->text, text1, 33, 64);
	splitString(p->text, text1, 65, 96);
	int x = 8;
	int y = 1;
	gotoxy(x, y++);
	printf("=========================================================");
	gotoxy(x, y++);
	printf("|                                                       |");
	gotoxy(x, y++);
	printf("|               ����: %-24s             |", getHistoryType(p));
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|             ������: %-22s             |", p->editor);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               ʱ��: %-32s         |", textTime1);
	gotoxy(x, y++);
	printf("|                    %-32s         |", textTime2);
	gotoxy(x, y++);
	printf("|                                                   |");
	gotoxy(x, y++);
	printf("|               ��ϸ:%-32s         |", text1);
	gotoxy(x, y++);
	printf("|                    %-32s         |", text2);
	gotoxy(x, y++);
	printf("|                    %-32s         |", text3);
	gotoxy(x, y++);
	printf("|                                                   |");
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

void addHistory(historyType type, date date, void* other) {
	char * prPower(int power);
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
	switch (type)
	{
	case C_ADMIN_T:
		sprintf(d->text, "�½�����Ա: %-16s Ȩ��: %-40s ", date.admin->name, prPower(date.admin->power));
		break;
	case D_ADMIN_T:
		sprintf(d->text, "ɾ������Ա: %-16s", date.admin->name);
		break;
	case U_ADMIN_T:
		sprintf(d->text, "�޸Ĺ���Ա��Ϣ: %-16s --> %-16s ", date.admin->name);
		break;
	case C_RATE_T:
		sprintf(d->text, "�½��Ʒѷ���: %-16s ���� %s �� %s �ϻ�����", date.rate->rule, date.rate->card, date.rate->pc);
		break;
	case D_RATE_T:
		sprintf(d->text, "ɾ���Ʒѷ���: %s", date.rate->rule);
		break;
	case U_RATE_T:
		sprintf(d->text, "�޸ļƷѷ���: %s --> %s", date.rate->rule);
		break;
	case C_CARD_T:
		sprintf(d->text, "����: %s(֤����: %s)����ͨ%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case D_CARD_T:
		sprintf(d->text, "ע��: %s(֤����: %s)��ע��%s", date.card->masterName, date.card->idcardNum, date.card->type);
		break;
	case U_CARD_T:
		sprintf(d->text, "�޸�: %s(֤����: %s)��ע��%s", date.card->masterName, date.card->idcardNum, date.card->type);
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
		sprintf(d->text, "������Ա������%s���ۼ�: %lf", date.cardType->name, date.cardType->price);
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
		sprintf(d->text, "�û�: %16d �� %16s ���� %16d �����»�, ����%5lfԪ", date.pc->user->id, date.pc->type, date.pc->id, (double*)other);
		break;
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
	printf("%6s%16s |%15s  |%19s %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), getHistoryType(p), p->editor, p->time, isOption ? getAttri("R") : getAttri("NR"));
}
