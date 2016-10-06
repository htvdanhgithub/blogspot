/* 
 * File:   myutils.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 12:30 PM
 */

#ifndef MYUTILS_H
#define	MYUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _CONCAT(a,b) a##b
#define _CONCAT2(port,pos)  TRIS##port##bits.TRIS##port##pos
#define _CONCAT3(port,pos)  R##port##pos
#define _CONCAT4(port, pos) IOC##port##Pbits.IOC##port##P##pos
#define _CONCAT5(port, pos) IOC##port##Fbits.IOC##port##F##pos
#define _CONCAT6(a,b) a,##b
#define _CONCAT7(port, pos) ANSEL##port##bits.ANS##port##pos

#define PORT(x) _CONCAT(PORT,x)
#define TRIS(x) _CONCAT(TRIS,x)
#define TRISBIT(__port,__pos) _CONCAT2(__port,__pos)
#define PORTBIT(__port,__pos) _CONCAT3(__port,__pos)

#define PIN(__port,__pos)     _CONCAT6(__port,__pos)

#define IOCPBIT(__port,__pos) _CONCAT4(__port,__pos)
#define IOCFBIT(__port,__pos) _CONCAT5(__port,__pos)

#define IO_INPUT(__port,__pos) (TRISBIT(__port,__pos) = 1)
#define IO_OUTPUT(__port,__pos) (TRISBIT(__port,__pos) = 0)
    
#define ANSELBIT(__port,__pos) _CONCAT7(__port,__pos)
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* MYUTILS_H */

