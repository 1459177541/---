#include"config.h"
pList pcTypeList = NULL;
int isEdit = 0;

//是否修改过
int isEditPCType() {
	return isEdit != 0;
}

//设置修改状态
void setEdit(int edit) {
	isEdit = edit;
}

//初始化
int length = 0;
int initPCType() {
	prPrompt("正在加载", "正在加载电脑配置");
	FILE *fp = NULL;
	if (NULL == (fp = fopen("data\\pc", "rb")))
	{
		return 1;
	}
	pPCtype p = (pPCtype)malloc(sizeof(PCtype));
	if (NULL==pcTypeList)
	{
		if (fread(p, sizeof(PCtype), 1, fp)>0)
		{
			pcTypeList = (pList)malloc(sizeof(List));
			pcTypeList->next = NULL;
			pcTypeList->last = NULL;
			pcTypeList->type = d_pcType;
			pcTypeList->date.pcType = p;
		}
		else
		{
			free(p);
			fclose(fp);
			return 1;
		}
	}
	pList q = pcTypeList;
	pList o = (pList)malloc(sizeof(List));
	p = (pPCtype)malloc(sizeof(PCtype));
	while (fread(p, sizeof(PCtype), 1, fp)>0)
	{
		length += p->num;
		o->type = d_pcType;
		o->date.pcType = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pPCtype)malloc(sizeof(PCtype));
		o = (pList)malloc(sizeof(List));
	}
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

//得到列表
pList getPCtypeList() {
	if (NULL == pcTypeList)
	{
		if (initPCType())
		{
			pcTypeList = (pList)malloc(sizeof(List));
			pcTypeList->last = NULL;
			pcTypeList->next = NULL;
			pcTypeList->type = d_pcType;
			pPCtype pctype = (pPCtype)malloc(sizeof(PCtype));
			strcpy(pctype->type, "所有类型");
			pctype->num = 0;
			pctype->startId = 0;
			pcTypeList->date.pcType = pctype;
		}
	}
	return pcTypeList;
}

//输出
void prPCtype(pPCtype p) {
	printf("     %24s    |%12d    |%12d       \n",  p->type, p->num, p->startId);
}

//修改电脑类型
void editPCtype(int type, pPCtype p) {
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                类型名称：%-21s|", 0 == type ? "" : p->type);
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                数    量：%-21s|", 1 == type ? "" : intToString(p->num));
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                起始编号：%-21s|", 2 == type ? "" : intToString(p->startId));
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("|                      ");
	OPTION_OK(3 == type);
	printf("                  |");
	gotoxy(x, y++);
	printf("|                                               |");
	gotoxy(x, y++);
	printf("=================================================");

	key key;
	char *in = (char*)malloc(sizeof(char) * 16);
	in[0] = '\0';
	if (0 == type)
	{
		key = input(x + 27, 8, p->type, 0, NUM | LETTER | CHINESE, NULL);
	}
	else if (1 == type)
	{
		length -= p->num;
		key = input(x + 27, 10, in, 0, INTER, NULL);
		p->num = '\0' == in[0] ? p->num : stringToInt(in);
		length += p->num;
		getPCtypeList()->date.pcType->num = length;
	}
	else
	{
		key = input(x + 27, 12, in, 0, INTER, NULL);
		p->startId = '\0' == in[0] ? p->startId : stringToInt(in);
	}
	free(in);
	switch (key)
	{
	case up:
		if (0 == type)
		{
			editPCtype(4, p);
		}
		else {
			editPCtype(type - 1, p);
		}
		break;
	case down:
	case tab:
		if (4 == type)
		{
			editPCtype(0, p);
		}
		else {
			editPCtype(type + 1, p);
		}
		break;
	case enter:
		if (3 != type)
		{
			editPCtype(3, p);
		}
		return;
	default:
		editPCtype(type, p);
		break;
	}
}

//修改信息提醒
int editPCTypePS(int type) {
	if (!hasLoginPC())
	{
		return 1;
	}
	int x = 16;
	int y = 8;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                    警告                       |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|         当前存在上机用户，需要强制下机        |");
	gotoxy(x, y++);
	printf("|         才可继续修改，是否强制下机？          |");
	gotoxy(x, y++);
	printf("|        ");
	prOption("强制下机", 0 == type, 12);
	printf("         ");
	prOption("返回", 1 == type, 6);
	printf("        |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	switch (k)
	{
	case up:
	case down:
	case left:
	case right:
	case tab:
		if (1==type)
		{
			return editPCTypePS(0);
		}
		else
		{
			return editPCTypePS(1);
		}
		break;
	case enter:
		if (0==type)
		{
			logoutPCAll();
			return 1;
		}
		else
		{
			return 0;
		}
	default:
		break;
	}
	return editPCTypePS(type);
}

//新建
pList newPCType(pList list) {
	pList q = list;
	while (NULL!=q->next)
	{
		q = q->next;
	}
	pPCtype p = (pPCtype)malloc(sizeof(PCtype));
	p->startId = getPCtypeList()->date.pcType->num;
	p->num = 0;
	p->type[0] = '\0';
	pList pl = (pList)malloc(sizeof(List));
	pl->last = q;
	pl->next = NULL;
	pl->date.pcType = p;
	pl->type = d_pcType;
	q->next = pl;
	editPCtype(0, p);
	setEdit(1);
	addHistory(C_PC_TYPE_T, pl->date, 0);
	return list;
}