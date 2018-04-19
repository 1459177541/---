#include"config.h"

//��ʼ��
pList adminLists = NULL;
int initAdminList() {
	FILE *fp;
	if (NULL==(fp = fopen("data\\admin","rb")))
	{
		return 1;
	}
	pAdmin p = (pAdmin)malloc(sizeof(admin));
	if (NULL == adminLists && fread(p, sizeof(admin), 1, fp)>0)
	{
		adminLists = (pList)malloc(sizeof(List));
		adminLists->next = NULL;
		adminLists->last = NULL;
		adminLists->date.admin = p;
	}
	pList o = (pList)malloc(sizeof(List));
	pList q = adminLists;
	while (fread(p, sizeof(admin), 1, fp)>0)
	{
		o->type = d_admin;
		o->date.admin = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pAdmin)malloc(sizeof(admin));
		o = (pList)malloc(sizeof(List));
	}
	return 0;
}

//�õ��б�
pList getAdminHead() {
	if (NULL == adminLists)
	{
		if (initAdminList())
		{
			//
		}
	}
	return adminLists;
}

pAdmin user;
void setUser(pAdmin u) {
	user = u;
}
pAdmin getUser() {
	return user;
}

//���ó�������Ա
void setRoot(pAdmin root) {
	if (NULL == getAdminHead())
	{
		adminLists = (pList)malloc(sizeof(List));
		adminLists->next = NULL;
		adminLists->last = NULL;
		adminLists->date.admin = root;
		return;
	}
	pList p = getAdminHead();
	p->date.admin = root;
	free(p);
}

//�޸Ĺ���Ա
void editUser(int type, pList p,char *pass1,char *pass2) {
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n\n");
	printf("                         -----=====�޸Ĺ���Ա=====-----                        \n\n");
	printf("                               -----������Ϣ-----                              \n\n");
	printf("                              �û�����%s\n\n", 0 == type ? p->date.admin->name : "");
	printf("                                ���룺%s\n\n", 1 == type ? "" : printfPassword(pass1));
	printf("                            ȷ�����룺%s\n\n", 2 == type ? "" : printfPassword(pass2));
	printf("                                 -----Ȩ��-----                                \n\n");
	printf("                    �������ͣ� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 3 == type ? '>' : ' ', isPower(p->date.admin->power, 14) ? getAttri("is") : getAttri("isNot")
		, 4 == type ? '>' : ' ', isPower(p->date.admin->power, 15) ? getAttri("is") : getAttri("isNot")
		, 5 == type ? '>' : ' ', isPower(p->date.admin->power, 16) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  ��Ա�����ͣ� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 6 == type ? '>' : ' ', isPower(p->date.admin->power, 11) ? getAttri("is") : getAttri("isNot")
		, 7 == type ? '>' : ' ', isPower(p->date.admin->power, 12) ? getAttri("is") : getAttri("isNot")
		, 8 == type ? '>' : ' ', isPower(p->date.admin->power, 13) ? getAttri("is") : getAttri("isNot")
	);
	printf("                   ��Ա������ %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 9 == type ? '>' : ' ', isPower(p->date.admin->power, 0) ? getAttri("is") : getAttri("isNot")
		, 10 == type ? '>' : ' ', isPower(p->date.admin->power, 1) ? getAttri("is") : getAttri("isNot")
		, 11 == type ? '>' : ' ', isPower(p->date.admin->power, 2) ? getAttri("is") : getAttri("isNot")
	);
	printf("                    �Ʒѱ�׼�� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 12 == type ? '>' : ' ', isPower(p->date.admin->power, 3) ? getAttri("is") : getAttri("isNot")
		, 13 == type ? '>' : ' ', isPower(p->date.admin->power, 4) ? getAttri("is") : getAttri("isNot")
		, 14 == type ? '>' : ' ', isPower(p->date.admin->power, 5) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  ����Ա���� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 15 == type ? '>' : ' ', isPower(p->date.admin->power, 8) ? getAttri("is") : getAttri("isNot")
		, 16 == type ? '>' : ' ', isPower(p->date.admin->power, 9) ? getAttri("is") : getAttri("isNot")
		, 17 == type ? '>' : ' ', isPower(p->date.admin->power, 10) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  %c %3s ��/�»�   %c %3s ��ѯ��¼   %c %3s ��ѯͳ��\n\n"
		, 18 == type ? '>' : ' ', isPower(p->date.admin->power, 6) ? getAttri("is") : getAttri("isNot")
		, 19== type ? '>' : ' ', isPower(p->date.admin->power, 7) ? getAttri("is") : getAttri("isNot")
		, 20 == type ? '>' : ' ', isPower(p->date.admin->power, 17) ? getAttri("is") : getAttri("isNot")
	);
	printf("                 ");
	OPTION_OK(21 == type);
	printf("                 ");
	OPTION_CANCEL(22 == type);
	key k;
	if (0==type)
	{
		k = input(7, 20, p->date.admin->name, 0, LETTER | CHINESE, NULL);
	}
	else if (1==type)
	{
		k = input(9, 20, p->date.admin->password, 1, NUM | LETTER | SYMBOL, NULL);
	}
	else
	{
		k = isKey(getch());
	}
	switch (k)
	{
	case up:
		if (0==type)
		{
			type = 22;
		}
		else if (3>type)
		{
			type--;
		}
		else if (6>type)
		{
			type = 2;
		}
		else
		{
			type -= 3;
		}
		editUser(type, p, pass1, pass2);
		break;
	case down:
		if (3>type)
		{
			type++;
		}
		else if (17<type)
		{
			type = 0;
		}
		else
		{
			type += 3;
		}
		editUser(type, p, pass1, pass2);
		break;
	case left:
		if (0==type)
		{
			type = 22;
		}
		else
		{
			type--;
		}
		editUser(type, p, pass1, pass2);
		break;
	case right:
		if (22==type)
		{
			type=0;
		}
		else
		{
			type++;
		}
		editUser(type, p, pass1, pass2);
		break;
	case tab:
		if (3>type)
		{
			type = 3;
		}
		else
		{
			type = 0;
		}
		editUser(type, p, pass1, pass2);
		break;
	case esc:
		return;
	case enter:
		switch (type)
		{
		case 0:
		case 1:
		case 2:
			type = 20;
			break;
		//ʹ���������ı�ѡ��״̬
		case 3:	
			p->date.admin->power ^= C_PC_TYPE;
			break;
		case 4:
			p->date.admin->power ^= D_PC_TYPE;
			break;
		case 5:
			p->date.admin->power ^= U_PC_TYPE;
			break;
		case 6:
			p->date.admin->power ^= C_CARD_TYPE;
			break;
		case 7:
			p->date.admin->power ^= D_CARD_TYPE;
			break;
		case 8:
			p->date.admin->power ^= U_CARD_TYPE;
			break;
		case 9:
			p->date.admin->power ^= C_CARD;
			break;
		case 10:
			p->date.admin->power ^= D_CARD;
			break;
		case 11:
			p->date.admin->power ^= U_CARD;
			break;
		case 12:
			p->date.admin->power ^= C_RATE;
			break;
		case 13:
			p->date.admin->power ^= D_RATE;
			break;
		case 14:
			p->date.admin->power ^= U_RATE;
			break;
		case 15:
			p->date.admin->power ^= C_ADMIN;
			break;
		case 16:
			p->date.admin->power ^= D_ADMIN;
			break;
		case 17:
			p->date.admin->power ^= U_ADMIN;
			break;
		case 18:
			p->date.admin->power ^= UP_DOWN;
			break;
		case 19:
			p->date.admin->power ^= HISTORY;
			break;
		case 20:
			p->date.admin->power ^= STATISTICS;
			break;
		case 21:
			if (!strcmp(pass1,pass2)&&'/0'!=pass1[0])
			{
				strcpy(p->date.admin->password, pass1);
				return;
			}
			else
			{
				pass1[0] = '\0';
				pass2[0] = '\0';
			}
		case 22:
			p->last->next = p->next;
			if (NULL != p->next)
			{
				p->next->last = p->last;
			}
			free(p);
			break;
		default:
			break;
		}
	default:
		break;
	}
	editUser(type, p, pass1, pass2);
}

//���Ȩ��
char * prPower(int power) {
	char str[40];
	int i = 0;
	if ((isPower(power, 0) && isPower(power, 1) && isPower(power, 2)))
	{
		str[i++] = 'A';
		str[i++] = 'C';
		str[i++] = ',';
	}
	else 
	{
		if (isPower(power, 0))
		{
			str[i++] = 'C';
			str[i++] = 'C';
			str[i++] = ',';
		}
		else if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'C';
			str[i++] = ',';
		}
		else if (isPower(power, 2))
		{
			str[i++] = 'U';
			str[i++] = 'C';
			str[i++] = ',';
		}
	} 
	if ((isPower(power, 11) && isPower(power, 12) && isPower(power, 13)))
	{
		str[i++] = 'A';
		str[i++] = 'C';
		str[i++] = 'T';
		str[i++] = ',';
	}
	else 
	{
		if (isPower(power, 11))
		{
			str[i++] = 'C';
			str[i++] = 'C';
			str[i++] = 'T';
			str[i++] = ',';
		}
		else if (isPower(power, 12))
		{
			str[i++] = 'D';
			str[i++] = 'C';
			str[i++] = 'T';
			str[i++] = ',';
		}
		else if (isPower(power, 13))
		{
			str[i++] = 'U';
			str[i++] = 'C';
			str[i++] = 'T';
			str[i++] = ',';
		}
	}
	if ((isPower(power, 14) && isPower(power, 15) && isPower(power, 16)))
	{
		str[i++] = 'A';
		str[i++] = 'P';
		str[i++] = 'T';
		str[i++] = ',';
	}
	else
	{
		if (isPower(power, 11))
		{
			str[i++] = 'C';
			str[i++] = 'P';
			str[i++] = 'T';
			str[i++] = ',';
		}
		else if (isPower(power, 12))
		{
			str[i++] = 'D';
			str[i++] = 'P';
			str[i++] = 'T';
			str[i++] = ',';
		}
		else if (isPower(power, 13))
		{
			str[i++] = 'U';
			str[i++] = 'P';
			str[i++] = 'T';
			str[i++] = ',';
		}
	}
	if ((isPower(power, 3) && isPower(power, 4) && isPower(power, 5)))
	{
		str[i++] = 'A';
		str[i++] = 'R';
		str[i++] = ',';
	}
	else
	{
		if (isPower(power, 0))
		{
			str[i++] = 'C';
			str[i++] = 'R';
			str[i++] = ',';
		}
		else if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'R';
			str[i++] = ',';
		}
		else if (isPower(power, 2))
		{
			str[i++] = 'U';
			str[i++] = 'R';
			str[i++] = ',';
		}
	}
	if ((isPower(power, 6)))
	{
		str[i++] = 'U';
		str[i++] = 'D';
		str[i++] = ',';
	}
	if ((isPower(power, 7)))
	{
		str[i++] = 'H';
		str[i++] = ',';
	}
	if ((isPower(power, 8) && isPower(power, 9) && isPower(power, 10)))
	{
		str[i++] = 'A';
		str[i++] = 'A';
		str[i++] = ',';
	}
	else
	{
		if (isPower(power, 0))
		{
			str[i++] = 'C';
			str[i++] = 'A';
			str[i++] = ',';
		}
		else if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'A';
			str[i++] = ',';
		}
		else if (isPower(power, 2))
		{
			str[i++] = 'U';
			str[i++] = 'A';
			str[i++] = ',';
		}
	}
	str[i] = '\0';
}

//�������Ա
void prUser(pAdmin p, int isOption) {
	printf(" %6s%15s | %40s %-6s   \n"
		, isOption ? getAttri("L") : getAttri("NL"), p->name,  prPower(p->power), isOption ? getAttri("R") : getAttri("NR"));
}

//����
void helpFromUser() {
	int x = 16;
	int y = 4;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                      ����                     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|            ÿ��Ȩ�޵ĵ�һ����ĸ�ֱ��ʾ��      |");
	gotoxy(x, y++);
	printf("|             ȫ��(All)������(Create)��          |");
	gotoxy(x, y++);
	printf("|             �޸�(Update)��ɾ��(Detele)        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|         ÿ��Ȩ�޵ĵڶ�(����)����ĸ�ֱ��ʾ��  |");
	gotoxy(x, y++);
	printf("|   ��Ա������(Card Type)����������(Pc Type)��  |");
	gotoxy(x, y++);
	printf("|   ��Ա��(Card)������Ա(Admin)���շѱ�׼(Rate) |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|         ��������һ���ʾ��������������д����  |");
	gotoxy(x, y++);
	printf("|  ��ѯ��ʷ��¼(History)��������/�»�(Up Down)  |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                    ");
	prOption("ȷ��", 1, 7);
	printf("                   |");
	gotoxy(x, y++);
	printf("=================================================");
	if (enter!=isKey(getch()))
	{
		helpFromUser();
	}
}

/*********************************************************
 * �ѷ���
 *********************************************************
//���ù���Ա
void setUserMenu(int type) {
	int length = 0;
	pList q = getAdminHead();
	pList op;
	while (length<type - 10 && NULL != q)
	{
		length++;
		q = q->next;
	}
	system("cls");
	system("mode con cols=80 lines=24");
	printf("\n\n                                   �����ù���Ա\n\n");
	printf("                  ================================================            \n");
	printf("          �û���        |                        Ȩ��                          \n");
	if (0 != length)
	{
		printf("            ++++++     |                       ++++++                    \n");
	}
	else
	{
		printf("                       |                                            \n");
	}
	int pr = 0;
	while (NULL != q->next)
	{
		q = q->next;
		length++;
		if (length == type)
		{
			op = q;
		}
		if (pr<10)
		{
			pr++;
			prUser(q->date, length == type);
		}
		else {
			break;
		}
	}
	for (int i = pr; i < 10; i++)
	{
		printf("                        |                                            \n");
	}
	if ((NULL != q && type >= 0) || (10 < length && type < 0))
	{
		printf("             ++++++     |                       ++++++                    \n");
	}
	else
	{
		printf("                        |                                            \n");
	}
	printf("                  ================================================            \n");
	if (0 == length && 1 == type)
	{
		type = 0;
	}
	printf("\n         ");
	prOption("  �½�  ", 0 == type, 13);
	printf("         ");
	prOption("  ���  ", -1 == type, 13);
	printf("         ");
	prOption("  ����  ", -2 == type, 13);
	while (1)
	{
		int in = getch();
		key k = isKey(in);
		switch (k)
		{
		case up:
			if (0 == type)
			{
				if (0 == length)
				{
					setUserMenu(-1);
				}
				else
				{
					setUserMenu(length + 1);
				}
			}
			else if (-1 == type)
			{
				setUserMenu(0);
			}
			else if (1 == type)
			{
				setUserMenu(-1);
			}
			else
			{
				setUserMenu(type - 1);
			}
			return;
			break;
		case down:
		case tab:
			if (0 == type)
			{
				setUserMenu(-1);
			}
			else if (-1 == type)
			{
				if (0 == length)
				{
					setUserMenu(0);
				}
				else
				{
					setUserMenu(1);
				}
			}
			else if (length == type)
			{
				setUserMenu(0);
			}
			else
			{
				setUserMenu(type + 1);
			}
			return;
		case enter:
			if (0 == type)
			{
				pAdmin p = (pAdmin)malloc(sizeof(admin));
				p->name[0] = '\0';
				p->password[0] = '\0';
				p->power = 0;
				while (NULL != q->next)
				{
					q = q->next;
				}
				pList pl = (pList)malloc(sizeof(adminList));
				pl->last = q;
				pl->next = NULL;
				pl->date = p;
				q->next = pl;
				editPCtype(0, pl);
				setUserMenu(type);
				return;
			}
			else if (-1 == type)
			{
				return;
			}
			else
			{
				editPCtype(0, op);
				setUserMenu(type);
				return;
			}
			break;
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

//����
void saveAdmin() {
	if (NULL == getAdminHead())
	{
		return;
	}
	FILE *fp;
	if (NULL == (fp = fopen("data\\admin", "wb")))
	{
		return;
	}
	pList p = getAdminHead();
	while (NULL != p)
	{
		if (fwrite(p->date, sizeof(admin), 1, fp))
		{
			p = p->next;

		}
	}
}
*/
