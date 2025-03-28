#ifndef GETCH_H
#define GETCH_H

extern void initTermios(int echo);
extern void resetTermios(void);
extern char getch_(int echo);
extern char getch(void);

#endif //GETCH_H