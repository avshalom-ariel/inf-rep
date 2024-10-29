
#include <stdio.h> /*printf*/

#include "uid.h" /*ilrd_uid_t*/
#include "test_utility.h" /*Test functions*/

#define TRUE 1
#define FALSE 0


void IsEquaGetBadlTest(void);

int main(void)
{
	IsEquaGetBadlTest();

	Test();
	
	return 0;
}


void IsEquaGetBadlTest(void)
{
	int res1 = 0;
	int res2 = 0;
	int res3 = 0;
	int res4 = 0;
	
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();
	ilrd_uid_t uid3 = UIDCreate();
	ilrd_uid_t uid4 = UIDGetBad();
	
	res1 = UIDIsEqual(uid1, uid1);
	res2 = UIDIsEqual(uid2, uid3);
	res3 = UIDIsEqual(uid1, uid4);
	res4 = UIDIsEqual(uid3, uid3);
	
	TestInt("IsEqua and GetBadl Test Test", __FILE__, __LINE__, TRUE, res1);
	TestInt("IsEqua and GetBadl Test Test", __FILE__, __LINE__, FALSE, res2);
	TestInt("IsEqua and GetBadl Test Test", __FILE__, __LINE__, FALSE, res3);
	TestInt("IsEqua and GetBadl Test Test", __FILE__, __LINE__, TRUE, res4);
}


