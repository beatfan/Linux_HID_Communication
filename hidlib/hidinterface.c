/*******************************************************
 Windows HID simplification

 Alan Ott
 Signal 11 Software

 8/22/2009

 Copyright 2009, All Rights Reserved.
 
 This contents of this file may be used by anyone
 for any reason without any conditions and may be
 used as a starting point for your own applications
 which use HIDAPI.
********************************************************/


#include "hidinterface.h"
#include <pthread.h>

void hidRead_thread(void);

int hidApi_Init(DataArriveCallBackFunc DataArriveCallBack)
{
    hidDataArriveCallBack = NULL;
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    ////handle = hid_open(0x4d8, 0x3f, L"12345");
    handle = hid_open(0x4d8, 0x3f, NULL);
    if (!handle) {
        printf("unable to open device\n");
        isOpen = 0;
        return -1;
    }

    printf("open device success\n");
    isOpen = 1;
    hidDataArriveCallBack = DataArriveCallBack;
    hidRead_thread();


    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    return 0;
}

int hidApi_Write(unsigned char *data, unsigned char length)
{
    int res;
    unsigned char realData[length+1];

    realData[0]=length;
    int i;
    for(i=0;i<length;i++)
    {
        realData[i+1]=data[i];
    }

    res = hid_write(handle, realData, length+1);
    if (res < 0) {
        printf("Unable to write()\n");
        printf("Error: %ls\n", hid_error(handle));
        return -1;
    }

    printf("write success\n");
    return 0;
}

void hidApi_DataReceive(unsigned char *recData,unsigned char length)
{
    if(hidDataArriveCallBack==NULL)
        return;

    hidDataArriveCallBack(recData,length);
}

void hidApi_Read()
{
    unsigned char recData[hidDataLength];

    int res;
    while (isOpen==1) {
        res = hid_read(handle, recData, hidDataLength);
        if (res == 0)
            ;//printf("waiting...\n");
        else if (res < 0)
        {
            printf("Unable to read()\n");
            return -1;
        }
        else
        {

            int i;

//            printf("Data read:\n   ");
//            // Print out the returned buffer.
//
//            for (i = 0; i < res; i++)
//                printf("%02hhx ", recData[i]);
//            printf("\n");

            unsigned char length = recData[0];

            unsigned char datas[length];
            for(i=0;i<length;i++)
            {
                datas[i]=recData[i+1];
            }

            hidApi_DataReceive(datas,length);
        }


        usleep(50*1000);

    }

}

void hidRead_thread(void)
{
   pthread_t id;
   int ret, i;
   ret=pthread_create(&id,NULL,(void *) hidApi_Read,NULL); // 成功返回0，错误返回错误编号
   if(ret!=0) {
       printf ("Create pthread error!\n");
       exit (1);
   }


   //pthread_join(id,NULL);

   printf ("Create pthread success!\n");
}

int hidApi_Close(void)
{
    hid_close(handle);
    isOpen = 0;
    /* Free static HIDAPI objects. */
    hid_exit();

    return 0;

}



