#include"config.h"
pList rateLists = NULL;

//��ʼ��
int initRate() {
	FILE *fp = NULL;
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

//�õ��б�
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

//�����б�
void setRateList(pList p) {
	rateLists = p;
}

//���
void prRate(pRate p) {
	printf("%30s | %-19s| %-20s \n", p->pc, p->card, p->rule);
}

//�����շѱ�׼
void setRule(int type, pRate p) {
	int x = 16;
	int y = 5;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                  �����շѱ�׼                 |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|            %-29s      |",p->rule);
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        ���÷�������ĸxΪ��һ��������          |");
	gotoxy(x, y++);
	printf("|        �ļ�����(��λ:Ԫ/ʱ)(��Ϊ��һ        |");
	gotoxy(x, y++);
	printf("|        ���Ʒѱ�׼��Ϊ0),��ĸtΪʱ��(         |");
	gotoxy(x, y++);
	printf("|        ��λ:h)�������Ӽ��˳��õ����         |");
	gotoxy(x, y++);
	printf("|        ���ݸ���һ�����������ļƷ�             |");
	gotoxy(x, y++);
	printf("|        ��׼����Ϊ���һ������Ϊ�շѽ�     |");
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

//�޸ļƷѱ�׼
void editRate(int type,int option[], pRate p) {
	myCls();
	printf("\n\n\n");
	printf("\n\n\n            %c�����������ͣ�",0==type?'>':' ');
	int i = 0;
	pList pPC = getPCtypeList();
	while (i!=option[0] && NULL != pPC)
	{
		pPC = pPC->next;
		i++;
	}
	strcpy(p->pc, pPC->date.pcType->type);
	printf("%s", pPC->date.pcType->type);
	
	printf("\n\n               %c���������ƣ�", 1 == type ? '>' : ' ');
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
	prOption("   �Ʒѱ�׼   ", 2 == type, 22);
	printf("\n\n              ");
	OPTION_OK(3 == type);

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

//����
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

//����۸�(��������)
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

//����۸�(ȫ������)
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
