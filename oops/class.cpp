#include<iostream>
class Game {
	public : int gid;
	public : char *gname;
	public :void show() {
		std::cout << "Game\t" << gname <<std::endl;
	}
};

class Player : public Game {
	public: char *pname;
	public: int pid;
};

void classMain() {
	std::cout << "class output\n";
	Player player;
	player.gid = 1;
	char gname[] = {'f', 'o', 'o', 't', 'b', 'a','l','l','\0'};
	player.gname = gname;
	player.pid = 1;
	char pname[] = { 'k', 'a', 'r', 't', 'h', 'i','\0' };
	player.pname = pname;
	player.show();
	std::cout << '\n';
}

