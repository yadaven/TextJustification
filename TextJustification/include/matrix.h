#ifndef __MATRIX__
#define __MATRIX__
struct MatrixOp {
	void (*print)(void *);
	int (*getsize)(void);
};

typedef struct MatrixOp MatrixOp_st;
#endif
