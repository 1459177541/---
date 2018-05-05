#include"config.h"

//链表结构保存配置信息
pList attributeLists = NULL;

//从文件中读取配置信息加载到内存,程序每次运行只执行一次
//return：从文件读取成功返回0；读取失败创建空链表并返回1
int initAttri() {
	FILE *fp;
	if (NULL == (fp = fopen("data\\config", "rb")))
	{
		return 1;
	}
	pAttribute p = (pAttribute)malloc(sizeof(attribute));
	if (NULL == attributeLists && fread(p, sizeof(attribute), 1, fp)>0)
	{
		attributeLists = (pList)malloc(sizeof(List));
		attributeLists->next = NULL;
		attributeLists->last = NULL;
		attributeLists->type = d_attri;
		attributeLists->date.card = p;
	}
	pList q = attributeLists;
	pList o = (pList)malloc(sizeof(List));
	p = (pAttribute)malloc(sizeof(attribute));;
	while (fread(p, sizeof(attribute), 1, fp)>0)
	{
		o->type = d_attri;
		o->date.card = p;
		o->last = q;
		o->next = NULL;
		q->next = o;
		q = q->next;
		p = (pAttribute)malloc(sizeof(attribute));
		o = (pList)malloc(sizeof(List));
	}
	free(p);
	free(o);
	fclose(fp);
	return 0;
}

pList getAttriList() {
	if (NULL==attributeLists)
	{
		initAttri();
	}
	return attributeLists;
}

//key：需要获取值的键
//return：依据键获取的值，无该键返回NULL
char* getAttri(char * key) {
	pList p = attributeLists;
	while (NULL!=p)
	{
		if (0 == strcmp(p->date.attri->key,key))
		{
			return p->date.attri->value;
		}
		p = p->next;
	}
	return NULL;
}

//修改key对应的value，若无该键则新增
void setAttri(char *key, char *value) {
	pList p = attributeLists;
	while (NULL != p && NULL != p->next)
	{
		if (0==strcmp(p->date.attri->key, key))
		{
			strcpy(p->date.attri->value, value);
			return;
		}
		p = p->next;		
	}
	if (NULL!=p && 0 == strcmp(p->date.attri->key, key))
	{
		strcpy(p->date.attri->value, value);
		return;
	}
	pAttribute d = (pAttribute)malloc(sizeof(attribute));
	strcpy(d->key, key);
	strcpy(d->value, value);
	if (NULL!=attributeLists)
	{
		pList q = (pList)malloc(sizeof(List));
		q->last = p;
		q->next = NULL;
		q->type = d_attri;
		q->date.attri = d;
		p->next = q;
	}
	else
	{
		attributeLists = (pList)malloc(sizeof(List));
		attributeLists->last = p;
		attributeLists->next = NULL;
		attributeLists->type = d_attri;
		attributeLists->date.attri = d;
	}
}
