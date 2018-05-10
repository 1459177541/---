#include"config.h"

//初始化
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

//验证登录用户合法性
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

//转换菜单
int toMenu(int power) {
	int menu = 0;
	//判断并用或运算修改对应位置的值
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

//输出菜单选项
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

//菜单
void mainMenu(pAdmin user, int type) {
	int menuOption = toMenu(user->power);
	menuLength = 0;
	while (!isPower(menuOption, type)){
		type++;
	}
	char *title = (char *)malloc(32 * sizeof(char));
	sprintf(title, "title %s : 主菜单", getUser()->name);
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
	printf("                       方向键/tab：切换选项   enter：确认");
	gotoxy(0, 9);
	
	int indexLength = 0;
	prMenuOption("   上/下机  ", menuOption, indexLength++, type);
	prMenuOption(" 会员卡管理 ", menuOption, indexLength++, type);
	prMenuOption("  网吧规模  ", menuOption, indexLength++, type);
	prMenuOption(" 会员卡类型 ", menuOption, indexLength++, type);
	prMenuOption("收费标准管理", menuOption, indexLength++, type);
	prMenuOption(" 管理员管理 ", menuOption, indexLength++, type);
	prMenuOption("查询历史记录", menuOption, indexLength++, type);
	prMenuOption("    统计    ", menuOption, indexLength++, type);
	prMenuOption("    设置    ", menuOption, indexLength++, type);
	prMenuOption("    保存    ", menuOption, indexLength++, type);
	prMenuOption("    注销    ", menuOption, indexLength++, type);
	if (0==indexLength%2)
	{
		printf("                     ");
	}
	prMenuOption("    退出    ", menuOption, indexLength++, type);

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
			system("title 上/下机");
			paginationMenu(getPCs(), d_pc, 0, 0);
			break;
		case 1:
			system("title 会员卡管理");
			paginationMenu(getCards(), d_card, 0, 0);
			break;
		case 2:
			system("title 网吧规模管理");
			scrollMenu(getPCtypeList(), d_pcType, 0);
			break;
		case 3:
			system("title 会员卡类型管理");
			scrollMenu(getCardTypeList(), d_cardType, 0);
			break;
		case 4:
			system("title 收费标准管理");
			scrollMenu(getRateList(), d_rate, 0);
			break;
		case 5:
			system("title 管理员管理");
			scrollMenu(getAdminHead(),d_admin,0);
			break;
		case 6:
			system("title 历史记录");
			paginationMenu(getHistorys(), d_history, 0, 0);
			break;
		case 7:
			system("title 统计");
			paginationMenu(getStat(), d_statistics, 0, 0);
			break;
		case 8:
			system("title 设置");
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

//登录
void login(pAdmin user, int type, char* text) {
	system("title 登陆");
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
	printf("             用户名：%s\n", 1 == type ? "" : user->name);
	printf("                                                         \n");
	printf("             密  码：%s\n", 2 == type ? "" : printfPassword(user->password));
	printf("\n                  %s\n", text);
	printf("                                                         \n");
	printf("              ESC:退出   上/下方向键、TAB：切换选项   ENTER：确认");
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
		login(user, 1, "[err:用户名或密码错误]");
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
