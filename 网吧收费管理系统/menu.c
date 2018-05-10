#include"config.h"

//��ʼ��
void init() {
	getAdminHead();
	getAttriList();
	getPCtypeList();
	getCardTypeList();
	getRateList();
	getCards();
	getHistorys();
	getPCs();
}

//��֤��¼�û��Ϸ���
pAdmin isCanLogin(pAdmin user) {
	if (NULL == getAdminHead())
	{
		initAdminList();
	}
	pList p = getAdminHead();
	while (NULL != p)
	{
		if (0 == strcmp(p->date.admin->name, user->name) && 0 == strcmp(p->date.admin->password, user->password))
		{
			return p->date.admin;
		}
		getch();
		p = p->next;
	}
	return NULL;
}

//ת���˵�
int toMenu(int power) {
	int menu = 0;
	//�жϲ��û������޸Ķ�Ӧλ�õ�ֵ
	if ((isPower(power, 0) || isPower(power, 1) || isPower(power, 2)))
	{
		menu |= SHL(0);
	}
	if ((isPower(power, 11) || isPower(power, 12) || isPower(power, 13)))
	{
		menu |= SHL(1);
	}
	if ((isPower(power, 14) || isPower(power, 15) || isPower(power, 16)))
	{
		menu |= SHL(2);
	}
	if ((isPower(power, 3) || isPower(power, 4) || isPower(power, 5)))
	{
		menu |= SHL(3);
	}
	if ((isPower(power, 6)))
	{
		menu |= SHL(4);
	}
	if ((isPower(power, 7)))
	{
		menu |= SHL(5);
	}
	if ((isPower(power, 8) || isPower(power, 9) || isPower(power, 10)))
	{
		menu |= SHL(6);
	}
	if (isPower(power,17))
	{
		menu |= SHL(7);
	}
	menu |= SHL(8);
	menu |= SHL(9);
	menu |= SHL(10);
	menu |= SHL(11);
	return menu;
}

//����˵�ѡ��
int menuLength = 0;
void prMenuOption(char* option, int menuOption, int menuID, int type) {
	static char sp[] = "           ";
	if (isPower(menuOption, menuID))
	{
		printf(sp);
		prOption(option, type == menuID, 18);
		menuLength++;
		printf(sp);
	}
	if (0 == menuLength % 2 && 0!=menuLength)
	{
		printf("\n\n");
	}
}

//�˵�
void mainMenu(pAdmin user, int type) {
	int menuOption = toMenu(user->power);
	menuLength = 0;
	while (!isPower(menuOption, type)){
		type++;
	}
	char *title = (char *)malloc(32 * sizeof(char));
	sprintf(title, "title %s : ���˵�", getUser()->name);
	system(title);
	free(title);
	myCls();
	printf("\n");
	printf("                     //||   //||                                     \n");
	printf("                    // ||  // ||    //===  //||  //  //  //          \n");
	printf("                   //  || //  ||   //===  // || //  //  //           \n");
	printf("                  //   ||//   ||  //===  //  ||//  //==//                \n");
	printf("         ===========================================================         \n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	gotoxy(0, 24);
	printf("                       �����/tab���л�ѡ��   enter��ȷ��");
	gotoxy(0, 9);
	
	int indexLength = 0;
	prMenuOption("   ��/�»�  ", menuOption, indexLength++, type);
	prMenuOption(" ��Ա������ ", menuOption, indexLength++, type);
	prMenuOption("  ���ɹ�ģ  ", menuOption, indexLength++, type);
	prMenuOption(" ��Ա������ ", menuOption, indexLength++, type);
	prMenuOption("�շѱ�׼����", menuOption, indexLength++, type);
	prMenuOption(" ����Ա���� ", menuOption, indexLength++, type);
	prMenuOption("��ѯ��ʷ��¼", menuOption, indexLength++, type);
	prMenuOption("    ͳ��    ", menuOption, indexLength++, type);
	prMenuOption("    ����    ", menuOption, indexLength++, type);
	prMenuOption("    ����    ", menuOption, indexLength++, type);
	prMenuOption("    ע��    ", menuOption, indexLength++, type);
	if (0==indexLength%2)
	{
		printf("                     ");
	}
	prMenuOption("    �˳�    ", menuOption, indexLength++, type);

	int length = 0;
 	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case number:
	{
		int index = in - '0';
		if (index >=0&& index <=9)
		{
			index--;
			if (0>index)
			{
				index = 9;
			}
			if (isPower(menuOption, index))
			{
				mainMenu(user, index);
				return;
			}
		}
		mainMenu(user, type);
		return;
	}
	case up:
		if (0==type)
		{
			length = 1;
		}
		do{
			type--;
		} while (!isPower(menuOption, type));
		do {
			type--;
		} while (!isPower(menuOption, type));
		if (type<0)
		{
			type = indexLength;
			do {
				type--;
			} while (!isPower(menuOption, type));
			type -= length;
		}
		mainMenu(user, type);
		break;
	case down:
		if (indexLength-1==type)
		{
			length = 1;
		}
		do {
			type++;
		} while (!isPower(menuOption, type));
		do {
			type++;
		} while (!isPower(menuOption, type));
		if (type>indexLength)
		{
			type = -1;
			do {
				type++;
			} while (!isPower(menuOption, type));
			type += length;
		}
		mainMenu(user, type);
	case left:
		do {
			type--;
		} while (!isPower(menuOption, type));
		if (type<0)
		{
			type = indexLength;
			do {
				type--;
			} while (!isPower(menuOption, type));
		}
		mainMenu(user, type);
		break;
	case right:
	case tab:
		do {
			type++;
		} while (!isPower(menuOption, type));
		if (type>indexLength-1)
		{
			type = -1;
			do {
				type++;
			} while (!isPower(menuOption, type));
		}
		mainMenu(user, type);
	case enter:
		switch (type)
		{
		case 0:
			system("title ��/�»�");
			paginationMenu(getPCs(), d_pc, 0, 0);
			break;
		case 1:
			system("title ��Ա������");
			paginationMenu(getCards(), d_card, 0, 0);
			break;
		case 2:
			system("title ���ɹ�ģ����");
			scrollMenu(getPCtypeList(), d_pcType, 0);
			break;
		case 3:
			system("title ��Ա�����͹���");
			scrollMenu(getCardTypeList(), d_cardType, 0);
			break;
		case 4:
			system("title �շѱ�׼����");
			scrollMenu(getRateList(), d_rate, 0);
			break;
		case 5:
			system("title ����Ա����");
			scrollMenu(getAdminHead(),d_admin,0);
			break;
		case 6:
			system("title ��ʷ��¼");
			paginationMenu(getHistorys(), d_history, 0, 0);
			break;
		case 7:
			system("title ͳ��");
			paginationMenu(getStat(), d_statistics, 0, 0);
			break;
		case 8:
			system("title ����");
			paginationMenu(getAttriList(), d_attri, 0, 0);
			break;
		case 9:
			saveAll();
			break;
		case 10:
			setUser(NULL);
			login(user, 0, "");
			return;
		case 11:
			if (!saveExit(0))
			{
				mainMenu(user, type);
				return;
			}
			return;
		default:
			break;
		}
		mainMenu(user, type);
		break;
	default:
		mainMenu(user, type);
		break;
	}
}

//��¼
void login(pAdmin user, int type, char* text) {
	system("title ��½");
	myCls();
	printf("                                                       \n");
	printf("                                                       \n");
	printf("                  //                                        \n");
	printf("                 //                             --            \n");
	printf("                //         //^^//    //^^//    //    //^^//  \n");
	printf("               //         //  //    //  //    //    //  //   \n");
	printf("              ^^^^^^^     ^^^^^     ^^^//                    \n");
	printf("                                  ||  //                     \n");
	printf("                                   ||//                      \n");
	printf("                                    ^^                       \n");
	printf("                                                             \n");
	printf("                                                             \n");
	printf("                                                             \n");
	printf("             �û�����%s\n", 1 == type ? "" : user->name);
	printf("                                                         \n");
	printf("             ��  �룺%s\n", 2 == type ? "" : printfPassword(user->password));
	printf("\n                  %s\n", text);
	printf("                                                         \n");
	printf("              ESC:�˳�   ��/�·������TAB���л�ѡ��   ENTER��ȷ��");
	key in = 1 == type ? input(21, 13, user->name, 0, NUM | LETTER, NULL) : input(21, 15, user->password, 1, NUM | LETTER, NULL);
	switch (in)
	{
	case tab:
	case up:
	case down:
		if (1 == type)
		{
			login(user, 2, "");
			return;
		}
		else
		{
			login(user, 1, "");
			return;
		}
	case enter:
		{
			pAdmin p = isCanLogin(user);
			if (p!=NULL)
			{
				init();
				setUser(p);
				mainMenu(p, 0);
				return;
			}
		}
		login(user, 1, "[err:�û������������]");
		return;
		break;
	case esc:
		if (!saveExit(0))
		{
			 login(user, type, "");
			 return;
		}
		return;
	default:
		login(user, type, "");
		return;
	}
	return;
}
