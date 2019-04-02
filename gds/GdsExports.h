
#ifndef GdsExports_h
#define GdsExports_h

#ifdef _WIN32
    #ifdef gds_EXPORTS
        #define  GDS_EXPORT __declspec( dllexport )
    #else
        #define  GDS_EXPORT __declspec( dllimport )
    #endif
#else
    #define    GDS_EXPORT
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>

//for delete
#include <math.h>

#endif // GdsExports_h
