/* Author : Yadavendra Yadav */

#include "generic_stuff.h"
#include "matrix.h"


void ExitFunc(char *fmt,...)
{
	va_list argp;
	va_start(argp,fmt);
	vfprintf(stderr,fmt,argp);
	va_end(argp);
	exit(EXIT_FAILURE);
}

void PrintInt(void *addr)
{
	PDEBUG("Value [%d]",*(int *)addr);
}


int GetIntSiz(void) {
	return sizeof(int);
}


int main(int argc,char **argv)
{

	char *LogFile = NULL;
	char *OptTrav = NULL;
	int fd = -1;


	int **MatrixForText = NULL;
	MatrixOp_st matst;

	char *WordList[] = {"Tushar","Roy","Loves","To","Code",NULL};
	int numwords = 0;



	while((--argc) && ((*++argv)[0] == '-')) {
		OptTrav = (*argv) + 1;
		switch(*OptTrav) {
			case 'f':
				LogFile = OptTrav+1;
				break;
			default:
				ExitFunc("Wrong Option");
				break;
		}
	}

	if (LogFile) {
		fd = open(LogFile,O_CREAT|O_RDWR|O_TRUNC);
		if (fd < 0) {
			ExitFunc("Unable to open file %s",LogFile);
		}
		if (dup2(fileno(stderr),fd) < 0) {
			ExitFunc("Unable to redirect logs to %s",LogFile);
		}	
	}

	matst.print = PrintInt;
	matst.getsize = GetIntSiz;

	numwords = GetNumWords(WordList);
	PDEBUG("Number of words %d",numwords);

	MatrixForText = (int **)Create2DimMat(numwords,numwords,&matst);
	if (NULL == MatrixForText)
		ExitFunc("Unable to create a matrix %dx%d",numwords,numwords);
	FillTextJustMatrix(MatrixForText,WordList,MAXLINCHAR);
	Print2DimMatrix((void **)MatrixForText,numwords,numwords,&matst);
	FillTextLineArr(MatrixForText,numwords);
	exit(EXIT_SUCCESS);
}
