#include"config.h"
/*****************************************************
 *
 * �������
 *
 * version:3.0
 *
 *****************************************************/
int main() {
	if (initAttri() || initAdminList())
	{
		initialization();
	}
	pAdmin user = (pAdmin)malloc(sizeof(admin));
	user->name[0] = '\0';
	user->password[0] = '\0';
	login(user,1,"");
}
