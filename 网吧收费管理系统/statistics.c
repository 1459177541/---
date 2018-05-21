#include"config.h"
pList statListsByTime = NULL;

void initStatByTime() {
	prPrompt("正在生成", "正在生成统计信息");
	pList history = getHistorys();
	if (NULL == history || NULL == history->data.history)
	{
		return;
	}
	statListsByTime = (pList)malloc(sizeof(List));
	pList p = statListsByTime;
	p->last = NULL;
	p->next = NULL;
	p->type = d_statistics;
	p->data.statisticsByTime = (pStat)malloc(sizeof(stat));
	p->data.statisticsByTime->startHistory = history;
	p->data.statisticsByTime->time = history->data.history->time;
	p->data.statisticsByTime->stat_card_login = 0;
	p->data.statisticsByTime->stat_card_logout = 0;
	p->data.statisticsByTime->stat_recharge_money = 0;
	p->data.statisticsByTime->stat_up = 0;
	p->data.statisticsByTime->stat_up_money = 0;
	while (NULL!=history)
	{
		if (history->data.history->time.tm_mon!=p->data.statisticsByTime->time.tm_mon)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->next = NULL;
			q->type = d_statistics;
			p->next = q;
			p = p->next;
			p->data.statisticsByTime = (pStat)malloc(sizeof(stat));
			p->data.statisticsByTime->startHistory = history;
			p->data.statisticsByTime->time = history->data.history->time;
			p->data.statisticsByTime->stat_card_login = 0;
			p->data.statisticsByTime->stat_card_logout = 0;
			p->data.statisticsByTime->stat_recharge_money = 0;
			p->data.statisticsByTime->stat_up = 0;
			p->data.statisticsByTime->stat_up_money = 0;
		}
		double num = history->data.history->money;
		switch (history->data.history->type)
		{
		case C_CARD_T:
			p->data.statisticsByTime->stat_card_login++;
			break;
		case D_CARD_T:
			p->data.statisticsByTime->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->data.statisticsByTime->stat_recharge_money += num;
			break;
		case UP_T:
			p->data.statisticsByTime->stat_up++;
			break;
		case DOWN_T:
			p->data.statisticsByTime->stat_up_money += num;
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
	pList history = start->data.statisticsByTime->startHistory;
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
	p->data.statisticsByTime = ps;
	while (NULL != history
		&& history->data.history->time.tm_mon == p->data.statisticsByTime->time.tm_mon)
	{
		if (history->data.history->time.tm_yday != p->data.statisticsByTime->time.tm_yday)
		{
			pList q = (pList)malloc(sizeof(List));
			q->last = p;
			q->next = NULL;
			q->type = d_statistics_more;
			p->next = q;
			p = p->next;
			p->data.statisticsByTime = (pStat)malloc(sizeof(stat));
			p->data.statisticsByTime->startHistory = history;
			p->data.statisticsByTime->time = history->data.history->time;
			p->data.statisticsByTime->stat_card_login = 0;
			p->data.statisticsByTime->stat_card_logout = 0;
			p->data.statisticsByTime->stat_recharge_money = 0;
			p->data.statisticsByTime->stat_up = 0;
			p->data.statisticsByTime->stat_up_money = 0;
		}
		double money = history->data.history->money;
		switch (history->data.history->type)
		{
		case C_CARD_T:
			p->data.statisticsByTime->stat_card_login++;
			break;
		case D_CARD_T:
			p->data.statisticsByTime->stat_card_logout++;
			break;
		case RECHARGE_T:
			p->data.statisticsByTime->stat_recharge_money += money;
			break;
		case UP_T:
			p->data.statisticsByTime->stat_up++;
			break;
		case DOWN_T:
			p->data.statisticsByTime->stat_up_money += money;
			break;
		default:
			break;
		}
		history = history->next;
	}
	return ret;
}

pList getStatByTime() {
	if (NULL == statListsByTime)
	{
		initStatByTime();
	}
	return statListsByTime;
}

void showStatByTime(pStat p,int isMore) {
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
	printf("|          充值总金额: %-13.2lf            |", p->stat_recharge_money);
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
		showStatByTime(p, isMore);
	}
}

void prStatByTime(pStat p, int isOption) {
	printf("\n %6s %4d年%2d月    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_year+1900, p->time.tm_mon, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}

void prStatMoreByTime(pStat p, int isOption) {
	printf("\n %6s   %2d月%2d日    | %17.2lf | %20.2lf %-6s"
		, isOption ? getAttri("L") : getAttri("NL"), p->time.tm_mon, p->time.tm_mday, p->stat_up_money, p->stat_recharge_money, isOption ? getAttri("R") : getAttri("NR"));
}
