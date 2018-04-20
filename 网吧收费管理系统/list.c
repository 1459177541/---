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
			if (fwrite(p->date.admin, sizeof(admin), 1, fp))
			{
				p = p->next;
			}
			break;
		case d_pcType:
			if (fwrite(p->date.pcType, sizeof(PCtype), 1, fp))
			{
				p = p->next;
			}
			break;
		case d_cardType:
			if (fwrite(p->date.cardType, sizeof(cardType), 1, fp))
			{
				p = p->next;
			}
			break;
		case d_rate:
			if (fwrite(p->date.rate, sizeof(rate), 1, fp))
			{
				p = p->next;
			}
			break;
		case d_history:
			if (fwrite(p->date.history, sizeof(history), 1, fp))
			{
				p = p->next;
			}
			break;
		case d_card:
			if (fwrite(p->date.card, sizeof(card), 1, fp))
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
	finalPage = length;
}

void paginationMenu(pList list, dateType type , int option) {
	pList p = list;
	if (-1==finalPage)
	{
		initFinalPage(list);
	}
	pList op = NULL;
	int length = 0;
	system("cls");
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pc:
		system("title ��/�»�");
		printf("\n\n                                                          ");
		prOption("�� ��", -5 == option, 9);
		printf("\n      id     |        ����        |      ��ǰ�û�      |      �ϻ�ʱ��      \n");
		break;
	case d_card:
		system("title ��Ա������");
		printf("\n                                                 ");
		prOption("�� ��", -6 == option, 9);
		prOption("�� ��", -5 == option, 9);
		printf("\n        id         |        ����        |       �û���       |      ���    \n");
		break;
	case d_history:
		system("title ��ʷ��¼");
		printf("\n                                                 ");
		prOption("�� ��", -5 == option, 9);
		printf("\n          ��������     |     ������     |                ʱ��               \n");
		break;
	default:
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			length++;
			switch (type)
			{
			case d_pc:
				prPC(p->date.pc, i == option);
				break;
			case d_card:
				prCard(p->date.card, i == option);
				break;
			case d_history:
				prHistory(p->date.history, i == option);
				break;
			default:
				break;
			}
			if (i == option)
			{
				op = p;
			}
			p = p->next;
		}
		else {
			printf("\n             |                    |                    |                       \n");
		}
	}

	printf("\n                     ");
	prOption("��  ҳ", option == -4, 9);
	printf("   ");
	prOption("��һҳ", option == -3, 9);
	printf("   ");
	prOption("��һҳ", option == -2, 9);
	printf("   ");
	prOption("β  ҳ", option == -1, 9);
	printf("   ");
	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case number:
		paginationMenu(list, type, in - '0');
		return;
	case up:
		option--;
		if (-7 >= option)
		{
			option = length - 1;
		}
		paginationMenu(list, type, option);
		return;
	case down:
		option++;
		if (length <= option)
		{
			option = -6;
		}
		paginationMenu(list, type, option);
		return;
	case tab:
		if (0 <= option)
		{
			paginationMenu(list, type, -6);
		}
		else
		{
			paginationMenu(list, type, 0);
		}
		return;
	case left:
		if (option<0)
		{
			if (-4 == option)
			{
				paginationMenu(list, type, 9);
			}
			else {
				paginationMenu(list, type, option - 5);
			}
		}
		else if (0 != thisPage)
		{
			for (int i = 0; i < 10; i++)
			{
				list = list->last;
			}
			thisPage--;
			paginationMenu(list, type, option);
		}
		else
		{
			paginationMenu(list, type, option);
		}
		return;
	case right:
		if (option<0)
		{
			paginationMenu(list, type, option + 1);
		}
		else if (thisPage > finalPage-1) {
			paginationMenu(list, type, option);
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				list = list->next;
			}
			thisPage++;
			paginationMenu(list, type, option);
		}
		return;
	case enter:
		switch (option)
		{
		case -1:
			for (int i = 0; i < 10*(finalPage-thisPage); i++)
			{
				list = list->next;
			}
			thisPage = finalPage;
			paginationMenu(list, type, option);
			break;
		case -2:
			for (int i = 0; i < 10; i++)
			{
				list = list->next;
			}
			thisPage++;
			paginationMenu(list, type, option);
			break;
		case -3:
			for (int i = 0; i < 10; i++)
			{
				list = list->last;
			}
			thisPage--;
			paginationMenu(list, type, option);
			break;
		case -4:
			for (int i = 0; i < 10*thisPage; i++)
			{
				list = list->next;
			}
			thisPage = 0;
			paginationMenu(list, type, option);
			break;
		case -5:
			switch (type)
			{
			case d_pc:
				list = selectToPC();
				break;

			default:
				break;
			}
			paginationMenu(list, type, option);
			break;
		case -6:
			switch (type)
			{
			case d_card:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				pass1[0] = '\0';
				pass2[0] = '\0';
				showCard(op, 1, "", pass1, pass2);
				break;
			}
			default:
				break;
			}
			paginationMenu(list, type, option);
			break;
		default:
			switch (type)
			{
			case d_pc:
				showPC(op, 0);
				break;
			case d_card:
			{
				char pass1[32];
				char pass2[32];
				strcpy(pass1, op->date.card->password);
				strcpy(pass2, op->date.card->password);
				showCard(op, 0, "", pass1, pass2);
				break;
			}
			case d_history:
				/////////////////////////////////////////////////
				break;
			default:
				break;
			}
			break;
		}
		return;
	case esc:
		return;
	default:
		break;
	}
	paginationMenu(list, type, option);
}

//�����˵�
void scrollMenu(pList list, dateType type, int option) {
	pList p = list;
	char more[79];
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
		strcpy(more, "                      ++++++     |     ++++++     |    ++++++                \n");
		strcpy(nMore, "                                 |                |                          \n");
		break;
	case d_cardType:
		printf("\n\n                             �������������ɻ�Ա������\n\n");
		printf("                  ================================================            \n");
		printf("                        ��Ա������       |     �۸�           \n");
		strcpy(more, "                              ++++++     |     ++++++               \n");
		strcpy(nMore, "                                         |                                 \n");
		break;
	case d_admin:
		printf("\n\n                                   �����ù���Ա\n\n");
		printf("                  ================================================            \n");
		printf("          �û���        |                        Ȩ��                          \n");
		strcpy(more, "            ++++++     |                       ++++++                    \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                             ���������������շѱ�׼\n\n");
		printf("                  ================================================            \n");
		printf("             ��ʼʱ��          |     ��Ա������     |     �շѱ�׼            \n");
		printf("             ����ʱ��          |      ��������      |                         \n");
		strcpy(more, "              ++++++           |       ++++++       |      ++++++            \n");
		strcpy(nMore, "                               |                    |                         \n");
		break;
	default:
		return;
	}
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
	if (0==isTop)
	{
		printf(more);
	}
	else
	{
		int top = isTop;
		while ((top--)>0)
		{
			printf(nMore);
		}
	}
	for (int i = isTop; i < 7; i++)
	{
		if (NULL!=p)
		{
			if (3==i)
			{
				printf("               ------------------+----------------+------------------         \n");
			}
			switch (type)
			{
			case d_pcType:
				prPCtype(p->date.pcType, 3 == 0);
				break;
			case d_cardType:
				prCardType(p->date.cardType, 3 == 0);
				break;
			case d_admin:
				prUser(p->date.admin, 3 == 0);
				break;
			case d_rate:
				prRate(p->date.rate, 3 == 0);
				break;
			default:
				return;
			}
			if (3 == i)
			{
				printf("               ------------------+----------------+------------------         \n");
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
	printf("\n         ");
	prOption("  �½�  ", 0 == option, 13);
	printf("         ");
	prOption("  ���  ", -1 == option, 13);
	printf("         ");
	if (d_admin==type)
	{
		prOption("  ����  ", -2 == option, 13);
	}
	while (1)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			if (0<=option)
			{
				if (NULL!=list->last)
				{
					list = list->last;
				}
				else
				{
					scrollMenu(list, type, -1);
				}
			}
			else
			{
				while (NULL!=list->next)
				{
					list = list->next;
				}
				scrollMenu(list, type, 0);
			}
			return;
		case down:
		case tab:
			if (0<=option)
			{
				if (NULL != list->next)
				{
					list = list->next;
				}
				else
				{
					scrollMenu(list, type, -1);
				}
			}
			else
			{
				while (NULL != list->last)
				{
					list = list->last;
				}
				scrollMenu(list, type, 0);
			}
			return;
		case enter:
		{
			int a[] = { 0,0 };
			if (0>=option)
			{
				switch (option)
				{
				case 0:
					///////////////////////////////////////////////////
					break;
				case -1:
					break;
				case -2:
					helpFromUser();
					scrollMenu(list, type, 0);
					break;
				default:
					break;
				}
				return;
			}
			else
			{
				switch (type)
				{
				case d_pcType:
					editPCtype(0, p->date.pcType);
					break;
				case  d_cardType:
					editCardType(0, p->date.cardType);
					break;
				case d_admin:
				{
					char pass1[32];
					char pass2[32];
					strcpy(pass1, p->date.admin->password);
					strcpy(pass2, p->date.admin->password);
					editUser(0, p->date.admin,pass1,pass2);
					break;
				}
				case d_rate:
					editRate(0, a, p->date.rate);
					break;
				default:
					break;
				}
				return;
			}
			break;
		}
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
