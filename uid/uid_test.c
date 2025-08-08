
/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 26/09/23
    uid - test file
*/

#include <stdio.h>
#include <assert.h>
#include "uid.h" 

#define MAC_ADDRESS_LENGTH 6

int main()
{
	ilrd_uid_t uid1 = UIDGet();
	ilrd_uid_t uid2 = UIDGet();
	

	
	printf("uid1 counter: %ld \n", uid1.counter);
	printf("uid1 time: %ld \n", uid1.timestamp);
	printf("uid1 pid: %d\n", uid1.pid);
	printf("uid1 MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
	uid1.mac_address[0], uid1.mac_address[1], uid1.mac_address[2],
	uid1.mac_address[3], uid1.mac_address[4], uid1.mac_address[5]);

	printf("\n\n");

	printf("uid2 counter: %ld \n", uid2.counter);
	printf("uid2 time: %ld \n", uid2.timestamp);
	printf("uid2 pid: %d\n", uid2.pid);
	printf("uid2 MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
	uid2.mac_address[0], uid2.mac_address[1], uid2.mac_address[2],
	uid2.mac_address[3], uid2.mac_address[4], uid2.mac_address[5]);

	(void)uid1;
	(void)uid2;
	
	if (0 != UIDIsSame(uid1, uid2))
	{
		printf("UIDIsSame test FAILED!\n");
	}
	
	else
	{
		printf("\n\nUIDGet test passed!\n");
	}
	
	return 0;
}
/***************************Tests impl****************************/    

    
