/*
 * platform_types.h
 *
 * Created on : Sep 25, 2025
 *     Author : Eng. Belal Hani Abu Sabha
 */
// Platform Types without using stdint.h 

// Header Protection
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
                                                             

typedef _Bool      boolean;
#ifndef FALSE
#define FALSE     (boolean)0
#endif
#ifndef TRUE
#define TRUE     (boolean)1
#endif


typedef unsigned char         uint8_t;
typedef unsigned short        uint16_t;
typedef unsigned int          uint32_t;
typedef unsigned long long    uint64_t; 

typedef signed char           sint8_t;
typedef signed short          sint16_t;
typedef signed int            sint32_t;
typedef signed long long      sint64_t; 


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

#endif 