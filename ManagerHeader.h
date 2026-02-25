#pragma once
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <sodium.h>
unsigned char out_key[crypto_secretbox_KEYBYTES];

struct UserPasswords;
struct User {
	//std::vector<UserPasswords>* userPass;
	std::string name;
	std::string pwhash;
	std::string email;
	unsigned char salt[crypto_pwhash_SALTBYTES];
	int ID;
	//int iloscHasel;
};
struct UserPasswords {
	std::string site;
	std::string name;
	std::string pass;
	unsigned char nonce[crypto_secretbox_NONCEBYTES];

};


 unsigned char* decrpyt(const std::string&  cryptedPass,const unsigned char nonce[]) {
	char encoded[2048];
	size_t cipher_len;
	unsigned char cipher[1024];
	unsigned char decrypted[1024];

	sodium_base642bin(cipher, sizeof cipher, cryptedPass.c_str(), cryptedPass.length(), NULL, &cipher_len, NULL, sodium_base64_VARIANT_ORIGINAL);
	//std::cout << bufor;
	const unsigned char* data =
		reinterpret_cast<const unsigned char*>(cryptedPass.c_str());

	crypto_secretbox_open_easy(decrypted,
		cipher, cipher_len, nonce, out_key);


	size_t message_len = cipher_len - crypto_secretbox_MACBYTES;
	decrypted[message_len] = '\0';
	std::cout << std::setw(45) << decrypted;

	return decrypted;

};
#include <cstring>

 void copy(const unsigned char data[], size_t lenght) {
#ifdef _WIN32
	 if (!OpenClipboard(NULL)) return;
	 EmptyClipboard();
	 HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, lenght + 1);
	 if (hGlob) {
		 void* pMem = GlobalLock(hGlob);
		 memcpy(pMem, data, lenght);
		 ((char*)pMem)[lenght] = '\0';

		 GlobalUnlock(hGlob);
		 SetClipboardData(CF_TEXT, hGlob);
	 }
	 CloseClipboard();
#endif
 }

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
		{"salt", u.salt},
		{"ID", u.ID}
	};
}


void from_json(const nlohmann::json& j, User& u) {
	j.at("user").get_to(u.name);
	j.at("email").get_to(u.email);
	j.at("code").get_to(u.pwhash);
	j.at("salt").get_to(u.salt);
	j.at("ID").get_to(u.ID);

}


void to_json(nlohmann::json& j, const UserPasswords& p) {
	j = nlohmann::json{
		{"site", p.site},
		{"name", p.name},
		{"pass", p.pass},
		{"nonce", p.nonce}
	};
}

void from_json(const nlohmann::json& j, UserPasswords& p) {
	j.at("site").get_to(p.site);
	j.at("name").get_to(p.name);
	j.at("pass").get_to(p.pass);
	j.at("nonce").get_to(p.nonce);
}
