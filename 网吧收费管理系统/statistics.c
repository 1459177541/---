#include"config.h"
pList statLists = NULL;

void initStatByTime() {
	prPrompt("��������", "��������ͳ����Ϣ");
	pList history = getHistorys();
	if (NULL == history || NULL == history->data.history)
	{
		return;
	}
	statLists = (pList)malloc(sizeof(List));
	pList p = statLists;
	p->last = NULL;
	p->next = NULL;
	p->type = d_statistics;
	p->data.statistics = (pStat)malloc(sizeof(stat));
	p->data.statistics->startHistory = history;
	p->data.statistics->time = history->data.history->time;
	p->data.statistics->stat_card_login = 0;
	p->data.statistics->stat_card_logout = 0;
	p->data.statistics->stat_recharge_money = 0;
	p->data.statistics->stat_up = 0;
	p->data.statistics->stat_up_money = 0;
	while (NULL!=history)
	{
		if (history->data.history->time.tm_mon!=p->data.statistics->time.tm_mon)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->next = NULL;
			q->type = d_statistics;
			p->next = q;
			p = p->next;
			p->data.statistics = (pStat)malloc(sizeof(stat));
			p->data.statistics->startHistory = history;
			p->data.statistics->time = history->data.history->time;
			p->data.statistics->stat_card_login = 0;
			p->data.statistics->stat_card_logout = 0;
			p->data.statistics->stat_recharge_money = 0;
			p->data.statistics->stat_up = 0;
			p->data.statistics->stat_up_money = 0;
		}
		double num = history->data.history->money;
		switch (history->data.history->type)
		{
		case C_CARD_T:
			p->data.statistics->stat_card_login++;
			break;
		case D_CARD_T:
			p->data.statistics->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->data.statistics->stat_recharge_money += num;
			break;
		case UP_T:
			p->data.statistics->stat_up++;
			break;
		case DOWN_T:
			p->data.statistics->stat_up_money += num;
			break;
		default:
			break;
		}
		history = history->next;
	}
}

pList getMoreStatByTime(pList start) {
	if (d_statistics!= start->type)
	{
		return NULL;
	}
	pList history = start->data.statistics->startHistory;
	pStat ps = (pStat)malloc(sizeof(stat));
	pList ret = (pList)malloc(sizeof(pList));
	ps->startHistory = history;
	ps->time = history->data.history->time;
	ps->stat_card_login = 0;
	ps->stat_card_logout = 0;
	ps->stat_recharge_money = 0;
	ps->stat_up = 0;
	ps->stat_up_money = 0;
	pList p = ret;
	p->last = NULL;
	p->next = NULL;
	p->type = d_statistics_more;
	p->data.statistics = ps;
	while (NULL != history
		&& history->data.history->time.tm_mon == p->data.statistics->time.tm_mon)
	{
		if (history->data.history->time.tm_yday != p->data.statistics->time.tm_yday)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->next = NULL;
			q->type = d_statistics_more;
			p->next = q;
			p = p->next;
			p->data.statistics = (pStat)malloc(sizeof(stat));
			p->data.statistics->startHistory = history;
			p->data.statistics->time = history->data.history->time;
			p->data.statistics->stat_card_login = 0;
			p->data.statistics->stat_card_logout = 0;
			p->data.statistics->stat_recharge_money = 0;
			p->data.statistics->stat_up = 0;
			p->data.statistics->stat_up_money = 0;
		}
		double money = history->data.history->money;
		switch (history->data.history->type)
		{
		case C_CARD_T:
			p->data.statistics->stat_card_login++;
			break;
		case D_CARD_T:
			p->data.statistics->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->data.statistics->stat_recharge_money += money;
			break;
		case UP_T:
			p->data.statistics->stat_up++;
			break;
		case DOWN_T:
			p->data.statistics->stat_up_money += money;
			break;
		default:
			break;
		}
		history = history->next;
	}
	return ret;
}

pList getStatByTime() {
	if (NULL == statLists)
	{
		initStatByTime();
	}
	return statLists;
}

void showStatByTime(pStat p,int isMore) {
	int x = 16;
	int y = 2;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                     ������Ϣ                  |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            ͳ������: %4d%s%2d%s               |"
		, isMore ? p->time.tm_mon : p->time.tm_year+1900, isMore ? "��" : "��"
		, isMore ? p->time.tm_mday : p->time.tm_mon, isMore ? "��" : "��"		
		);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            ע�Ῠ��: %-13d            |",p->stat_card_login);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            ��ֵ���: %-13.2lf            |", p->stat_recharge_money);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            ע������: %-13d            |", p->stat_card_logout);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            �ϻ�����: %-13d            |", p->stat_up);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|          �ϻ��ܽ��: %-13.2lf            |", p->stat_up_money);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(1 == 1);
	printf("                  |");
	gotoxy(x, y++);
	printf("=================================================");
	if (enter == isKey(getch()))
	{
		return;
	}
	else
	{
		showStatByTime(p, isMore);
	}
}

void prStatByTime(pStat p, int isOption) {
	printf("\n %6s %4d��%2d��    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_year+1900, p->time.tm_mon, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}

void prStatMoreByTime(pStat p, int isOption) {
	printf("\n %6s   %2d��%2d��    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_mon, p->time.tm_mday, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}
