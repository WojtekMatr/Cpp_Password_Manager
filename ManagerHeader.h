#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

struct UserPasswords;
struct User {
	std::vector<UserPasswords>* userPass;
	std::string name;
	unsigned char pwhash[32];
	std::string email;
	int iloscHasel;
};
struct UserPasswords {
	std::string name;
	std::string pass;
	std::string site;
};


class JsonPasswords {
	nlohmann::json* j;
	std::vector<User>* users;

public:

};