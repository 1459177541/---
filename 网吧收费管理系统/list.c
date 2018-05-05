#include"config.h"

//����
void save(dateType type) {
	FILE *fp;
	pList p = NULL;
	char fileName[14] = "";
	switch (type)
	{
	case d_admin:
		strcpy(fileName, "data\\admin");
		p = getAdminHead();
		break;
	case d_pcType:
		strcpy(fileName, "data\\pc");
		p = getPCtypeList();
		break;
	case d_cardType:
		strcpy(fileName, "data\\cardType");
		p = getCardTypeList();
		break;
	case d_rate:
		strcpy(fileName, "data\\rate");
		p = getRateList();
		break;
	case d_history:
		strcpy(fileName, "data\\history");
		p = getHistorys();
		break;
	case d_card:
		strcpy(fileName, "data\\card");
		p = getCards();
		break;
	case d_attri:
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
		if (NULL == p->date.admin)
		{
			p = p->next;
			continue;
		}
		switch (type)
		{
		case d_admin:
			if (fwrite(p->date.admin, sizeof(admin), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_pcType:
			if (fwrite(p->date.pcType, sizeof(PCtype), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_cardType:
			if (fwrite(p->date.cardType, sizeof(cardType), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_rate:
			if (fwrite(p->date.rate, sizeof(rate), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_history:
			if (fwrite(p->date.history, sizeof(history), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_card:
			if (fwrite(p->date.card, sizeof(card), 1, fp)>0)
			{
				p = p->next;
			}
			break;;
		case d_attri:
			if (fwrite(p->date.card, sizeof(attribute), 1, fp)>0)
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
	prPrompt("���ڱ���", "���ڱ������Ա��Ϣ");
	save(d_admin);
	prPrompt("���ڱ���", "���ڱ�������");
	save(d_attri);
	prPrompt("���ڱ���", "���ڱ������ɹ�ģ");
	save(d_pcType);
	prPrompt("���ڱ���", "���ڱ����Ա������");
	save(d_cardType);
	prPrompt("���ڱ���", "���ڱ���Ʒѷ���");
	save(d_rate);
	prPrompt("���ڱ���", "���ڱ����Ա��");
	save(d_card);
	prPrompt("���ڱ���", "���ڱ�����ʷ��¼");
	save(d_history);
}

//��ҳ�˵�
int thisPage = 0;
int finalPage = -1;
void initFinalPage(pList list) {
	int length = 0;
	while (NULL!=list)
	{
		length++;
		list = list->next;
	}
	finalPage = length/10;
}

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

pList paginationMenu(pList list, dateType type, int index, int option) {
	pList p = list;
	if (-1==finalPage)
	{
		initFinalPage(list);
	}
	pList ret = NULL;
	pList op = list;
	int length = 0;
	int optionLength = 0;
	myCls();
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pc:
		system("title ��/�»�");
		printf("\n                             ---===��/�»�===---\n");
		printf("\n-------------+--------------------+--------------------+------------------------");
		printf("\n      id     |        ����        |      ��ǰ�û�      |      �ϻ�ʱ��      ");
		printf("\n-------------+--------------------+--------------------+------------------------");
		optionLength = 8;
		break;
	case d_card:
		system("title ��Ա������");
		printf("\n                          ---===��Ա������===---\n");
		printf("\n-------------------+--------------------+--------------------+------------------");
		printf("\n        id         |        ����        |       �û���       |      ���    ");
		printf("\n-------------------+--------------------+--------------------+------------------");
		optionLength = 9;
		break;
	case d_history:
		system("title ��ʷ��¼");
		printf("\n                           ---===��ʷ��¼===---\n");
		printf("\n----------------------+-----------------+---------------------------------------");
		printf("\n         ��������     |      ������     |                ʱ��               ");
		printf("\n----------------------+-----------------+---------------------------------------");
		optionLength = 6;
		break;
	case d_statistics:
		optionLength--;
	case d_statistics_more:
		system("title ͳ��");
		printf("\n                               ---===ͳ��===---\n");
		printf("\n----------------------+-------------------+-------------------------------------");
		printf("\n         ʱ��         |      �ϻ����     |                ��ֵ���             ");
		printf("\n----------------------+-------------------+-------------------------------------");
		optionLength += 5;
		break;
	default:
		return NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->date.admin)
			{
				length++;
				switch (type)
				{
				case d_pc:
					prPC(p->date.pc, i == index);
					break;
				case d_card:
					prCard(p->date.card, i == index);
					break;
				case d_history:
					prHistory(p->date.history, i == index);
					break;
				case d_statistics:
					prStat(p->date.statistics, i == index);
					break;
				case d_statistics_more:
					prStatMore(p->date.statistics, i == index);
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
		prOption("��/�»�", 5 == option, 12);
		printf("   ");
		prOption("��ϸ", 6 == option, 6);
		printf("   ");
		prOption("ɸѡ", 7 == option, 6);
		printf("   ");
		prOption("����", 8 == option, 6);
		break;
	case d_card:
		printf("\n\n            ");
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
		break;
	case d_history:
		printf("\n\n                    ");
		prOption("��ϸ", 4 == option, 6);
		printf("            ");
		prOption("ɸѡ", 5 == option, 6);
		printf("            ");
		prOption("����", 6 == option, 6);
		break;
	case d_statistics:
		printf("\n\n                         ");
		prOption("��ϸ", 4 == option, 6);
		printf("                  ");
		prOption("����", 5 == option, 6);
		break;
	case d_statistics_more:
		printf("\n\n                                           ");
		prOption("����", 4 == option, 6);
		break;
	default:
		break;
	}
	if (isFirst)
	{
		MenuHelp(0);
		return paginationMenu(list, type, index, option);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)		//����������
	{
	case number:
	{
		ret = paginationMenu(list, type, in - '0', option);
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
			ret = paginationMenu(list, type, index, option);
			return ret;
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
			ret = paginationMenu(list, type, index, option);
			return ret;
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
				prPrompt("�����������ɹ�ģ", "�����������");
				getch();
				scrollMenu(getPCtypeList(), d_pcType, 0);
				if (isEditPCType())
				{
					clossPC();
					list = getPCs();
					setEdit(0);
				}
				break;
			case d_card:		//�½�
			{
				if (isPower(getUser()->power, 0))
				{
					while (NULL==getCardTypeList()->next)
					{
						prPrompt("û�л�Ա������", "�������ת����Ա�������б�\n��esc��ȡ���½�");
						key key = isKey(getch());
						if (esc == key)
						{
							return paginationMenu(list, type, index, option);							
						}
						scrollMenu(getCardTypeList(), d_cardType, 0);
					}
					char *pass1 = (char *)malloc(sizeof(char) * 16);
					char *pass2 = (char *)malloc(sizeof(char) * 16);
					pass1[0] = '\0';
					pass2[0] = '\0';
					pCard p = (pCard)malloc(sizeof(card));
					p->balance = 0.0;
					p->id = -1;
					p->idcardNum[0] = '\0';
					p->masterName[0] = '\0';
					p->password[0] = '\0';
					strcpy(p->type, getCardTypeList()->date.cardType->name);
					pList pl = list;
					while (NULL!=pl->next)
					{
						pl = pl->next;
					}
					pList ql = (pList)malloc(sizeof(List));
					ql->date.card = p;
					ql->next = NULL;
					ql->last = pl;
					ql->type = d_card;
					pl->next = ql;
					showCard(0, p, "", pass1, pass2);
					strcpy(pass1, "***************");
					strcpy(pass2, "***************");
					free(pass1);
					free(pass2);
					addHistory(C_CARD_TYPE_T, pl->date, 0);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			}
			case d_history:		//��ϸ
				showHistory(op->date.history);
				break;
			case d_statistics:	//��ϸ
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				thisPage = 0;
				finalPage = -1;
				pList p = getMoreStat(op);
				paginationMenu(p, d_statistics, 0, 0);
				thisPage = ttp;
				finalPage = tfp;
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			}
			case d_statistics_more:	//�˳�
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
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
				thisPage = 0;
				finalPage = -1;
				logPC(op->date.pc);
				thisPage = ttp;
				finalPage = tfp;
				break;
			}
			case d_card:		//ɾ��
				if (isPower(getUser()->power, 1))
				{
					if (NULL != op->last)
					{
						pList temp = NULL != op->next ? op->next : op->last;
						op->last->next = op->next;
						if (NULL != op->next)
						{
							op->next->last = op->last;
						}
						addHistory(D_CARD_TYPE_T, op->date, 0);
						free(op);
						op = temp;
					}
					else
					{
						pCard temp = op->date.card;
						op->date.card = NULL;
						addHistory(D_CARD_TYPE_T, op->date, 0);
						free(temp);
					}
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			case d_history:		//ɸѡ
				finalPage = -1;
				p = selectToHistory();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			default:
				break;
			}
			break;
		case 6:
			//������������
			switch (type)		
			{
			case d_pc:			//��ϸ
				showPC(op->date.pc);
				break;
			case d_card:		//��ֵ
				recharge(op->date.card);
				break;
			case d_history:		//�˳�
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
			pList p;
			//������������
			switch (type)		
			{
			case d_pc:			//ɸѡ
				finalPage = -1;
				p = selectToPC();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			case d_card:		//��ϸ
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, op->date.card->password);
				strcpy(pass2, op->date.card->password);
				showCard(0, op->date.card, "", pass1, pass2);
				strcpy(pass1, "***************");
				strcpy(pass2, "***************");
				free(pass1);
				free(pass2);
				break;
			}
			default:
				break;
			}
			return ret;
		}
		case 8:	
		{
			switch (type)
			{
			case d_pc:			//�˳�
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			case d_card:		//ɸѡ
				finalPage = -1;
				p = selectToCard();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			default:
				break;
			}
		}
		case 9:
		{
			switch (type)
			{
			case d_card:		//�˳�
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
		ret = paginationMenu(list, type, index, option);
		return ret;
		}
		default:
			break;
		}
		return paginationMenu(list, type, index, option);
	case esc:
	{
		finalPage = -1;
		thisPage = 0;
		isFirst = 1;
		return NULL;
	}
	default:
		break;
	}
	ret = paginationMenu(list, type, index, option);
	return ret;
}

//�����˵�
pList scrollMenu(pList list, dateType type, int option) {
	pList ret = NULL;
	char *nMore = (char*)malloc(160 * sizeof(char));
	int isTop = 0;
	myCls();
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pcType:
		printf("\n\n                                 �������������ɹ�ģ\n\n");
		printf("                  ================================================            \n");
		printf("                    ����         |      ����      |    ��ʼ���               \n");
		printf("                  ---------------+----------------+---------------         \n");
		strcpy(nMore, "                                 |                |                          \n");
		break;
	case d_cardType:
		printf("\n\n                             �������������ɻ�Ա������\n\n");
		printf("                  ================================================            \n");
		printf("                        ��Ա������       |     �۸�           \n");
		printf("                  -----------------------+------------------------            \n");
		strcpy(nMore, "                                         |                                 \n");
		break;
	case d_admin:
		printf("\n\n                                   �����ù���Ա\n\n");
		printf("                  ================================================            \n");
		printf("             �û���    |                        Ȩ��                          \n");
		printf("                  -----+------------------------------------------         \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                             ���������������շѱ�׼\n\n");
		printf("                  ================================================            \n");
		printf("             ��������          |     ��Ա������     |     �շѱ�׼            \n");
		printf("                  -------------+--------------------+-------------            \n");
		strcpy(nMore, "                               |                    |                         \n");
		break;
	default:
		return NULL;
	}
	int length = (d_rate == type) ? 3 : 7;
	pList p = list;
	for (int i = 0; i < length/2; i++)
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
	for (int i = isTop; i < length; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->date.admin)
			{
				if (length / 2 == i)
				{
					ret = p;
				}
				switch (type)
				{
				case d_pcType:
					if (length / 2 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					prPCtype(p->date.pcType);
					if (length / 2 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					break;
				case d_cardType:
					if (length / 2 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					prCardType(p->date.cardType);
					if (length / 2 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					break;
				case d_admin:
					if (length / 2 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					prUser(p->date.admin);
					if (length / 2 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					break;
				case d_rate:
					if (length / 2 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					prRate(p->date.rate);
					if (length / 2 == i)
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
	prOption("  ����  ", 4 == option, 13);
	free(nMore);
	if (isFirst)
	{
		MenuHelp(1);
		return scrollMenu(list, type, option);
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
		ret = scrollMenu(list, type, option);
		break;
	case down:
		if (NULL != list->next)
		{
			list = list->next;
		}
		ret= scrollMenu(list, type, option);
		break;
	case left:
		if (0==option)
		{
			option = 5;
		}
		option--;
		ret = scrollMenu(list, type, option);
		break;
	case tab:
	case right:
		if (4 == option)
		{
			option = -1;
		}
		option++;
		ret = scrollMenu(list, type, option);
		break;
	case enter:
	{
		int a[] = { 0,0 };
		switch (option)		//����ѡ����
		{
		case 0:
		{
			int isNULL = 0;
			pList q = list;
			if (NULL == q)
			{
				q = (pList)malloc(sizeof(List));
				q->date.admin = NULL;
				q->last = NULL;
				q->next = NULL;
				q->type = type;
				list = q;
				isNULL = 1;
			}
			while (NULL != q->next)
			{
				q = q->next;
			}
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
					pPCtype p = (pPCtype)malloc(sizeof(PCtype));
					p->startId = getPCtypeList()->date.pcType->num;
					p->num = 0;
					p->type[0] = '\0';
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.pcType = p;
					pl->type = d_pcType;
					q->next = pl;
					editPCtype(0, p);
					setEdit(1);
					addHistory(C_PC_TYPE_T, pl->date, 0);
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
					pCardType p = (pCardType)malloc(sizeof(cardType));
					p->name[0] = '\0';
					p->price = 0;
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.cardType = p;
					pl->type = d_cardType;
					q->next = pl;
					editCardType(0, p);
					addHistory(C_CARD_TYPE_T, pl->date, 0);
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
					char *pass1 = (char *)malloc(sizeof(char) * 16);
					char *pass2 = (char *)malloc(sizeof(char) * 16);
					pass1[0] = '\0';
					pass2[0] = '\0';
					pAdmin p = (pAdmin)malloc(sizeof(admin));
					p->name[0] = '\0';
					p->password[0] = '\0';
					p->power = 0;
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.admin = p;
					pl->type = d_admin;
					q->next = pl;
					editUser(0, p, pass1, pass2);
					free(pass1);
					free(pass2);
					addHistory(C_ADMIN_T, pl->date, 0);
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
					pRate p = (pRate)malloc(sizeof(rate));
					p->card[0] = '\0';
					p->pc[0] = '\0';
					p->rule[0] = '\0';
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.rate = p;
					pl->type = d_rate;
					q->next = pl;
					editRate(0, a, p);
					if (isNULL)
					{
						list = list->next;
						pl->last = NULL;
						setRateList(pl);
					}
					addHistory(C_RATE_T, pl->date, 0);
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
						else
						{
							setEdit(1);
						}
					}
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
						addHistory(D_PC_TYPE_T, list->date, 0);
						break;
					case d_cardType:
						addHistory(D_CARD_T, list->date, 0);
						break;
					case d_admin:
						addHistory(D_ADMIN_T, list->date, 0);
						break;
					case d_rate:
						addHistory(D_RATE_T, list->date, 0);
						break;
					default:
						break;
					}
					free(list);
					list = temp;
				}
				else if (NULL!=list->next)
				{
					if (d_pcType == type || d_cardType == type)
					{
						prPrompt("ɾ��ʧ��", "�޷�ɾ������\n�����������");
						getch();
					}
					else
					{
						pList temp = list->next;
						list->next->last = NULL;
						switch (type)
						{
						case d_pcType:
							addHistory(D_PC_TYPE_T, list->date, 0);
							break;
						case d_cardType:
							addHistory(D_CARD_T, list->date, 0);
							break;
						case d_admin:
							addHistory(D_ADMIN_T, list->date, 0);
							break;
						case d_rate:
							addHistory(D_RATE_T, list->date, 0);
							break;
						default:
							break;
						}
						free(list);
						list = temp;
					}

				}
				else
				{
					list = NULL;
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
			switch (type)		//������������
			{
			case d_pcType:
				if (!editPCTypePS(0))
				{
					break;
				}
				setEdit(1);
				editPCtype(0, list->date.pcType);
				addHistory(U_PC_TYPE_T, list->date, 0);
				break;
			case  d_cardType:
				editCardType(0, list->date.cardType);
				addHistory(U_CARD_TYPE_T, list->date, 0);
				break;
			case d_admin:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, list->date.admin->password);
				strcpy(pass2, list->date.admin->password);
				editUser(0, list->date.admin,pass1,pass2);
				free(pass1);
				free(pass2);
				addHistory(U_ADMIN_T, list->date, 0);
				break;
			}
			case d_rate:
				editRate(0, a, list->date.rate);
				addHistory(U_RATE_T, list->date, 0);
				break;
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
			break;
		case 4:
			isFirst = 1;
			return ret;;
		default:
			break;
		}
		ret = scrollMenu(list, type, option);
		return ret;
	}
	case esc:
		isFirst = 1;
		return ret;
	default:
		break;
	}
	return ret;
}
