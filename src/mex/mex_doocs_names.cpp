
// main_doocs_client_template.cpp
// 2018 March 02

// set Debugging->Envronment  = Path=$(UDOOCSROOT_AMD64_dev)/dev/sys/$(TargetFolderBase)/dll;$(Path)

#include <eq_client.h>
#include <mex.h>

#define HANDLE_MEMORY_DEFF(_ptr,...)	do{if(!(_ptr)){exit(1);}}while(0)

void mexFunction(int a_nOutputsNumber, mxArray *a_pOutputs[], int a_nInputsNumber, const mxArray *a_pInput[])
{
	char *pcTmp,*pcLastAccurance=NULL,*pcDoocsAddressByUser,*pcDoocsAddressFinal;
	USTR* pUstr;
	mxArray* pString;
	EqData dataOut;
	EqAdr dcsAddr;
	EqCall eqCall;
	size_t	unStringLenPlus1;
	int i,nNumberOfSlashes;
	int nDoocsReturn;

	if( (a_nInputsNumber<1)||(!mxIsChar(a_pInput[0])) ){
		mexErrMsgTxt("Provide DOOCS address as a string argument.\n");
		return;
	}

	unStringLenPlus1 =mxGetNumberOfElements(a_pInput[0])+1;
	pcTmp=pcDoocsAddressByUser = (char*)alloca(unStringLenPlus1 + 1);
	mxGetString(a_pInput[0],pcDoocsAddressByUser,unStringLenPlus1);

	for (nNumberOfSlashes = 0;;) {
		pcTmp = strchr(pcTmp, '/');
		if(pcTmp){++nNumberOfSlashes; pcLastAccurance=pcTmp++;}
		else{break;}
	}
	pcTmp=pcLastAccurance+1;

	if((nNumberOfSlashes==4)&&pcLastAccurance&&(*pcTmp)){pcDoocsAddressFinal = pcDoocsAddressByUser;}
	else{
		pcDoocsAddressFinal = (char*)alloca(unStringLenPlus1 + 10);
		unStringLenPlus1 = strlen(pcDoocsAddressByUser);
		memcpy(pcDoocsAddressFinal, pcDoocsAddressByUser, unStringLenPlus1);
		if( pcLastAccurance&&(!(*pcTmp)) ){ pcDoocsAddressFinal[unStringLenPlus1++] = '*';}
		//if((!pcLastAccurance)||(pcLastAccurance&&(*pcTmp))){unStringLenPlus1=strlen(pcDoocsAddressByUser);}
		//else {unStringLenPlus1 = (size_t)pcTmp - (size_t)pcDoocsAddressByUser;}
		//unStringLenPlus1 = (size_t)pcLastAccurance - (size_t)pcDoocsAddressByUser + 1;
		
		for(i=nNumberOfSlashes;i<4;++i){
			pcDoocsAddressFinal[unStringLenPlus1++]='/';
			pcDoocsAddressFinal[unStringLenPlus1++]='*';
		}
		pcDoocsAddressFinal[unStringLenPlus1]='\0';
	}

	dcsAddr.adr(pcDoocsAddressFinal);
	dataOut.init();
	nDoocsReturn=eqCall.names(&dcsAddr,&dataOut);
	if(nDoocsReturn){
		mexPrintf(
			"Call to doocs::names returned error\n" 
			"Error code is %d, error strintg is \"%s\"\n",
			nDoocsReturn,dataOut.get_string().c_str());
		a_pOutputs[0] = mxCreateString("DOOCS error accured");
		return;
	}

	nNumberOfSlashes= dataOut.length();
	a_pOutputs[0]=mxCreateCellMatrix(1,nNumberOfSlashes);
	HANDLE_MEMORY_DEFF(a_pOutputs[0]," ");

	for(i=0;i<nNumberOfSlashes;++i){
		pUstr = dataOut.get_ustr(i);
		if (!pUstr) { continue; }
		pString = mxCreateString(pUstr->str_data.str_data_val);
		HANDLE_MEMORY_DEFF(a_pOutputs[0], " ");
		mxSetCell(a_pOutputs[0],i, pString);
	}
}

