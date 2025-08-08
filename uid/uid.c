
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 26/09/23
    uid - src file
*/
    
#include <unistd.h>     /* getpid */
#include <time.h>       /* time */
#include <ifaddrs.h>    /* getifaddrs, freeifaddrs */
#include <string.h>     /* memcpy */
#include <linux/if_packet.h> 

#include <stdio.h>


#include "uid.h" /* uid API */


/*****************************TypeDefs***********************************/
#define MAC_ADDRESS_SIZE 6


const ilrd_uid_t bad_uid = {(size_t)-1, (time_t)-1, (pid_t)-1, {'0'}};

/******************Service function decleration*************************/
static int GetMacAddress(unsigned char mac_address[6]);

/****************************Implementation*****************************/

ilrd_uid_t UIDGet()
{
	static size_t counter = 0;
	unsigned char mac_address[6] = {0};
	ilrd_uid_t new_uid = bad_uid;
	struct ifaddrs *ifaddr = NULL;
	
	++counter;
	
	new_uid.counter = counter;
	
	if (-1 == (new_uid.timestamp = time(NULL)))
	{
		return bad_uid;
	}
	
	if (-1 == (new_uid.pid = getpid()))
	{
		return bad_uid;
	}
	
	if (-1 == (GetMacAddress(mac_address)))
	{
		return bad_uid;
	}
	
	memcpy(new_uid.mac_address, mac_address, sizeof(new_uid.mac_address));
	freeifaddrs(ifaddr);
	
	return new_uid;
}


int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	if (uid1.counter != uid2.counter)
	{
		return 0;
	}
	
	if (uid1.timestamp != uid2.timestamp)
	{
		return 0;
	}
	
	if (uid1.pid != uid2.pid)
	{
		return 0;
	}	
	
    if (0 != memcmp(uid1.mac_address, uid2.mac_address, sizeof(uid1.mac_address)))
	{
		return 0;
	}	
	
	return 1;
}



/*********************Service function impl*****************************/

static int GetMacAddress(unsigned char mac_address[6])
{
    struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;

    if (-1 == getifaddrs(&ifaddr))
    {
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_PACKET)
        {
            struct sockaddr_ll *sll = (struct sockaddr_ll *)ifa->ifa_addr;
            if (sll->sll_halen == MAC_ADDRESS_SIZE)
            {
                if (0 != *(sll->sll_addr))
				{
					memcpy(mac_address, sll->sll_addr, MAC_ADDRESS_SIZE);
					freeifaddrs(ifaddr);
					return 0;
				}
            }
        }
    }

    freeifaddrs(ifaddr);
    return -1;
}
    
    
