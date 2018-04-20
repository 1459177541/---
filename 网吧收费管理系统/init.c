#include"config.h"

//输出头
void pr_weclome() {
	system("title welcome");
	system("cls");
	system("mode con cols=80 lines=24");
	gotoxy(0, 0);
	printf("                                                                             \n");
	printf("                                                         \n");
	printf("        \\\\    //\\\\    //         //                       \n");
	printf("         \\\\  //  \\\\  //  //~//  //     //~~  //~//  //\\\\  //\\\\    //~//  \n");
	printf("          \\\\//    \\\\//  //~~   //     //    // //  //  \\\\//  \\\\  //~~ \n");
	printf("           ~~      ~~   ~~~~   ~~~~~  ~~~~  ~~~~   ~    ~~    ~  ~~~~          \n");
	printf("       ===================================================================    \n");
	printf("                                                         \n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	gotoxy(0, 24);
	printf("              ESC:上一步/退出   上/下方向键、TAB：切换选项   ENTER：确认");
	gotoxy(0, 9);
}

//设置管理员密码
void setRootPassword(int type,char * pass1,char * pass2,char *text) {
	pr_weclome();
	printf("              我们检测到您是第一次运行该程序，请设置超级管理员           \n");
	printf("                                                         \n");
	printf("                        用户名 ：root \n");
	printf("                                                         \n");
	printf("                      您的密码 ：%s\n", 1 == type ? "" : printfPassword(pass1));
	printf("                                                         \n");
	printf("                      再次输入 ：%s\n", 2 == type ? "" : printfPassword(pass2));
	printf("                                                         \n");
	printf("\n                                                        \n");
	printf("                       %s \n",text);
	key in = 1 == type ? input(33, 13, pass1, 1, NUM | LETTER, NULL) : input(33, 15, pass2, 1, NUM | LETTER, NULL);
	switch (in)
	{
	case tab:
	case up:
	case down:
		if (1 == type)
		{
			setRootPassword(2, pass1, pass2, "");
		}
		else
		{
			setRootPassword(1, pass1, pass2, "");
		}
		break;
	case enter:
		if ('\0'==pass1[0]||'\0'==pass2[0])
		{
			pass1[0] = '\0';
			pass2[0] = '\0';
			setRootPassword(1, pass1, pass2, "[     err:请输入密码     ]");
			return;
		}
		if (0==strcmp(pass1,pass2))
		{
			pAdmin root = (pAdmin)malloc(sizeof(admin));
			strcpy(root->name, "root");
			strcpy(root->password, pass1);
			root->power = ~0;
			setRoot(root);
			strcpy(pass1, "***************");
			strcpy(pass2, "***************");
			free(pass1);
			free(pass2);
			return;
		}
		else
		{
			pass1[0] = '\0';
			pass2[0] = '\0';
			setRootPassword(1, pass1, pass2, "[err:两次输入的密码不一样]");
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
	setAttri("L", "[");
	setAttri("R", "]");
	setAttri("NL", " ");
	setAttri("NR", " ");
}

/*********************************************************
 * 已废弃
 *********************************************************
//初始化
int init(int type) {
	pr_weclome();
	printf("                我们检测到您是第一次运行该程序，是否进入快速设置？   \n");
	printf("                                                         \n");
	printf("                                                         \n");
	printf("           	                  ");
	prOption("快速设置", 1 == type, 12);
	printf("\n                                                         \n");
	printf("                                                         \n");
	printf("           	                  ");
	prOption("恢复备份", 2 == type, 12);
	printf("\n                                                         \n");
	printf("                                                         \n");
	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case tab:
	case down:
	case up:
		if (1==type)
		{
			return init(2);
		}
		else
		{
			return init(1);
		}
		break;
	case enter:
		return type;
	case esc:
		if (!saveExit(0))
		{
			return init(type);
		}
		break;
	default:
		break;
	}
	return init(type);
}
*/

//初始化流程控制
int initialization() {
	setting();
	mkdir("data");
//	if (1==init(1))
	{
		char *pass1 = (char *)malloc(sizeof(char)*16);
		char *pass2 = (char *)malloc(sizeof(char)*16);
		pass1[0] = '\0';
		pass2[0] = '\0';
		int type = 0;
		int isWhile = 1;
		setRootPassword(1, pass1, pass2, "");
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
					scrollMenu(getPCtypeList(), d_pcType, 0);
					break;
				case 1:
					scrollMenu(getCardTypeList(), d_cardType, 0);
					break;
				case 2:
					scrollMenu(getRateList(), d_rate, 0);
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

		save(d_admin);
		save(d_pcType);
		save(d_cardType);
		save(d_rate);
	}

	return 0;
}
