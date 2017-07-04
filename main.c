#include <hidlib/hidinterface.h>

// down 50000 50 : FA 00 00 04 03 01 00 00 00 50 C3 00 00 32 00 00 00 A7 A5
unsigned char bufferDown50[] = {0xFA, 0x00, 0x00, 0x04, 0x03, 0x01, 0x00, 0x00, 0x00, 0x50, 0xC3, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0xA7, 0xA5};
// down 50000 10 : FA 00 00 04 03 01 00 00 00 50 C3 00 00 0A 00 00 00 9F A5
unsigned char bufferDown10[] = {0xFA, 0x00, 0x00, 0x04, 0x03, 0x01, 0x00, 0x00, 0x00, 0x50, 0xC3, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x9F, 0xA5};

// up 50000 50 : FA 00 00 04 03 00 00 00 00 50 C3 00 00 32 00 00 00 A6 A5
unsigned char bufferUp50[] = {0xFA, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x50, 0xC3, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0xA6, 0xA5};
// up 50000 10 : FA 00 00 04 03 00 00 00 00 50 C3 00 00 0A 00 00 00 9E A5
unsigned char bufferUp10[] = {0xFA, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x50, 0xC3, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x9E, 0xA5};


// go home FA 00 02 04 03 00 00 00 00 00 00 00 00 0A 00 00 00 0D A5
unsigned char bufferGoHome[] = { 0xFA, 0x00, 0x02, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0xA5};

char isReponse = 0;

void datarec(unsigned char *recData,unsigned char length)
{
    printf("Data Receive: ");
    int i;
    for(i=0;i<length;i++)
    {
        printf("%02hhx ", recData[i]);
    }
    printf("\n");
    isReponse = 1;
}

int main(int argc, char* argv[])
{

    hidApi_Init(datarec);

    isReponse = 1;
    while(1)
    {
        while(isReponse==0) usleep(500*1000);
        isReponse =0;
        hidApi_Write(bufferGoHome,0x13);
        usleep(500*1000);

        while(isReponse==0) usleep(500*1000);
        isReponse =0;
        hidApi_Write(bufferDown10,0x13);
        usleep(500*1000);

        while(isReponse==0) usleep(500*1000);
        isReponse =0;
        hidApi_Write(bufferDown50,0x13);

        while(isReponse==0) usleep(500*1000);
        isReponse =0;
        hidApi_Write(bufferDown10,0x13);
        usleep(500*1000);

        usleep(2*1000*1000);
        while(isReponse==0) usleep(500*1000);
        isReponse =0;
        hidApi_Write(bufferGoHome,0x13);

        usleep(2*1000*1000);
    }

    hidApi_Close();

    return 0;
}
