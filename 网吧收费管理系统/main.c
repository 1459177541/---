/*****************************************************
 *
 * �������
 *
 * version: 3.3
 *
 *****************************************************/
#include"config.h"
int main() {
	//��ʼ��
	system("mode con cols=80 lines=24");
	int isFirstRun = initAdminList();
	if (initAttri())
	{
		setting();
		if (!isFirstRun)
		{
			myCls();
			prPrompt("ע�⣡", "��⵽�����ļ�����\n������ΪĬ������\n�����������");
			getch();
		}
	}
	if (isFirstRun)
	{
		initialization();
	}
	//��½�����˵�
	pAdmin user = (pAdmin)malloc(sizeof(admin));
	user->name[0] = '\0';
	user->password[0] = '\0';
	system("title ��½");
	login(user,1,"");
	//�˳�
	prPrompt("�˳���", "���ڹر���Դ");
	free(user);
	closeAll();
	prPrompt("�ѳɹ��ر�", "��л����ʹ��");
	gotoxy(31, 13);
	return 0;
}
