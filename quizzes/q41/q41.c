
#include <stdio.h>	/*printf*/

static void TowerOfHanoi(char src, char helper, char dest, char disk_num);

int main(void)
{
	printf("For 3 disks:\n");
	TowerOfHanoi('A', 'B', 'C', 3);
	
	printf("\nFor 4 disks:\n");
	TowerOfHanoi('A', 'B', 'C', 4);
	
	return 0;
}


void TowerOfHanoi(char src, char helper, char dest, char disk_num)
{
	if (1 == disk_num)
	{
		printf("Disk 1 moved from %c to %c\n", src, dest);
		return;
	}
	
	TowerOfHanoi(src, dest, helper, disk_num - 1);
	
	printf("Disk %d moved from %c to %c\n", disk_num, src, dest);

	TowerOfHanoi(helper, src, dest, disk_num - 1);
}
