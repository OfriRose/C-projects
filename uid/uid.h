/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 26/09/23
    uid - h file
*/
    
/* DESCRIPTION:
 * 	API for UID. UID is a unique identination for easy manegment of diffrent
 *     elements. the API allows for generating and comparision for validation 
 *     of UIDs
 *     major functions: Get, IsSame
 */
 
#ifndef __ILRD_OL149_H_UID__
#define __ILRD_OL149_H_UID__

#include <stddef.h>    /* size_t*/
#include <sys/types.h> /* pid_t*/
#include <time.h>      /*time_t*/

/* UID structure */

typedef struct ilrd_uid
{
    size_t counter;
    time_t timestamp;
    pid_t pid;
    char mac_address[6];
} ilrd_uid_t;

extern const ilrd_uid_t bad_uid;

/* Function to generate a new UID
 * @return: return a uid_t on success, otherwise BAD_UID.
 * @complexity Time: O(1), Space: O(1).
 */
ilrd_uid_t UIDGet(void);

/* Function to compare two UIDs
 * @return: return 1 if equal, 0 otherwise.
 * @complexity Time: O(1), Space: O(1)
 * @note: int that represents bool.
 */
int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2);

#endif /*__ILRD_OL149_H_UID__*/
