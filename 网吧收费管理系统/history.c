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

void addHistory(historyType type, pPC pp, pCard pc, pRate pr,pAdmin pa) {
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


/*********************************************************
 * �ѷ���
 *********************************************************
//History���˵�
void HistoryMenu(pHistoryList historyList, int page, int option) {
	pHistoryList p = getHistorys();
	if (10 >= option)
	{
		page += option / 10;
		option %= 10;
	}
	pHistory op = NULL;
	for (int i = 0; i < page * 10 && p != NULL; i++)
	{
		p = p->next;
	}
	int length = 0;
	system("title ��Ա������");
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n                                                 ");
	prOption("�� ��", -1 == option, 9);
	printf("\n          ��������     |     ������     |                ʱ��               \n");
	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			length++;
			prHistory(p->date, i == option);
			if (i == option)
			{
				op = p->date;
			}
			p = p->next;
		}
		else {
			printf("\n\n");
		}
	}
	printf("\n                     ");
	prOption("��  ҳ", option == -6, 9);
	printf("   ");
	prOption("��һҳ", option == -5, 9);
	printf("   ");
	prOption("��һҳ", option == -4, 9);
	printf("   ");
	prOption("β  ҳ", option == -3, 9);
	printf("   ");
	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case number:
		HistoryMenu(historyList, page, in - '0');
		return;
	case up:
		option--;
		if (-6 >= option)
		{
			option = length - 1;
		}
		HistoryMenu(historyList, page, option);
		return;
	case down:
		option++;
		if (length <= option)
		{
			option = -5;
		}
		HistoryMenu(historyList, page, option);
		return;
	case tab:
		if (0 <= option)
		{
			HistoryMenu(historyList, page, -5);
		}
		else
		{
			HistoryMenu(historyList, page, 0);
		}
		return;
	case left:
		if (option<0)
		{
			if (-4 == option)
			{
				HistoryMenu(historyList, page, 9);
			}
			else {
				HistoryMenu(historyList, page, option - 5);
			}
		}
		else if (0 != page)
		{
			HistoryMenu(historyList, page - 1, option);
		}
		else
		{
			HistoryMenu(historyList, page, option);
		}
		return;
	case right:
		if (option<0)
		{
			HistoryMenu(historyList, page, option + 1);
		}
		else if (page > HistoryLength / 10 - 1) {
			HistoryMenu(historyList, page, option);
		}
		else
		{
			HistoryMenu(historyList, page + 1, option);
		}
		return;
	case enter:
		if (-1 == option)
		{
			/////////////////////
		}
		else if (-6 == option)
		{
			HistoryMenu(historyList, 0, option);
		}
		else if (-5 == option)
		{
			HistoryMenu(historyList, page - 1, option);
		}
		else if (-4 == option)
		{
			HistoryMenu(historyList, page + 1, option);
		}
		else if (-3 == option)
		{
			HistoryMenu(historyList, HistoryLength / 10, option);
		}
		else
		{
			HistoryMenu(historyList, page, option);
		}
		break;
	case esc:
		return;
	default:
		break;
	}
}

//����
void saveHistory() {
	if (NULL == getHistorys())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\history", "wb")))
	{
		return;
	}
	pHistoryList p = getHistorys();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(history), 1, fp))
		{
			p = p->next;
		}
	}
}
*/
