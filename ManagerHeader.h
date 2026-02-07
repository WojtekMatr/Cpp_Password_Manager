#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <sodium.h>

struct UserPasswords;
struct User {
	//std::vector<UserPasswords>* userPass;
	std::string name;
	std::string pwhash;
	std::string email;
	int ID;
	//int iloscHasel;
};
struct UserPasswords {
	std::string site;
	std::string name;
	std::string pass;
};


class JsonPasswords {
	nlohmann::json* j;
	std::vector<User>* users;

public:

};

int count(const std::vector<UserPasswords>& name) {
	int size=0;
	for (auto i : name) {
		size++;
	}

	return size;
};

//overloading json's methods for our objects:

void to_json(nlohmann::json& j, const User& u) {
	j = nlohmann::json{
		{"user", u.name},
		{"email", u.email},
		{"code", u.pwhash},
		{"ID", u.ID}
	};
}


void from_json(const nlohmann::json& j, User& u) {
	j.at("user").get_to(u.name);
	j.at("email").get_to(u.email);
	j.at("code").get_to(u.pwhash);
	j.at("ID").get_to(u.ID);
}


void to_json(nlohmann::json& j, const UserPasswords& p) {
	j = nlohmann::json{
		{"site", p.site},
		{"name", p.name},
		{"pass", p.pass}
	};
}

void from_json(const nlohmann::json& j, UserPasswords& p) {
	j.at("site").get_to(p.site);
	j.at("name").get_to(p.name);
	j.at("pass").get_to(p.pass);
}
