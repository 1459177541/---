#include"config.h"

//输出头
void pr_weclome() {
	system("title welcome");
	myCls();
	gotoxy(0, 0);
	printf("                                                                             \n");
	printf("                                                                             \n");
	printf("        \\\\    //\\\\    //         //                                      \n");
	printf("         \\\\  //  \\\\  //  //~//  //     //~~  //~//  //\\\\  //\\\\    //~//  \n");
	printf("          \\\\//    \\\\//  //~~   //     //    // //  //  \\\\//  \\\\  //~~ \n");
	printf("           ~~      ~~   ~~~~   ~~~~~  ~~~~  ~~~~   ~    ~~    ~  ~~~~          \n");
	printf("       ===================================================================    \n");
	printf("                                                                             \n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	gotoxy(0, 24);
	printf("              ESC:上一步/退出   上/下方向键、TAB：切换选项   ENTER：确认");
	gotoxy(0, 9);
}

//设置管理员密码
void setRootPassword(int type,char * password1,char * password2,char *text) {
	char *pass1 = (char *)malloc(sizeof(char) * 16);
	char *pass2 = (char *)malloc(sizeof(char) * 16);
	printfPassword(password1, pass1);
	printfPassword(password2, pass2);
	pr_weclome();
	printf("              我们检测到您是第一次运行该程序，请设置超级管理员密码           \n");
	printf("                      请务必记住您的用户名及密码！！        \n");
	printf("                                                         \n");
	printf("                                                         \n");
	printf("                        用户名 ：root \n");
	printf("                                                         \n");
	printf("                      您的密码 ：%s\n", 1 == type ? "" : pass1);
	printf("                                                         \n");
	printf("                      再次输入 ：%s\n", 2 == type ? "" : pass2);
	printf("                                                         \n");
	printf("\n                                                        \n");
	printf("                       %s \n",text);
	key in = 1 == type ? input(33, 15, password1, 1, NUM | LETTER, NULL) : input(33, 17, password2, 1, NUM | LETTER, NULL);
	free(pass1);
	free(pass2);
	switch (in)
	{
	case tab:
	case up:
	case down:
		if (1 == type)
		{
			setRootPassword(2, password1, password2, "");
		}
		else
		{
			setRootPassword(1, password1, password2, "");
		}
		break;
	case enter:
		if ('\0'== password1[0]||'\0'== password2[0])
		{
			password1[0] = '\0';
			password2[0] = '\0';
			setRootPassword(1, password1, password2, "[     err:请输入密码     ]");
			return;
		}
		if (0==strcmp(password1, password2))
		{
			pAdmin root = (pAdmin)malloc(sizeof(admin));
			strcpy(root->name, "root");
			strcpy(root->password, password1);
			root->power = ~0;
			setRoot(root);
			setUser(root);
			strcpy(password1, "***************");
			strcpy(password2, "***************");
			return;
		}
		else
		{
			password1[0] = '\0';
			password2[0] = '\0';
			setRootPassword(1, password1, password2, "[err:两次输入的密码不一样]");
			return;
		}
		break;
	case esc:
		initialization();
		return;
	default:
		break;
	}
}

//设置默认外观
void setting() {
	setAttri("L", "[", "“选中”时左边的样式");
	setAttri("R", "]", "“选中”时右边的样式");
	setAttri("NL", " ", "“未选中”时左边的样式");
	setAttri("NR", " ", "“未选中”时右边的样式");
	setAttri("is", "[X]", "“选中”时的样式");
	setAttri("isNot", "[ ]", "“未选中”时的样式");
	setAttri("select", ">", "“选中”时简单的样式");
	setAttri("nSelect", " ", "“未选中”时简单的样式");
	setAttri("checkTime", "10", "检查余额的时间间隔(min)");
}

//初始化流程控制
int initialization() {
	mkdir("data");
	char *pass1 = (char *)malloc(sizeof(char)*16);
	char *pass2 = (char *)malloc(sizeof(char)*16);
	pass1[0] = '\0';
	pass2[0] = '\0';
	int type = 0;
	int isWhile = 1;
	setRootPassword(1, pass1, pass2, "");
	free(pass1);
	free(pass2);
	while (isWhile)
	{
		pr_weclome();
		printf("                             请选择需要设置的项目                             \n");
		printf("                           你可以随时通过管理员修改                           \n");
		printf("\n\n                              ");
		prOption(" 网吧规模 ", 0 == type, 18);
		printf("\n\n                              ");
		prOption("  会员卡  ", 1 == type, 18);
		printf("\n\n                              ");
		prOption(" 收费标准 ", 2 == type, 18);
		printf("\n\n                              ");
		prOption("   完成   ", 3 == type, 18);
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
		case left:
			type--;
			if (0>type)
			{
				type = 3;
			}
			break;
		case down:
		case right:
		case tab:
			type++;
			if (3<type)
			{
				type = 0;
			}
			break;
		case esc:
			initialization();
			break;
		case enter:
			switch (type)
			{
			case 0:
				scrollMenu(getPCtypeList());
				break;
			case 1:
				scrollMenu(getCardTypeList());
				break;
			case 2:
				scrollMenu(getRateList());
				break;
			case 3:
				isWhile = 0;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	setUser(NULL);
	save(d_attri);
	save(d_admin);
	save(d_pcType);
	save(d_cardType);
	save(d_rate);
	save(d_history);
	return 0;
}
