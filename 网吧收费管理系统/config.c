#include"config.h"

//����ṹ����������Ϣ
pList attributeLists = NULL;

//���ļ��ж�ȡ������Ϣ���ص��ڴ�,����ÿ������ִֻ��һ��
//return�����ļ���ȡ�ɹ�����0����ȡʧ�ܴ�������������1
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

//key����Ҫ��ȡֵ�ļ�
//return�����ݼ���ȡ��ֵ���޸ü�����NULL
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

//�޸�key��Ӧ��value�����޸ü�������
void setAttri(char *key, char *value, char *name) {
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
	strcpy(d->name, name);
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

//�޸�ֵ
void editAttri(pAttribute p) {
	prPrompt("���������õ�ֵ", "");
	char *in = (char *)malloc(sizeof(char) * 32);
	key k = input(26, 12, in, 0, INTER | LETTER | SYMBOL, NULL);
	if (enter==k)
	{
		setAttri(p->key, in, p->name);
		return;
	}
	else
	{
		editAttri(p);
	}
}

//���
void prAttri(pAttribute p, int isOption) {
	printf("\n%3s %29s |  %-32s% -3s"
		, isOption ? getAttri("L") : getAttri("NL"), p->name, p->value, isOption ? getAttri("R") : getAttri("NR"));
}
