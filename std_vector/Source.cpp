#include<iostream>
#include<vector>

class Player {
public: std::string name;
public: int id;
};
//overloaded binary operator
 std::ostream& operator<<(std::ostream& stream, const Player& player) {
	stream << player.name << '\t' << player.id;
	return stream;
}


int main() {
	std::vector<Player> players;
	players.push_back({ "karthikeyan",1 });
	players.push_back({ "Kavi",2 });
	players.push_back({ "Naveen",3 });
	for (int i = 0;i < players.size();i++) {
		std::cout << players[i] << std::endl;
	}

	players.erase(players.begin() + 2);

	std::cout << "after erased 2nd player"<<std::endl;
	for (Player& player : players)
		std::cout << player << std::endl;

}