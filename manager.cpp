#include "ManagerHeader.h"
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>





int main() {
	std::cout << "Paswword manager -- Without GUI, next time i'll sit on this and learn Cpp Gui" << std::endl;

	while (1) {
		std::unique_ptr<User> user = std::make_unique<User>();
		std::cout << "1. Log in" << std::endl;
		std::cout << "2. Sign in" << std::endl;
		std::cout << "3. Password reset" << std::endl;
		int n;
		std::cin >> n;
		system("cls");
		switch (n) {
		case 1:

			std::cout << "User name: " << std::endl;
			std::getline(std::cin, (user->name));
			std::cout << "Password: " << std::endl;
			std::getline(std::cin, (user->pass));
		case 2:
			std::cout << "User name: " << std::endl;
			std::getline(std::cin, (user->name));
			std::cout << "Password: " << std::endl;
			std::getline(std::cin, (user->pass));
			std::cout << "Your email address: " << std::endl;
			std::getline(std::cin, (user->name));
			unsigned char salt[crypto_pwhash_SALTBYTES];//crypto_pwhash_SALTBYTES const from libsoduim tells us how many bytes supose have salt 
			// in practice salt[0] - 1st byte salt[1] - 2nd byte...
			randombytes_buf(salt, sizeof salt);
			unsigned char pwhash[32];

			crypto_pwhash(
				pwhash,
				sizeof pwhash,
				user->pass.c_str(),
				user->pass.size(),
				salt,
				crypto_pwhash_OPSLIMIT_MODERATE,
				crypto_pwhash_MEMLIMIT_MODERATE,
				crypto_pwhash_ALG_ARGON2ID13
			);
			std::cout << pwhash;









		}











	}


}