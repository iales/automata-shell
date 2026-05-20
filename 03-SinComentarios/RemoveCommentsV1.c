#include <stdio.h>

void N(void);
void SE(void);
void LC(void);
void BC(void);
void BCS(void);
void STR(void);
void CHR(void);
void ESC_STR(void);
void ESC_CHR(void);

int main(){
    N();
}

void N(void){
    int c = getchar();

    switch (c){
    case '/':
        SE();
        break;

    case '\"':
        putchar(c);
        STR();
        break;

    case '\'':
        putchar(c);
        CHR();
        break;
    
    case EOF:
        return;

    default:
        putchar(c);
        N();
        break;
    }
    return;
}

void SE(void){
    int c = getchar();

    switch (c){
    case '/':
        LC();
        break;

    case '*':
        BC();
        break;

    case '\"':
        putchar('/'); 
        putchar(c);
        STR();
        break;

    case '\'':
        putchar('/'); 
        putchar(c);
        CHR();
        break;
    
    case EOF:
        return;

    default:
        putchar('/'); 
        putchar(c);
        N();
        break;
    }
    return;
}

void LC(void){
    int c = getchar();

    switch (c){
    case '\n':
        putchar(' ');
        putchar(c);
        N();
        break;
    
    case EOF:
        return;

    default:
        LC();
        break;
    }
    return;
}

void BC(void){
    int c = getchar();

    switch (c){
    case '*':
        BCS();
        break;
    
    case EOF:
        return;

    default:
        BC();
        break;
    }
    return;
}

void BCS(void){
    int c = getchar();

    switch (c){
    case '*':
        BCS();
        break;
    
    case '/':
        putchar(' ');
        N();
        break;

    case EOF:
        return;

    default:
        BC();
        break;
    }
    return;
}

void STR(void){
    int c = getchar();

    switch (c){
    case '\"':
        putchar(c);
        N();
        break;
    
    case '\\':
        putchar(c);
        ESC_STR();
        break;

    case EOF:
        return;

    default:
        putchar(c);
        STR();
        break;
    }
    return;
}

void CHR(void){
    int c = getchar();

    switch (c){
    case '\'':
        putchar(c);
        N();
        break;
    
    case '\\':
        putchar(c);
        ESC_CHR();
        break;

    case EOF:
        return;

    default:
        putchar(c);
        CHR();
        break;
    }
    return;
}

void ESC_STR(void){
    int c = getchar();

    switch (c){
    case EOF:
        return;

    default:
        putchar(c);
        STR();
        break;
    }
    return;
}

void ESC_CHR(void){
    int c = getchar();

    switch (c){
    case EOF:
        return;

    default:
        putchar(c);
        CHR();
        break;
    }
    return;
}