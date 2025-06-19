#ifndef _FND_LIB_H_
#define _FND_LIB_H_

#define MAX_FND_NUM         6
#define FND_DATA_BUFF_LEN   (MAX_FND_NUM + 2)

#define MODE_STATIC_DIS 0
#define MODE_TIME_DIS 1
#define MODE_COUNT_DIS 2


typedef struct FNDWriteDataForm_tag
{
   char   DataNumeric[FND_DATA_BUFF_LEN];
   char   DataDot[FND_DATA_BUFF_LEN];
   char   DataValid[FND_DATA_BUFF_LEN];
} stFndWriteForm;


int fndLibInit(void);
int fndDisp(int num, int dotflag);
void fndLibExit(void);

#endif
