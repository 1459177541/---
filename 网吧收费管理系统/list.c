#include"config.h"

//����
void save(dataType type) {
	FILE *fp = NULL;
	pList p = NULL;
	char fileName[14] = "";
	switch (type)
	{
	case d_admin:
		prPrompt("���ڱ���", "���ڱ������Ա��Ϣ");
		strcpy(fileName, "data\\admin");
		p = getAdminHead();
		break;
	case d_pcType:
		prPrompt("���ڱ���", "���ڱ������ɹ�ģ");
		strcpy(fileName, "data\\pc");
		p = getPCtypeList();
		break;
	case d_cardType:
		prPrompt("���ڱ���", "���ڱ����Ա������");
		strcpy(fileName, "data\\cardType");
		p = getCardTypeList();
		break;
	case d_rate:
		prPrompt("���ڱ���", "���ڱ���Ʒѷ���");
		strcpy(fileName, "data\\rate");
		p = getRateList();
		break;
	case d_history:
		prPrompt("���ڱ���", "���ڱ�����ʷ��¼");
		strcpy(fileName, "data\\history");
		p = getHistorys();
		break;
	case d_card:
		prPrompt("���ڱ���", "���ڱ����Ա��");
		strcpy(fileName, "data\\card");
		p = getCards();
		break;
	case d_attri:
		prPrompt("���ڱ���", "���ڱ�������");
		strcpy(fileName, "data\\config");
		p = getAttriList();
		break;
	default:
		break;
	}
	if (NULL==p || NULL == (fp = fopen(fileName, "wb")))
	{
		return;
	}
	while (NULL != p)
	{
		if (NULL == p->data.admin)
		{
			p = p->next;
			continue;
		}
		switch (type)
		{
		case d_admin:
			if (fwrite(p->data.admin, sizeof(admin), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_pcType:
			if (fwrite(p->data.pcType, sizeof(PCtype), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_cardType:
			if (fwrite(p->data.cardType, sizeof(cardType), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_rate:
			if (fwrite(p->data.rate, sizeof(rate), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_history:
			if (fwrite(p->data.history, sizeof(history), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_card:
			if (fwrite(p->data.card, sizeof(card), 1, fp)>0)
			{
				p = p->next;
			}
			break;;
		case d_attri:
			if (fwrite(p->data.card, sizeof(attribute), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		default:
			break;
		}
	}
	fclose(fp);
}

//ȫ������
void saveAll() {
	save(d_admin);
	save(d_attri);
	save(d_pcType);
	save(d_cardType);
	save(d_rate);
	save(d_card);
	save(d_history);
}

//�ر���Դ
void close(dataType type) {
	pList p = NULL;
	switch (type)
	{
	case d_admin:
		p = getAdminHead();
		break;
	case d_attri:
		p = getAttriList();
		break;
	case d_card:
		p = getCards();
		break;
	case d_cardType:
		p = getCardTypeList();
		break;
	case d_history:
		p = getHistorys();
		break;
	case d_pc:
		if (hasLoginPC())
		{
			logoutPCAll();
		}
		if (NULL==getPCtypeList()->next)
		{
			return;
		}
		p = getPCs();
		break;
	case d_pcType:
		p = getPCtypeList();
		break;
	case d_rate:
		p = getRateList();
		break;
	case d_statistics:
		p = getStatByTime();
		break;
	default:
		p = NULL;
		break;
	}
	if (NULL==p)
	{
		return;
	}
	pList q;
	while (NULL != p->next)
	{
		q = p->next;
		free(p->data.admin);
		free(p);
		p = q;
	}
	free(p);
}

//�ر�ȫ��
void closeAll() {
	close(d_admin);
	close(d_attri);
	close(d_card);
//	close(d_cardType);
	close(d_statistics);
	close(d_history);
	close(d_pc);
	close(d_pcType);
	close(d_rate);
}

//������
void swap(pList a, pList b) {
	if (a==b)
	{
		return;
	}
	data t = a->data;
	a->data = b->data;
	b->data = t;
}

//����---���ܳ���
pList _sort(pList start, pList end, int length, int(*isUP)(pList a, pList b), int isNot) {
	if (0>=length)
	{
		return start;
	}
	if (8>length)
	{
		//ѡ������
		pList t = start;
		while (t!=end)
		{
			pList min = t;
			pList tt = t;
			while (tt!=end)
			{
				tt = tt->next;
				if (isUP(min,tt)&&!isNot)
				{
					min = tt;
				}
				else if (isUP(tt,min)&&isNot)
				{
					min = tt;
				}
			}
			swap(min, t);
			t = t->next;
		}
		return start;
	}
	//�鲢����
	pList mid = start;
	int minLength = length / 2;
	for (int i = 0; i < minLength-1; i++)
	{
		mid = mid->next;
	}
	pList midNext = mid->next;
	pList endNext = end->next;
	pList a = _sort(start, mid, minLength, isUP, isNot);
	pList b = _sort(midNext, end, length - minLength, isUP, isNot);
	midNext = b;
	pList p = (pList)malloc(sizeof(List));
	pList ret = p;
	p->next = NULL;
	p->last = NULL;
	for (int i = 0; i < length; i++)
	{
		if (a != midNext)
		{
			if (endNext == b || (isNot && isUP(a,b)) || (!isNot && isUP(b,a)))
			{
				p->next = a;
				a->last = p;
				a = a->next;
				p = p->next;
				p->next = NULL;
				continue;
			}
		}
		if(b != endNext)
		{
			p->next = b;
			b->last = p;
			b = b->next;
			p = p->next;
			p->next = NULL;
			continue;
		}
	}
	pList pp = ret->next;
	pp->last = NULL;
	free(ret);
	return pp;
}

pList sort(pList list, int (*isUP)(pList a, pList b), int isNot) {
	if (NULL==list)
	{
		return NULL;
	}
	pList s = list;
	pList e = list;
	int l = 1;
	while (NULL!=s->last)
	{
		l++;
		s = s->last;
	}
	while (NULL!=e->next)
	{
		l++;
		e = e->next;
	}
	list = _sort(s, e, l, isUP, isNot);
	while (NULL != list->last)
	{
		list = list->last;
	}
	return list;
}

//�˵�����
int isFirst = 1;
void MenuHelp(int type) {
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                      ����                     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	if (0 == type)
	{
		gotoxy(x, y++);
		printf("|         pagup/pagdown ��ǰ/��һҳ             |");
	}
	gotoxy(x, y++);
	printf("|               up/down ��ǰ/��һ��             |");
	gotoxy(x, y++);
	printf("|            right/left ��ǰ/��һѡ��           |");
	gotoxy(x, y++);
	printf("|                   tab ���л�ѡ����            |");
	gotoxy(x, y++);
	printf("|                 enter ��ȷ��                  |");
	gotoxy(x, y++);
	printf("|                   esc ������                  |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                    ");
	OPTION_OK(1);
	printf("                    |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	if (enter == k || esc == k)
	{
		isFirst = 0;
		return;
	}
	else
	{
		MenuHelp(type);
	}

}

//��ҳ�˵�
int initFinalPage(pList list) {
	int length = 0;
	while (NULL!=list)
	{
		length++;
		list = list->next;
	}
	return length;
}
pList paginationMenu(pList list) {
	dataType type = list->type;
	static int index = 0;
	static int option = 0;
	static int thisPage = 0;
	static int finalPage = -1;
	static int Length = 0;
	if (d_pc!=type
		&& d_card!=type
		&& d_history!=type
		&& d_statistics!=type
		&& d_statistics_more!=type
		&& d_attri!=type
		)
	{
		prPrompt("���棡", "�þ����������в������\n����������þ��棬����ϵ����\n��������Զ�ʶ����ͼ������");
		getch();
		return scrollMenu(list);
	}
	if (-1==finalPage)
	{
		Length = initFinalPage(list);
		finalPage = (Length - 1) / 10;
	}
	thisPage = finalPage < thisPage ? finalPage : thisPage;
	if (thisPage == finalPage && (Length-1)%10<index)
	{
		index = (Length-1) % 10;
	}
	pList p = list;
	pList ret = NULL;
	pList op = list;
	int length = 0;
	int optionLength = 0;
	myCls();
	switch (type)
	{
	case d_pc:
		printf("\n                             ---===��/�»�===---\n");
		printf("\n-------------+--------------------+--------------------+------------------------");
		printf("\n      id     |        ����        |      ��ǰ�û�      |      �ϻ�ʱ��      ");
		printf("\n-------------+--------------------+--------------------+------------------------");
		optionLength = 8;
		break;
	case d_card:
		printf("\n                          ---===��Ա������===---\n");
		printf("\n-------------------+--------------------+--------------------+------------------");
		printf("\n        id         |        ����        |       �û���       |      ���    ");
		printf("\n-------------------+--------------------+--------------------+------------------");
		optionLength = 10;
		break;
	case d_history:
		printf("\n                           ---===��ʷ��¼===---\n");
		printf("\n----------------------+-----------------+---------------------------------------");
		printf("\n         ��������     |      ������     |                ʱ��               ");
		printf("\n----------------------+-----------------+---------------------------------------");
		optionLength = 6;
		break;
	case d_statistics_more:
		optionLength--;
	case d_statistics:
		printf("\n                               ---===ͳ��===---\n");
		printf("\n----------------------+-------------------+-------------------------------------");
		printf("\n         ʱ��         |      �ϻ����     |                ��ֵ���             ");
		printf("\n----------------------+-------------------+-------------------------------------");
		optionLength += 6;
		break;
	case d_attri:
		printf("\n                               ---===����===---\n");
		printf("\n----------------------------------+---------------------------------------------");
		printf("\n                    ������        |               ����ֵ                        ");
		printf("\n----------------------------------+---------------------------------------------");
		optionLength += 5;
		break;
	default:
		return NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->data.admin)
			{
				length++;
				switch (type)
				{
				case d_pc:
					prPC(p->data.pc, i == index);
					break;
				case d_card:
					prCard(p->data.card, i == index);
					break;
				case d_history:
					prHistory(p->data.history, i == index);
					break;
				case d_statistics:
					prStatByTime(p->data.statistics, i == index);
					break;
				case d_statistics_more:
					prStatMoreByTime(p->data.statistics, i == index);
					break;
				case d_attri:
					prAttri(p->data.attri, i == index);
					break;
				default:
					break;
				}
				if (i == index)
				{
					op = p;
				}
				p = p->next;
				continue;
			}
			i--;
			p = p->next;
		}
		else {
			switch (type)
			{
			case d_pc:
				printf("\n             |                    |                    |                       "); 
				break;
			case d_card:
				printf("\n                   |                    |                    |                  ");
				break;
			case d_history:
				printf("\n                      |                 |                                       ");
				break;
			case d_statistics:
			case d_statistics_more:
				printf("\n                      |                   |                                     ");
				break;
			case d_attri:
				printf("\n                                  |                                             ");
				break;
			default:
				break;
			}
		}
	}
	switch (type)
	{
	case d_pc:
		printf("\n-------------+--------------------+--------------------+------------------------");
		break;
	case d_card:
		printf("\n-------------------+--------------------+--------------------+------------------");
		break;
	case d_history:
		printf("\n----------------------+-----------------+---------------------------------------");
		break;
	case d_statistics:
	case d_statistics_more:
		printf("\n----------------------+-------------------+-------------------------------------");
		break;
	case d_attri:
		printf("\n----------------------------------+---------------------------------------------");
		break;
	default:
		break;
	}
	printf("                              %5d / %-5d\n", thisPage+1, finalPage+1);
	printf("\n                  ");
	prOption("��  ҳ", 0 == option, 9);
	printf("   ");
	prOption("��һҳ", 1 == option, 9);
	printf("   ");
	prOption("��һҳ", 2 == option, 9);
	printf("   ");
	prOption("β  ҳ", 3 == option, 9);
	switch (type)
	{
	case d_pc:
		printf("\n\n           ");
		prOption("ת�����ɹ�ģ", 4 == option, 18);
		printf(" ");
		if (NULL==op->data.pc->user)
		{
			prOption("�ϻ�", 5 == option, 6);
		}
		else
		{
			prOption("�»�", 5 == option, 6);
		}
		printf("   ");
		prOption("��ϸ", 6 == option, 6);
		printf("   ");
		prOption("ɸѡ", 7 == option, 6);
		printf("   ");
		prOption("���", 8 == option, 6);
		break;
	case d_card:
		printf("\n\n       ");
		prOption("�½�", 4 == option, 6);
		printf("    ");
		prOption("ɾ��", 5 == option, 6);
		printf("    ");
		prOption("��ֵ", 6 == option, 6);
		printf("    ");
		prOption("��ϸ", 7 == option, 6);
		printf("    ");
		prOption("ɸѡ", 8 == option, 6);
		printf("    ");
		prOption("����", 9 == option, 6);
		printf("    ");
		prOption("���", 10 == option, 6);
		break;
	case d_history:
		printf("\n\n                 ");
		prOption("��ϸ", 4 == option, 6);
		printf("            ");
		prOption("ɸѡ", 5 == option, 6);
		printf("            ");
		prOption("���", 6 == option, 6);
		break;
	case d_statistics:
		printf("\n\n                    ");
		prOption("����", 4 == option, 6);
		printf("            ");
		prOption("��ϸ", 5 == option, 6);
		printf("            ");
		prOption("���", 6 == option, 6);
		break;
	case d_statistics_more:
		printf("\n\n                          ");
		prOption("����", 4 == option, 6);
		printf("                ");
		prOption("���", 5 == option, 6);
		break;
	case d_attri:
		printf("\n\n                         ");
		prOption("�޸�", 4 == option, 6);
		printf("                  ");
		prOption("���", 5 == option, 6);
		break;
	default:
		break;
	}
	if (isFirst)
	{
		MenuHelp(0);
		return paginationMenu(list);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)		//����������
	{
	case number:
	{
		index = in - '0';
		break;
	}
	case up:
		index--;
		if (0 > index)
		{
			index = length-1;
		}
		break;
	case down:
		index++;
		if (length <= index)
		{
			index = 0;
		}
		break;
	case tab:
		if (4 > option)
		{
			option += 4;
		}
		else
		{
			option -= 4;
		}
		break;
	case left:
		option--;
		if (0 > option)
		{
			option = optionLength;
		}
		break;
	case right:
		option++;
		if (optionLength < option)
		{
			option = 0;
		}
		break;
	case pgup:
		if (0>=thisPage)
		{
			break;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->last;
		}
		thisPage--;
		break;
	case pgdn:
		if (finalPage<=thisPage)
		{
			break;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->next;
		}
		thisPage++;
		break;
	case enter:
		//����ѡ����
		switch (option)		
		{
		case 0:	//��ҳ
			for (int i = 0; i < 10 * thisPage; i++)
			{
				list = list->last;
			}
			thisPage = 0;
			break;
		case 1:	//��һҳ
			if (0 >= thisPage)
			{
				break;
			}
			for (int i = 0; i < 10; i++)
			{
				list = list->last;
			}
			thisPage--;
			break;
		case 2:	//��һҳ
			if (finalPage <= thisPage)
			{
				break;
			}
			for (int i = 0; i < 10; i++)
			{
				list = list->next;
			}
			thisPage++;
			break;
		case 3:	//βҳ
			for (int i = 0; i < 10 * (finalPage - thisPage); i++)
			{
				list = list->next;
			}
			thisPage = finalPage;
			break;
		case 4:
			//������������
			switch (type)		
			{
			case d_pc:			//���ɹ�ģ
				if ((isPower(getUser()->power, 14) || isPower(getUser()->power, 15) || isPower(getUser()->power, 16)))
				{
					prPrompt("�����������ɹ�ģ", "�����������");
					getch();
					system("title ���ɹ�ģ����");
					scrollMenu(getPCtypeList());
					if (isEditPCType())
					{
						thisPage = 0;
						finalPage = -1;
						list = getPCs();
					}
					system("title ��/�»�");
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			case d_card:		//�½�
			{
				if (isPower(getUser()->power, 0))
				{
					list = newCard(list);
					finalPage = -1;
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			case d_history:		//��ϸ
				showHistory(op->data.history);
				break;
			case d_statistics:			//������Ϣ
				showStatByTime(op->data.statistics, 0);
				break;
			case d_statistics_more:		//������Ϣ
				showStatByTime(op->data.statistics, 1);
				break;
			case d_attri:
				editAttri(op->data.attri);
				break;
			default:
				break;
			}
			break;
		case 5:
			//������������
			switch (type)		
			{
			case d_pc:			//��/�»�
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				int tin = index;
				int top = option;
				index = 0;
				option = 9;
				thisPage = 0;
				finalPage = -1;
				logPC(op->data.pc);
				index = tin;
				option = top;
				thisPage = ttp;
				finalPage = tfp;
				break;
			}
			case d_card:		//ɾ��
				if (isPower(getUser()->power, 1))
				{
					pList temp = (NULL != op->next) ? op->next : op->last;
					delCard(op);
					op = temp;
					finalPage = -1;
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			case d_history:		//ɸѡ
			{
				pList t = NULL;
				index = 0;
				thisPage = 0;
				finalPage = -1;
				t = selectToHistory();
				if (NULL == t || NULL == t->data.history)
				{
					prPrompt("ע��", "��ǰɸѡ���Ϊ��\n����ʾȫ�����\n�����������");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.history = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			case d_statistics:	//��ϸ
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				int tin = index;
				int top = option;
				index = 0;
				option = 0;
				thisPage = 0;
				finalPage = -1;
				pList ms = getMoreStatByTime(op);
				paginationMenu(ms);
				index = tin;
				option = top;
				thisPage = ttp;
				finalPage = tfp;
				pList q = ms->next;
				while (NULL != q)
				{
					free(ms);
					ms = q;
					q = q->next;
				}
				break;
			}
			case d_statistics_more:	//�˳�
			case d_attri:
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		case 6:
			//������������
			switch (type)		
			{
			case d_pc:			//��ϸ
				showPC(op->data.pc);
				break;
			case d_card:		//��ֵ
				recharge(op->data.card);
				break;
			case d_history:		//�˳�
			case d_statistics:
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		case 7:	
		{
			//������������
			switch (type)		
			{
			case d_pc:			//ɸѡ
			{
				pList t = NULL;
				finalPage = -1;
				thisPage = 0;
				index = 0;
				option = 0;
				t = selectToPC();
				if (NULL==t||NULL==t->data.pc)
				{
					prPrompt("ע��", "��ǰɸѡ���Ϊ��\n����ʾȫ�����\n�����������");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.pc = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			case d_card:		//��ϸ
			{
				pList typeList = getCardTypeList();
				while (0 != strcmp(op->data.card->type, typeList->data.cardType->name) && NULL != typeList->next)
				{
					typeList = typeList->next;
				}

				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, op->data.card->password);
				strcpy(pass2, op->data.card->password);
				showCard(0, op->data.card, "", pass1, pass2);
				strcpy(pass1, "***************");
				strcpy(pass2, "***************");
				free(pass1);
				free(pass2);

				pList typeList2 = getCardTypeList();
				while (0 != strcmp(op->data.card->type, typeList2->data.cardType->name) && NULL != typeList2->next)
				{
					typeList2 = typeList2->next;
				}
				char *money = (char *)malloc(sizeof(char) * 64);
				int iMoney = typeList2->data.cardType->price - typeList->data.cardType->price;
				if (iMoney>0)
				{
					sprintf(money, "����ȡ%.2lfע�����\n(�ǳ�ֵ)\n�����������", iMoney / 100.0);
					prPrompt("ע��", money);
					getch();
				}
				else if (iMoney<0)
				{
					sprintf(money, "�뷵��%.2lfע�����\n�����������", -iMoney / 100.0);
					prPrompt("ע��", money);
					getch();
				}
				free(money);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 8:	
		{
			switch (type)
			{
			case d_pc:			//�˳�
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			case d_card:		//ɸѡ
			{
				pList t = NULL;
				finalPage = -1;
				thisPage = 0;
				index = 0;
				option = 0;
				t = selectToCard();
				if (NULL == t || NULL == t->data.card)
				{
					prPrompt("ע��", "��ǰɸѡ���Ϊ��\n����ʾȫ�����\n�����������");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.card = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			default:
				break;
			}
			break;
		}
		case 9:
			switch (type)
			{
			case d_card:		//����
			{
				sortCard();
				list = getCards();
				thisPage = 0;
				break;
			}
			default:
				break;
			}
			break;
		case 10:
		{
			switch (type)
			{
			case d_card:		//�˳�
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	case esc:
	{
		index = 0;
		option = 0;
		finalPage = -1;
		thisPage = 0;
		isFirst = 1;
		return op;
	}
	default:
		break;
	}
	return paginationMenu(list);
}

//�����˵�
pList scrollMenu(pList list) {
	dataType type = list->type;
	static int option = 0;
	if (NULL==list)
	{
		return NULL;
	}
	if (d_pcType != type
		&& d_cardType != type
		&& d_admin != type
		&& d_rate != type
		)
	{
		prPrompt("���棡", "�þ����������в������\n����������þ��棬����ϵ����\n��������Զ�ʶ����ͼ������");
		getch();
		return paginationMenu(list);
	}
	pList ret = NULL;
	char *nMore = (char*)malloc(160 * sizeof(char));
	int isTop = 0;
	myCls();
	switch (type)
	{
	case d_pcType:
		printf("\n\n                                      ���ɹ�ģ\n\n");
		printf("                  ================================================            \n");
		printf("                        ����     |      ����      |    ��ʼ���               \n");
		printf("                  ---------------+----------------+---------------         \n");
		strcpy(nMore, "                                 |                |                          \n");
		break;
	case d_cardType:
		printf("\n\n                                  ���ɻ�Ա������\n\n");
		printf("                  ================================================            \n");
		printf("                        ��Ա������       |     �۸�           \n");
		printf("                  -----------------------+------------------------            \n");
		strcpy(nMore, "                                         |                                 \n");
		break;
	case d_admin:
		printf("\n\n                                      ����Ա\n\n");
		printf("                  ================================================            \n");
		printf("             �û���    |                        Ȩ��                          \n");
		printf("                  -----+------------------------------------------         \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                                  �����շѱ�׼\n\n");
		printf("                  ================================================            \n");
		printf("                    ��������   |     ��Ա������     |     �շѱ�׼            \n");
		printf("                  -------------+--------------------+-------------            \n");
		strcpy(nMore, "                               |                    |                         \n");
		break;
	default:
		return NULL;
	}
	pList p = list;
	for (int i = 0; i < 3; i++)
	{
		if (NULL!=p && NULL!=p->last)
		{
			p = p->last;
		}
		else
		{
			isTop++;
		}
	}
	if(0!=isTop)
	{
		int top = isTop;
		while ((top--)>0)
		{
			printf(nMore);
		}
	}
	for (int i = isTop; i < 7; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->data.admin)
			{
				if (3 == i)
				{
					ret = p;
				}
				switch (type)
				{
				case d_pcType:
					if (3 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					prPCtype(p->data.pcType);
					if (3 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					break;
				case d_cardType:
					if (3 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					prCardType(p->data.cardType);
					if (3 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					break;
				case d_admin:
					if (3 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					prUser(p->data.admin);
					if (3 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					break;
				case d_rate:
					if (3 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					prRate(p->data.rate);
					if (3 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					break;
				default:
					return ret;
				}
			}
			p = p->next;
		}
		if (6==i && NULL!=p)
		{
			printf(nMore);
		}
		else if(NULL==p)
		{
			printf(nMore);
		}
	}
	printf("                  ================================================            \n");
	printf("\n\n      ");
	prOption("  �½�  ", 0 == option, 13);
	printf(" ");
	prOption("  ɾ��  ", 1 == option, 13);
	printf(" ");
	prOption("  ��ϸ  ", 2 == option, 13);
	printf(" ");
	prOption("  ����  ", 3 == option, 13);
	printf(" ");
	prOption("  ���  ", 4 == option, 13);
	if (d_rate == type)
	{
		printf("\n\n                    ");
		prOption("  ����  ", 5 == option, 13);
		printf("               ");
		prOption("  ����  ", 6 == option, 13);
		printf(" ");
	}
	free(nMore);
	if (isFirst)
	{
		MenuHelp(1);
		return scrollMenu(list);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)	//����������
	{
	case up:
		if (NULL!=list->last)
		{
			list = list->last;
		}
		break;
	case down:
		if (NULL != list->next)
		{
			list = list->next;
		}
		break;
	case left:
		if (0==option)
		{
			option = d_rate == type ? 7 : 5;
		}
		option--;
		break;
	case tab:
	case right:
		if ((d_rate == type ? 6 : 4) == option)
		{
			option = -1;
		}
		option++;
		break;
	case symbol:
		if ('+' == in && d_rate == type)
		{
			if (isPower(getUser()->power, 5))
			{
				if (NULL != list->last)
				{
					if (NULL == list->last->last)
					{
						prPrompt("����", "Ĭ�ϵļƷѷ��������ǵ�һ��\n�����������");
						getch();
					}
					else
					{
						swap(list, list->last);
						list = list->last;
					}
				}
			}
			else
			{
				prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
				getch();
			}
		}
		if ('-' == in && d_rate == type)
		{
			if (isPower(getUser()->power, 5))
			{
				if (NULL==list->last)
				{
					prPrompt("����", "Ĭ�ϵļƷѷ��������ǵ�һ��\n�����������");
					getch();
				}
				else if (NULL!=list->next)
				{
					swap(list, list->next);
					list = list->next;
				}
			}
			else
			{
				prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
				getch();
			}
		}
		ret = scrollMenu(list);
		break;
	case enter:
	{
		switch (option)		//����ѡ����
		{
		case 0:
		{
			switch (type)		//������������
			{
			case d_pcType:
			{
				if (isPower(getUser()->power,14))
				{
					if (!editPCTypePS(0))
					{
						break;
					}
					list = newPCType(list);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			case  d_cardType:
			{
				if (isPower(getUser()->power, 11))
				{
					list = newCardType(list);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			case d_admin:
			{
				if (isPower(getUser()->power, 8))
				{
					list = newAdmin(list);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			case d_rate:
			{
				if (isPower(getUser()->power, 3))
				{
					list = newRate(list);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case 1:
			if ((isPower(getUser()->power, 15) && d_pcType == type)
					|| (isPower(getUser()->power, 12) && d_cardType == type)
					|| (isPower(getUser()->power, 9) && d_admin == type)
					|| (isPower(getUser()->power, 4) && d_rate == type)
				)
			{
				if (d_pcType == type)
				{
					if (!editPCTypePS(0))
					{
						break;
					}
				}
				setEdit(1);
				if (NULL!=list->last)
				{
					pList temp = NULL!=list->next? list->next : list->last;
					list->last->next = list->next;
					if (NULL != list->next)
					{
						list->next->last = list->last;
					}
					switch (type)
					{
					case d_pcType:
						getPCtypeList()->data.pcType->num -= list->data.pcType->num;						
						addHistory(D_PC_TYPE_T, list->data, 0);
						break;
					case d_cardType:
						addHistory(D_CARD_T, list->data, 0);
						break;
					case d_admin:
						addHistory(D_ADMIN_T, list->data, 0);
						break;
					case d_rate:
						addHistory(D_RATE_T, list->data, 0);
						break;
					default:
						break;
					}
					free(list);
					list = temp;
				}
				else
				{
					if (d_pcType == type || d_cardType == type || d_rate == type)
					{
						prPrompt("ɾ��ʧ��", "��ֹɾ��Ĭ��ѡ��\n�����������");
						getch();
					}
					else if (d_admin == type)
					{
						prPrompt("ɾ��ʧ��", "��ֹɾ����������Ա\n�����������");
						getch();
					}
				}
			}
			else
			{
				prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
				getch();
			}
			break;
		case 2:
		{
			if (NULL==list->last)
			{
				if (d_admin==type)
				{
					if (strcmp(getUser()->name,"root")==0)
					{
						char *pass = (char*)malloc(sizeof(char) * 32);
						pass[0] = '\0';
						prPrompt("�����볬������Ա������", "\n��enter��ȷ�ϣ���escȡ��");
						key key = input(32, 12, pass, 1, NUM | LETTER | SYMBOL, NULL);
						if (enter==key)
						{
							while (strcmp(pass,getUser()->password)!=0 
								&& enter != key && esc != key)
							{
								prPrompt("�����������������", "\n��enter��ȷ�ϣ���escȡ��");
								key = input(32, 12, pass, 1, NUM | LETTER | SYMBOL, NULL);
							}
						}
						else
						{
							break;
						}
						if (esc==k)
						{
							break;
						}
						prPrompt("��ʾ", "����������κ��޸Ķ����ᱣ��\n�����������");
						getch();
					}
					else
					{
						prPrompt("��ֹ��", "ֻ�г�������Ա�����޸ĳ�������Ա\n�����������");
						getch();
						break;
					}
				}
				else
				{
					prPrompt("��ֹ����", "��ֹ�޸�Ĭ��ѡ��\n�����������");
					getch();
					break;
				}
			}
			switch (type)		//������������
			{
			case d_pcType:
				if (!editPCTypePS(0))
				{
					break;
				}
				setEdit(1);
				editPCtype(0, list->data.pcType);
				addHistory(U_PC_TYPE_T, list->data, 0);
				break;
			case  d_cardType:
				editCardType(0, list->data.cardType);
				addHistory(U_CARD_TYPE_T, list->data, 0);
				break;
			case d_admin:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, list->data.admin->password);
				strcpy(pass2, list->data.admin->password);
				editUser(0, list->data.admin,pass1,pass2);
				free(pass1);
				free(pass2);
				addHistory(U_ADMIN_T, list->data, 0);
				if (NULL==list->last)
				{
					list->data.admin->power = ~0;
					strcpy(list->data.admin->name, "root");
				}
				break;
			}
			case d_rate:
			{
				int a[] = { 0,0 };
				editRate(0, a, list->data.rate);
				addHistory(U_RATE_T, list->data, 0);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 3:
			if (d_admin==type)
			{
				helpFromUser();
			}
			MenuHelp(1);
			getch();
			return scrollMenu(list);
			break;
		case 4:
			isFirst = 1;
			option = 0;
			return ret;
		case 5:
			if (isPower(getUser()->power, 5))
			{
				if (NULL != list->last)
				{
					if (NULL == list->last->last)
					{
						prPrompt("����", "Ĭ�ϵļƷѷ��������ǵ�һ��\n�����������");
						getch();
					}
					else
					{
						swap(list, list->last);
						list = list->last;
					}
				}
			}
			else
			{
				prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
				getch();
			}
			break;
		case 6:
			if (isPower(getUser()->power, 5))
			{
				if (NULL == list->last)
				{
					prPrompt("����", "Ĭ�ϵļƷѷ��������ǵ�һ��\n�����������");
					getch();
				}
				else if (NULL != list->next)
				{
					swap(list, list->next);
					list = list->next;
				}
			}
			else
			{
				prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
				getch();
			}
			break;
		default:
			break;
		}
		ret = scrollMenu(list);
		return ret;
	}
	case esc:
		option = 0;
		isFirst = 1;
		return ret;
	default:
		break;
	}
	return scrollMenu(list);
}
