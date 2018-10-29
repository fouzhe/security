/*
 * goose_publisher_example.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "mms_value.h"
#include "goose_publisher.h"
#include "hal_thread.h"

// has to be executed as root!
int
main(int argc, char** argv)
{
    char* interface;

    if (argc > 1)
       interface = argv[1];
    else
       interface = "eth0";

    printf("Using interface %s\n", interface);

	LinkedList dataSetValues = LinkedList_create();

	int j=0;
    for(j=0;j<4;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<5;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<25;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<8;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<6;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<4;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<6;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));

    LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(212));

    for(j=0;j<10;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<20;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<3;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<5;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<8;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<8;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<10;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<4;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<12;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<12;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<19;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<5;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
    for(j=0;j<1;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
    for(j=0;j<2;j++)
	LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));

	CommParameters gooseCommParameters;

	gooseCommParameters.appId = 1000;
    gooseCommParameters.dstAddress[0] = 0x00;
	gooseCommParameters.dstAddress[1] = 0x32;
	gooseCommParameters.dstAddress[2] = 0x75;
	gooseCommParameters.dstAddress[3] = 0x8a;
	gooseCommParameters.dstAddress[4] = 0xfc;
	gooseCommParameters.dstAddress[5] = 0x3f;
	gooseCommParameters.vlanId = 0;
	gooseCommParameters.vlanPriority = 4;

	/*
	 * Create a new GOOSE publisher instance. As the second parameter the interface
	 * name can be provided (e.g. "eth0" on a Linux system). If the second parameter
	 * is NULL the interface name as defined with CONFIG_ETHERNET_INTERFACE_ID in
	 * stack_config.h is used.
	 */
	GoosePublisher publisher = GoosePublisher_create(&gooseCommParameters, interface);

	GoosePublisher_setGoCbRef(publisher, "simpleIOGenericIO/LLN0$GO$gcbAnalogValues");
	GoosePublisher_setConfRev(publisher, 1);
	GoosePublisher_setDataSetRef(publisher, "simpleIOGenericIO/LLN0$AnalogValues");

	int i = 0;

	for (i = 0; i < 3; i++) {
		Thread_sleep(1000);

		if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
			printf("Error sending message!\n");
		}
	}

	GoosePublisher_destroy(publisher);

	LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction) MmsValue_delete);
}




