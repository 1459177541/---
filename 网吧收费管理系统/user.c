#include"config.h"

//��ʼ��
pList adminLists = NULL;
int initAdminList() {
	prPrompt("���ڼ���", "���ڼ��ع���Ա��Ϣ");
	FILE *fp = NULL;
	if (NULL==(fp = fopen("data\\admin","rb")))
	{
		return 1;
	}
	pAdmin p = (pAdmin)malloc(sizeof(admin));
	if (NULL == adminLists)
	{
		if (fread(p, sizeof(admin), 1, fp)>0)
		{
			adminLists = (pList)malloc(sizeof(List));
			adminLists->next = NULL;
			adminLists->last = NULL;
			adminLists->type = d_admin;
			adminLists->date.admin = p;
		}
		else
		{
			fclose(fp);
			return 1;
		}
	}
	pList o = (pList)malloc(sizeof(List));
	pList q = adminLists;
	p = (pAdmin)malloc(sizeof(admin));
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
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

//�õ��б�
pList getAdminHead() {
	if (NULL == adminLists)
	{
		if (initAdminList())
		{
			adminLists = (pList)malloc(sizeof(List));
			adminLists->next = NULL;
			adminLists->last = NULL;
			adminLists->date.admin = NULL;
			adminLists->type = d_admin;
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
	pList p = getAdminHead();
	p->date.admin = root;
}

//�޸Ĺ���Ա
void editUser(int type, pAdmin p,char *password1,char *password2) {
	char *pass1 = (char *)malloc(sizeof(char) * 16);
	char *pass2 = (char *)malloc(sizeof(char) * 16);
	printfPassword(password1, pass1);
	printfPassword(password2, pass2);
	system("mode con cols=80 lines=24");
	myCls();
	printf("\n\n");
	printf("                         -----=====�޸Ĺ���Ա=====-----                        \n\n");
	printf("                               -----������Ϣ-----                              \n\n");
	printf("                              �û�����%s\n\n", 0 == type ?  "" : p->name);
	printf("                                ���룺%s\n\n", 1 == type ? "" : pass1);
	printf("                            ȷ�����룺%s\n\n", 2 == type ? "" : pass2);
	printf("                                 -----Ȩ��-----                                \n\n");
	printf("                    �������ͣ� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 3 == type ? '>' : ' ', isPower(p->power, 14) ? getAttri("is") : getAttri("isNot")
		, 4 == type ? '>' : ' ', isPower(p->power, 15) ? getAttri("is") : getAttri("isNot")
		, 5 == type ? '>' : ' ', isPower(p->power, 16) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  ��Ա�����ͣ� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 6 == type ? '>' : ' ', isPower(p->power, 11) ? getAttri("is") : getAttri("isNot")
		, 7 == type ? '>' : ' ', isPower(p->power, 12) ? getAttri("is") : getAttri("isNot")
		, 8 == type ? '>' : ' ', isPower(p->power, 13) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  ��Ա������ %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 9 == type ? '>' : ' ', isPower(p->power, 0) ? getAttri("is") : getAttri("isNot")
		, 10 == type ? '>' : ' ', isPower(p->power, 1) ? getAttri("is") : getAttri("isNot")
		, 11 == type ? '>' : ' ', isPower(p->power, 2) ? getAttri("is") : getAttri("isNot")
	);
	printf("                    �Ʒѱ�׼�� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 12 == type ? '>' : ' ', isPower(p->power, 3) ? getAttri("is") : getAttri("isNot")
		, 13 == type ? '>' : ' ', isPower(p->power, 4) ? getAttri("is") : getAttri("isNot")
		, 14 == type ? '>' : ' ', isPower(p->power, 5) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  ����Ա���� %c %3s ���  %c %3s ɾ��  %c %3s �޸�\n\n"
		, 15 == type ? '>' : ' ', isPower(p->power, 8) ? getAttri("is") : getAttri("isNot")
		, 16 == type ? '>' : ' ', isPower(p->power, 9) ? getAttri("is") : getAttri("isNot")
		, 17 == type ? '>' : ' ', isPower(p->power, 10) ? getAttri("is") : getAttri("isNot")
	);
	printf("                  %c %3s ��/�»�   %c %3s ��ѯ��¼   %c %3s ��ѯͳ��\n\n"
		, 18 == type ? '>' : ' ', isPower(p->power, 6) ? getAttri("is") : getAttri("isNot")
		, 19== type ? '>' : ' ', isPower(p->power, 7) ? getAttri("is") : getAttri("isNot")
		, 20 == type ? '>' : ' ', isPower(p->power, 17) ? getAttri("is") : getAttri("isNot")
	);
	printf("                                  ");
	OPTION_OK(21 == type);
	free(pass1);
	free(pass2);
	key k;
	if (0==type)
	{
		k = input(38, 3, p->name, 0, LETTER | CHINESE, NULL);
	}
	else if (1==type)
	{
		k = input(38, 5, password1, 1, NUM | LETTER | SYMBOL, NULL);
	}
	else if (2 == type)
	{
		k = input(38, 7, password2, 1, NUM | LETTER | SYMBOL, NULL);
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
			type = 21;
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
		break;
	case left:
		if (0==type)
		{
			type = 21;
		}
		else
		{
			type--;
		}
		break;
	case right:
		if (21==type)
		{
			type=0;
		}
		else
		{
			type++;
		}
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
		break;
	case esc:
		return;
	case enter:
		switch (type)
		{
		case 0:
		case 1:
		case 2:
			type = 21;
			break;
		//ʹ���������ı�ѡ��״̬
		case 3:	
			p->power ^= C_PC_TYPE;
			break;
		case 4:
			p->power ^= D_PC_TYPE;
			break;
		case 5:
			p->power ^= U_PC_TYPE;
			break;
		case 6:
			p->power ^= C_CARD_TYPE;
			break;
		case 7:
			p->power ^= D_CARD_TYPE;
			break;
		case 8:
			p->power ^= U_CARD_TYPE;
			break;
		case 9:
			p->power ^= C_CARD;
			break;
		case 10:
			p->power ^= D_CARD;
			break;
		case 11:
			p->power ^= U_CARD;
			break;
		case 12:
			p->power ^= C_RATE;
			break;
		case 13:
			p->power ^= D_RATE;
			break;
		case 14:
			p->power ^= U_RATE;
			break;
		case 15:
			p->power ^= C_ADMIN;
			break;
		case 16:
			p->power ^= D_ADMIN;
			break;
		case 17:
			p->power ^= U_ADMIN;
			break;
		case 18:
			p->power ^= UP_DOWN;
			break;
		case 19:
			p->power ^= HISTORY;
			break;
		case 20:
			p->power ^= STATISTICS;
			break;
		case 21:
			if (!strcmp(password1, password2)&&'/0'!= password1[0])
			{
				strcpy(p->password, password1);
				return;
			}
			else
			{
				password1[0] = '\0';
				password2[0] = '\0';
			}
		default:
			break;
		}
	default:
		break;
	}
	editUser(type, p, password1, password2);
}

//���Ȩ��
char * prPower(int power) {
	char *str = (char*)malloc(40*sizeof(char));
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
		if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'C';
			str[i++] = ',';
		}
		if (isPower(power, 2))
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
		if (isPower(power, 12))
		{
			str[i++] = 'D';
			str[i++] = 'C';
			str[i++] = 'T';
			str[i++] = ',';
		}
		if (isPower(power, 13))
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
		if (isPower(power, 12))
		{
			str[i++] = 'D';
			str[i++] = 'P';
			str[i++] = 'T';
			str[i++] = ',';
		}
		if (isPower(power, 13))
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
		if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'R';
			str[i++] = ',';
		}
		if (isPower(power, 2))
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
		if (isPower(power, 1))
		{
			str[i++] = 'D';
			str[i++] = 'A';
			str[i++] = ',';
		}
		if (isPower(power, 2))
		{
			str[i++] = 'U';
			str[i++] = 'A';
			str[i++] = ',';
		}
	}
	if (i>0)
	{
		str[i-1] = '\0';
	}
	else
	{
		str[0] = '\0';
	}
	return str;
}

//�������Ա
void prUser(pAdmin p) {
	printf(" %21s | %-47s   \n", p->name, prPower(p->power));
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
	printf("|            ÿ��Ȩ�޵ĵ�һ����ĸ�ֱ��ʾ��     |");
	gotoxy(x, y++);
	printf("|             ȫ��(All)������(Create)��         |");
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
	printf("                    |");
	gotoxy(x, y++);
	printf("=================================================");
	if (enter!=isKey(getch()))
	{
		helpFromUser();
	}
}

