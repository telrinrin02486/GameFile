
#include "GameMain.h"

int main(int argc, char *argv[]) {

	GameMain& gm = GameMain::Instance();
	gm.Run();
	return 0;
}