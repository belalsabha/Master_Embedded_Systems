// Platform Types without using stdint.h 

// Header Protection
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H


                                                 



#define CPU_TYPE_8           8
#define CPU_TYPE_16          16
#define CPU_TYPE_32          32
#define CPU_TYPE_64          64


#define MSB_FIRST            0   
#define LSB_FIRST            1   

#define CPU_TYPE             CPU_TYPE_32   
#define CPU_BIT_ORDER        LSB_FIRST     
#define CPU_BYTE_ORDER       LSB_FIRST    
                                                            

#ifndef _BOOL
#define _BOOL unsigned char
#endif

typedef _Bool               boolean;


#ifndef FALSE
#define FALSE               (boolean)0
#endif
#ifndef TRUE
#define TRUE                (boolean)1
#endif




typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned int          uint32;
typedef unsigned long long    uint64; 


typedef signed char           sint8;
typedef signed short          sint16;
typedef signed int            sint32;
typedef signed long long      sint64; 



typedef unsigned int          uint8_least;
typedef unsigned int          uint16_least;
typedef unsigned int          uint32_least;

typedef signed int            sint8_least;
typedef signed int            sint16_least;
typedef signed int            sint32_least;





typedef float                 float32;
typedef double                float64;



typedef volatile sint8        vint8_t;
typedef volatile uint8        vuint8_t;

typedef volatile sint16       vint16_t;
typedef volatile uint16       vuint16_t;

typedef volatile sint32       vint32_t;
typedef volatile uint32       vuint32_t;

typedef volatile sint64       vint64_t;
typedef volatile uint64       vuint64_t;

#endif 