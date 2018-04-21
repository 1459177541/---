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
	historyFinal = q->last;
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

void addHistory(historyType type, date date) {
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
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (type)
	{
	case C_ADMIN_T:

		break;
	case D_ADMIN_T:

		break;
	case U_ADMIN_T:

		break;
	case C_RATE_T:

		break;
	case D_RATE_T:

		break;
	case U_RATE_T:

		break;
	case C_CARD_T:

		break;
	case D_CARD_T:

		break;
	case U_CARD_T:

		break;
	case C_PC_TYPE_T:

		break;
	case D_PC_TYPE_T:

		break;
	case U_PC_TYPE_T:

		break;
	case C_CARD_TYPE_T:

		break;
	case D_CARD_TYPE_T:

		break;
	case U_CARD_TYPE_T:

		break;
	case UP_T:

		break;
	case DOWN_T:

		break;
	default:
		strcpy(pl->date.history->text, "ERROR");
		break;
	}
}

void prHistory(pHistory p, int isOption) {
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
	printf("%6s%16s |%15s  |%19s %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), type, p->editor, p->time, isOption ? getAttri("R") : getAttri("NR"));
}
