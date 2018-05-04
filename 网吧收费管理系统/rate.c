#include"config.h"
pList rateLists = NULL;

//初始化
int initRate() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\rate", "rb")))
	{
		return 1;
	}
	pRate p = (pRate)malloc(sizeof(rate));
	if (NULL==rateLists && fread(p,sizeof(rate),1,fp)>0)
	{
		rateLists = (pList)malloc(sizeof(List));
		rateLists->last = NULL;
		rateLists->next = NULL;
		rateLists->date.rate = p;
	}
	pList q = getRateList();
	pList o = (pList)malloc(sizeof(List));
	p = (pRate)malloc(sizeof(rate));
	while (fread(p, sizeof(card), 1, fp)>0)
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
	char *time1 = (char*)malloc(25 * sizeof(char));
	char *time2 = (char*)malloc(25 * sizeof(char));
	time1[0] = '\0';
	time2[0] = '\0';
	char * time = (char *)malloc(sizeof(char) * 50);
	time[0] = '\0';
	prTimes(p->startTime, p->endTime, time);
	splitString(time, time1, 0, 24);
	if (24<strlen(time))
	{
		splitString(time, time2, 25, 49);
	}
	printf("%30s | %-19s| %-20s \n", time1, p->card, p->rule);
	printf("%30s | %-19s| %-20s \n", time2, p->pc, "");
	free(time);
	free(time2);
	free(time1);
}

//设置时间段
//T	0:年 1:月 2:周 3:日
void setTimes(pTm start, pTm end, int type, int T) {
	int x = 16;
	int y = 2;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|               周期: ");
	switch (T)
	{
	case 0:
		printf("每年");
		break;
	case 1:
		printf("每月");
		break;
	case 2:
		printf("每周");
		break;
	case 3:
		printf("每日");
		break;
	default:
		break;
	}
	printf("               |");
	gotoxy(x, y++);
	printf("|                                               |");
	switch (T)
	{
	case 0:
		gotoxy(x, y++);
		printf("|               年份:                           |");
		gotoxy(x, y++);
		printf("|                                               |");
	case 1:
		gotoxy(x, y++);
		printf("|               月份:                           |");
		gotoxy(x, y++);
		printf("|                                               |");
	case 3:
		gotoxy(x, y++);
		printf("|                 日:                           |");
		gotoxy(x, y++);
		printf("|                                               |");
		break;
	case 2:
		gotoxy(x, y++);
		printf("|                每周                           |");
		gotoxy(x, y++);
		printf("|                                               |");
		break;
	default:
		break;
	}
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                       时   分                 |");
	gotoxy(x, y++);
	printf("|                  至   时   分                 |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(-1 == type);
	printf("                  |");
	gotoxy(x, y++);
	printf("=================================================");
	char *in = (char*)malloc(16 * sizeof(char));
	in[0] = '\0';
	key k = input(x + 19, 7 + type * 2, in, 0, INTER, NULL);
	int num = atoi(in);
	switch (k)
	{
	case up:
		type++;
		switch (T)
		{
		case 0:
			if (7<type)
			{
				type = -1;
			}
			break;
		case 1:
			if (6<type)
			{
				type = -1;
			}
			break;
		case 2:
			if (5<type)
			{
				type = -1;
			}
			break;
		case 3:
			if (5<type)
			{
				type = -1;
			}
			break;
		default:
			break;
		}
		break;
	case down:
		type--;
		if (-1>type)
		{
			switch (T)
			{
			case 0:
				type = 7;
				break;
			case 1:
			case 2:
			case 3:
				type = 6;
				break;
			default:
				break;
			}
		}
		break;
	case left:
		T--;
		if (0>T)
		{
			T = 3;
		}
		break;
	case right:
		T++;
		if (3<T)
		{
			T = 0;
		}
		break;
	case enter:
		if (type!=-1)
		{
			type = -1;
		}
		else
		{
			return;
		}
	default:
		break;
	}
	if (-1!=type)
	{
		///////////////////////////////////////////////////////////////
	}
	free(in);
	setTimes(start, end, type, T);
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
	printf("|            %-29s      |",p->rule);
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        设置方法：字母x为上一符合条件          |");
	gotoxy(x, y++);
	printf("|        的计算结果(单位:元/时)(若为第一        |");
	gotoxy(x, y++);
	printf("|        个计费标准则为0),字母t为时间(         |");
	gotoxy(x, y++);
	printf("|        单位:h)，经过加减乘除得到结果         |");
	gotoxy(x, y++);
	printf("|        传递给下一个符合条件的计费             |");
	gotoxy(x, y++);
	printf("|        标准，若为最后一个，则为收费金额。     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                    ");
	OPTION_OK(1==type);
	printf("                    |");
	gotoxy(x, y++);
	printf("=================================================");
	key k;
	if (0==type)
	{
		k = input(x + 16, 8, p->rule, 0, NUM | OTHER, "+-*/xXtT");
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
	printf("\n\n\n");
	printf("\n\n\n            %c关联电脑类型：",0==type?'>':' ');
	int i = 0;
	pList pPC = getPCtypeList();
	while (i!=option[0] && NULL != pPC)
	{
		pPC = pPC->next;
		i++;
	}
	strcpy(p->pc, pPC->date.pcType->type);
	printf("%s", pPC->date.pcType->type);
	
	printf("\n\n               %c关联卡名称：", 1 == type ? '>' : ' ');
	i = 0;
	pList pCardType = getCardTypeList();
	while (i != option[1] && NULL!=pCardType)
	{
		pCardType = pCardType->next;
		i++;
	}
	strcpy(p->card, pCardType->date.cardType->name);
	printf("%s", pCardType->date.cardType->name);
	
	printf("\n\n              ");
	prOption("设置收费时间段",2==type,22);
	printf("\n\n              ");
	prOption("   计费标准   ", 3 == type, 22);
	printf("\n\n              ");
	OPTION_OK(4 == type);

	int in = getch();
	key k= isKey(in);
	switch (k)
	{
	case left:
		option[type]--;
		if (option[type] < 0)
		{
			option[type] = 0;
		}
		editRate(type, option, p);
		break;
	case right:
		option[type]++;
		if ((1 == type && NULL == pPC->next) || (2 == type && NULL == pCardType->next))
		{
			option[type]--;
		}
		editRate(type, option, p);
		break;
	case up:
		type--;
		if (type < 0)
		{
			type = 5;
		}
		editRate(type, option, p);
		break;
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
		case 1:
			editRate(5, option, p);
			return;
		case 2:
			setTimes(p->startTime, p->endTime, 0, 0);
			editRate(type, option, p);
			return;
		case 3:
			setRule(0,p);
			editRate(type, option, p);
			return;
		case 4:
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
	///////////////////////////////////////////////
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
