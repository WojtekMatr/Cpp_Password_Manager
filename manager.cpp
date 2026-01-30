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
	nlohmann::json j;
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
			case 1:

				std::cout << "User name: " << std::endl;
				std::getline(std::cin, (user->name));
				std::cout << "Password: " << std::endl;
				std::getline(std::cin, (*pass));
				break;
			case 2:
				std::cout << "User name: " << std::endl;
				std::getline(std::cin, (user->name));
				std::cout << "Password: " << std::endl;
				std::getline(std::cin, (*pass));
				std::cout << "Your email address: " << std::endl;
				std::getline(std::cin, (user->name));
				unsigned char salt[crypto_pwhash_SALTBYTES];//crypto_pwhash_SALTBYTES const from libsoduim tells us how many bytes supose have salt 
				// in practice salt[0] - 1st byte salt[1] - 2nd byte...
				randombytes_buf(salt, sizeof salt);
				unsigned char pwhash[32];

				crypto_pwhash(
					pwhash,
					sizeof pwhash,
					pass->c_str(),
					pass->size(),
					salt,
					crypto_pwhash_OPSLIMIT_MODERATE,
					crypto_pwhash_MEMLIMIT_MODERATE,
					crypto_pwhash_ALG_ARGON2ID13
				);
				std::cout << pwhash<<std::endl;
				memcpy(user->pwhash, pwhash, 32);
				std::cout << *pass;
				j["user"] = user->name;
				j["kod"] = user->pwhash;
				j["e-mail"] = user->email;

				break;
			case 3:
				std::cout << "Reseting password!" << std::endl;
				std::cout << "User name\n";
				std::getline(std::cin, (user->name));
				std::cout << """Email\n";
				std::getline(std::cin, (user->email));
				break;





			}
			std::ofstream file("output.json", std::ios::out | std::ios::trunc);
			if (file.is_open()) {
				file << j.dump(4); 
				file.close();
			}

		}










	}


}