#include"config.h"
pRate rateLists = NULL;

//初始化
int initRate() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\rate", "rb")))
	{
		return 1;
	}
	pList q = getRateList();
	pList o = (pList)malloc(sizeof(List));
	pRate p = (pRate)malloc(sizeof(card));
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

//输出
void prRate(pRate p, int isOption) {
	char time1[25];
	char time2[25];
	char * time = (char *)malloc(sizeof(char) * 50);
	prTimes(p->startTime, p->endTime, time);
	splitString(time, time1, 0, 24);
	splitString(time, time2, 25, 49);
	printf("%5s%25s |%19s |%20s  %-5s\n"
		, isOption ? getAttri("L") : getAttri("NL"), time1, p->card, p->rule, isOption ? getAttri("R") : getAttri("NR"));
	printf("%5s%25s |%19s |%20s  %-5s\n"
		, isOption ? getAttri("L") : getAttri("NL"), time2, p->pc, "", isOption ? getAttri("R") : getAttri("NR"));
}

//设置时间段
void setTimes(pTm start,pTm end) {
	//////////////////////////////////////////////////
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
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        设置方法：字母x为上一符合条件          |");
	gotoxy(x, y++);
	printf("|        的计算结果(若为第一个计费标准则        |");
	gotoxy(x, y++);
	printf("|        为0)，经过加减乘除得到结果传递         |");
	gotoxy(x, y++);
	printf("|        给下一个符合条件的计费标准，若         |");
	gotoxy(x, y++);
	printf("|        为最后一个，则为收费金额。             |");
	gotoxy(x, y++);
	printf("|        (单位:元/时)                           |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        ");
	OPTION_OK(1==type);
	printf("        |");
	gotoxy(x, y++);
	printf("=================================================");
	key k;
	if (0==type)
	{
		k = input(x + 16, 9, p->rule, 0, NUM | OTHER, "+-*/xX");
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
	system("cls");
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
			setTimes(p->startTime, p->endTime);
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
}

//计算价格(单条规则)
double result(pPC pc, pCard user, pRate rate, double src) {
	if (strcmp(pc->type,rate->pc)!=0)
	{
		return src;
	}
	if (strcmp(user->type,rate->card)!=0)
	{
		return src;
	}

	char number[16];
	sprintf(number, "%.2lf", src);
	char * rule = (char*)malloc(32 * sizeof(char));
	char * temp = (char*)malloc(32 * sizeof(char));
	strcpy(rule, rate->rule);
	
	int i = 0;
	while ('\0' != rule[i])
	{
		if ('x' == rule[i] || 'X' == rule[i])
		{
			int j = 0;
			int it = i;
			while (rule[it]!='\0')
			{
				temp[j] = rule[it];
				it++;
			}
			temp[j] = '\0';
			while (number[j]!='\0')
			{
				rule[i] = number[j];
				i++;
				j++;
			}
			j = 0;
			while ('\0'!=temp[j])
			{
				rule[i] = temp[j];
				i++;
				j++;
			}
			break;
		}
		i++;
	}
	rule[i] = '\0';
	double result = compute(rule,0,i);
	free(rule);
	free(temp);
	return result;
}

//计算价格(全部规则)
double results(pPC pc, pCard user) {
	pList p = getRateList()->next;
	double money = 0;
	while (NULL!=p)
	{
		money = result(pc, user, p->date.rate, money);
		p = p->next;
	}
	return money;
}
