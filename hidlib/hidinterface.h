#ifndef DeltaHIDINTERFACE_H
#define DeltaHIDINTERFACE_H

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

// Headers needed for sleeping.
#include <unistd.h>

#define hidDataLength 64

//hid data receive callback function
typedef void (*DataArriveCallBackFunc)(unsigned char *recData,unsigned char length);

DataArriveCallBackFunc hidDataArriveCallBack;

hid_device *handle;

unsigned char isOpen;


int hidApi_Init(DataArriveCallBackFunc DataArriveCallBack);

int hidApi_Write(unsigned char *data, unsigned char length);

//when data arrived, the function will be called
void hidApi_DataReceive(unsigned char *recData,unsigned char length);

int hidApi_Close(void);

#endif // HIDINTERFACE_H
