#ifndef __GENERIC__
#define __GENERIC__

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include "matrix.h"

#if defined (__KERNEL__)
#define PDEBUG(fmt,...)		printk(KERN_INFO "%s:%s::%s:%s:%d " fmt "\n",__DATE__,__TIME__,__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
#define PDEBUG(fmt,...)		fprintf(stderr,"%s:%s::%s:%s:%d " fmt "\n",__DATE__,__TIME__,__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#endif


#define handle_error(fmt,args...)	do {\
						PDEBUG(fmt,##args);\
						PDEBUG("Errno [%d]",errno);\
						perror("System error:");\
					}while(0)


#define MAXLINCHAR 10
#define INF -1


int GetNumWords(char **WordList);
void FillTextJustMatrix(int  **DbPtrToHeadOfMat,char ** DbPtrToHeadOfWrdList, int maxcharinline);
void ** Create2DimMat(int nrow,int ncol, MatrixOp_st *OpSt);
void Print2DimMatrix(void **DbPtrToRowHead,int nrows,int ncols,MatrixOp_st *OpSt);


#endif
