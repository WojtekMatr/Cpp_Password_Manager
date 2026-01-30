#include "ManagerHeader.h"
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <fstream>





int main() {
	std::cout << "Paswword manager -- Without GUI, next time i'll sit on this and learn Cpp Gui" << std::endl;
	std::ifstream in("output.json");
	nlohmann::json j = in ? nlohmann::json::parse(in) : nlohmann::json::array();
	std::vector<User> users;
	if (in) {
		std::cout << "wykonuje sie";
		 users = j.get<std::vector<User>>();
		for (const auto& u : users) {
			std::cout << u.name << " " << "\n";
		}
	}
	{
		std::unique_ptr<User> user = std::make_unique<User>();
		std::cout << "1. Log in" << std::endl;
		std::cout << "2. Sign in" << std::endl;
		std::cout << "3. Password reset" << std::endl;
		int n;
		std::cin >> n;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		{
			std::unique_ptr<std::string> pass = std::make_unique<std::string>();
			switch (n) {
			case 1: {

				std::cout << "User name: " << std::endl;
				std::getline(std::cin, (user->name));
				std::cout << "Password: " << std::endl;
				std::getline(std::cin, (*pass));
				auto it = std::find_if(users.begin(), users.end(), [&](User a) {
					return a.name == user->name;
					});
				if (it != users.end()) {
					std::cout << "Find him!" << std::endl;

					std::cout <<"Hash: "<< (it->pwhash).c_str() <<" haslo: " <<(*pass).c_str() <<" dlugosc "<< strlen((*pass).c_str()) << " Prawdziwosc "<< crypto_pwhash_str_verify(
						(it->pwhash).c_str(),
						(*pass).c_str(), strlen((*pass).c_str()));

					if (crypto_pwhash_str_verify(
						(it->pwhash).c_str(),
						(*pass).c_str(), strlen((*pass).c_str())
					) == 1) {
						std::cout << "Dobre haslo" << std::endl;
					}
				}

				break;
			}
			case 2:
				std::cout << "User name: " << std::endl;
				std::getline(std::cin, (user->name));
				std::cout << "Password: " << std::endl;
				std::getline(std::cin, (*pass));
				std::cout << "Your email address: " << std::endl;
				std::getline(std::cin, (user->email));
			    char pwhash[crypto_pwhash_STRBYTES];

				crypto_pwhash_str(
					pwhash,
					pass->c_str(),
					pass->size(),
					crypto_pwhash_OPSLIMIT_MODERATE,
					crypto_pwhash_MEMLIMIT_MODERATE
				);
				std::cout << pwhash<<std::endl;
				//memcpy((user->pwhash).c_str(), pwhash, crypto_pwhash_STRBYTES);
				user->pwhash = pwhash;
				std::cout << *pass;
				j.push_back({ {"user", user->name}, {"code", user->pwhash}, {"email", user->email} });

				break;
			case 3:
				std::cout << "Reseting password!" << std::endl;
				std::cout << "User name\n";
				std::getline(std::cin, (user->name));
				std::cout << """Email\n";
				std::getline(std::cin, (user->email));
				break;





			}
			std::ofstream file("output.json");
			if (file.is_open()) {
				file << j.dump(4); 
				file.close();
			}

		}










	}


}