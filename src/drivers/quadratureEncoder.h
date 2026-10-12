/********************************************************************/
/*              Header for QEI module library functions             */
/********************************************************************/

#ifndef __QEI_H
#define __QEI_H

/*QEI is defined in following variants */
#if defined(__dsPIC30F2010__) || defined(__dsPIC30F3010__) || defined(__dsPIC30F4012__) || \
    defined(__dsPIC30F3011__) || defined(__dsPIC30F4011__) || defined(__dsPIC30F6010__) || \
    defined(__dsPIC30F5015__) || defined(__dsPIC30F6010A__) || defined(__dsPIC30F5016__) || \
    defined(__dsPIC30F6015__)


/* QEI Function Prototypes */

void OpenQEI(unsigned int config1, unsigned int config2) __attribute__ ((section (".libperi"))); /* Configure QEI */

void CloseQEI(void) __attribute__ ((section (".libperi")));                                      /* Disables the QEI module */

void ConfigIntQEI(unsigned int) __attribute__ ((section (".libperi")));                          /* QEI interrupt configuration */

unsigned int ReadQEI(void) __attribute__ ((section (".libperi")));                               /* Read QEI result */

void WriteQEI(unsigned int position) __attribute__ ((section (".libperi")));                     /* Write QEI result */

#endif

#endif /*__QEI_H */