#include"config.h"

//���ͷ
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
	printf("              ESC:��һ��/�˳�   ��/�·������TAB���л�ѡ��   ENTER��ȷ��");
	gotoxy(0, 9);
}

//���ù���Ա����
void setRootPassword(int type,char * password1,char * password2,char *text) {
	char *pass1 = (char *)malloc(sizeof(char) * 16);
	char *pass2 = (char *)malloc(sizeof(char) * 16);
	printfPassword(password1, pass1);
	printfPassword(password2, pass2);
	pr_weclome();
	printf("              ���Ǽ�⵽���ǵ�һ�����иó��������ó�������Ա����           \n");
	printf("                      ����ؼ�ס�����û��������룡��        \n");
	printf("                                                         \n");
	printf("                                                         \n");
	printf("                        �û��� ��root \n");
	printf("                                                         \n");
	printf("                      �������� ��%s\n", 1 == type ? "" : pass1);
	printf("                                                         \n");
	printf("                      �ٴ����� ��%s\n", 2 == type ? "" : pass2);
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
			setRootPassword(1, password1, password2, "[     err:����������     ]");
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
			setRootPassword(1, password1, password2, "[err:������������벻һ��]");
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

//����Ĭ�����
void setting() {
	setAttri("L", "[", "��ѡ�С�ʱ��ߵ���ʽ");
	setAttri("R", "]", "��ѡ�С�ʱ�ұߵ���ʽ");
	setAttri("NL", " ", "��δѡ�С�ʱ��ߵ���ʽ");
	setAttri("NR", " ", "��δѡ�С�ʱ�ұߵ���ʽ");
	setAttri("is", "[X]", "��ѡ�С�ʱ����ʽ");
	setAttri("isNot", "[ ]", "��δѡ�С�ʱ����ʽ");
	setAttri("select", ">", "��ѡ�С�ʱ�򵥵���ʽ");
	setAttri("nSelect", " ", "��δѡ�С�ʱ�򵥵���ʽ");
	setAttri("checkTime", "10", "�������ʱ����(min)");
}

//��ʼ�����̿���
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
		printf("                             ��ѡ����Ҫ���õ���Ŀ                             \n");
		printf("                           �������ʱͨ������Ա�޸�                           \n");
		printf("\n\n                              ");
		prOption(" ���ɹ�ģ ", 0 == type, 18);
		printf("\n\n                              ");
		prOption("  ��Ա��  ", 1 == type, 18);
		printf("\n\n                              ");
		prOption(" �շѱ�׼ ", 2 == type, 18);
		printf("\n\n                              ");
		prOption("   ���   ", 3 == type, 18);
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
