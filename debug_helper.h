#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

#define ds(s) printf("\nDEBUG--*"#s " : %s*\n", s);
#define dc(c) printf("\nDEBUG--%"#c " : %c%\n", c);
#define di(i) printf("\nDEBUG--#"#i " : %d#\n", i);
//#define dd(d) printf("\nDEBUG--$"#d " : %.15f\n", *(double*)d);
#define dd(d) printf("\nDEBUG--$"#d " : %.15f\n", d);
#endif
