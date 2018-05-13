#include"config.h"
pList rateLists = NULL;

//初始化
int initRate() {
	prPrompt("正在加载", "正在加载计费方案");
	FILE *fp = NULL;
	if (NULL == (fp = fopen("data\\rate", "rb")))
	{
		return 1;
	}
	pRate p = (pRate)malloc(sizeof(rate));
	if (NULL==rateLists)
	{
		if (fread(p,sizeof(rate),1,fp)>0)
		{
			rateLists = (pList)malloc(sizeof(List));
			rateLists->last = NULL;
			rateLists->next = NULL;
			rateLists->type = d_rate;
			rateLists->date.rate = p;
		}
		else
		{
			free(rateLists);
			free(p);
			fclose(fp);
			return 1;
		}
	}
	pList q = getRateList();
	pList o = (pList)malloc(sizeof(List));
	p = (pRate)malloc(sizeof(rate));
	while (fread(p, sizeof(rate), 1, fp)>0)
	{
		o->type = d_rate;
		o->date.rate = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pRate)malloc(sizeof(rate));
		o = (pList)malloc(sizeof(List));
	}
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

//得到列表
pList getRateList() {
	if (NULL == rateLists)
	{
		if (initRate())
		{
			/*
			pRate rateHead = (pRate)malloc(sizeof(rate));
			strcpy(rateHead->pc, getPCtypeList()->date->type);
			strcpy(rateHead->card, getCardTypeList()->date->name);
			rateHead->startTime = NULL;
			rateHead->endTime = NULL;
			rateHead->rule[0] = '\0';
			*/
		}
	}
	return rateLists;
}

//设置列表
void setRateList(pList p) {
	rateLists = p;
}

//输出
void prRate(pRate p) {
	printf("%30s | %-19s| %-20s \n", p->pc, p->card, p->rule);
}

//设置收费标准
void setRule(int type, pRate p) {
	int x = 16;
	int y = 5;
	gotoxy(x, y++); 
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                  设置收费标准                 |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|            %-29s      |", 0 == type ? "" : p->rule);
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        设置方法:在此处输入一个含有x(          |");//字母x为上一符合条件
	gotoxy(x, y++);
	printf("|        单位:元/时)的式子,用于计算符           |");
	gotoxy(x, y++);
	printf("|        合本条标准的金额(若为第一个计          |");
	gotoxy(x, y++);
	printf("|        费标准则为 0),字母t为时间(单           |");
	gotoxy(x, y++);
	printf("|        位:h),然后根据下一个符合条件           |");
	gotoxy(x, y++);
	printf("|        的计费标准进行计算,若该标准为          |");
	gotoxy(x, y++);
	printf("|        最后一个,则为最后收费金额。            |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                    ");
	OPTION_OK(1 == type);
	printf("                    |");
	gotoxy(x, y++);
	printf("=================================================");

	key k;
	if (0==type)
	{
		k = input(x + 13, 8, p->rule, 0, NUM | OTHER, "+-*/xXtT");
	}
	else
	{
		k = isKey(getch());
	}
	switch (k)
	{
	case up:
	case down:
	case left:
	case right:
	case tab:
		if (1==type)
		{
			setRule(0, p);
		}
		else
		{
			setRule(1, p);
		}
		return;
	case enter:
		if (1!=type)
		{
			setRule(1, p);
		}
		else
		{
			return;
		}
	default:
		break;
	}
}

//修改计费标准
void editRate(int type,int option[], pRate p) {
	myCls();
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               ");
	prOption(" 选择关联电脑 ", 0 == type, 22);
	printf("            | ");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               ");
	prOption("  选择关联卡  ", 1 == type, 22);
	printf("            | ");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               ");
	prOption("   计费标准   ", 2 == type, 22);
	printf("            |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                    ");
	OPTION_OK(3 == type);
	printf("                    |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);

	int in = getch();
	key k= isKey(in);
	switch (k)
	{
	case left:
	case up:
		type--;
		if (type < 0)
		{
			type = 5;
		}
		editRate(type, option, p);
		break;
	case right:
	case down:
	case tab:
		type++;
		if (type > 5)
		{
			type = 0;
		}
		editRate(type, option, p);
		break;
	case enter:
		switch (type)
		{
		case 0:
		{
			system("title 选择关联电脑");
			pList op = scrollMenu(getPCtypeList(), d_pcType, 4);
			strcpy(p->pc, op->date.pcType->type);
			system("title 收费标准管理");
			editRate(type, option, p);
			break;
		}
		case 1:
		{
			system("title 选择关联会员卡类型");
			pList op = scrollMenu(getCardTypeList(), d_cardType, 4);
			strcpy(p->card, op->date.cardType->name);
			system("title 收费标准管理");
			editRate(type, option, p);
			break;
		}
		case 2:
			setRule(0,p);
			editRate(type, option, p);
			return;
		case 3:
			return;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}

//计算
double compute(char *expression, int start, int end) {
	int index = -1;
	for (int i = start; i < end; i++)
	{
		if ('//' == expression[i] || '*' == expression[i])
		{
			index = i;
		}
		if ('+' == expression[i] || '-' == expression[i])
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
	{
		char * number = (char *)malloc(sizeof(char) * (end - start));
		for (int i = 0; i < end - start; i++)
		{
			number[i] = expression[i + start];
		}
		double num = atof(number);
		free(number);
		return num;
	}
	double a = compute(expression, start, index);
	double b = compute(expression, index + 1, end);
	switch (expression[index])
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a*b;
	case '//':
		return a / b;
	default:
		break;
	}
	return 0;
}

//计算价格(单条规则)
double result(pPC pc, pCard user, pRate rate,pTm ptm_time, double src) {
	if (strcmp(pc->type,rate->pc)!=0)
	{
		return src;
	}
	if (strcmp(user->type,rate->card)!=0)
	{
		return src;
	}
	char number[16];
	char time[16];
	sprintf(time, "%.2lf", ptm_time->tm_hour / 60.0 + ptm_time->tm_min);
	sprintf(number, "%.2lf", src);
	char * rule = (char*)malloc(64 * sizeof(char));
	strcpy(rule, rate->rule);

	replaceString(rule, 'x', number);
	replaceString(rule, 'X', number);
	replaceString(rule, 't', time);
	replaceString(rule, 'T', time);
	
	double result = compute(rule,0,strlen(rule));
	free(rule);
	return result;
}

//计算价格(全部规则)
double results(pPC pc, pCard user, pTm time) {
	if (NULL==getRateList() || NULL==user)
	{
		return 0;
	}
	pList p = getRateList()->next;
	double money = 0;
	while (NULL!=p)
	{
		money = result(pc, user, p->date.rate, time, money);
		p = p->next;
	}
	return money;
}
