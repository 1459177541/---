#include"config.h"
typedef struct attribute{
	char key[32];
	char value[64];
	struct attribute *next;
}attribute,* pAttribute;

//链表结构保存配置信息
pAttribute attributeHead;

//从文件中读取配置信息加载到内存,程序每次运行只执行一次
//return：从文件读取成功返回0；读取失败创建空链表并返回1
int initAttri() {
	
	return 0;
}

//key：需要获取值的键
//return：依据键获取的值，无该键返回NULL
char* getAttri(char * key) {
	if (!strcmp("L",key))
	{
		return "[";
	}
	else if (!strcmp("R", key))
	{
		return "]";
	}
	else if (!strcmp("NL", key))
	{
		return " ";
	}
	else if (!strcmp("NR", key))
	{
		return " ";
	}
	else if (!strcmp("is", key))
	{
		return "[X]";
	}
	else if (!strcmp("isNot", key))
	{
		return "[ ]";
	}
	else if (!strcmp("checkTime", key))
	{
		return "10";
	}
	return NULL;
}

//修改key对应的value，若无该键则新增
void setAttri(char *key, char *value) {

}

//将属性信息储存到/data/config文件中
//程序运行课执行多次
void saveAttri() {

}

//释放资源，程序每次运行只执行一次
void closeAttri() {

}
