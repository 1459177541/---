#include"config.h"

//���ͷ
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
	printf("              ESC:��һ��/�˳�   ��/�·������TAB���л�ѡ��   ENTER��ȷ��");
	gotoxy(0, 9);
}

//���ù���Ա����
void setRootPassword(int type,char * pass1,char * pass2,char *text) {
	pr_weclome();
	printf("              ���Ǽ�⵽���ǵ�һ�����иó��������ó�������Ա           \n");
	printf("                                                         \n");
	printf("                        �û��� ��root \n");
	printf("                                                         \n");
	printf("                      �������� ��%s\n", 1 == type ? "" : printfPassword(pass1));
	printf("                                                         \n");
	printf("                      �ٴ����� ��%s\n", 2 == type ? "" : printfPassword(pass2));
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
			setRootPassword(1, pass1, pass2, "[     err:����������     ]");
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
			setRootPassword(1, pass1, pass2, "[err:������������벻һ��]");
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
	setAttri("L", "[");
	setAttri("R", "]");
	setAttri("NL", " ");
	setAttri("NR", " ");
}

/*********************************************************
 * �ѷ���
 *********************************************************
//��ʼ��
int init(int type) {
	pr_weclome();
	printf("                ���Ǽ�⵽���ǵ�һ�����иó����Ƿ����������ã�   \n");
	printf("                                                         \n");
	printf("                                                         \n");
	printf("           	                  ");
	prOption("��������", 1 == type, 12);
	printf("\n                                                         \n");
	printf("                                                         \n");
	printf("           	                  ");
	prOption("�ָ�����", 2 == type, 12);
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

//��ʼ�����̿���
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
