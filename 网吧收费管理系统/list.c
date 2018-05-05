#include"config.h"

//保存
void save(dateType type) {
	FILE *fp;
	pList p = NULL;
	char fileName[14] = "";
	switch (type)
	{
	case d_admin:
		strcpy(fileName, "data\\admin");
		p = getAdminHead();
		break;
	case d_pcType:
		strcpy(fileName, "data\\pc");
		p = getPCtypeList();
		break;
	case d_cardType:
		strcpy(fileName, "data\\cardType");
		p = getCardTypeList();
		break;
	case d_rate:
		strcpy(fileName, "data\\rate");
		p = getRateList();
		break;
	case d_history:
		strcpy(fileName, "data\\history");
		p = getHistorys();
		break;
	case d_card:
		strcpy(fileName, "data\\card");
		p = getCards();
		break;
	case d_attri:
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
		if (NULL == p->date.admin)
		{
			p = p->next;
			continue;
		}
		switch (type)
		{
		case d_admin:
			if (fwrite(p->date.admin, sizeof(admin), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_pcType:
			if (fwrite(p->date.pcType, sizeof(PCtype), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_cardType:
			if (fwrite(p->date.cardType, sizeof(cardType), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_rate:
			if (fwrite(p->date.rate, sizeof(rate), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_history:
			if (fwrite(p->date.history, sizeof(history), 1, fp)>0)
			{
				p = p->next;
			}
			break;
		case d_card:
			if (fwrite(p->date.card, sizeof(card), 1, fp)>0)
			{
				p = p->next;
			}
			break;;
		case d_attri:
			if (fwrite(p->date.card, sizeof(attribute), 1, fp)>0)
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
	prPrompt("正在保存", "正在保存管理员信息");
	save(d_admin);
	prPrompt("正在保存", "正在保存配置");
	save(d_attri);
	prPrompt("正在保存", "正在保存网吧规模");
	save(d_pcType);
	prPrompt("正在保存", "正在保存会员卡类型");
	save(d_cardType);
	prPrompt("正在保存", "正在保存计费方案");
	save(d_rate);
	prPrompt("正在保存", "正在保存会员卡");
	save(d_card);
	prPrompt("正在保存", "正在保存历史记录");
	save(d_history);
}

//分页菜单
int thisPage = 0;
int finalPage = -1;
void initFinalPage(pList list) {
	int length = 0;
	while (NULL!=list)
	{
		length++;
		list = list->next;
	}
	finalPage = length/10;
}

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

pList paginationMenu(pList list, dateType type, int index, int option) {
	pList p = list;
	if (-1==finalPage)
	{
		initFinalPage(list);
	}
	pList ret = NULL;
	pList op = list;
	int length = 0;
	int optionLength = 0;
	myCls();
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pc:
		system("title 上/下机");
		printf("\n                             ---===上/下机===---\n");
		printf("\n-------------+--------------------+--------------------+------------------------");
		printf("\n      id     |        类型        |      当前用户      |      上机时间      ");
		printf("\n-------------+--------------------+--------------------+------------------------");
		optionLength = 8;
		break;
	case d_card:
		system("title 会员卡管理");
		printf("\n                          ---===会员卡管理===---\n");
		printf("\n-------------------+--------------------+--------------------+------------------");
		printf("\n        id         |        类型        |       用户名       |      余额    ");
		printf("\n-------------------+--------------------+--------------------+------------------");
		optionLength = 9;
		break;
	case d_history:
		system("title 历史记录");
		printf("\n                           ---===历史记录===---\n");
		printf("\n----------------------+-----------------+---------------------------------------");
		printf("\n         操作类型     |      操作人     |                时间               ");
		printf("\n----------------------+-----------------+---------------------------------------");
		optionLength = 6;
		break;
	case d_statistics:
		optionLength--;
	case d_statistics_more:
		system("title 统计");
		printf("\n                               ---===统计===---\n");
		printf("\n----------------------+-------------------+-------------------------------------");
		printf("\n         时间         |      上机金额     |                充值金额             ");
		printf("\n----------------------+-------------------+-------------------------------------");
		optionLength += 5;
		break;
	default:
		return NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->date.admin)
			{
				length++;
				switch (type)
				{
				case d_pc:
					prPC(p->date.pc, i == index);
					break;
				case d_card:
					prCard(p->date.card, i == index);
					break;
				case d_history:
					prHistory(p->date.history, i == index);
					break;
				case d_statistics:
					prStat(p->date.statistics, i == index);
					break;
				case d_statistics_more:
					prStatMore(p->date.statistics, i == index);
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
		prOption("上/下机", 5 == option, 12);
		printf("   ");
		prOption("详细", 6 == option, 6);
		printf("   ");
		prOption("筛选", 7 == option, 6);
		printf("   ");
		prOption("返回", 8 == option, 6);
		break;
	case d_card:
		printf("\n\n            ");
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
		prOption("返回", 9 == option, 6);
		break;
	case d_history:
		printf("\n\n                    ");
		prOption("详细", 4 == option, 6);
		printf("            ");
		prOption("筛选", 5 == option, 6);
		printf("            ");
		prOption("返回", 6 == option, 6);
		break;
	case d_statistics:
		printf("\n\n                         ");
		prOption("详细", 4 == option, 6);
		printf("                  ");
		prOption("返回", 5 == option, 6);
		break;
	case d_statistics_more:
		printf("\n\n                                           ");
		prOption("返回", 4 == option, 6);
		break;
	default:
		break;
	}
	if (isFirst)
	{
		MenuHelp(0);
		return paginationMenu(list, type, index, option);
	}
	int in = getch();
	key k = isKey(in);
	switch (k)		//处理按键类型
	{
	case number:
	{
		ret = paginationMenu(list, type, in - '0', option);
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
			ret = paginationMenu(list, type, index, option);
			return ret;
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
			ret = paginationMenu(list, type, index, option);
			return ret;
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
				prPrompt("即将进入网吧规模", "按任意键继续");
				getch();
				scrollMenu(getPCtypeList(), d_pcType, 0);
				if (isEditPCType())
				{
					clossPC();
					list = getPCs();
					setEdit(0);
				}
				break;
			case d_card:		//新建
			{
				if (isPower(getUser()->power, 0))
				{
					while (NULL==getCardTypeList()->next)
					{
						prPrompt("没有会员卡类型", "按任意键转到会员卡类型列表\n按esc键取消新建");
						key key = isKey(getch());
						if (esc == key)
						{
							return paginationMenu(list, type, index, option);							
						}
						scrollMenu(getCardTypeList(), d_cardType, 0);
					}
					char *pass1 = (char *)malloc(sizeof(char) * 16);
					char *pass2 = (char *)malloc(sizeof(char) * 16);
					pass1[0] = '\0';
					pass2[0] = '\0';
					pCard p = (pCard)malloc(sizeof(card));
					p->balance = 0.0;
					p->id = -1;
					p->idcardNum[0] = '\0';
					p->masterName[0] = '\0';
					p->password[0] = '\0';
					strcpy(p->type, getCardTypeList()->date.cardType->name);
					pList pl = list;
					while (NULL!=pl->next)
					{
						pl = pl->next;
					}
					pList ql = (pList)malloc(sizeof(List));
					ql->date.card = p;
					ql->next = NULL;
					ql->last = pl;
					ql->type = d_card;
					pl->next = ql;
					showCard(0, p, "", pass1, pass2);
					strcpy(pass1, "***************");
					strcpy(pass2, "***************");
					free(pass1);
					free(pass2);
					addHistory(C_CARD_TYPE_T, pl->date, 0);
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			}
			case d_history:		//详细
				showHistory(op->date.history);
				break;
			case d_statistics:	//详细
			{
				int	ttp = thisPage;
				int tfp = finalPage;
				thisPage = 0;
				finalPage = -1;
				pList p = getMoreStat(op);
				paginationMenu(p, d_statistics, 0, 0);
				thisPage = ttp;
				finalPage = tfp;
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			}
			case d_statistics_more:	//退出
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
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
				thisPage = 0;
				finalPage = -1;
				logPC(op->date.pc);
				thisPage = ttp;
				finalPage = tfp;
				break;
			}
			case d_card:		//删除
				if (isPower(getUser()->power, 1))
				{
					if (NULL != op->last)
					{
						pList temp = NULL != op->next ? op->next : op->last;
						op->last->next = op->next;
						if (NULL != op->next)
						{
							op->next->last = op->last;
						}
						addHistory(D_CARD_TYPE_T, op->date, 0);
						free(op);
						op = temp;
					}
					else
					{
						pCard temp = op->date.card;
						op->date.card = NULL;
						addHistory(D_CARD_TYPE_T, op->date, 0);
						free(temp);
					}
				}
				else
				{
					prPrompt("权限不足", "请尝试联系超级管理员\n按任意键返回");
					getch();
				}
				break;
			case d_history:		//筛选
				finalPage = -1;
				p = selectToHistory();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			default:
				break;
			}
			break;
		case 6:
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//详细
				showPC(op->date.pc);
				break;
			case d_card:		//充值
				recharge(op->date.card);
				break;
			case d_history:		//退出
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
			pList p;
			//处理链表类型
			switch (type)		
			{
			case d_pc:			//筛选
				finalPage = -1;
				p = selectToPC();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			case d_card:		//详细
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, op->date.card->password);
				strcpy(pass2, op->date.card->password);
				showCard(0, op->date.card, "", pass1, pass2);
				strcpy(pass1, "***************");
				strcpy(pass2, "***************");
				free(pass1);
				free(pass2);
				break;
			}
			default:
				break;
			}
			return ret;
		}
		case 8:	
		{
			switch (type)
			{
			case d_pc:			//退出
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			case d_card:		//筛选
				finalPage = -1;
				p = selectToCard();
				ret = paginationMenu(p, type, index, option);
				pList q = p->next;
				while (NULL != q)
				{
					free(p);
					p = q;
					q = q->next;
				}
				return ret;
			default:
				break;
			}
		}
		case 9:
		{
			switch (type)
			{
			case d_card:		//退出
				finalPage = -1;
				thisPage = 0;
				isFirst = 1;
				return op;
			default:
				break;
			}
		ret = paginationMenu(list, type, index, option);
		return ret;
		}
		default:
			break;
		}
		return paginationMenu(list, type, index, option);
	case esc:
	{
		finalPage = -1;
		thisPage = 0;
		isFirst = 1;
		return NULL;
	}
	default:
		break;
	}
	ret = paginationMenu(list, type, index, option);
	return ret;
}

//滚动菜单
pList scrollMenu(pList list, dateType type, int option) {
	pList ret = NULL;
	char *nMore = (char*)malloc(160 * sizeof(char));
	int isTop = 0;
	myCls();
	system("mode con cols=80 lines=24");
	switch (type)
	{
	case d_pcType:
		printf("\n\n                                 请设置您的网吧规模\n\n");
		printf("                  ================================================            \n");
		printf("                    类型         |      数量      |    起始编号               \n");
		printf("                  ---------------+----------------+---------------         \n");
		strcpy(nMore, "                                 |                |                          \n");
		break;
	case d_cardType:
		printf("\n\n                             请设置您的网吧会员卡类型\n\n");
		printf("                  ================================================            \n");
		printf("                        会员卡名称       |     价格           \n");
		printf("                  -----------------------+------------------------            \n");
		strcpy(nMore, "                                         |                                 \n");
		break;
	case d_admin:
		printf("\n\n                                   请设置管理员\n\n");
		printf("                  ================================================            \n");
		printf("             用户名    |                        权限                          \n");
		printf("                  -----+------------------------------------------         \n");
		strcpy(nMore, "                       |                                            \n");
		break;
	case d_rate:
		printf("\n\n                             请设置您的网吧收费标准\n\n");
		printf("                  ================================================            \n");
		printf("             电脑类型          |     会员卡类型     |     收费标准            \n");
		printf("                  -------------+--------------------+-------------            \n");
		strcpy(nMore, "                               |                    |                         \n");
		break;
	default:
		return NULL;
	}
	int length = (d_rate == type) ? 3 : 7;
	pList p = list;
	for (int i = 0; i < length/2; i++)
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
	for (int i = isTop; i < length; i++)
	{
		if (NULL != p)
		{
			if (NULL != p->date.admin)
			{
				if (length / 2 == i)
				{
					ret = p;
				}
				switch (type)
				{
				case d_pcType:
					if (length / 2 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					prPCtype(p->date.pcType);
					if (length / 2 == i)
					{
						printf("               ------------------+----------------+------------------         \n");
					}
					break;
				case d_cardType:
					if (length / 2 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					prCardType(p->date.cardType);
					if (length / 2 == i)
					{
						printf("               --------------------------+---------------------------         \n");
					}
					break;
				case d_admin:
					if (length / 2 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					prUser(p->date.admin);
					if (length / 2 == i)
					{
						printf("               --------+---------------------------------------------         \n");
					}
					break;
				case d_rate:
					if (length / 2 == i)
					{
						printf("               ----------------+--------------------+----------------         \n");
					}
					prRate(p->date.rate);
					if (length / 2 == i)
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
	prOption("  返回  ", 4 == option, 13);
	free(nMore);
	if (isFirst)
	{
		MenuHelp(1);
		return scrollMenu(list, type, option);
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
		ret = scrollMenu(list, type, option);
		break;
	case down:
		if (NULL != list->next)
		{
			list = list->next;
		}
		ret= scrollMenu(list, type, option);
		break;
	case left:
		if (0==option)
		{
			option = 5;
		}
		option--;
		ret = scrollMenu(list, type, option);
		break;
	case tab:
	case right:
		if (4 == option)
		{
			option = -1;
		}
		option++;
		ret = scrollMenu(list, type, option);
		break;
	case enter:
	{
		int a[] = { 0,0 };
		switch (option)		//处理选择项
		{
		case 0:
		{
			int isNULL = 0;
			pList q = list;
			if (NULL == q)
			{
				q = (pList)malloc(sizeof(List));
				q->date.admin = NULL;
				q->last = NULL;
				q->next = NULL;
				q->type = type;
				list = q;
				isNULL = 1;
			}
			while (NULL != q->next)
			{
				q = q->next;
			}
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
					pCardType p = (pCardType)malloc(sizeof(cardType));
					p->name[0] = '\0';
					p->price = 0;
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.cardType = p;
					pl->type = d_cardType;
					q->next = pl;
					editCardType(0, p);
					addHistory(C_CARD_TYPE_T, pl->date, 0);
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
					char *pass1 = (char *)malloc(sizeof(char) * 16);
					char *pass2 = (char *)malloc(sizeof(char) * 16);
					pass1[0] = '\0';
					pass2[0] = '\0';
					pAdmin p = (pAdmin)malloc(sizeof(admin));
					p->name[0] = '\0';
					p->password[0] = '\0';
					p->power = 0;
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.admin = p;
					pl->type = d_admin;
					q->next = pl;
					editUser(0, p, pass1, pass2);
					free(pass1);
					free(pass2);
					addHistory(C_ADMIN_T, pl->date, 0);
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
					pRate p = (pRate)malloc(sizeof(rate));
					p->card[0] = '\0';
					p->pc[0] = '\0';
					p->rule[0] = '\0';
					pList pl = (pList)malloc(sizeof(List));
					pl->last = q;
					pl->next = NULL;
					pl->date.rate = p;
					pl->type = d_rate;
					q->next = pl;
					editRate(0, a, p);
					if (isNULL)
					{
						list = list->next;
						pl->last = NULL;
						setRateList(pl);
					}
					addHistory(C_RATE_T, pl->date, 0);
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
						else
						{
							setEdit(1);
						}
					}
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
						addHistory(D_PC_TYPE_T, list->date, 0);
						break;
					case d_cardType:
						addHistory(D_CARD_T, list->date, 0);
						break;
					case d_admin:
						addHistory(D_ADMIN_T, list->date, 0);
						break;
					case d_rate:
						addHistory(D_RATE_T, list->date, 0);
						break;
					default:
						break;
					}
					free(list);
					list = temp;
				}
				else if (NULL!=list->next)
				{
					if (d_pcType == type || d_cardType == type)
					{
						prPrompt("删除失败", "无法删除该项\n按任意键返回");
						getch();
					}
					else
					{
						pList temp = list->next;
						list->next->last = NULL;
						switch (type)
						{
						case d_pcType:
							addHistory(D_PC_TYPE_T, list->date, 0);
							break;
						case d_cardType:
							addHistory(D_CARD_T, list->date, 0);
							break;
						case d_admin:
							addHistory(D_ADMIN_T, list->date, 0);
							break;
						case d_rate:
							addHistory(D_RATE_T, list->date, 0);
							break;
						default:
							break;
						}
						free(list);
						list = temp;
					}

				}
				else
				{
					list = NULL;
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
			switch (type)		//处理链表类型
			{
			case d_pcType:
				if (!editPCTypePS(0))
				{
					break;
				}
				setEdit(1);
				editPCtype(0, list->date.pcType);
				addHistory(U_PC_TYPE_T, list->date, 0);
				break;
			case  d_cardType:
				editCardType(0, list->date.cardType);
				addHistory(U_CARD_TYPE_T, list->date, 0);
				break;
			case d_admin:
			{
				char *pass1 = (char *)malloc(sizeof(char) * 16);
				char *pass2 = (char *)malloc(sizeof(char) * 16);
				strcpy(pass1, list->date.admin->password);
				strcpy(pass2, list->date.admin->password);
				editUser(0, list->date.admin,pass1,pass2);
				free(pass1);
				free(pass2);
				addHistory(U_ADMIN_T, list->date, 0);
				break;
			}
			case d_rate:
				editRate(0, a, list->date.rate);
				addHistory(U_RATE_T, list->date, 0);
				break;
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
			break;
		case 4:
			isFirst = 1;
			return ret;;
		default:
			break;
		}
		ret = scrollMenu(list, type, option);
		return ret;
	}
	case esc:
		isFirst = 1;
		return ret;
	default:
		break;
	}
	return ret;
}
