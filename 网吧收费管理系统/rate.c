#include"config.h"
pRate rateLists = NULL;

//��ʼ��
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

//���
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

//����ʱ���
void setTimes(pTm start,pTm end) {
	//////////////////////////////////////////////////
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
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|        ���÷�������ĸxΪ��һ��������          |");
	gotoxy(x, y++);
	printf("|        �ļ�����(��Ϊ��һ���Ʒѱ�׼��        |");
	gotoxy(x, y++);
	printf("|        Ϊ0)�������Ӽ��˳��õ��������         |");
	gotoxy(x, y++);
	printf("|        ����һ�����������ļƷѱ�׼����         |");
	gotoxy(x, y++);
	printf("|        Ϊ���һ������Ϊ�շѽ�             |");
	gotoxy(x, y++);
	printf("|        (��λ:Ԫ/ʱ)                           |");
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

//�޸ļƷѱ�׼
void editRate(int type,int option[], pRate p) {
	system("cls");
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
	prOption("�����շ�ʱ���",2==type,22);
	printf("\n\n              ");
	prOption("   �Ʒѱ�׼   ", 3 == type, 22);
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

/*********************************************************
 * �ѷ���
 *********************************************************
//�����շѱ�׼
void rateMenu(int type) {
	int length = 0;
	pRateList q = getRateList();
	pRateList op = q;
	while (length<type - 10 && NULL != q)
	{
		length++;
		q = q;
	}
	system("cls");
	printf("\n\n                             ���������������շѱ�׼\n\n");
	printf("                  ================================================            \n");
	printf("             ��ʼʱ��          |     ��Ա������     |     �շѱ�׼            \n");
	printf("             ����ʱ��          |      ��������      |                         \n");
	if (0 != length)
	{
		printf("              ++++++           |       ++++++       |      ++++++            \n");
	}
	else
	{
		printf("                               |                    |                         \n");
	}
	int pr = 0;
	while (NULL != q)
	{
		length++;
		if (length == type)
		{
			op = q->date;
		}
		if (pr<5)
		{
			pr++;
			prRate(q->date, length == type);
		}
		else {
			break;
		}
		q = q->next;
	}
	for (int i = pr; i < 5; i++)
	{
		printf("                               |                    |                         \n");
		printf("                               |                    |                         \n");
	}
	if ((NULL != q && type >= 0) || (10 < length && type < 0))
	{
		printf("              ++++++           |       ++++++       |      ++++++            \n");
	}
	else
	{
		printf("                               |                    |                         \n");
	}
	printf("                  ================================================            \n");
	if (0 == length && 1 == type)
	{
		type = 0;
	}
	printf("\n           	                  ");
	prOption("  �½�  ", 0 == type, 13);
	printf("\n           	                  ");
	prOption("  ���  ", -1 == type, 13);
	printf("\n           	                  ");
	while (1)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			if (0 == type)
			{
				if (0 == length)
				{
					rateMenu(-1);
				}
				else
				{
					rateMenu(length);
				}
			}
			else if (-1 == type)
			{
				rateMenu(0);
			}
			else if (1 == type)
			{
				rateMenu(-1);
			}
			else
			{
				rateMenu(type - 1);
			}
			return;
			break;
		case down:
		case tab:
			if (0 == type)
			{
				rateMenu(-1);
			}
			else if (-1 == type)
			{
				if (0 == length)
				{
					rateMenu(0);
				}
				else
				{
					rateMenu(1);
				}
			}
			else if (length == type)
			{
				rateMenu(0);
			}
			else
			{
				rateMenu(type + 1);
			}
			return;
		case enter:
		{
			int a[] = {0,0};
			if (0 == type)
			{
				pRate p = (pRate)malloc(sizeof(rate));
				p->card[0] = '\0';
				p->pc[0] = '\0';
				p->startTime = NULL;
				p->endTime = NULL;
				p->rule[0] = '\0';
				while (NULL != q)
				{
					q = q->next;
				}
				pRateList pl = (pRateList)malloc(sizeof(rateList));
				pl->last = q;
				pl->next = NULL;
				pl->date = p;
				q->next = pl;
				editRate(0,a, pl);
				rateMenu(type);
				return;
			}
			else if (-1 == type)
			{
				return;
			}
			else
			{
				editRate(0, a, op);
				rateMenu(type);
				return;
			}
		}
			break;
		case esc:
		{
			return;
		}
		break;
		default:
			break;
		}
	}
}

//����
void saveRate() {
	if (NULL == getRateList())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\rate", "wb")))
	{
		return;
	}
	pRateList p = getRateList();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(rate), 1, fp))
		{
			p = p->next;

		}
	}
}
*/

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
}

//����۸�(��������)
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

//����۸�(ȫ������)
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
