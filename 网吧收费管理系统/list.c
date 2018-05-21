#include"config.h"

//保存
void save(dataType type) {
	FILE *fp = NULL;
	pList p = NULL;
	char fileName[14] = "";
	switch (type)
	{
	case d_admin:
		prPrompt("正在保存", "正在保存管理员信息");
		strcpy(fileName, "data\\admin");
		p = getAdminHead();
		break;
	case d_pcType:
		prPrompt("正在保存", "正在保存网吧规模");
		strcpy(fileName, "data\\pc");
		p = getPCtypeList();
		break;
	case d_cardType:
		prPrompt("正在保存", "正在保存会员卡类型");
		strcpy(fileName, "data\\cardType");
		p = getCardTypeList();
		break;
	case d_rate:
		prPrompt("正在保存", "正在保存计费方案");
		strcpy(fileName, "data\\rate");
		p = getRateList();
		break;
	case d_history:
		prPrompt("正在保存", "正在保存历史记录");
		strcpy(fileName, "data\\history");
		p = getHistorys();
		break;
	case d_card:
		prPrompt("正在保存", "正在保存会员卡");
		strcpy(fileName, "data\\card");
		p = getCards();
		break;
	case d_attri:
		prPrompt("正在保存", "正在保存配置");
		strcpy(fileName, "data\\config");
		p = getAttriList();
		break;
	default:
		break;
	}
	if (NULL==p || NULL == (fp = fopen(fileName, "wb")))
	{
		return;
	}
	while (NULL != p)
	{
		if (NULL == p->data.admin)
		{
			p = p->next;
			continue;
		}
		switch (type)
		{
		case d_admin:
			if (fwrite(p->data.admin, sizeof(admin), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_pcType:
			if (fwrite(p->data.pcType, sizeof(PCtype), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_cardType:
			if (fwrite(p->data.cardType, sizeof(cardType), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_rate:
			if (fwrite(p->data.rate, sizeof(rate), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_history:
			if (fwrite(p->data.history, sizeof(history), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_card:
			if (fwrite(p->data.card, sizeof(card), 1, fp)>0)
			{
				p = p->next;
			}
			break;;
		case d_attri:
			if (fwrite(p->data.card, sizeof(attribute), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		default:
			break;
		}
	}
	fclose(fp);
}

//全部保存
void saveAll() {
	save(d_admin);
	save(d_attri);
	save(d_pcType);
	save(d_cardType);
	save(d_rate);
	save(d_card);
	save(d_history);
}

//关闭资源
void close(dataType type) {
	pList p = NULL;
	switch (type)
	{
	case d_admin:
		p = getAdminHead();
		break;
	case d_attri:
		p = getAttriList();
		break;
	case d_card:
		p = getCards();
		break;
	case d_cardType:
		p = getCardTypeList();
		break;
	case d_history:
		p = getHistorys();
		break;
	case d_pc:
		if (hasLoginPC())
		{
			logoutPCAll();
		}
		if (NULL==getPCtypeList()->next)
		{
			return;
		}
		p = getPCs();
		break;
	case d_pcType:
		p = getPCtypeList();
		break;
	case d_rate:
		p = getRateList();
		break;
	case d_statistics:
		p = getStatByTime();
		break;
	default:
		p = NULL;
		break;
	}
	if (NULL==p)
	{
		return;
	}
	pList q;
	while (NULL != p->next)
	{
		q = p->next;
		free(p->data.admin);
		free(p);
		p = q;
	}
	free(p);
}

//关闭全部
void closeAll() {
	close(d_admin);
	close(d_attri);
	close(d_card);
//	close(d_cardType);
	close(d_statistics);
	close(d_history);
	close(d_pc);
	close(d_pcType);
	close(d_rate);
}

//链表交换
void swap(pList a, pList b) {
	if (a==b)
	{
		return;
	}
	data t = a->data;
	a->data = b->data;
	b->data = t;
}

//排序---可能出错
pList _sort(pList start, pList end, int length, int(*isUP)(pList a, pList b), int isNot) {
	if (0>=length)
	{
		return start;
	}
	if (8>length)
	{
		//选择排序
		pList t = start;
		while (t!=end)
		{
			pList min = t;
			pList tt = t;
			while (tt!=end)
			{
				tt = tt->next;
				if (isUP(min,tt)&&!isNot)
				{
					min = tt;
				}
				else if (isUP(tt,min)&&isNot)
				{
					min = tt;
				}
			}
			swap(min, t);
			t = t->next;
		}
		return start;
	}
	//归并排序
	pList mid = start;
	int minLength = length / 2;
	for (int i = 0; i < minLength-1; i++)
	{
		mid = mid->next;
	}
	pList midNext = mid->next;
	pList endNext = end->next;
	pList a = _sort(start, mid, minLength, isUP, isNot);
	pList b = _sort(midNext, end, length - minLength, isUP, isNot);
	midNext = b;
	pList p = (pList)malloc(sizeof(List));
	pList ret = p;
	p->next = NULL;
	p->last = NULL;
	for (int i = 0; i < length; i++)
	{
		if (a != midNext)
		{
			if (endNext == b || (isNot && isUP(a,b)) || (!isNot && isUP(b,a)))
			{
				p->next = a;
				a->last = p;
				a = a->next;
				p = p->next;
				p->next = NULL;
				continue;
			}
		}
		if(b != endNext)
		{
			p->next = b;
			b->last = p;
			b = b->next;
			p = p->next;
			p->next = NULL;
			continue;
		}
	}
	pList pp = ret->next;
	pp->last = NULL;
	free(ret);
	return pp;
}

pList sort(pList list, int (*isUP)(pList a, pList b), int isNot) {
	if (NULL==list)
	{
		return NULL;
	}
	pList s = list;
	pList e = list;
	int l = 1;
	while (NULL!=s->last)
	{
		l++;
		s = s->last;
	}
	while (NULL!=e->next)
	{
		l++;
		e = e->next;
	}
	list = _sort(s, e, l, isUP, isNot);
	while (NULL != list->last)
	{
		list = list->last;
	}
	return list;
}

//菜单帮助
int isFirst = 1;
void MenuHelp(int type) {
	int x = 16;
	int y = 6;
	gotoxy(x, y++);
	printf("=================================================");
	gotoxy(x, y++);
	printf("|                      帮助                     |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	if (0 == type)
	{
		gotoxy(x, y++);
		printf("|         pagup/pagdown ：前/后一页             |");
	}
	gotoxy(x, y++);
	printf("|               up/down ：前/后一项             |");
	gotoxy(x, y++);
	printf("|            right/left ：前/后一选项           |");
	gotoxy(x, y++);
	printf("|                   tab ：切换选项行            |");
	gotoxy(x, y++);
	printf("|                 enter ：确定                  |");
	gotoxy(x, y++);
	printf("|                   esc ：返回                  |");
	gotoxy(x, y++);
	printf("|        -------------------------------        |");
	gotoxy(x, y++);
	printf("|                    ");
	OPTION_OK(1);
	printf("                    |");
	gotoxy(x, y++);
	printf("=================================================");
	key k = isKey(getch());
	if (enter == k || esc == k)
	{
		isFirst = 0;
		return;
	}
	else
	{
		MenuHelp(type);
	}

}

//分页菜单
int initFinalPage(pList list) {
	int length = 0;
	while (NULL!=list)
	{
		length++;
		list = list->next;
	}
	return length;
}
pList paginationMenu(pList list) {
	dataType type = list->type;
	static int index = 0;
	static int option = 0;
	static int thisPage = 0;
	static int finalPage = -1;
	static int Length = 0;
	if (d_pc!=type
		&& d_card!=type
		&& d_history!=type
		&& d_statistics!=type
		&& d_statistics_more!=type
		&& d_attri!=type
		)
	{
		prPrompt("警告！", "该警告正常运行不会出现\n如果您看到该警告，请联系作者\n按任意键自动识别意图并继续");
		getch();
		return scrollMenu(list);
	}
	if (-1==finalPage)
	{
		Length = initFinalPage(list);
		finalPage = (Length - 1) / 10;
	}
	thisPage = finalPage < thisPage ? finalPage : thisPage;
	if (thisPage == finalPage && (Length-1)%10<index)
	{
		index = (Length-1) % 10;
	}
	pList p = list;
	pList ret = NULL;
	pList op = list;
	int length = 0;
	int optionLength = 0;
	myCls();
	switch (type)
	{
	case d_pc:
		printf("\n                             ---===上/下机===---\n");
		printf("\n-------------+--------------------+--------------------+------------------------");
		printf("\n      id     |        类型        |      当前用户      |      上机时间      ");
		printf("\n-------------+--------------------+--------------------+------------------------");
		optionLength = 8;
		break;
	case d_card:
		printf("\n                          ---===会员卡管理===---\n");
		printf("\n-------------------+--------------------+--------------------+------------------");
		printf("\n        id         |        类型        |       用户名       |      余额    ");
		printf("\n-------------------+--------------------+--------------------+------------------");
		optionLength = 10;
		break;
	case d_history:
		printf("\n                           ---===历史记录===---\n");
		printf("\n----------------------+-----------------+---------------------------------------");
		printf("\n         操作类型     |      操作人     |                时间               ");
		printf("\n----------------------+-----------------+---------------------------------------");
		optionLength = 6;
		break;
	case d_statistics_more:
		optionLength--;
	case d_statistics:
		printf("\n                               ---===统计===---\n");
		printf("\n----------------------+-------------------+-------------------------------------");
		printf("\n         时间         |      上机金额     |                充值金额             ");
		printf("\n----------------------+-------------------+-------------------------------------");
		optionLength += 6;
		break;
	case d_attri:
		printf("\n                               ---===设置===---\n");
		printf("\n----------------------------------+---------------------------------------------");
		printf("\n                    设置项        |               设置值                        ");
		printf("\n----------------------------------+---------------------------------------------");
		optionLength += 5;
		break;
	default:
		return NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->data.admin)
			{
				length++;
				switch (type)
				{
				case d_pc:
					prPC(p->data.pc, i == index);
					break;
				case d_card:
					prCard(p->data.card, i == index);
					break;
				case d_history:
					prHistory(p->data.history, i == index);
					break;
				case d_statistics:
					prStatByTime(p->data.statistics, i == index);
					break;
				case d_statistics_more:
					prStatMoreByTime(p->data.statistics, i == index);
					break;
				case d_attri:
					prAttri(p->data.attri, i == index);
					break;
				default:
					break;
				}
				if (i == index)
				{
					op = p;
				}
				p = p->next;
				continue;
			}
			i--;
			p = p->next;
		}
		else {
			switch (type)
			{
			case d_pc:
				printf("\n             |                    |                    |                       "); 
				break;
			case d_card:
				printf("\n                   |                    |                    |                  ");
				break;
			case d_history:
				printf("\n                      |                 |                                       ");
				break;
			case d_statistics:
			case d_statistics_more:
				printf("\n                      |                   |                                     ");
				break;
			case d_attri:
				printf("\n                                  |                                             ");
				break;
			default:
				break;
			}
		}
	}
	switch (type)
	{
	case d_pc:
		printf("\n-------------+--------------------+--------------------+------------------------");
		break;
	case d_card:
		printf("\n-------------------+--------------------+--------------------+------------------");
		break;
	case d_history:
		printf("\n----------------------+-----------------+---------------------------------------");
		break;
	case d_statistics:
	case d_statistics_more:
		printf("\n----------------------+-------------------+-------------------------------------");
		break;
	case d_attri:
		printf("\n----------------------------------+---------------------------------------------");
		break;
	default:
		break;
	}
	printf("                              %5d / %-5d\n", thisPage+1, finalPage+1);
	printf("\n                  ");
	prOption("首  页", 0 == option, 9);
	printf("   ");
	prOption("上一页", 1 == option, 9);
	printf("   ");
	prOption("下一页", 2 == option, 9);
	printf("   ");
	prOption("尾  页", 3 == option, 9);
	switch (type)
	{
	case d_pc:
		printf("\n\n           ");
		prOption("转到网吧规模", 4 == option, 18);
		printf(" ");
		if (NULL==op->data.pc->user)
		{
			prOption("上机", 5 == option, 6);
		}
		else
		{
			prOption("下机", 5 == option, 6);
		}
		printf("   ");
		prOption("详细", 6 == option, 6);
		printf("   ");
		prOption("筛选", 7 == option, 6);
		printf("   ");
		prOption("完成", 8 == option, 6);
		break;
	case d_card:
		printf("\n\n       ");
		prOption("新建", 4 == option, 6);
		printf("    ");
		prOption("删除", 5 == option, 6);
		printf("    ");
		prOption("充值", 6 == option, 6);
		printf("    ");
		prOption("详细", 7 == option, 6);
		printf("    ");
		prOption("筛选", 8 == option, 6);
		printf("    ");
		prOption("排序", 9 == option, 6);
		printf("    ");
		prOption("完成", 10 == option, 6);
		break;
	case d_history:
		printf("\n\n                 ");
		prOption("详细", 4 == option, 6);
		printf("            ");
		prOption("筛选", 5 == option, 6);
		printf("            ");
		prOption("完成", 6 == option, 6);
		break;
	case d_statistics:
		printf("\n\n                    ");
		prOption("更多", 4 == option, 6);
		printf("            ");
		prOption("详细", 5 == option, 6);
		printf("            ");
		prOption("完成", 6 == option, 6);
		break;
	case d_statistics_more:
		printf("\n\n                          ");
		prOption("更多", 4 == option, 6);
		printf("                ");
		prOption("完成", 5 == option, 6);
		break;
	case d_attri:
		printf("\n\n                         ");
		prOption("修改", 4 == option, 6);
		printf("                  ");
		prOption("完成", 5 == option, 6);
		break;
	default:
		break;
	}
	if (isFirst)
	{
		MenuHelp(0);
		return paginationMenu(list);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)		//处理按键类型
	{
	case number:
	{
		index = in - '0';
		break;
	}
	case up:
		index--;
		if (0 > index)
		{
			index = length-1;
		}
		break;
	case down:
		index++;
		if (length <= index)
		{
			index = 0;
		}
		break;
	case tab:
		if (4 > option)
		{
			option += 4;
		}
		else
		{
			option -= 4;
		}
		break;
	case left:
		option--;
		if (0 > option)
		{
			option = optionLength;
		}
		break;
	case right:
		option++;
		if (optionLength < option)
		{
			option = 0;
		}
		break;
	case pgup:
		if (0>=thisPage)
		{
			break;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->last;
		}
		thisPage--;
		break;
	case pgdn:
		if (finalPage<=thisPage)
		{
			break;
		}
		for (int i = 0; i < 10; i++)
		{
			list = list->next;
		}
		thisPage++;
		break;
	case enter:
		//处理选择项
		switch (option)		
		{
		case 0:	//首页
			for (int i = 0; i < 10 * thisPage; i++)
			{
				list = list->last;
			}
			thisPage = 0;
			break;
		case 1:	//上一页
			if (0 >= thisPage)
			{
				break;
			}
			for (int i = 0; i < 10; i++)
			{
				list = list->last;
			}
			thisPage--;
			break;
		case 2:	//下一页
			if (finalPage <= thisPage)
			{
				break;
			}
			for (int i = 0; i < 10; i++)
			{
				list = list->next;
			}
			thisPage++;
			break;
		case 3:	//尾页
			for (int i = 0; i < 10 * (finalPage - thisPage); i++)
			{
				list = list->next;
			}
			thisPage = finalPage;
			break;
		case 4:
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//网吧规模
				if ((isPower(getUser()->power, 14) || isPower(getUser()->power, 15) || isPower(getUser()->power, 16)))
				{
					prPrompt("即将进入网吧规模", "按任意键继续");
					getch();
					system("title 网吧规模管理");
					scrollMenu(getPCtypeList());
					if (isEditPCType())
					{
						thisPage = 0;
						finalPage = -1;
						list = getPCs();
					}
					system("title 上/下机");
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			case d_card:		//新建
			{
				if (isPower(getUser()->power, 0))
				{
					list = newCard(list);
					finalPage = -1;
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			case d_history:		//详细
				showHistory(op->data.history);
				break;
			case d_statistics:			//更多信息
				showStatByTime(op->data.statistics, 0);
				break;
			case d_statistics_more:		//更多信息
				showStatByTime(op->data.statistics, 1);
				break;
			case d_attri:
				editAttri(op->data.attri);
				break;
			default:
				break;
			}
			break;
		case 5:
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//上/下机
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				int tin = index;
				int top = option;
				index = 0;
				option = 9;
				thisPage = 0;
				finalPage = -1;
				logPC(op->data.pc);
				index = tin;
				option = top;
				thisPage = ttp;
				finalPage = tfp;
				break;
			}
			case d_card:		//删除
				if (isPower(getUser()->power, 1))
				{
					pList temp = (NULL != op->next) ? op->next : op->last;
					delCard(op);
					op = temp;
					finalPage = -1;
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			case d_history:		//筛选
			{
				pList t = NULL;
				index = 0;
				thisPage = 0;
				finalPage = -1;
				t = selectToHistory();
				if (NULL == t || NULL == t->data.history)
				{
					prPrompt("注意", "当前筛选结果为空\n将显示全部结果\n按任意键继续");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.history = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			case d_statistics:	//详细
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				int tin = index;
				int top = option;
				index = 0;
				option = 0;
				thisPage = 0;
				finalPage = -1;
				pList ms = getMoreStatByTime(op);
				paginationMenu(ms);
				index = tin;
				option = top;
				thisPage = ttp;
				finalPage = tfp;
				pList q = ms->next;
				while (NULL != q)
				{
					free(ms);
					ms = q;
					q = q->next;
				}
				break;
			}
			case d_statistics_more:	//退出
			case d_attri:
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		case 6:
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//详细
				showPC(op->data.pc);
				break;
			case d_card:		//充值
				recharge(op->data.card);
				break;
			case d_history:		//退出
			case d_statistics:
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		case 7:	
		{
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//筛选
			{
				pList t = NULL;
				finalPage = -1;
				thisPage = 0;
				index = 0;
				option = 0;
				t = selectToPC();
				if (NULL==t||NULL==t->data.pc)
				{
					prPrompt("注意", "当前筛选结果为空\n将显示全部结果\n按任意键继续");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.pc = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			case d_card:		//详细
			{
				pList typeList = getCardTypeList();
				while (0 != strcmp(op->data.card->type, typeList->data.cardType->name) && NULL != typeList->next)
				{
					typeList = typeList->next;
				}

				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, op->data.card->password);
				strcpy(pass2, op->data.card->password);
				showCard(0, op->data.card, "", pass1, pass2);
				strcpy(pass1, "***************");
				strcpy(pass2, "***************");
				free(pass1);
				free(pass2);

				pList typeList2 = getCardTypeList();
				while (0 != strcmp(op->data.card->type, typeList2->data.cardType->name) && NULL != typeList2->next)
				{
					typeList2 = typeList2->next;
				}
				char *money = (char *)malloc(sizeof(char) * 64);
				int iMoney = typeList2->data.cardType->price - typeList->data.cardType->price;
				if (iMoney>0)
				{
					sprintf(money, "请收取%.2lf注册费用\n(非充值)\n按任意键继续", iMoney / 100.0);
					prPrompt("注册", money);
					getch();
				}
				else if (iMoney<0)
				{
					sprintf(money, "请返还%.2lf注册费用\n按任意键继续", -iMoney / 100.0);
					prPrompt("注册", money);
					getch();
				}
				free(money);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 8:	
		{
			switch (type)
			{
			case d_pc:			//退出
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			case d_card:		//筛选
			{
				pList t = NULL;
				finalPage = -1;
				thisPage = 0;
				index = 0;
				option = 0;
				t = selectToCard();
				if (NULL == t || NULL == t->data.card)
				{
					prPrompt("注意", "当前筛选结果为空\n将显示全部结果\n按任意键继续");
					getch();
					ret = paginationMenu(list);
				}
				else
				{
					ret = paginationMenu(t);
					pList q = t->next;
					while (NULL != q)
					{
						t->data.card = NULL;
						free(t);
						t = q;
						q = q->next;
					}
				}
				index = 0;
				option = 0;
				return ret;
			}
			default:
				break;
			}
			break;
		}
		case 9:
			switch (type)
			{
			case d_card:		//排序
			{
				sortCard();
				list = getCards();
				thisPage = 0;
				break;
			}
			default:
				break;
			}
			break;
		case 10:
		{
			switch (type)
			{
			case d_card:		//退出
				index = 0;
				option = 0;
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	case esc:
	{
		index = 0;
		option = 0;
		finalPage = -1;
		thisPage = 0;
		isFirst = 1;
		return op;
	}
	default:
		break;
	}
	return paginationMenu(list);
}

//滚动菜单
pList scrollMenu(pList list) {
	dataType type = list->type;
	static int option = 0;
	if (NULL==list)
	{
		return NULL;
	}
	if (d_pcType != type
		&& d_cardType != type
		&& d_admin != type
		&& d_rate != type
		)
	{
		prPrompt("警告！", "该警告正常运行不会出现\n如果您看到该警告，请联系作者\n按任意键自动识别意图并继续");
		getch();
		return paginationMenu(list);
	}
	pList ret = NULL;
	char *nMore = (char*)malloc(160 * sizeof(char));
	int isTop = 0;
	myCls();
	switch (type)
	{
	case d_pcType:
		printf("\n\n                                      网吧规模\n\n");
		printf("                  ================================================            \n");
		printf("                        类型     |      数量      |    起始编号               \n");
		printf("                  ---------------+----------------+---------------         \n");
		strcpy(nMore, "                                 |                |                          \n");
		break;
	case d_cardType:
		printf("\n\n                                  网吧会员卡类型\n\n");
		printf("                  ================================================            \n");
		printf("                        会员卡名称       |     价格           \n");
		printf("                  -----------------------+------------------------            \n");
		strcpy(nMore, "                                         |                                 \n");
		break;
	case d_admin:
		printf("\n\n                                      管理员\n\n");
		printf("                  ================================================            \n");
		printf("             用户名    |                        权限                          \n");
		printf("                  -----+------------------------------------------         \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                                  网吧收费标准\n\n");
		printf("                  ================================================            \n");
		printf("                    电脑类型   |     会员卡类型     |     收费标准            \n");
		printf("                  -------------+--------------------+-------------            \n");
		strcpy(nMore, "                               |                    |                         \n");
		break;
	default:
		return NULL;
	}
	pList p = list;
	for (int i = 0; i < 3; i++)
	{
		if (NULL!=p && NULL!=p->last)
		{
			p = p->last;
		}
		else
		{
			isTop++;
		}
	}
	if(0!=isTop)
	{
		int top = isTop;
		while ((top--)>0)
		{
			printf(nMore);
		}
	}
	for (int i = isTop; i < 7; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->data.admin)
			{
				if (3 == i)
				{
					ret = p;
				}
				switch (type)
				{
				case d_pcType:
					if (3 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					prPCtype(p->data.pcType);
					if (3 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					break;
				case d_cardType:
					if (3 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					prCardType(p->data.cardType);
					if (3 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					break;
				case d_admin:
					if (3 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					prUser(p->data.admin);
					if (3 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					break;
				case d_rate:
					if (3 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					prRate(p->data.rate);
					if (3 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					break;
				default:
					return ret;
				}
			}
			p = p->next;
		}
		if (6==i && NULL!=p)
		{
			printf(nMore);
		}
		else if(NULL==p)
		{
			printf(nMore);
		}
	}
	printf("                  ================================================            \n");
	printf("\n\n      ");
	prOption("  新建  ", 0 == option, 13);
	printf(" ");
	prOption("  删除  ", 1 == option, 13);
	printf(" ");
	prOption("  详细  ", 2 == option, 13);
	printf(" ");
	prOption("  帮助  ", 3 == option, 13);
	printf(" ");
	prOption("  完成  ", 4 == option, 13);
	if (d_rate == type)
	{
		printf("\n\n                    ");
		prOption("  上移  ", 5 == option, 13);
		printf("               ");
		prOption("  下移  ", 6 == option, 13);
		printf(" ");
	}
	free(nMore);
	if (isFirst)
	{
		MenuHelp(1);
		return scrollMenu(list);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)	//处理按键类型
	{
	case up:
		if (NULL!=list->last)
		{
			list = list->last;
		}
		break;
	case down:
		if (NULL != list->next)
		{
			list = list->next;
		}
		break;
	case left:
		if (0==option)
		{
			option = d_rate == type ? 7 : 5;
		}
		option--;
		break;
	case tab:
	case right:
		if ((d_rate == type ? 6 : 4) == option)
		{
			option = -1;
		}
		option++;
		break;
	case symbol:
		if ('+' == in && d_rate == type)
		{
			if (isPower(getUser()->power, 5))
			{
				if (NULL != list->last)
				{
					if (NULL == list->last->last)
					{
						prPrompt("警告", "默认的计费方案必须是第一个\n按任意键继续");
						getch();
					}
					else
					{
						swap(list, list->last);
						list = list->last;
					}
				}
			}
			else
			{
				prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
				getch();
			}
		}
		if ('-' == in && d_rate == type)
		{
			if (isPower(getUser()->power, 5))
			{
				if (NULL==list->last)
				{
					prPrompt("警告", "默认的计费方案必须是第一个\n按任意键继续");
					getch();
				}
				else if (NULL!=list->next)
				{
					swap(list, list->next);
					list = list->next;
				}
			}
			else
			{
				prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
				getch();
			}
		}
		ret = scrollMenu(list);
		break;
	case enter:
	{
		switch (option)		//处理选择项
		{
		case 0:
		{
			switch (type)		//处理链表类型
			{
			case d_pcType:
			{
				if (isPower(getUser()->power,14))
				{
					if (!editPCTypePS(0))
					{
						break;
					}
					list = newPCType(list);
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			case  d_cardType:
			{
				if (isPower(getUser()->power, 11))
				{
					list = newCardType(list);
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			case d_admin:
			{
				if (isPower(getUser()->power, 8))
				{
					list = newAdmin(list);
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			case d_rate:
			{
				if (isPower(getUser()->power, 3))
				{
					list = newRate(list);
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case 1:
			if ((isPower(getUser()->power, 15) && d_pcType == type)
					|| (isPower(getUser()->power, 12) && d_cardType == type)
					|| (isPower(getUser()->power, 9) && d_admin == type)
					|| (isPower(getUser()->power, 4) && d_rate == type)
				)
			{
				if (d_pcType == type)
				{
					if (!editPCTypePS(0))
					{
						break;
					}
				}
				setEdit(1);
				if (NULL!=list->last)
				{
					pList temp = NULL!=list->next? list->next : list->last;
					list->last->next = list->next;
					if (NULL != list->next)
					{
						list->next->last = list->last;
					}
					switch (type)
					{
					case d_pcType:
						getPCtypeList()->data.pcType->num -= list->data.pcType->num;						
						addHistory(D_PC_TYPE_T, list->data, 0);
						break;
					case d_cardType:
						addHistory(D_CARD_T, list->data, 0);
						break;
					case d_admin:
						addHistory(D_ADMIN_T, list->data, 0);
						break;
					case d_rate:
						addHistory(D_RATE_T, list->data, 0);
						break;
					default:
						break;
					}
					free(list);
					list = temp;
				}
				else
				{
					if (d_pcType == type || d_cardType == type || d_rate == type)
					{
						prPrompt("删除失败", "禁止删除默认选项\n按任意键返回");
						getch();
					}
					else if (d_admin == type)
					{
						prPrompt("删除失败", "禁止删除超级管理员\n按任意键返回");
						getch();
					}
				}
			}
			else
			{
				prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
				getch();
			}
			break;
		case 2:
		{
			if (NULL==list->last)
			{
				if (d_admin==type)
				{
					if (strcmp(getUser()->name,"root")==0)
					{
						char *pass = (char*)malloc(sizeof(char) * 32);
						pass[0] = '\0';
						prPrompt("请输入超级管理员的密码", "\n按enter键确认，按esc取消");
						key key = input(32, 12, pass, 1, NUM | LETTER | SYMBOL, NULL);
						if (enter==key)
						{
							while (strcmp(pass,getUser()->password)!=0 
								&& enter != key && esc != key)
							{
								prPrompt("密码错误，请重新输入", "\n按enter键确认，按esc取消");
								key = input(32, 12, pass, 1, NUM | LETTER | SYMBOL, NULL);
							}
						}
						else
						{
							break;
						}
						if (esc==k)
						{
							break;
						}
						prPrompt("提示", "除密码外的任何修改都不会保存\n按任意键继续");
						getch();
					}
					else
					{
						prPrompt("禁止！", "只有超级管理员可以修改超级管理员\n按任意键继续");
						getch();
						break;
					}
				}
				else
				{
					prPrompt("禁止！！", "禁止修改默认选项\n按任意键继续");
					getch();
					break;
				}
			}
			switch (type)		//处理链表类型
			{
			case d_pcType:
				if (!editPCTypePS(0))
				{
					break;
				}
				setEdit(1);
				editPCtype(0, list->data.pcType);
				addHistory(U_PC_TYPE_T, list->data, 0);
				break;
			case  d_cardType:
				editCardType(0, list->data.cardType);
				addHistory(U_CARD_TYPE_T, list->data, 0);
				break;
			case d_admin:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, list->data.admin->password);
				strcpy(pass2, list->data.admin->password);
				editUser(0, list->data.admin,pass1,pass2);
				free(pass1);
				free(pass2);
				addHistory(U_ADMIN_T, list->data, 0);
				if (NULL==list->last)
				{
					list->data.admin->power = ~0;
					strcpy(list->data.admin->name, "root");
				}
				break;
			}
			case d_rate:
			{
				int a[] = { 0,0 };
				editRate(0, a, list->data.rate);
				addHistory(U_RATE_T, list->data, 0);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 3:
			if (d_admin==type)
			{
				helpFromUser();
			}
			MenuHelp(1);
			getch();
			return scrollMenu(list);
			break;
		case 4:
			isFirst = 1;
			option = 0;
			return ret;
		case 5:
			if (isPower(getUser()->power, 5))
			{
				if (NULL != list->last)
				{
					if (NULL == list->last->last)
					{
						prPrompt("警告", "默认的计费方案必须是第一个\n按任意键继续");
						getch();
					}
					else
					{
						swap(list, list->last);
						list = list->last;
					}
				}
			}
			else
			{
				prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
				getch();
			}
			break;
		case 6:
			if (isPower(getUser()->power, 5))
			{
				if (NULL == list->last)
				{
					prPrompt("警告", "默认的计费方案必须是第一个\n按任意键继续");
					getch();
				}
				else if (NULL != list->next)
				{
					swap(list, list->next);
					list = list->next;
				}
			}
			else
			{
				prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
				getch();
			}
			break;
		default:
			break;
		}
		ret = scrollMenu(list);
		return ret;
	}
	case esc:
		option = 0;
		isFirst = 1;
		return ret;
	default:
		break;
	}
	return scrollMenu(list);
}
