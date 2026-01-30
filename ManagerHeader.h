#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <sodium.h>

struct UserPasswords;
struct User {
	std::vector<UserPasswords>* userPass;
	std::string name;
	std::string pwhash;
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
//overloading json's methods for our objects:

void to_json(nlohmann::json& j, const User& u) {
	j = nlohmann::json{
		{"user", u.name},
		{"email", u.email},
		{"code", u.pwhash}
	};
}

void from_json(const nlohmann::json& j, User& u) {
	j.at("user").get_to(u.name);
	j.at("email").get_to(u.email);
	j.at("code").get_to(u.pwhash);
}