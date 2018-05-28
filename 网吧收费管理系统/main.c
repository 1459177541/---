/*****************************************************
 *
 * 程序入口
 *
 * version: 3.3
 *
 *****************************************************/
#include"config.h"
int main() {
	//初始化
	system("mode con cols=80 lines=24");
	int isFirstRun = initAdminList();
	if (initAttri())
	{
		setting();
		if (!isFirstRun)
		{
			myCls();
			prPrompt("注意！", "检测到配置文件已损坏\n已重置为默认配置\n按任意键继续");
			getch();
		}
	}
	if (isFirstRun)
	{
		initialization();
	}
	//登陆及主菜单
	pAdmin user = (pAdmin)malloc(sizeof(admin));
	user->name[0] = '\0';
	user->password[0] = '\0';
	system("title 登陆");
	login(user,1,"");
	//退出
	prPrompt("退出中", "正在关闭资源");
	free(user);
	closeAll();
	prPrompt("已成功关闭", "感谢您的使用");
	gotoxy(31, 13);
	return 0;
}
