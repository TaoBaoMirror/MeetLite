#pragma once
#include "string"
class ShortMassage
{
public:
	ShortMassage(void);
	~ShortMassage(void);
	bool Login();
	bool Logout();
	std::string GetAPhoneNumber();
	std::string GetVeryfyNumberForPhone(std::string);
	bool AddPhoneToBlackList(std::string);
	bool ReleasePhoneNumber();

private:

	const std::string m_type;
};

