#include"config.h"
pList statLists = NULL;

void initStat() {
	prPrompt("正在生成", "正在生成统计信息");
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
	p->date.statistics->startHistory = history;
	p->date.statistics->time = history->date.history->time;
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
			p->date.statistics->startHistory = history;
			p->date.statistics->time = history->date.history->time;
			p->date.statistics->stat_card_login = 0;
			p->date.statistics->stat_card_logout = 0;
			p->date.statistics->stat_recharge_money = 0;
			p->date.statistics->stat_up = 0;
			p->date.statistics->stat_up_money = 0;
		}
		double num = history->date.history->money;
		switch (history->date.history->type)
		{
		case C_CARD_T:
			p->date.statistics->stat_card_login++;
			break;
		case D_CARD_T:
			p->date.statistics->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->date.statistics->stat_recharge_money += num;
			break;
		case UP_T:
			p->date.statistics->stat_up++;
			break;
		case DOWN_T:
			p->date.statistics->stat_up_money += num;
			break;
		default:
			break;
		}
		history = history->next;
	}
}

pList getMoreStat(pList start) {
	if (d_statistics!= start->type)
	{
		return NULL;
	}
	pList history = start->date.statistics->startHistory;
	pStat ps = (pStat)malloc(sizeof(stat));
	pList ret = (pList)malloc(sizeof(pList));
	ps->startHistory = history;
	ps->time = history->date.history->time;
	ps->stat_card_login = 0;
	ps->stat_card_logout = 0;
	ps->stat_recharge_money = 0;
	ps->stat_up = 0;
	ps->stat_up_money = 0;
	pList p = ret;
	p->last = NULL;
	p->next = NULL;
	p->type = d_statistics_more;
	p->date.statistics = ps;
	while (NULL != history
		&& history->date.history->time.tm_yday != p->date.statistics->time.tm_yday)
	{
		if (history->date.history->time.tm_yday != p->date.statistics->time.tm_yday)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->type = d_statistics_more;
			p->next = q;
			p = p->next;
			p->date.statistics = (pStat)malloc(sizeof(stat));
			p->date.statistics->startHistory = history;
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
			p->date.statistics->stat_up_money += money;
			break;
		default:
			break;
		}
		history = history->next;
	}
	return ret;
}

pList getStat() {
	if (NULL == statLists)
	{
		initStat();
	}
	return statLists;
}

void showStat(pStat p,int isMore) {
	int x = 16;
	int y = 2;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                     更多信息                  |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            统计日期: %4d%s%2d%s               |"
		, isMore ? p->time.tm_mon : p->time.tm_year+1900, isMore ? "月" : "年"
		, isMore ? p->time.tm_mday : p->time.tm_mon, isMore ? "日" : "月"		
		);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            注册卡数: %-13d            |",p->stat_card_login);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            充值金额: %-13.2lf            |", p->stat_recharge_money);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            注销卡数: %-13d            |", p->stat_card_logout);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|            上机次数: %-13d            |", p->stat_up);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|          上机总金额: %-13.2lf            |", p->stat_up_money);
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
		showStat(p, isMore);
	}
}

void prStat(pStat p, int isOption) {
	printf(" %6s %4d年%2d月    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_year+1900, p->time.tm_mon, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}

void prStatMore(pStat p, int isOption) {
	printf(" %6s   %2d月%2d日    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_mon, p->time.tm_mday, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}
