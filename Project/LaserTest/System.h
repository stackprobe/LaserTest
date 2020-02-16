#define error() \
	error2(__FILE__, __LINE__, __FUNCTION__)

#define errorCase(status) \
	do { \
	if((status)) error(); \
	} while(0)

void error2(char *source, int lineno, char *function);

#define l_x(message) \
	l2_x(__FILE__, __LINE__, __FUNCTION__, (message))

void l2_x(char *source, int lineno, char *function, char *message);

void *memAlloc(int size);
void *memCalloc(int size);
void *memRealloc(void *block, int size);
void memFree(void *block);
void *memClone(void *block, int size);

// 'New Array'
#define na_(type_t, count) \
	((type_t *)memCalloc(sizeof(type_t) * (count)))

// 'New Block'
#define nb_(type_t) \
	(na_(type_t, 1))

// 'Clear Array'
#define ca_(block, type_t, count) \
	(memset((block), 0x00, sizeof(type_t) * (count)))

// 'Clear Block'
#define cb_(block, type_t) \
	(ca_((block), type_t, 1))
