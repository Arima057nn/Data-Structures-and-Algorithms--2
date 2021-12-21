#include <stdio.h>
#include <btree.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[30];
    long number;
} phoneBook;

int list(BTA *btact)
{
	int status = 0,
		count = 0;
	BTint val;
	char key[ZKYLEN];

	while (status == 0)
	{
		status = bnxtky(btact, key, &val);
		if (status == 0)
		{
			printf("Name: %s, SDT = " ZINTFMT "\n", key, val);
			count++;
		}
	}
	if ((status == 0 || status == QNOKEY))
		printf("%d keys listed\n", count);
	return ((status == 0 || status == QNOKEY) ? 0 : status);
}
int main(){
    char c;
    btinit();
    BTA *BTC = btcrt("phonebook",0,FALSE);
    int choose;
    char name[30];
    int sdt,k;
    int returnCode;
    while(1){
        printf("\n------MENU------\n"
                "1. Insert\n"
                "2. Delete\n"
                "3. Display\n"
                "4. Searching\n"
                "5. Update\n"
                "6. Exit\n"
                "---> Select ");
        scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            printf("Name: ");
			c = getchar();
            gets(name);
			printf("SDT: ");
			scanf("%d%*c", &sdt);
            binsky(BTC,name,sdt);
            break;

        case 2: 
            printf("name: ");
            c = getchar();
            gets(name);
            bdelky(BTC, name);

            break;
        case 3:
            
            btpos(BTC, 1);
			printf("LIST:\n");
			list(BTC);
            break;
        case 4:
            printf("Name: ");
			c = getchar();
            gets(name);
			printf("SDT: ");
			scanf("%d%*c", &sdt);
            int k = bfndky(BTC,name,&sdt);
            printf("%d",k);
            break;
        case 5:
            printf("Name: ");
			c = getchar();
            gets(name);
            printf("SDT: ");
			scanf("%d%*c", &sdt);
            k = bupdky(BTC, name, sdt);
            if(k == 0)  printf("Thanh cong !");
            else printf("Khong thanh cong");

            break;
        
        case 6:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}


//gcc -o lab2 lab2.c -L ~/Arima/C_Advance/Library/B\ Tree/lib/ -lbt -I ~/Arima/C_Advance/Library/B\ Tree/inc/
