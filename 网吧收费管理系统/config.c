#include"config.h"
typedef struct attribute{
	char key[32];
	char value[64];
	struct attribute *next;
}attribute,* pAttribute;

//����ṹ����������Ϣ
pAttribute attributeHead;

//���ļ��ж�ȡ������Ϣ���ص��ڴ�,����ÿ������ִֻ��һ��
//return�����ļ���ȡ�ɹ�����0����ȡʧ�ܴ�������������1
int initAttri() {
	
	return 0;
}

//key����Ҫ��ȡֵ�ļ�
//return�����ݼ���ȡ��ֵ���޸ü�����NULL
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

//�޸�key��Ӧ��value�����޸ü�������
void setAttri(char *key, char *value) {

}

//��������Ϣ���浽/data/config�ļ���
//�������п�ִ�ж��
void saveAttri() {

}

//�ͷ���Դ������ÿ������ִֻ��һ��
void closeAttri() {

}
