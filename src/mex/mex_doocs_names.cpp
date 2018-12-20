
// main_doocs_client_template.cpp
// 2018 March 02

// set Debugging->Envronment  = Path=$(UDOOCSROOT_AMD64_dev)/dev/sys/$(TargetFolderBase)/dll;$(Path)

#include <eq_client.h>
#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#define printLast	printf
#else
#define _getch(...)	
#define printLast(...)
#endif

#define ADDRESS_TO_TEST	"PITZ.UTIL/MEMORY/TEST_PROP/FL1"

int main()
{
	EqCall eqCall;
	EqData eqDataIn, eqDataOut;
	EqAdr  eqAddr;
	int nReturn;

	eqDataIn.init();
	eqAddr.adr(ADDRESS_TO_TEST);
	nReturn=eqCall.get(&eqAddr,&eqDataIn,&eqDataOut);
	printf("eq.call returned: %d\n",nReturn);

	printLast("Press any key to exit!\n"); fflush(stdout);
	_getch();
	printLast("\n");

	return 0;
}
