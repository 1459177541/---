#include"config.h"

//����ժ�����룬ʵ�ֹ���λ����ת
void gotoxy(int x, int y)
{
	COORD coord = { x, y };
	/*COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��

	typedef struct _COORD {

	SHORT X; // horizontal coordinate

	SHORT Y; // vertical coordinate
	} COORD;*/

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//����
void myCls() {
	static int i = 0;
	if (i>20)
	{
		i = 0;
		system("cls");
		return;
	}
	i++;
	printf("\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	gotoxy(0, 0);
}

//�ַ�ת��Ϊ����
int stringToInt(char * string) {
	int num = 0;
	int i = 0;
	while ('\0'!=string[i])
	{
		if ('0'<=string[i]&&'9'>=string[i])
		{
			num = num * 10 + string[i] - '0';
		}
		i++;
	}
	return num;
}

//����ת��Ϊ�ַ�
char * intToString(int num) {
	if (0 == num)
	{
		return "0";
	}
	char *str = (char *)malloc(sizeof(char) * 34);
	str[33] = '\0';
	for (int i = 0; i < 33; i++)
	{
		str[i] = '0';
	}
	if (num<0)
	{
		str[0] = '-';
	}
	int t = num>0 ? num : -num;
	for (int i = 32; i > 0 && t != 0; i--)
	{
		str[i] = t % 10 + '0';
		t /= 10;
	}
	int index = 0;
	while ('0' == str[index] || '-' == str[index])
	{
		index++;
	}
	int i = num < 0 ? 1 : 0;
	for (; i < 33; i++, index++)
	{
		str[i] = str[index];
	}
	str[i] = '\0';
	return str;
}

//�и��ַ���
void splitString(char *src, char *ret,int start,int length) {
	int i = 0;
	while (i<length&&src[start+i]!='\0')
	{
		ret[i] = src[start + i];
		i++;
	}
	ret[i] = '\0';
}

//�滻�ַ���
void replaceString(char *src, char old, char *new) {
	char * temp = (char*)malloc(32 * sizeof(char));
	int i = 0;
	while ('\0' != src[i])
	{
		if (old == src[i] || old == src[i])
		{
			int j = 0;
			int it = i;
			while (src[it] != '\0')
			{
				temp[j] = src[it];
				it++;
			}
			temp[j] = '\0';
			while (new[j] != '\0')
			{
				src[i] = new[j];
				i++;
				j++;
			}
			j = 0;
			while ('\0' != temp[j])
			{
				src[i] = temp[j];
				i++;
				j++;
			}
			break;
		}
		i++;
	}
	src[i] = '\0';
	free(temp);
}

//�������
char *printfPassword(char *password) {
	int i = 0;
	while ('\0'!=password[i++])	{	}
	char *pass = (char*)malloc(sizeof(char)*(i+1));
	for (int j = 0; j < i-1; j++)
	{
		pass[j] = '*';
	}
	pass[i-1] = '\0';
	return pass;
}

//�ж��Ƿ��ǡ�����
int isNum(char in) {
	return ('0' <= in&&'9' >= in)||'.'==in;
}
int isInt(char in) {
	return '0' <= in&&'9' >= in;
}
int isLetter(char in) {
	return ('a' <= in&&'z' >= in) || ('A' <= in&&'Z' >= in);
}
int isSymbol(char in) {
	return (0x20 <= in&& 0x2f >= in) || (0x3a <= in&& 0x40 >= in) || (0x5b <= in && 0x60 >= in) || (0x7b <= in && 0x7e >= in);
}
int isChinese(char in) {
	return 0 >= in;
}

//�ж����밴������
key isKey(int in){
	if (9 == in)
	{
		return tab;
	}
	else if (27 == in)
	{
		return esc;
	}
	else if (8 == in)
	{
		return backspace;
	}
	else if (13 == in)
	{
		return enter;
	}
	else if (isNum(in))
	{
		return number;
	}
	else if (224==in||-32==in)
	{
		switch (getch())
		{
		case 72:
			return up;
		case 75:
			return left;
		case 77:
			return right;
		case 80:
			return down;
		case 73:
			return pgup;
		case 81:
			return pgdn;
		case 83:
			return del;
		case 79:
			return end;
		case 82:
			return ins;
		case 71:
			return home;
		default:
			break;
		}
	}
	return no;
}

//�Ƿ���ָ��Ȩ��
int isPower(int powerCode,int point) {
	int p = (powerCode >> point) & 1;
	return p == 1;
}

//���ѡ��
void prOption(char * name,int isOption,int length) {
	char str[] = "%  s%  s%-  s";
	if (length/6>=10)
	{
		str[1] = (length / 6) / 10 + '0';
		str[10] = (length / 6) / 10 + '0';
		str[5] = (length - length / 6 * 2) / 10 + '0';
	}
	str[2] = (length / 6) % 10 + '0';
	str[11] = (length / 6) % 10 + '0';
	str[6] = (length - length / 6 * 2) % 10 + '0';
	printf(str, isOption ? getAttri("L") : getAttri("NL"),name, isOption ? getAttri("R") : getAttri("NR"));
}

//�����ʾ��
void prPrompt(char *title, char *body) {
	char *text1 = (char*)malloc(sizeof(char) * 64);
	char *text2 = (char*)malloc(sizeof(char) * 64);
	char *text3 = (char*)malloc(sizeof(char) * 64);
	text1[0] = '\0';
	text2[0] = '\0';
	text3[0] = '\0';
	int row = 0;
	int i = 0;
	int j = 0;
	int isEnd = 0;
	while (!isEnd && '\0' != body[i] && '\n' != body[i])
	{
		text1[j] = body[i];
		j++;
		i++;
	}
	if ('\n' == body[i])
	{
		row++;
	}
	else
	{
		isEnd = 1;
	}
	text1[j] = '\0';
	j = 0;
	i++;
	while (!isEnd && '\0'!=body[i]&&'\n'!=body[i])
	{
		text2[j] = body[i];
		j++;
		i++;
	}
	if ('\n' == body[i])
	{
		row++;
	}
	else
	{
		isEnd = 1;
	}
	text2[j] = '\0';
	j = 0;
	i++;
	while (!isEnd && '\0' != body[i] && '\n' != body[i])
	{
		text3[j] = body[i];
		j++;
		i++;
	}
	text3[j] = '\0';
	int x = 16;
	int y = 8;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x + 25 - strlen(title) / 2, 9);
	printf("%s", title);
	if (0==row)
	{
		gotoxy(x + 25 - strlen(body) / 2, 12);
		printf("%s", body);
	}
	else if (1==row)
	{
		gotoxy(x + 25 - strlen(text1) / 2, 12);
		printf("%s", text1);
		gotoxy(x + 25 - strlen(text2) / 2, 13);
		printf("%s", text2);
	}
	else if (2==row)
	{
		gotoxy(x + 25 - strlen(text1) / 2, 11);
		printf("%s", text1);
		gotoxy(x + 25 - strlen(text2) / 2, 12);
		printf("%s", text2);
		gotoxy(x + 25 - strlen(text3) / 2, 13);
		printf("%s", text3);
	}
	free(text3);
	free(text2);
	free(text1);
	gotoxy(0, 23);
}

//����
key input(int x,int y,char *in,int isPassword,int power,char * other) {
	gotoxy(x, y);
	char *input = (char *)malloc(sizeof(char) * 32);
	int i = 0;
	while (1)
	{
		input[i] = getch();
		key k = isKey(input[i]);
		int isBreak = 0;
		switch (k)
		{
		case letter:
		case symbol:
		case number:
			break;
		case no:
			break;
		case left:
		case right:
		case up:
		case down:
		case tab:
		case enter:
			input[i] = '\0';
			if (0 != i)
			{
				strcpy(in, input);
			}
			return k;
		case backspace:
			isBreak = 1;
			if (0 == i)
			{
				break;
			}
			if (isChinese(input[i]))
			{
				gotoxy(x - 1 + i, y);
				printf(" ");
				gotoxy(x - 1 + i, y);
				i--;
			}
			gotoxy(x - 1 + i, y);
			printf(" ");
			gotoxy(x - 1 + i, y);
			i--;
			break;
		case esc:
			return esc;
		default:
			isBreak = 1;
			break;
		}
		if (isBreak)
		{
			continue;
		}
		int isIn = 0;
		if ( isInt(input[i]) && isPower(power, 5) )		//�Ƿ��д������
		{
			isIn = 1;
		}
		if ( isNum(input[i]) && isPower(power, 0) )		//�Ƿ��д������
		{
			isIn = 1;
		}
		if ( isLetter(input[i]) && isPower(power, 1) )		//�Ƿ��д����ĸ
		{
			isIn = 1;
		}
		if ( isSymbol(input[i]) && isPower(power, 2) ) 	//�Ƿ��д�����
		{
			isIn = 1;
		}
		if ( isChinese(input[i]) && isPower(power, 3) )	//�Ƿ��д������
		{
			isIn = 1;
		}
		if(NULL!=other && isPower(power,4)){
			int j = 0;
			while (other[j]!='\0')
			{
				if (other[j]==input[i])
				{
					isIn = 1;
					break;
				}
				j++;
			}
		}
		if (!isIn)
		{
			continue;
		}
		if (i>31)											//�Ƿ񳬹�����
		{
			continue;
		}
		if (isPassword)
		{
			printf("*");
		}
		else
		{
			printf("%c", input[i]);
		}
		i++;
	}
}

//�˳�
int saveExit(int type) {
	int x = 16;
	gotoxy(x, 8);
	printf("=================================================");
	gotoxy(x, 9);
	printf("|                      �˳�                     |");
	gotoxy(x, 10);
	printf("|        -------------------------------        |");
	gotoxy(x, 11);
	printf("|                    �Ƿ񱣴棿                 |");
	gotoxy(x, 12);
	printf("|                                               |");
	gotoxy(x, 13);
	printf("|    ");
	prOption("���沢�˳�", 0 == type, 15);
	printf("     ");
	prOption("���˳�", 1 == type, 9);
	printf("     ");
	prOption("ȡ��", 2 == type, 6);
	printf("    |");
	gotoxy(x, 14);
	printf("=================================================");
	int in = getch();
	key k = isKey(in);
	switch (k)
	{
	case down:
	case right:
	case tab:
		if (2==type)
		{
			type = -1;
		}
		return saveExit(type + 1);
	case left:
	case up:
		if (0==type)
		{
			type = 3;
		}
		return saveExit(type - 1);
	case enter:
		switch (type)
		{
		case 0:
			saveAll();
		case 1:
			prPrompt("�˳���", "���ڽ�����");
			logoutPCAll();
			prPrompt("�ѳɹ��ر�", "��л����ʹ��");
			gotoxy(x + 15, 13);
//			exit(0);
			return 1;
		case 2:
			return 0;
		default:
			break;
		}
	case esc:
		return 0;
	default:
		saveExit(type);
		break;
	}
	return 1;
}
