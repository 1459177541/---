#include"config.h"
/*****************************************************
 *
 * �������
 *
 * version: 3.1
 *
 *****************************************************/
int main() {
	system("mode con cols=80 lines=24");
	if (initAttri() || initAdminList())
	{
		initialization();
	}
	pAdmin user = (pAdmin)malloc(sizeof(admin));
	user->name[0] = '\0';
	user->password[0] = '\0';
	system("title ��½");
	login(user,1,"");
	prPrompt("�˳���", "���ڹر���Դ");
	free(user);
	closeAll();
	prPrompt("�ѳɹ��ر�", "��л����ʹ��");
	gotoxy(31, 13);
	return 0;
}
