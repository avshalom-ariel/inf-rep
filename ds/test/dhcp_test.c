
#include <math.h>				/*pow*/
#include <string.h>				/*memcmp*/

#include "dhcp.h"				/*Typedefs, Function declarations*/
#include "test_utility.h"		/*Test Functions*/

#define BITS_IN_BYTE 8
#define PREALLOC_ADD_NUM 3

static unsigned char base_network_id[4] = {192, 12, 10, 0};
static size_t subnet_prefix = 24;

static void DHCPCreateDestroyTest(void);
static void DHCPAllocateIPTest(void);
static void DHCPFreeIPTest(void);
static void DHCPCountFreeTest(void);

int main(void)
{
	DHCPCreateDestroyTest();
	DHCPAllocateIPTest();
	DHCPFreeIPTest();
	DHCPCountFreeTest();
	
	
	Test();
	
	return 0;
}


void DHCPCreateDestroyTest(void)
{
	DHCP_Server_t *dhcp = DHCPCreate(base_network_id, subnet_prefix);
	
	DHCPDestroy(dhcp);
}

void DHCPAllocateIPTest(void)
{
	unsigned char requested_ip1[4] = {192, 12, 10, 0};
	unsigned char requested_ip2[4] = {192, 12, 10, 10};
	unsigned char requested_ip3[4] = {192, 12, 10, 10};
	unsigned char requested_ip4[4] = {200, 12, 10, 50};
	
	unsigned char received_ip1[4] = {0, 0, 0, 0};
	unsigned char received_ip2[4] = {0, 0, 0, 0};
	unsigned char received_ip3[4] = {0, 0, 0, 0};
	unsigned char received_ip4[4] = {0, 0, 0, 0};
	
	unsigned char next_requested_ip1[4] = {192, 12, 10, 1};
	unsigned char next_requested_ip3[4] = {192, 12, 10, 11};

	DHCP_Server_t *dhcp = DHCPCreate(base_network_id, subnet_prefix);
	
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip1, received_ip1));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip2, received_ip2));					
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip3, received_ip3));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip4, received_ip4));
	
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(next_requested_ip1, received_ip1, BYTES_IN_IP));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(requested_ip2, received_ip2, BYTES_IN_IP));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(next_requested_ip3, received_ip3, BYTES_IN_IP));
	
	DHCPDestroy(dhcp);
}


void DHCPFreeIPTest(void)
{
	unsigned char requested_ip1[4] = {192, 12, 10, 1};
	unsigned char requested_ip2[4] = {192, 12, 10, 2};
	unsigned char requested_ip3[4] = {192, 12, 10, 3};
	
	unsigned char received_ip1[4] = {0, 0, 0, 0};
	unsigned char received_ip2[4] = {0, 0, 0, 0};
	unsigned char received_ip3[4] = {0, 0, 0, 0};
	unsigned char received_ip4[4] = {0, 0, 0, 0};

	DHCP_Server_t *dhcp = DHCPCreate(base_network_id, subnet_prefix);
	
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip1, received_ip1));
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip2, received_ip2));					
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip3, received_ip3));
						
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(requested_ip1, received_ip1, BYTES_IN_IP));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(requested_ip2, received_ip2, BYTES_IN_IP));
	TestInt("DHCPAllocateIPTest", __FILE__, __LINE__, 1, 0 == memcmp(requested_ip3, received_ip3, BYTES_IN_IP));
						
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, SUCCESS == DHCPFreeIP(dhcp, received_ip2));
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, DOUBLE_FREE == DHCPFreeIP(dhcp, received_ip2));
	TestInt("DHCPFreeIPTest", __FILE__, __LINE__, 1, SUCCESS == DHCPFreeIP(dhcp, received_ip3));
	
	DHCPDestroy(dhcp);
}


void DHCPCountFreeTest(void)
{
	unsigned char requested_ip1[4] = {192, 12, 10, 1};
	unsigned char requested_ip2[4] = {192, 12, 10, 2};
	unsigned char requested_ip3[4] = {192, 12, 10, 3};
	
	unsigned char received_ip1[4] = {0, 0, 0, 0};
	unsigned char received_ip2[4] = {0, 0, 0, 0};
	unsigned char received_ip3[4] = {0, 0, 0, 0};

	size_t add_range = pow(2, BYTES_IN_IP * BITS_IN_BYTE - subnet_prefix) - PREALLOC_ADD_NUM;

	DHCP_Server_t *dhcp = DHCPCreate(base_network_id, subnet_prefix);
	
	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range, DHCPCountFree(dhcp));
	
	
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip1, received_ip1));
	
	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range - 1, DHCPCountFree(dhcp));
						
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip2, received_ip2));					

	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range - 2, DHCPCountFree(dhcp));
	
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, 
						SUCCESS == DHCPAllocateIP(dhcp, requested_ip3, received_ip3));

	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range - 3, DHCPCountFree(dhcp));
						
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, SUCCESS == DHCPFreeIP(dhcp, received_ip1));
	
	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range - 2, DHCPCountFree(dhcp));
	
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, SUCCESS == DHCPFreeIP(dhcp, received_ip2));
	
	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range - 1, DHCPCountFree(dhcp));	
	
	TestInt("DHCPCountFreeTest", __FILE__, __LINE__, 1, SUCCESS == DHCPFreeIP(dhcp, received_ip3));

	TestSizeT("DHCPCountFreeTest", __FILE__, __LINE__, add_range, DHCPCountFree(dhcp));
}










