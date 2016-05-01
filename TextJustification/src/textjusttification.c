#include "generic_stuff.h"
#include "matrix.h"

void ExitFunc(char *,...);


int Pow(int num,int pow)
{

	if (pow == 0)
		return 1;
	return num * Pow(num,pow-1);
}

int GetNumWords(char **WordList)
{
	int nwords = 0;
	if (NULL == WordList)
		return 0;

	while (*WordList) {
		nwords++;
		WordList++;
	}
	return nwords;
}


int GetWorstness(int stindex,int endindex,int maxchar,char **DbPtrToHeadOfWrdList)
{

	char **IterPtr;	
	int lenofword = 0;
	int worstness = 0;

	if (NULL == DbPtrToHeadOfWrdList)
		return INF;

	for (IterPtr=(DbPtrToHeadOfWrdList + stindex);IterPtr <= (DbPtrToHeadOfWrdList + endindex);IterPtr++) {
		lenofword = strlen(*IterPtr);
		worstness += lenofword;						
	}

	worstness += (endindex - stindex);

	if (worstness <= maxchar)
		worstness = Pow(maxchar - worstness,2);
	else
		worstness = INF;
	return worstness;
}




void FillTextJustMatrix(int  **DbPtrToHeadOfMat,char ** DbPtrToHeadOfWrdList, int maxcharinline)
{

	int nwords = 0;

	int rIter,cIter;
	int worstness = 0;

	if (!DbPtrToHeadOfMat || !DbPtrToHeadOfWrdList)
		return;
	nwords = GetNumWords(DbPtrToHeadOfWrdList);


	for (rIter=0;rIter<nwords;rIter++) {
		for(cIter=rIter;cIter<nwords;cIter++) {
			worstness = GetWorstness(rIter,cIter,maxcharinline,DbPtrToHeadOfWrdList);
			*(*(DbPtrToHeadOfMat+rIter) + cIter) = worstness;			
		}		
	}
	return;
}


int * FillTextLineArr(int **DbPtrToMatHead,int nwords)
{

	int *Arr1 = NULL;
	int *Arr2 = NULL;
	int split=0,lastmin=0,newcost,Iter;
	Arr1 = (int *)malloc(nwords*sizeof(int));
	if (NULL ==Arr1)
		ExitFunc("No Mem");
	Arr2 = (int *)malloc(nwords*sizeof(int));
	if (!Arr2)
		ExitFunc("No Mem");

	memset(Arr1,0,nwords*sizeof(int));
	memset(Arr2,0,nwords*sizeof(int));

	for(Iter=nwords-1;Iter>=0;Iter--) {
		if (*(*(DbPtrToMatHead+Iter) + (nwords -1)) != INF) {
			Arr1[Iter] = *(*(DbPtrToMatHead + Iter) + (nwords -1));
			Arr2[Iter] = nwords;
		}
		else {
			lastmin=0;
			for(split=nwords-1;split>=Iter;split--) {
				if ((DbPtrToMatHead[Iter][split-1] != INF) /*&& (DbPtrToMatHead[Iter][split-1] !=INF)*/) {
//					newcost = DbPtrToMatHead[split][nwords-1] + DbPtrToMatHead[Iter][split-1];
					newcost = DbPtrToMatHead[Iter][split-1] + Arr1[split];
					
					if ((newcost < lastmin) || !lastmin) {
						lastmin = newcost;
						Arr1[Iter] = newcost;
						Arr2[Iter] = split;
					}
				}
			}			
		}

	}
	
	for(Iter=0;Iter<nwords;Iter++) {
		
		PDEBUG("Arr2[%d] = [%d]",Iter,Arr2[Iter]);
	}	
		for(Iter=0;Iter<nwords;Iter++) {
		
		PDEBUG("Arr1[%d] = [%d]",Iter,Arr1[Iter]);
	}	
	
}




