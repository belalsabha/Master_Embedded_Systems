/*
 * PLATFORM_TYPES.h
 *
 *
 *  Created on: Dec 25, 2025
 *      Author:  Belal Hani Sabha
 */


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


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




typedef unsigned char         uint8_t;
typedef unsigned short        uint16_t;
typedef unsigned int          uint32_t;
typedef unsigned long long    uint64_t;


typedef signed char           sint8_t;
typedef signed short          sint16_t;
typedef signed int            sint32_t;
typedef signed long long      sint64_t;



typedef unsigned int          uint8_least;
typedef unsigned int          uint16_least;
typedef unsigned int          uint32_least;

typedef signed int            sint8_least;
typedef signed int            sint16_least;
typedef signed int            sint32_least;





typedef float                 float32;
typedef double                float64;



typedef volatile sint8_t        vint8_t;
typedef volatile uint8_t        vuint8_t;

typedef volatile sint16_t       vint16_t;
typedef volatile uint16_t       vuint16_t;

typedef volatile sint32_t       vint32_t;
typedef volatile uint32_t       vuint32_t;

typedef volatile sint64_t       vint64_t;
typedef volatile uint64_t       vuint64_t;

#endif /* PLATFORM_TYPES_H_ */
