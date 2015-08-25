#pragma  once
#include<string>

typedef struct ThreadPram
{
	HWND mWND;
	char* phone;
}ThreadPram;

typedef struct ReadBuf
{
	unsigned char* mBuf;
	int mSizeBuf;
}ReadBuf;


#define READBUF_MAXLEN 0x1000000