#include "StdAfx.h"
#include "HttpClient.h"
#include "CommonDef.h"
#include "MJGbkHelper.h"
#include "MJGbkcode.h"

HttpClient* HttpClient::mClient=NULL;

HttpClient::HttpClient(void)
{
	curl_global_init(CURL_GLOBAL_ALL);
}



HttpClient* HttpClient::sharedInstance()
{
	if(mClient==NULL)
	{
		mClient=new HttpClient;
	}
	return mClient;
}

HttpClient::~HttpClient(void)
{
}
size_t HttpClient:: write_data(void * ptr, size_t size, size_t nmemb, void * stream)
{
	ReadBuf * vPReadBuf=(ReadBuf*)stream;
	memcpy(vPReadBuf->mBuf+vPReadBuf->mSizeBuf,ptr,size*nmemb);
	vPReadBuf->mSizeBuf+=size*nmemb;
	return size*nmemb;
}
std::string HttpClient::HttpGetAction(const char* host,struct curl_slist* headers)
{
	std::string response="";
	CURL* pCURL=curl_easy_init();
	curl_easy_setopt(pCURL,CURLOPT_URL,host);

	ReadBuf vReadBuf;
	vReadBuf.mBuf=(unsigned char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	vReadBuf.mSizeBuf=0;
	curl_easy_setopt(pCURL, CURLOPT_WRITEDATA, &vReadBuf);
	curl_easy_setopt(pCURL, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(pCURL,CURLOPT_COOKIEFILE,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_COOKIEJAR,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_HTTPHEADER,headers);
	curl_easy_setopt(pCURL,CURLOPT_HEADER,1);
	curl_easy_perform(pCURL);
	curl_easy_cleanup(pCURL);

	char* gb2312buf=(char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	MJ_GBK_HELPER::UTF_8ToGB2312(gb2312buf,(char*)vReadBuf.mBuf,vReadBuf.mSizeBuf);

	response=gb2312buf;
	GlobalFree(gb2312buf);
	GlobalFree(vReadBuf.mBuf);
	return response;
}
bool HttpClient::SetDelegate(const char*host ,const char* port)
{
	mHost=host;
	mPort=port;
	return 0;
}
std::string   HttpClient::HttpPostAction(const char* host,struct curl_slist* headers,const char* postDada)
{
	CURL* pCURL=curl_easy_init();
	curl_easy_setopt(pCURL,CURLOPT_URL,host);
	curl_easy_setopt(pCURL,CURLOPT_POSTFIELDS,postDada);

	ReadBuf vReadBuf;
	vReadBuf.mBuf=(unsigned char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	vReadBuf.mSizeBuf=0;
	curl_easy_setopt(pCURL, CURLOPT_WRITEDATA, &vReadBuf);
	curl_easy_setopt(pCURL, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(pCURL,CURLOPT_COOKIEFILE,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_COOKIEJAR,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_HTTPHEADER,headers);
	curl_easy_setopt(pCURL,CURLOPT_HEADER,1);
	curl_easy_perform(pCURL);
	curl_easy_cleanup(pCURL);

	//зЊТы
	char* gb2312buf=(char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	MJ_GBK_HELPER::UTF_8ToGB2312(gb2312buf,(char*)vReadBuf.mBuf,vReadBuf.mSizeBuf);

	std::string responce=gb2312buf;
	GlobalFree(gb2312buf);
	GlobalFree(vReadBuf.mBuf);
	return responce;
}