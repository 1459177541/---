#include"config.h"
pList statLists = NULL;

void initStat() {
	pList history = getHistorys();
	if (NULL == history || NULL == history->date.history)
	{
		return;
	}
	statLists = (pList)malloc(sizeof(List));
	pList p = statLists;
	p->last = NULL;
	p->next = NULL;
	p->type = d_statistics;
	p->date.statistics = (pStat)malloc(sizeof(stat));
	p->date.statistics->time.tm_mon = history->date.history->time.tm_mon;
	p->date.statistics->stat_card_login = 0;
	p->date.statistics->stat_card_logout = 0;
	p->date.statistics->stat_recharge_money = 0;
	p->date.statistics->stat_up = 0;
	p->date.statistics->stat_up_money = 0;
	while (NULL!=history)
	{
		if (history->date.history->time.tm_mon!=p->date.statistics->time.tm_mon)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->type = d_statistics;
			p->next = q;
			p = p->next;
			p->date.statistics = (pStat)malloc(sizeof(stat));
			p->date.statistics->time = history->date.history->time;
			p->date.statistics->stat_card_login = 0;
			p->date.statistics->stat_card_logout = 0;
			p->date.statistics->stat_recharge_money = 0;
			p->date.statistics->stat_up = 0;
			p->date.statistics->stat_up_money = 0;
		}
		double money = history->date.history->money;
		switch (history->date.history->type)
		{
		case C_CARD_T:
			p->date.statistics->stat_card_login++;
			break;
		case D_CARD_T:
			p->date.statistics->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->date.statistics->stat_recharge_money += money;
			break;
		case UP_T:
			p->date.statistics->stat_up++;
			break;
		case DOWN_T:
			p->date.statistics->stat_card_login+=money;
			break;
		default:
			break;
		}
		history = history->next;
	}

}

pList getStat() {
	if (NULL == statLists)
	{
		initStat();
	}
	return statLists;
}

void prStat(pStat p, int isOption) {
	printf(" %6s %4dÄê%2dÔÂ | %20.2lf | %20.2lf %-6s\n"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_year, p->time.tm_mon, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("L") : getAttri("NL"));
}