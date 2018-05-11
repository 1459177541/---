#include"config.h"
/*****************************************************
 *
 * ³ÌÐòÈë¿Ú
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
	login(user,1,"");
	free(user);
	return 0;
}
