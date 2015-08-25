#include "StdAfx.h"
#include "ShortMassage.h"
#include "HttpClient.h"


ShortMassage::ShortMassage(void):m_type("15")
{
}


ShortMassage::~ShortMassage(void)
{
}

bool ShortMassage::Login()
{
	bool vResult=false;
	curl_slist *headerlist=curl_slist_append(0,"Accept-Encoding: deflate");
	std::string response=HttpClient::sharedInstance()->HttpGetAction("http://42.120.60.152/do.aspx?action=loginIn&uid=taobaoyang1112&pwd=ultimater",headerlist);
	if(response.find("Login success")!=std::string::npos)
	{
		vResult=true;
	}
	return vResult;
}
bool ShortMassage::Logout()
{
	bool vResult=false;
	return vResult;
}
std::string ShortMassage::GetAPhoneNumber()
{
	std::string vResult="";
	curl_slist *headerlist=curl_slist_append(0,"Accept-Encoding: deflate");
	std::string response=HttpClient::sharedInstance()->HttpGetAction("http://42.120.60.152/do.aspx?action=getMobilenum&type=15",headerlist);
	if(response.find("PS|")!=std::string::npos)
	{
		vResult=response.substr(response.find("PS|")+3,11);
	}
	return vResult;
}
std::string ShortMassage:: GetVeryfyNumberForPhone(std::string phone)
{
	std::string vResult="";
	curl_slist *headerlist=curl_slist_append(0,"Accept-Encoding: deflate");
	std::string response=HttpClient::sharedInstance()->HttpGetAction(("http://42.120.60.152/do.aspx?action=getSMS&phone="+phone).c_str(),headerlist);
	return vResult;
}
bool ShortMassage::AddPhoneToBlackList(std::string phone)
{
	bool vResult=false;
	curl_slist *headerlist=curl_slist_append(0,"Accept-Encoding: deflate");
	std::string response=HttpClient::sharedInstance()->HttpGetAction(("http://42.120.60.152/do.aspx?action=BlackList&phone="+phone).c_str(),headerlist);
	return vResult;
}
bool ShortMassage:: ReleasePhoneNumber()
{
	bool vResult=false;
	curl_slist *headerlist=curl_slist_append(0,"Accept-Encoding: deflate");
	std::string response=HttpClient::sharedInstance()->HttpGetAction("http://42.120.60.152/do.aspx?action=releasePhone&type=15",headerlist);
	return vResult;
}