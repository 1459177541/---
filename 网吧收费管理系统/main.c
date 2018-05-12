#include"config.h"
/*****************************************************
 *
 * 程序入口
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
	system("title 登陆");
	login(user,1,"");
	prPrompt("退出中", "正在关闭资源");
	free(user);
	closeAll();
	prPrompt("已成功关闭", "感谢您的使用");
	gotoxy(31, 13);
	return 0;
}
