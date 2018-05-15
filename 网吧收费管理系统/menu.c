#include"config.h"

//初始化
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

//验证登录用户合法性
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

//输出菜单选项
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

//菜单
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
	int optionLength = 0;
	optionLength += prMenuOption("   上/下机  ", menuOption, indexLength++, type);
	optionLength += prMenuOption(" 会员卡管理 ", menuOption, indexLength++, type);
	optionLength += prMenuOption("  网吧规模  ", menuOption, indexLength++, type);
	optionLength += prMenuOption(" 会员卡类型 ", menuOption, indexLength++, type);
	optionLength += prMenuOption("收费标准管理", menuOption, indexLength++, type);
	optionLength += prMenuOption(" 管理员管理 ", menuOption, indexLength++, type);
	optionLength += prMenuOption("查询历史记录", menuOption, indexLength++, type);
	optionLength += prMenuOption("    统计    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    设置    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    保存    ", menuOption, indexLength++, type);
	optionLength += prMenuOption("    注销    ", menuOption, indexLength++, type);
	if (0==optionLength%2)
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
			prPrompt("保存成功", "按任意键继续");
			getch();
			break;
		case 10:
		{
			system("title 登陆");
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

//登录
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
	printf("             用户名：%s\n", 1 == type ? "" : user->name);
	printf("                                                         \n");
	printf("             密  码：%s\n", 2 == type ? "" : pass);
	printf("\n                  %s\n", text);
	printf("                                                         \n");
	printf("              ESC:退出   上/下方向键、TAB：切换选项   ENTER：确认");
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
