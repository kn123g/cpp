#include<iostream>
class Game {
public: int gid;
public: char* gname;
// should be implemented in child class
public:virtual void show() = 0;
};

class Player : public Game {
public: char* pname;
public: int pid;
// override keyword is optional throw error when method is not declared in parent class
public: void show() override {
	std::cout << "Game\t" << Game::gname << "\tPlayer\t" << pname << std::endl;
}
};

void interfaceMain() {
	std::cout << "interface_pure_function output\n";
	Player player;
	player.gid = 1;
	char gname[] = { 'f', 'o', 'o', 't', 'b', 'a','l','l','\0' };
	player.gname = gname;
	player.pid = 1;
	char pname[] = { 'k', 'a', 'r', 't', 'h', 'i','\0' };
	player.pname = pname;
	player.show();
	std::cout << '\n';
}

