#pragma once
#include "string"
#include "curl/curl.h"
class HttpClient
{
public:
	
	~HttpClient(void);
	std::string HttpGetAction(const char* host,struct curl_slist* headers);
	std::string HttpPostAction(const char* host,struct curl_slist* headers,const char* postDada);
	bool SetDelegate(const char* host,const char* port);
	static HttpClient* sharedInstance();
private:
	static HttpClient* mClient;
	const char* mHost,*mPort;
	static size_t write_data(void * ptr, size_t size, size_t nmemb, void * stream);
	HttpClient(void);
};

