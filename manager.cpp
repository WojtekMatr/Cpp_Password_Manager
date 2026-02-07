#include "ManagerHeader.h"
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <limits>
#include <cstring>
//#include <bcrypt.h>




int main() {
	std::cout << "\aPaswword manager -- Without GUI, next time i'll sit on this and learn Cpp Gui" << std::endl;
	std::ifstream in("output.json");
	nlohmann::json j = in ? nlohmann::json::parse(in) : nlohmann::json::array();
	std::vector<User> users;
	bool logged = false;
	unsigned char out_key[crypto_secretbox_KEYBYTES];
	unsigned char salt[crypto_pwhash_SALTBYTES];
	unsigned char nonce[crypto_secretbox_NONCEBYTES];
	auto it = users.begin();

	if (in) {
		 users = j.get<std::vector<User>>();
		for (const auto& u : users) {
			std::cout << u.name << " " << "\n";
		}
	}
	{
		std::unique_ptr<User> user = std::make_unique<User>();
		while(1){
			if (logged)
				break;
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
				it = std::find_if(users.begin(), users.end(), [&](User a) {
					return a.name == user->name;
					});
				if (it != users.end()) {
					std::cout << "Find him!" << std::endl;

					if (crypto_pwhash_str_verify(
						(it->pwhash).c_str(),
						(*pass).c_str(), strlen((*pass).c_str())
					) == 0) {
						std::cout << "Good password!" << std::endl;
						logged = true;

					}
				}
				*user = *it;

				std::cout << std::endl;;

				break;
			}
			case 2:{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(1, 250000);

				std::cout << "User name: " << std::endl;
				std::getline(std::cin, (user->name));
				it = std::find_if(users.begin(), users.end(), [&](User a) {
					return a.name == user->name;
					});
				if (it != users.end()) {
					printf("There is User with this name");
					break;

				}
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

				//crypto_pwhash(

				//);
				std::cout << pwhash << std::endl;
				//memcpy((user->pwhash).c_str(), pwhash, crypto_pwhash_STRBYTES);
				user->pwhash = pwhash;
				std::cout << *pass;
				int ID;
				while (1) {
					ID = dist(gen);
					it = std::find_if(users.begin(), users.end(), [&](User a) {
						return a.ID == ID;
						});
					if (it == users.end()) { break; }
				}
				user->ID = ID;
				j.push_back({ {"user", user->name}, {"code", user->pwhash}, {"email", user->email} , {"ID", ID} });
				users.push_back(*user);
				std::cout << "\n" << std::endl;;
				break;
			}
			case 3:
				std::cout << "Reseting password!" << std::endl;
				std::cout << "User name\n";
				std::getline(std::cin, (user->name));
				std::cout << "Email\n";
				std::getline(std::cin, (user->email));
				 it = std::find_if(users.begin(), users.end(), [&](User a) {
					return a.name == user->name && a.email == user->email;
					});
				if (it != users.end()) {
					printf("In future i will send you email with new password");


				}
				std::cout << std::endl;;




				break;





			}
		}
			std::ofstream file("output.json");
			if (file.is_open()) {
				file << j.dump(4); 
				file.close();
			}



		}
		std::string name = std::to_string(user->ID);
		std::ifstream in2(name +".json");
		nlohmann::json pass = in2 ? nlohmann::json::parse(in2) : nlohmann::json::array();
		std::vector<UserPasswords> passwords;
		if (in2)
			passwords = pass.get<std::vector<UserPasswords>>();
		int sizePass = count(passwords);
		while (1) {
			std::unique_ptr<UserPasswords> userPass = std::make_unique<UserPasswords>();
			std::cout << "1. Add password" << std::endl;
			std::cout << "2. Password list" << std::endl;
			std::cout << "3. Change password" << std::endl;
			std::cout << "4. Delete password" << std::endl;
			int n;
			std::cin >> n;
			std::cout << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::string pass1;
			const char* message;

			switch (n) {
			case 1: {
				std::cout << "1. User name:" << std::endl;
				std::getline(std::cin, userPass->name);
				std::cout << "2. Site name:" << std::endl;
				std::getline(std::cin, userPass->site);
				std::cout << "3. Password" << std::endl;
				std::cout << "a) Write password" << std::endl;
				std::cout << "b) Generate password (recommended)" << std::endl;
				char b;
				std::cin >> b;

				while (1) {
					if (b == 'a') {
						std::cout << "Write password: \n";
						std::getline(std::cin, pass1);
						break;
					}
					else if (b == 'b') {
						std::random_device rd1;
						std::mt19937 gen(rd1());
						std::uniform_int_distribution<> dist(32, 255);
						for (int i = 0; i < 15; i++) {
							pass1.push_back(dist(gen));
						}
						//userPass->pass = pass1;
						break;
					}
					else { std::cout << " You choose wrong, choose between a or b" << std::endl; }
				}
				if (sodium_init() < 0) return 1;
				unsigned char key1[crypto_secretbox_KEYBYTES];
				randombytes_buf(key1, sizeof key1);
				randombytes_buf(salt, sizeof salt);
				randombytes_buf(nonce, sizeof nonce);
				unsigned char ciphertext[1024];
				size_t msg_len = pass1.size();
				crypto_secretbox_easy(ciphertext,
					reinterpret_cast<const unsigned char*>(pass1.c_str()),
					msg_len,
					nonce,
					key1);

				message = pass1.c_str();
				char encoded[2048];
				sodium_bin2base64(
					encoded,
					sizeof encoded,
					ciphertext,
					crypto_secretbox_MACBYTES + msg_len,
					sodium_base64_VARIANT_ORIGINAL
				);


				//memcpy(userPass->pass, encoded, sizeof(encoded));
				userPass->pass = encoded;


				//crypto_secretbox_easy(ciphertext, (const unsigned char*)message, strlen(message), nonce,key1);
				//size_t cipher_len = strlen(pass1.c_str()) + crypto_secretbox_MACBYTES;
				//memcpy(userPass->pass, ciphertext, sizeof(ciphertext));

				std::cout << encoded;

				//strcpy(userPass->pass, ciphertext);
				passwords.push_back(*userPass);
				pass.push_back({ {"site", userPass->site}, {"name", userPass->name}, {"pass", userPass->pass} , {"salt", salt}, {"nonce", nonce}});

				std::cout << "\n";
				sizePass++;
				break;
			}
			case 2: {
				int m=-1;
				while (1) {
					int countPasswords = 0;
					for (const auto& i : passwords) {
						countPasswords++;
						if (m == 0) {
							std::cout << std::left << std::setw(15)<< i.name << std::setw(45) << i.pass << std::setw(45) << i.site << std::endl;
						}
						else {
							if (m == countPasswords) {
								std::string uncodedPassword;
								char encoded[2048];
								unsigned char cipher[1024];
								unsigned char decrypted[1024];

								sodium_base642bin(cipher, sizeof cipher, i.pass.c_str(), i.pass.length(), NULL,NULL,NULL, sodium_base64_VARIANT_ORIGINAL);
								//std::cout << bufor;

								//crypto_secretbox_open_easy(decrypted, cipher, sizeof cipher, )
								
								
								
								std::cout << std::left<< std::setw(15)<<  i.name << std::setw(45) << i.pass << std::setw(45) << i.site << std::endl;
							}
							else {
								std::string hiddenPassword;
								for (int b = 0; b < sizeof i.pass; b++) {
									hiddenPassword += '*';
								}
								std::cout << std::left << std::setw(15)<< i.name << std::setw(45) << hiddenPassword << std::setw(45) << i.site << std::endl;
							}
							}
						}

				

					std::cout << "\n\n Ktore haslo chcesz pokazac, napisz numer indeksu:" << std::endl;
					std::cout << "\n Jesli chcesz pokazac wszystkie (niezalecane) kliknij 0\n" << std::endl;
						
					while (1) {
						std::cin >> m;
						if (m > sizePass || m < 0) {
							std::cout << "Podano zla liczbe\n";
						}
						else {
							break;
						}
					}




				}
					break;
				
			}
			case 3:
				printf("1");
				break;

			case 4:
				printf("1");
				break;
			
			
			
			}
			std::ofstream file(name+".json");
			if (file.is_open()) {
				file << pass.dump(4);
				file.close();
			}
		
		
		
		
		
		
		
		
		
		}



	}


}