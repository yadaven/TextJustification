#include "generic_stuff.h"
#include "matrix.h"


/* Input should be 
	nrow ==> number of rows
	ncol ==> number of columns
	sizofcell ==> size of a cell

   returns a double pointer starting at row address of a matrix

*/


void Print2DimMatrix(void **DbPtrToRowHead,int nrows,int ncols,MatrixOp_st *OpSt)
{
	int Iter = 0,cIter = 0;
	if (NULL == DbPtrToRowHead)
		return;
	
	for(Iter=0;Iter < nrows; Iter++) {
		for(cIter=0;cIter<ncols;cIter++) {
			PDEBUG("[%d][%d]",Iter,cIter);
			OpSt->print(*(DbPtrToRowHead+Iter) + cIter*OpSt->getsize());
		}
	}
	return;
}


void ** Create2DimMat(int nrow,int ncol, MatrixOp_st *OpSt)
{
	void **DoublePtrToMatrix = NULL;
	int Iter = 0;

	if (!nrow || !ncol)
		return NULL;

/* Create a array of pointers equal to number of rows */
	
	DoublePtrToMatrix = (void **)calloc(nrow,sizeof(void *));
	
	if (NULL == DoublePtrToMatrix) {
		PDEBUG("No Memory");
		return NULL;
	}

	*(DoublePtrToMatrix + 0) = (void *)calloc(nrow*ncol,OpSt->getsize());
	
	if (NULL == *(DoublePtrToMatrix + 0)) {
		PDEBUG("No Memory");
		goto freerow;
	}

	for(Iter = 0; Iter < nrow; Iter++) {
		*(DoublePtrToMatrix + Iter) = *(DoublePtrToMatrix + 0) + (Iter*ncol*(OpSt->getsize()));		
	}

	goto out;	

freerow:
	free(DoublePtrToMatrix);
	DoublePtrToMatrix = NULL;
out:
	return DoublePtrToMatrix;
}



