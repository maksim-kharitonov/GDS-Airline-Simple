#include "GdsExports.h"

#ifdef __cplusplus
#define CEXTERN extern "C"
#else
#define CEXTERN
#endif

using namespace std;

CEXTERN Sirena_API core::BaseGDS *__cdecl CreateGDS(map<string,string> _param);