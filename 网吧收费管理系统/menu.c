#include"config.h"

//��ʼ��
void init() {
	getAdminHead();
	getAttriList();
	getRateList();

	getCardTypeList();
	getCards();

	getHistorys();
	getStat();

	getPCtypeList();
	getPCs();
}

//��֤��¼�û��Ϸ���
pAdmin isCanLogin(pAdmin user) {
	pList p = getAdminHead();
	while (NULL != p)
	{
		if (0 == strcmp(p->date.admin->name, user->name) && 0 == strcmp(p->date.admin->password, user->password))
		{
			return p->date.admin;
		}
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
	if ((isPower(power, 8) || isPower(power, 9) || isPower(power, 10)))
	{
		menu |= SHL(5);
	}
	if ((isPower(power, 7)))
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
int prMenuOption(char* option, int menuOption, int menuID, int type) {
	static char sp[] = "           ";
	int ret = 0;
	if (isPower(menuOption, menuID))
	{
		printf(sp);
		prOption(option, type == menuID, 18);
		menuLength++;
		printf(sp);
		ret = 1;
	}
	if (0 == menuLength % 2 && 0!=menuLength)
	{
		printf("\n\n");
	}
	return ret;
}

//�˵�
void mainMenu(int type) {
	static int menuOption = 0;
	if (0== menuOption)
	{
		menuOption = toMenu(getUser()->power);
	}
	menuLength = 0;
	while (!isPower(menuOption, type)){
		type++;
	}
	char *title = NULL;
	title = (char *)malloc(64 * sizeof(char));
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
	int optionLength = 0;
	optionLength += prMenuOption("   ��/�»�  ", menuOption, indexLength++, type);
	optionLength += prMenuOption(" ��Ա������ ", menuOption, indexLength++, type);
	optionLength += prMenuOption("  ���ɹ�ģ  ", menuOption, indexLength++, type);
	optionLength += prMenuOption(" ��Ա������ ", menuOption, indexLength++, type);
	optionLength += prMenuOption("�շѱ�׼����", menuOption, indexLength++, type);
	optionLength += prMenuOption(" ����Ա���� ", menuOption, indexLength++, type);
	optionLength += prMenuOption("��ѯ��ʷ��¼", menuOption, indexLength++, type);
	optionLength += prMenuOption("    ͳ��    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    ����    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    ����    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    ע��    ", menuOption, indexLength++, type);
	if (0==optionLength%2)
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
		if (index >= 0 && index <= 9)
		{
			index--;
			if (0>index)
			{
				index = 9;
			}
			if (isPower(menuOption, index))
			{
				mainMenu(index);
				return;
			}
		}
		mainMenu(type);
		return;
	}
	case up:
		if (0==type)
		{
			length = optionLength % 2;
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
		mainMenu(type);
		break;
	case down:
		if (indexLength-1==type)
		{
			length = optionLength % 2;
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
		mainMenu(type);
		break;
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
		mainMenu(type);
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
		mainMenu(type);
		break;
	case esc:
		if (!saveExit(0))
		{
			mainMenu(type);
			return;
		}
		break;
	case backspace:
	{
		pAdmin user = (pAdmin)malloc(sizeof(admin));
		user->name[0] = '\0';
		user->password[0] = '\0';
		setUser(NULL);
		menuOption = 0;
		login(user, 1, "");
		free(user);
		return;
	}
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
			prPrompt("����ɹ�", "�����������");
			getch();
			break;
		case 10:
		{
			system("title ��½");
			pAdmin user = (pAdmin)malloc(sizeof(admin));
			user->name[0] = '\0';
			user->password[0] = '\0';
			setUser(NULL);
			menuOption = 0;
			login(user, 1, "");
			free(user);
			return;
		}
		case 11:
			if (!saveExit(0))
			{
				mainMenu(type);
				return;
			}
			return;
		default:
			break;
		}
		mainMenu(type);
		break;
	default:
		mainMenu(type);
		break;
	}
}

//��¼
void login(pAdmin user, int type, char* text) {
	char *pass = (char *)malloc(sizeof(char) * 16);
	printfPassword(user->password, pass);
	myCls();
	printf("                                                             \n");
	printf("                                                             \n");
	printf("                  //                                         \n");
	printf("                 //                             --           \n");
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
	printf("             ��  �룺%s\n", 2 == type ? "" : pass);
	printf("\n                  %s\n", text);
	printf("                                                         \n");
	printf("              ESC:�˳�   ��/�·������TAB���л�ѡ��   ENTER��ȷ��");
	free(pass);
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
				setUser(p);
				init();
				mainMenu(0);
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
