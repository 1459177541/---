#pragma once
/*****************************
 *
 * 声明文件，以便调用
 *
 *****************************/
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>

//左移运算
#define SHL(x) (1<<x)

//时间格式
#define DATE SHL(0)
#define TIME SHL(1)

//时间
typedef struct tm tm, * pTm;

//管理员
typedef struct {
	char name[32];
	char password[32];
	int power;			//权限码，使用二进制保存对应权限
}admin,* pAdmin;

//会员卡类型
typedef struct {
	char name[16];
	double price;
}cardType,* pCardType;

//会员卡
typedef struct {
	char type[16];
	int id;
	char masterName[16];
	char idcardNum[24];
	char password[16];
	double balance;
}card,* pCard;

//电脑类型
typedef struct {
	char type[16];
	int num;
	int startId;
}PCtype,* pPCtype;

//电脑
typedef struct {
	char type[16];
	int id;
	pCard user;
	pTm startTime;
}PC,* pPC;

//收费标准
typedef struct {
	char pc[16];
	char card[16];
	pTm startTime;
	pTm endTime;
	char rule[16];
}rate,* pRate;

//历史记录类型
typedef enum {
	 C_CARD_T, D_CARD_T, U_CARD_T
	,C_RATE_T, D_RATE_T, U_RATE_T
	,C_ADMIN_T, D_ADMIN_T, U_ADMIN_T
	,C_CARD_TYPE_T, D_CARD_TYPE_T, U_CARD_TYPE_T
	,C_PC_TYPE_T, D_PC_TYPE_T, U_PC_TYPE_T
	,UP_T, DOWN_T
}historyType;

//记录
typedef struct {
	historyType type;
	char text[64];
	char editor[16];
	char time[64];
}history,* pHistory;

//列表
typedef union {
	pAdmin admin;
	pPC pc;
	pCard card;
	pPCtype pcType;
	pCardType cardType;
	pRate rate;
	pHistory history;
}date,* pDate;

typedef enum {
	d_admin, d_pc, d_card, d_pcType, d_cardType, d_rate, d_history
}dateType;

typedef struct List{
	dateType type;
	date date;
	struct List *last;
	struct List *next;
}List,* pList;

//键盘按键
typedef enum {
	no, left, right, up, down, pgup, pgdn, ins, del, home, end, tab, esc, enter, backspace, number, letter, symbol
}key;

//tool
void gotoxy(int x, int y);
int stringToInt(char * string);
char * intToString(int num);
void splitString(char *src, char *ret, int start, int length);
char* printfPassword(char *password);
key isKey(int in);
	//输入限定，使用左移运算得到对应的二进制位
	#define NUM SHL(0)
	#define LETTER SHL(1)
	#define SYMBOL SHL(2)
	#define CHINESE SHL(3)
	#define OTHER SHL(4)
	#define INTER SHL(5)
int isPower(int powerCode, int point);
	//默认外观
	#define OPTION_OK(isOption) prOption("确定", isOption, 7);
	#define OPTION_CANCEL(isOption) prOption("取消/删除", isOption, 15);
char* prOption(char * name, int isOption, int length);
char * prTime(pTm p, int style);
void prTimes(pTm start, pTm end, char * text);
key input(int x, int y, char *in, int isPassword, int power, char * other);
int saveExit(int type);

//config
int initAttri();
char* getAttri(char * key);
void setAttri(char *key, char *value);
void saveAttri();
void closeAttri();

//init
int initialization();

//user
	//权限，使用左移运算得到对应的二进制位
	#define C_CARD SHL(0)
	#define D_CARD SHL(1)
	#define U_CARD SHL(2)
	#define C_RATE SHL(3)
	#define D_RATE SHL(4)
	#define U_RATE SHL(5)
	#define UP_DOWN SHL(6)
	#define HISTORY SHL(7)
	#define C_ADMIN SHL(8)
	#define D_ADMIN SHL(9)
	#define U_ADMIN SHL(10)
	#define C_CARD_TYPE SHL(11)
	#define D_CARD_TYPE SHL(12)
	#define U_CARD_TYPE SHL(13)
	#define C_PC_TYPE SHL(14)
	#define D_PC_TYPE SHL(15)
	#define U_PC_TYPE SHL(16)
	#define STATISTICS SHL(17)
pList getAdminHead();
void setRoot(pAdmin root);
void setUser(pAdmin u);
pAdmin getUser();
void prUser(pAdmin p, int isOption);
void editUser(int type, pAdmin p, char *pass1, char *pass2);
void helpFromUser();

//menu
int initAdminList();
void login(pAdmin user,int type,char* text);

//pcType
pList getPCtypeList();
void prPCtype(pPCtype p, int isOption);
void editPCtype(int type, pPCtype p);

//PC
pList getPCs();
void logoutPCAll();
void prPC(pPC p, int isOption);
pList selectToPC();
int showPC(pList p, int type);

//cardType
pList getCardTypeList();
void prCardType(pCardType p, int isOption);
void editCardType(int type, pCardType p);

//card
pCard getCard(int id);
pList getCards();
void prCard(pCard p, int isOption);
int showCard(pCard p, int type, char * text, char *password, char *password2);

//rate
pList getRateList();
double results(pPC pc, pCard user);
void prRate(pRate p, int isOption);
void editRate(int type, int option[], pRate p);

//history
pList getHistorys();
void prHistory(pHistory p, int isOption);

//list
void save(dateType type);
void saveAll();
void paginationMenu(pList list, dateType type, int index, int option);	//上/下机、会员卡、历史记录
void scrollMenu(pList list, dateType type, int option);		//电脑类型、会员卡类型、管理员、收费标准
