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
	default:
		break;
	}
	if (NULL == (fp = fopen(fileName, "wb")))
	{
		return;
	}
	while (NULL != p)
	{
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
			break;
		default:
			break;
		}
	}
}

//ȫ������
void saveAll() {
	save(d_admin);
	save(d_card);
	save(d_cardType);
	save(d_pcType);
	save(d_rate);
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

void paginationMenu(pList list, dateType type, int index, int option) {
	pList p = list;
	if (-1==finalPage)
	{
		initFinalPage(list);
	}
	pList op = list;
	int length = 0;
	system("cls");
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pc:
		system("title ��/�»�");
		printf("\n                             ---===��/�»�===---\n");
		printf("\n-------------+--------------------+--------------------+------------------------");
		printf("\n      id     |        ����        |      ��ǰ�û�      |      �ϻ�ʱ��      ");
		printf("\n-------------+--------------------+--------------------+------------------------");
		break;
	case d_card:
		system("title ��Ա������");
		printf("\n                          ---===��Ա������===---\n");
		printf("\n-------------------+--------------------+--------------------+------------------");
		printf("\n        id         |        ����        |       �û���       |      ���    ");
		printf("\n-------------------+--------------------+--------------------+------------------");
		break;
	case d_history:
		system("title ��ʷ��¼");
		printf("\n                           ---===��ʷ��¼===---\n");
		printf("\n----------------------+-----------------+---------------------------------------");
		printf("\n         ��������     |      ������     |                ʱ��               ");
		printf("\n----------------------+-----------------+---------------------------------------");
		break;
	default:
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p && NULL != p->date.admin)
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
			default:
				break;
			}
			if (i == index)
			{
				op = p;
			}
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
	default:
		break;
	}
	printf("                              %5d / %-5d\n", thisPage+1, finalPage+1);
	printf("\n                     ");
	prOption("��  ҳ", 0 == option, 9);
	printf("   ");
	prOption("��һҳ", 1 == option, 9);
	printf("   ");
	prOption("��һҳ", 2 == option, 9);
	printf("   ");
	prOption("β  ҳ", 3 == option, 9);
	printf("\n\n      ");
	prOption("  �½�  ", 4 == option, 13);
	printf(" ");
	prOption("  ɾ��  ", 5 == option, 13);
	printf(" ");
	prOption("  ��ϸ  ", 6 == option, 13);
	printf(" ");
	prOption("  ɸѡ  ", 7 == option, 13);
	printf(" ");
	prOption("  ����  ", 8 == option, 13);
	int in = getch();
	key k = isKey(in);
	switch (k)		//����������
	{
	case number:
		paginationMenu(list, type, in - '0', option);
		return;
	case up:
		index--;
		if (0 > index)
		{
			index = length;
		}
		paginationMenu(list, type, index, option);
		return;
	case down:
		index++;
		if (length <= index)
		{
			index = 0;
		}
		paginationMenu(list, type, index, option);
		return;
	case tab:
		if (4 > option)
		{
			option += 4;
		}
		else
		{
			option -= 4;
		}
		paginationMenu(list, type, index, option);
		return;
	case left:
		option--;
		if (0 > option)
		{
			option = 8;
		}
		paginationMenu(list, type, index, option);
		return;
	case right:
		option++;
		if (8 < option)
		{
			option = 0;
		}
		paginationMenu(list, type, index, option);
		return;
	case pgup:
		if (0>=thisPage)
		{
			paginationMenu(list, type, index, option);
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->last;
		}
		thisPage--;
		paginationMenu(list, type, index, option);
		return;
	case pgdn:
		if (finalPage<=thisPage)
		{
			paginationMenu(list, type, index, option);
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->next;
		}
		thisPage++;
		paginationMenu(list, type, index, option);
		return;
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
		case 4:	//�½�
			//������������
			switch (type)		
			{
			case d_pc:
				prPrompt("�����������ɹ�ģ", "�����������");
				getch();
				scrollMenu(getPCtypeList(), d_pcType, 0);
				break;
			case d_card:
			{
				if (isPower(getUser()->power, 0))
				{
					char *pass1 = (char *)malloc(sizeof(char) * 16);
					char *pass2 = (char *)malloc(sizeof(char) * 16);
					pass1[0] = '\0';
					pass2[0] = '\0';
					pCard p = (pCard)malloc(sizeof(card));
					p->balance = 0;
					p->id = -1;
					p->idcardNum[0] = '\0';
					p->masterName[0] = '\0';
					p->password[0] = '\0';
					strcpy(p->type, getCardTypeList()->date.cardType->name);
					op->date.card = p;
					showCard(0, op->date.card, "", pass1, pass2);
					strcpy(pass1, "***************");
					strcpy(pass2, "***************");
					free(pass1);
					free(pass2);
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
				break;
			case d_history:
				prPrompt("��ֹ������", "ֻ��ͨ�������Զ�����\n�޷��ֶ�����\n�����������");
				getch();
				break;
			}
			default:
				break;
			}
			break;
		case 5:	//ɾ��
			//������������
			switch (type)		
			{
			case d_pc:
				prPrompt("�����������ɹ�ģ", "�����������");
				getch();
				scrollMenu(getPCtypeList(), d_pcType, 0);
				break;
			case d_card:
				if (isPower(getUser()->power, 1))
				{
					if (NULL != list->last)
					{
						pList temp = NULL != list->next ? list->next : list->last;
						list->last->next = list->next;
						if (NULL != list->next)
						{
							list->next->last = list->last;
						}
						free(list);
						list = temp;
					}
				}
				else
				{
					prPrompt("Ȩ�޲���", "�볢����ϵ��������Ա\n�����������");
					getch();
				}
			case d_history:
				prPrompt("��ֹ������", "ɾ����ʷ��¼�ᵼ�²���Ԥ�������鷢��\n��ֹ����ɾ��\n�����������");
				getch();
				break;
			default:
				break;
			}
			break;
		case 6:	//��ϸ
			//������������
			switch (type)		
			{
			case d_pc:
				showPC(op->date.pc, 0);
				break;
			case d_card:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, op->date.card->password);
				strcpy(pass2, op->date.card->password);
				showCard(0, op, "", pass1, pass2);
				strcpy(pass1, "***************");
				strcpy(pass2, "***************");
				free(pass1);
				free(pass2);
				break;
			}
			case d_history:
				showHistory(op->date.history);
				break;
			default:
				break;
			}
			break;
			break;
		case 7:	//ɸѡ
		{
			pList p;
			//������������
			switch (type)		
			{
			case d_pc:
				finalPage = -1;
				p = selectToPC();
				break;
			case d_card:
				/////////////////////////////////////////////////
				break;
			case d_history:
				/////////////////////////////////////////////////
				break;
			default:
				break;
			}
			paginationMenu(p, type, index, option);
			pList q = p->next;
			while (NULL!=q)
			{
				free(p);
				p = q;
				q = q->next;
			}
			return;
		}
		case 8:	//����
			finalPage = -1;
			thisPage = 0;
			return;
		default:
			break;
		}
		paginationMenu(list, type, index, option);
		return;
	case esc:
		paginationMenu(list, type, index, 8);
		return;
	default:
		break;
	}
}

//�����˵�
void scrollMenu(pList list, dateType type, int option) {
	pList p = list;
	char nMore[79];
	int isTop = 0;
	system("cls");
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
		printf("          �û���        |                        Ȩ��                          \n");
		printf("                  -----+------------------------------------------         \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                             ���������������շѱ�׼\n\n");
		printf("                  ================================================            \n");
		printf("             ��ʼʱ��          |     ��Ա������     |     �շѱ�׼            \n");
		printf("             ����ʱ��          |      ��������      |                         \n");
		printf("                  -------------+--------------------+-------------            \n");
		strcpy(nMore, "                               |                    |                         \n                               |                    |                         \n");
		break;
	default:
		return;
	}
	int length = d_rate == type ? 3 : 7;
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
			switch (type)
			{
			case d_pcType:
				if (length / 2 == i)
				{
					printf("               ------------------+----------------+------------------         \n");
				}
				prPCtype(p->date.pcType, 3 == 0);
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
				prCardType(p->date.cardType, 3 == 0);
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
				prUser(p->date.admin, 3 == 0);
				if (length / 2 == i)
				{
					printf("               ----------------+--------------------+----------------         \n");
				}
				break;
			case d_rate:
				if (length / 2 == i)
				{
					printf("               ----------------+--------------------+----------------         \n");
				}
				prRate(p->date.rate, 3 == 0);
				break;
			default:
				return;
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

	int in = getch();
	key k = isKey(in);
	switch (k)	//����������
	{
	case up:
		if (NULL!=list->last)
		{
			list = list->last;
		}
		scrollMenu(list, type, option);
		break;
	case down:
		if (NULL != list->next)
		{
			list = list->next;
		}
		scrollMenu(list, type, option);
		break;
	case left:
		if (0==option)
		{
			option = 5;
		}
		option--;
		scrollMenu(list, type, option);
		break;
	case tab:
	case right:
		if (4 == option)
		{
			option = -1;
		}
		option++;
		scrollMenu(list, type, option);
		break;
	case enter:
	{
		int a[] = { 0,0 };
		switch (option)		//����ѡ����
		{
		case 0:
		{
			pList q = list;
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
					pPCtype p = (pPCtype)malloc(sizeof(PCtype));
					p->startId = getPCtypeList()->date.pcType->num;
					p->num = 0;
					p->type[0] = '\0';
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.pc = p;
					pl->type = d_pcType;
					q->next = pl;
					editPCtype(0, p);
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
					pl->date.card = p;
					pl->type = d_cardType;
					q->next = pl;
					editCardType(0, p);
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
					strcpy(pass1, p->date.admin->password);
					strcpy(pass2, p->date.admin->password);
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
					p->startTime = NULL;
					p->endTime = NULL;
					p->rule[0] = '\0';
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.rate = p;
					pl->type = d_rate;
					q->next = pl;
					editRate(0, a, p);
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
				if (NULL!=list->last)
				{
					pList temp = NULL!=list->next? list->next : list->last;
					list->last->next = list->next;
					if (NULL != list->next)
					{
						list->next->last = list->last;
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
				editPCtype(0, list->date.pcType);
				break;
			case  d_cardType:
				editCardType(0, list->date.cardType);
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
				break;
			}
			case d_rate:
				editRate(0, a, list->date.rate);
				break;
			default:
				break;
			}
		}
		case 3:
			if (d_admin==type)
			{
				helpFromUser();
			}
			break;
		case 4:
			return;
		default:
			break;
		}
		scrollMenu(list, type, option);
		return;
	}
	case esc:
		return;
	default:
		break;
	}
}
