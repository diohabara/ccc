// -*- c -*-

// This is a line comment

/**
 * This is a block comment
 */

int g1;
int g2[4];

char g3 = 3;
short g4 = 4;
int g5 = 5;
long g6 = 6;
int *g7 = &g5;
char *g8 = "abc";

int g9[3] = {0, 1, 2};
char *g10[] = {"foo", "bar"};
struct {char a; int b;} g11[2] = {{1, 2}, {3, 4}};
struct {int a[2];} g12[2] = {{{1, 2}}, {{3, 4}}};

struct {int a[2];} g13[2] = {{1, 2}, 3, 4};
struct {int a[2];} g14[2] = {1, 2, 3, 4};
char *g15 = {"foo"};
char g16[][4] = {'f', 'o', 'o', 0, 'b', 'a', 'r', 0};

char g17[] = "foobar";
char g18[10] = "foobar";
char g19[3] = "foobar";

char *g20 = g17+0;
char *g21 = g17+3;
char *g22 = g17-3;
int g23=3;
int *g24=&g23;

int assert(long expected, long actual, char *code) {
  if (expected == actual) {
    printf("%s => %ld\n", code, actual);
  } else {
    printf("%s => %ld expected but got %ld\n", code, expected, actual);
    exit(1);
  }
}

int ret3() {
  return 3;
  return 5;
}

int add2(int x, int y) { return x + y; }

int sub2(int x, int y) { return x - y; }

int add6(int a, int b, int c, int d, int e, int f) {
  return a + b + c + d + e + f;
}

int addx(int *x, int y) { return *x + y; }

int sub_char(char a, char b, char c) { return a - b - c; }

int sub_short(short a, short b, short c) {
  return a - b - c;
}

int sub_long(long a, long b, long c) {
  return a - b - c;
}

int *g1_ptr() {
  return &g1;
}

int fib(int x) {
  if (x <= 1) return 1;
  return fib(x - 1) + fib(x - 2);
}

char char_fn();

int count() {
  static cnt;
  cnt = cnt + 1;
  return cnt;
}

int param_decay(int x[]) { return 0[x]; }

void voidfn(void) {}

static int static_fn(void) {}

extern int ext1;
extern int *ext2;
int ext_fn1(int x);
extern int ext_fn2(int x);

int main() {
  assert(8, ({ int a=3; int z=5; a+z; }), "int a=3; int z=5; a+z;");

  assert(0, 0, "0");
  assert(42, 42, "42");
  assert(5, 5, "0");
  assert(41,  12 + 34 - 5 , " 12 + 34 - 5 ");
  assert(5, 5, "0");
  assert(15, 5*(9-6), "5*(9-6)");
  assert(4, (3+5)/2, "(3+5)/2");
  assert(-10, -10, "0");
  assert(10, - -10, "- -10");
  assert(10, - - +10, "- - +10");

  assert(0, 0==1, "0==1");
  assert(1, 42==42, "42==42");
  assert(1, 0!=1, "0!=1");
  assert(0, 42!=42, "42!=42");

  assert(1, 0<1, "0<1");
  assert(0, 1<1, "1<1");
  assert(0, 2<1, "2<1");
  assert(1, 0<=1, "0<=1");
  assert(1, 1<=1, "1<=1");
  assert(0, 2<=1, "2<=1");

  assert(1, 1>0, "1>0");
  assert(0, 1>1, "1>1");
  assert(0, 1>2, "1>2");
  assert(1, 1>=0, "1>=0");
  assert(1, 1>=1, "1>=1");
  assert(0, 1>=2, "1>=2");

  assert(3, ({ int a; a=3; a; }), "int a; a=3; a;");
  assert(8, ({ int a; int z; a=3; z=5; a+z; }), "int a; int z; a=3; z=5; a+z;");
  assert(3, ({ int a=3; a; }), "int a=3; a;");
  assert(8, ({ int a=3; int z=5; a+z; }), "int a=3; int z=5; a+z;");

  assert(3, ({ int foo=3; foo; }), "int foo=3; foo;");
  assert(8, ({ int foo123=3; int bar=5; foo123+bar; }), "int foo123=3; int bar=5; foo123+bar;");

  assert(3, ret3(), "ret3();");

  assert(3, ({ int x=0; if (0) x=2; else x=3; x; }), "int x=0; if (0) x=2; else x=3; x;");
  assert(3, ({ int x=0; if (1-1) x=2; else x=3; x; }), "int x=0; if (1-1) x=2; else x=3; x;");
  assert(2, ({ int x=0; if (1) x=2; else x=3; x; }), "int x=0; if (1) x=2; else x=3; x;");
  assert(2, ({ int x=0; if (2-1) x=2; else x=3; x; }), "int x=0; if (2-1) x=2; else x=3; x;");

  assert(3, ({ 1; {2;} 3; }), "1; {2;} 3;");
  assert(10, ({ int i=0; i=0; while(i<10) i=i+1; i; }), "int i=0; i=0; while(i<10) i=i+1; i;");
  assert(55, ({ int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} j; }), "int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} j;");
  assert(55, ({ int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; j; }), "int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; j;");

  assert(8, add2(3, 5), "add(3, 5)");
  assert(2, sub2(5, 3), "sub(5, 3)");
  assert(21, add6(1,2,3,4,5,6), "add6(1,2,3,4,5,6)");
  assert(55, fib(9), "fib(9)");

  assert(3, ({ int x=3; *&x; }), "int x=3; *&x;");
  assert(3, ({ int x=3; int *y=&x; int **z=&y; **z; }), "int x=3; int *y=&x; int **z=&y; **z;");
  assert(5, ({ int x=3; int y=5; *(&x+1); }), "int x=3; int y=5; *(&x+1);");
  assert(5, ({ int x=3; int y=5; *(1+&x); }), "int x=3; int y=5; *(1+&x);");
  assert(3, ({ int x=3; int y=5; *(&y-1); }), "int x=3; int y=5; *(&y-1);");
  assert(5, ({ int x=3; int y=5; int *z=&x; *(z+1); }), "int x=3; int y=5; int *z=&x; *(z+1);");
  assert(3, ({ int x=3; int y=5; int *z=&y; *(z-1); }), "int x=3; int y=5; int *z=&y; *(z-1);");
  assert(5, ({ int x=3; int *y=&x; *y=5; x; }), "int x=3; int *y=&x; *y=5; x;");
  assert(7, ({ int x=3; int y=5; *(&x+1)=7; y; }), "int x=3; int y=5; *(&x+1)=7; y;");
  assert(7, ({ int x=3; int y=5; *(&y-1)=7; x; }), "int x=3; int y=5; *(&y-1)=7; x;");
  assert(8, ({ int x=3; int y=5; addx(&x, y); }), "int x=3; int y=5; addx(&x, y);");

  assert(3, ({ int x[2]; int *y=&x; *y=3; *x; }), "int x[2]; int *y=&x; *y=3; *x;");

  assert(3, ({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *x; }), "int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *x;");
  assert(4, ({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+1); }), "int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+1);");
  assert(5, ({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+2); }), "int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+2);");

  assert(0, ({ int x[2][3]; int *y=x; *y=0; **x; }), "int x[2][3]; int *y=x; *y=0; **x;");
  assert(1, ({ int x[2][3]; int *y=x; *(y+1)=1; *(*x+1); }), "int x[2][3]; int *y=x; *(y+1)=1; *(*x+1);");
  assert(2, ({ int x[2][3]; int *y=x; *(y+2)=2; *(*x+2); }), "int x[2][3]; int *y=x; *(y+2)=2; *(*x+2);");
  assert(3, ({ int x[2][3]; int *y=x; *(y+3)=3; **(x+1); }), "int x[2][3]; int *y=x; *(y+3)=3; **(x+1);");
  assert(4, ({ int x[2][3]; int *y=x; *(y+4)=4; *(*(x+1)+1); }), "int x[2][3]; int *y=x; *(y+4)=4; *(*(x+1)+1);");
  assert(5, ({ int x[2][3]; int *y=x; *(y+5)=5; *(*(x+1)+2); }), "int x[2][3]; int *y=x; *(y+5)=5; *(*(x+1)+2);");
  assert(6, ({ int x[2][3]; int *y=x; *(y+6)=6; **(x+2); }), "int x[2][3]; int *y=x; *(y+6)=6; **(x+2);");

  assert(3, ({ int x[3]; *x=3; x[1]=4; x[2]=5; *x; }), "int x[3]; *x=3; x[1]=4; x[2]=5; *x;");
  assert(4, ({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+1); }), "int x[3]; *x=3; x[1]=4; x[2]=5; *(x+1);");
  assert(5, ({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2); }), "int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2);");
  assert(5, ({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2); }), "int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2);");
  assert(5, ({ int x[3]; *x=3; x[1]=4; 2[x]=5; *(x+2); }), "int x[3]; *x=3; x[1]=4; 2[x]=5; *(x+2);");

  assert(0, ({ int x[2][3]; int *y=x; y[0]=0; x[0][0]; }), "int x[2][3]; int *y=x; y[0]=0; x[0][0];");
  assert(1, ({ int x[2][3]; int *y=x; y[1]=1; x[0][1]; }), "int x[2][3]; int *y=x; y[1]=1; x[0][1];");
  assert(2, ({ int x[2][3]; int *y=x; y[2]=2; x[0][2]; }), "int x[2][3]; int *y=x; y[2]=2; x[0][2];");
  assert(3, ({ int x[2][3]; int *y=x; y[3]=3; x[1][0]; }), "int x[2][3]; int *y=x; y[3]=3; x[1][0];");
  assert(4, ({ int x[2][3]; int *y=x; y[4]=4; x[1][1]; }), "int x[2][3]; int *y=x; y[4]=4; x[1][1];");
  assert(5, ({ int x[2][3]; int *y=x; y[5]=5; x[1][2]; }), "int x[2][3]; int *y=x; y[5]=5; x[1][2];");
  assert(6, ({ int x[2][3]; int *y=x; y[6]=6; x[2][0]; }), "int x[2][3]; int *y=x; y[6]=6; x[2][0];");

  assert(4, ({ int x; sizeof(x); }), "int x; sizeof(x);");
  assert(4, ({ int x; sizeof x; }), "int x; sizeof x;");
  assert(8, ({ int *x; sizeof(x); }), "int *x; sizeof(x);");
  assert(16, ({ int x[4]; sizeof(x); }), "int x[4]; sizeof(x);");
  assert(48, ({ int x[3][4]; sizeof(x); }), "int x[3][4]; sizeof(x);");
  assert(16, ({ int x[3][4]; sizeof(*x); }), "int x[3][4]; sizeof(*x);");
  assert(4, ({ int x[3][4]; sizeof(**x); }), "int x[3][4]; sizeof(**x);");
  assert(5, ({ int x[3][4]; sizeof(**x) + 1; }), "int x[3][4]; sizeof(**x) + 1;");
  assert(5, ({ int x[3][4]; sizeof **x + 1; }), "int x[3][4]; sizeof **x + 1;");
  assert(4, ({ int x[3][4]; sizeof(**x + 1); }), "int x[3][4]; sizeof(**x + 1);");

  assert(0, g1, "g1");
  g1=3;
  assert(3, g1, "g1");

  g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3;
  assert(0, g2[0], "g2[0]");
  assert(1, g2[1], "g2[1]");
  assert(2, g2[2], "g2[2]");
  assert(3, g2[3], "g2[3]");

  assert(4, sizeof(g1), "sizeof(g1)");
  assert(16, sizeof(g2), "sizeof(g2)");

  assert(1, ({ char x=1; x; }), "char x=1; x;");
  assert(1, ({ char x=1; char y=2; x; }), "char x=1; char y=2; x;");
  assert(2, ({ char x=1; char y=2; y; }), "char x=1; char y=2; y;");

  assert(1, ({ char x; sizeof(x); }), "char x; sizeof(x);");
  assert(10, ({ char x[10]; sizeof(x); }), "char x[10]; sizeof(x);");
  assert(1, sub_char(7, 3, 3), "sub_char(7, 3, 3)");

  assert(97, "abc"[0], "\"abc\"[0]");
  assert(98, "abc"[1], "\"abc\"[1]");
  assert(99, "abc"[2], "\"abc\"[2]");
  assert(0, "abc"[3], "\"abc\"[3]");
  assert(4, sizeof("abc"), "sizeof(\"abc\")");

  assert(7, "\a"[0], "\"\\a\"[0]");
  assert(8, "\b"[0], "\"\\b\"[0]");
  assert(9, "\t"[0], "\"\\t\"[0]");
  assert(10, "\n"[0], "\"\\n\"[0]");
  assert(11, "\v"[0], "\"\\v\"[0]");
  assert(12, "\f"[0], "\"\\f\"[0]");
  assert(13, "\r"[0], "\"\\r\"[0]");
  assert(27, "\e"[0], "\"\\e\"[0]");
  assert(0, "\0"[0], "\"\\0\"[0]");

  assert(106, "\j"[0], "\"\\j\"[0]");
  assert(107, "\k"[0], "\"\\k\"[0]");
  assert(108, "\l"[0], "\"\\l\"[0]");

  assert(2, ({ int x=2; { int x=3; } x; }), "int x=2; { int x=3; } x;");
  assert(2, ({ int x=2; { int x=3; } int y=4; x; }), "int x=2; { int x=3; } int y=4; x;");
  assert(3, ({ int x=2; { x=3; } x; }), "int x=2; { x=3; } x;");

  assert(1, ({ struct {int a; int b;} x; x.a=1; x.b=2; x.a; }), "struct {int a; int b;} x; x.a=1; x.b=2; x.a;");
  assert(2, ({ struct {int a; int b;} x; x.a=1; x.b=2; x.b; }), "struct {int a; int b;} x; x.a=1; x.b=2; x.b;");
  assert(1, ({ struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.a; }), "struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.a;");
  assert(2, ({ struct {char a; int b; char c;} x; x.b=1; x.b=2; x.c=3; x.b; }), "struct {char a; int b; char c;} a; x.b=x; x.a=2; x.b=3; x.b;");
  assert(3, ({ struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.c; }), "struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.c;");

  assert(0, ({ struct {int a; int b;} x[3]; int *p=x; p[0]=0; x[0].a; }), "struct {int a; int b;} x[3]; int *p=x; p[0]=0; x[0].a;");
  assert(1, ({ struct {int a; int b;} x[3]; int *p=x; p[1]=1; x[0].b; }), "struct {int a; int b;} x[3]; int *p=x; p[1]=1; x[0].b;");
  assert(2, ({ struct {int a; int b;} x[3]; int *p=x; p[2]=2; x[1].a; }), "struct {int a; int b;} x[3]; int *p=x; p[2]=2; x[1].a;");
  assert(3, ({ struct {int a; int b;} x[3]; int *p=x; p[3]=3; x[1].b; }), "struct {int a; int b;} x[3]; int *p=x; p[3]=3; x[1].b;");

  assert(6, ({ struct {int a[3]; int b[5];} x; int *p=&x; x.a[0]=6; p[0]; }), "struct {int a[3]; int b[5];} x; int *p=&x; x.a[0]=6; p[0];");
  assert(7, ({ struct {int a[3]; int b[5];} x; int *p=&x; x.b[0]=7; p[3]; }), "struct {int a[3]; int b[5];} x; int *p=&x; x.b[0]=7; p[3];");

  assert(6, ({ struct { struct { int b; } a; } x; x.a.b=6; x.a.b; }), "struct { struct { int b; } a; } x; x.a.b=6; x.a.b;");

  assert(4, ({ struct {int a;} x; sizeof(x); }), "struct {int a;} x; sizeof(x);");
  assert(8, ({ struct {int a; int b;} x; sizeof(x); }), "struct {int a; int b;} x; sizeof(x);");
  assert(12, ({ struct {int a[3];} x; sizeof(x); }), "struct {int a[3];} x; sizeof(x);");
  assert(16, ({ struct {int a;} x[4]; sizeof(x); }), "struct {int a;} x[4]; sizeof(x);");
  assert(24, ({ struct {int a[3];} x[2]; sizeof(x); }), "struct {int a[3];} x[2]; sizeof(x)};");
  assert(2, ({ struct {char a; char b;} x; sizeof(x); }), "struct {char a; char b;} x; sizeof(x);");
  assert(8, ({ struct {char a; int b;} x; sizeof(x); }), "struct {char a; int b;} x; sizeof(x);");
  assert(8, ({ struct {int a; char b;} x; sizeof(x); }), "struct {int a; char b;} x; sizeof(x);");

  assert(7, ({ int x; char y; int a=&x; int b=&y; b-a; }), "int x; char y; int a=&x; int b=&y; b-a;");
  assert(1, ({ char x; int y; int a=&x; int b=&y; b-a; }), "char x; int y; int a=&x; int b=&y; b-a;");

  assert(2, ({ struct t {char a[2];}; { struct t {char a[4];}; } struct t y; sizeof(y); }), "struct t {char a[2];}; { struct t {char a[4];}; } struct t y; sizeof(y);");
  assert(3, ({ struct t {int x;}; int t=1; struct t y; y.x=2; t+y.x; }), "struct t {int x;}; int t=1; struct t y; y.x=2; t+y.x;");

  assert(3, ({ struct t {char a;} x; struct t *y = &x; x.a=3; y->a; }), "struct t {char a;} x; struct t *y = &x; x.a=3; y->a;");
  assert(3, ({ struct t {char a;} x; struct t *y = &x; y->a=3; x.a; }), "struct t {char a;} x; struct t *y = &x; y->a=3; x.a;");

  assert(1, ({ typedef int t; t x=1; x; }), "typedef int t; t x=1; x;");
  assert(1, ({ typedef struct {int a;} t; t x; x.a=1; x.a; }), "typedef struct {int a;} t; t x; x.a=1; x.a;");
  assert(1, ({ typedef int t; t t=1; t; }), "typedef int t; t t=1; t;");
  assert(2, ({ typedef struct {int a;} t; { typedef int t; } t x; x.a=2; x.a; }), "typedef struct {int a;} t; { typedef int t; } t x; x.a=2; x.a;");
  assert(3, ({ typedef struct Token Token; struct Token { Token *next; int x; }; Token t; t.x=3; t.x; }), "edef struct Token Token; struct Token {Token* next; int x}; Token t; t.x=3; t.x; ");

  assert(8, ({ struct t {int a; int b;} x; struct t y; sizeof(y); }), "struct t {int a; int b;} x; struct t y; sizeof(y);");
  assert(8, ({ struct t {int a; int b;}; struct t y; sizeof(y); }), "struct t {int a; int b;}; struct t y; sizeof(y);");

  assert(2, ({ short x; sizeof(x); }), "short x; sizeof(x);");
  assert(4, ({ struct {char a; short b;} x; sizeof(x); }), "struct {char a; short b;} x; sizeof(x);");

  assert(8, ({ long x; sizeof(x); }), "long x; sizeof(x);");
  assert(16, ({ struct {char a; long b;} x; sizeof(x); }), "struct {char a; long b} x; sizeof(x);");

  assert(1, sub_short(7, 3, 3), "sub_short(7, 3, 3)");
  assert(1, sub_long(7, 3, 3), "sub_long(7, 3, 3)");

  assert(24, ({ int *x[3]; sizeof(x); }), "int *x[3]; sizeof(x);");
  assert(8, ({ int (*x)[3]; sizeof(x); }), "int (*x)[3]; sizeof(x);");
  assert(3, ({ int *x[3]; int y; x[0]=&y; y=3; x[0][0]; }), "int *x[3]; int y; x[0]=&y; y=3; x[0][0];");
  assert(4, ({ int x[3]; int (*y)[3]=x; y[0][0]=4; y[0][0]; }), "int x[3]; int (*y)[3]=x; y[0][0]=4; y[0][0];");

  assert(3, *g1_ptr(), "*g1_ptr()");

  { void *x; }

  assert(0, ({ _Bool x=0; x; }), "_Bool x=0; x;");
  assert(1, ({ _Bool x=1; x; }), "_Bool x=1; x;");
  assert(1, ({ _Bool x=2; x; }), "_Bool x=2; x;");

  assert(1, ({ char x; sizeof(x); }), "char x; sizeof(x);");
  assert(2, ({ short int x; sizeof(x); }), "short int x; sizeof(x);");
  assert(2, ({ int short x; sizeof(x); }), "int short x; sizeof(x);");
  assert(4, ({ int x; sizeof(x); }), "int x; sizeof(x);");
  assert(4, ({ typedef t; t x; sizeof(x); }), "typedef t; t x; sizeof(x);");
  assert(8, ({ long int x; sizeof(x); }), "long int x; sizeof(x);");
  assert(8, ({ int long x; sizeof(x); }), "int long x; sizeof(x);");

  assert(1, sizeof(char), "sizeof(char)");
  assert(2, sizeof(short), "sizeof(short)");
  assert(2, sizeof(short int), "sizeof(short int)");
  assert(2, sizeof(int short), "sizeof(int short)");
  assert(4, sizeof(int), "sizeof(int)");
  assert(8, sizeof(long), "sizeof(long)");
  assert(8, sizeof(long int), "sizeof(long int)");
  assert(8, sizeof(long int), "sizeof(long int)");
  assert(8, sizeof(char *), "sizeof(char *)");
  assert(8, sizeof(int *), "sizeof(int *)");
  assert(8, sizeof(long *), "sizeof(long *)");
  assert(8, sizeof(int **), "sizeof(int **)");
  assert(8, sizeof(int(*)[4]), "sizeof(int(*)[4])");
  assert(32, sizeof(int*[4]), "sizeof(int(*)[4])");
  assert(16, sizeof(int[4]), "sizeof(int[4])");
  assert(48, sizeof(int[3][4]), "sizeof(int[3][4])");

  assert(4, sizeof(0), "sizeof(0)");
  assert(4294967297, 4294967297, "4294967297");
  assert(8, sizeof(4294967297), "sizeof(4294967297)");

  assert(131585, (int)8590066177, "(int)8590066177");
  assert(513, (short)8590066177, "(short)8590066177");
  assert(1, (char)8590066177, "(char)8590066177");
  assert(1, (_Bool)1, "(_Bool)1");
  assert(1, (_Bool)2, "(_Bool)2");
  assert(0, (_Bool)(char)256, "(_Bool)(char)256");
  assert(1, (long)1, "(long)1");
  assert(0, (long)&*(int *)0, "(long)&*(int *)0");
  assert(5, ({ int x=5; long y=(long)&x; *(int*)y; }), "int x=5; long y=(long)&x; *(int*)y");

  assert(97, 'a', "'a'");
  assert(10, '\n', "\'\\n\'");

  assert(1, char_fn(), "char_fn()");

  assert(0, ({ enum { zero, one, two }; zero; }), "enum { zero, one, two }; zero;");
  assert(1, ({ enum { zero, one, two }; one; }), "enum { zero, one, two }; one;");
  assert(2, ({ enum { zero, one, two }; two; }), "enum { zero, one, two }; two;");
  assert(5, ({ enum { five=5, six, seven }; five; }), "enum { five=5, six, seven }; five;");
  assert(6, ({ enum { five=5, six, seven }; six; }), "enum { five=5, six, seven }; six;");
  assert(0, ({ enum { zero, five=5, three=3, four }; zero; }), "enum { zero, five=5, three=3, four }; zero;");
  assert(5, ({ enum { zero, five=5, three=3, four }; five; }), "enum { zero, five=5, three=3, four }; five;");
  assert(3, ({ enum { zero, five=5, three=3, four }; three; }), "enum { zero, five=5, three=3, four }; three;");
  assert(4, ({ enum { zero, five=5, three=3, four }; four; }), "enum { zero, five=5, three=3, four }; four;");
  assert(4, ({ enum { zero, one, two } x; sizeof(x); }), "enum { zero, one, two } x; sizeof(x);");
  assert(4, ({ enum t { zero, one, two }; enum t y; sizeof(y); }), "enum t { zero, one, two }; enum t y; sizeof(y);");
  assert(4, ({ typedef enum { zero, one, two} t; t y; sizeof(y); }), "typedef enum { zero, one, two} t; enum t y; sizeof(y);");
  assert(1, ({ typedef enum { TK_RESERVED, } TokenKind; typedef struct Token Token; struct Token { TokenKind kind; Token *next; int x; }; Token t; t.x=1; t.x; }),
    "typedef enum { TK_RESERVED, } TokenKind; typedef struct Token Token; struct Token { TokenKind kind; Token *next; int x; }; Token t; t.x=1; t.x;");

  assert(1, count(), "count()");
  assert(2, count(), "count()");
  assert(3, count(), "count()");

  assert(55, ({ int j=0; for (int i=0; i<=10; i=i+1) j=j+i; j; }), "int j=0; for (int i=0; i<=10; i=i+1) j=j+i; j;");
  assert(3, ({ int i=3; int j=0; for (int i=0; i<=10; i=i+1) j=j+i; i; }), "int i=3; int j=0; for (int i=0; i<=10; i=i+1) j=j+i; i;");

  assert(3, (1,2,3), "(1,2,3)");

  assert(3, ({ int i=2; ++i; }), "int i=2; ++i;");
  assert(1, ({ int i=2; --i; }), "int i=2; --i;");
  assert(2, ({ int i=2; i++; }), "int i=2; i++;");
  assert(2, ({ int i=2; i--; }), "int i=2; i--;");
  assert(3, ({ int i=2; i++; i; }), "int i=2; i++; i;");
  assert(1, ({ int i=2; i--; i; }), "int i=2; i--; i;");
  assert(1, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++;");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; ++*p; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; ++*p;");
  assert(1, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p--; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p--;");
  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; --*p; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; --*p;");

  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[0]; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++); a[0];");
  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[1]; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++); a[0];");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[2]; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++); a[0];");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; *p; }), "int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++); a[0];");

  assert(7, ({ int i=2; i+=5; i; }), "int i=2; i+=5; i;");
  assert(7, ({ int i=2; i+=5; }), "int i=2; i+=5;");
  assert(3, ({ int i=5; i-=2; i; }), "int i=5; i-=2; i;");
  assert(3, ({ int i=5; i-=2; }), "int i=5; i-=2;");
  assert(6, ({ int i=3; i*=2; i; }), "int i=3; i*=2; i;");
  assert(6, ({ int i=3; i*=2; }), "int i=3; i*=2;");
  assert(3, ({ int i=6; i/=2; i; }), "int i=6; i/=2; i;");
  assert(3, ({ int i=6; i/=2; }), "int i=6; i/=2;");

  assert(0, !1, "!1");
  assert(0, !2, "!2");
  assert(1, !0, "!0");

  assert(-1, ~0, "~0");
  assert(0, ~-1, "~-1");

  assert(0, 0&1, "0&1");
  assert(1, 3&1, "3&1");
  assert(3, 7&3, "7&3");
  assert(10, -1&10, " -1&10");

  assert(1, 0|1, "0|1");
  assert(3, 2|1, "2|1");
  assert(3, 1|3, "1|3");

  assert(0, 0^0, "0^0");
  assert(0, 8^8, "8^8");
  assert(4, 7^3, "7^3");
  assert(2, 7^5, "7^5");

  assert(1, 0||1, "0||1");
  assert(1, 0||(2-2)||5, "0||(2-2)||5");
  assert(0, 0||0, "0||0");
  assert(0, 0||(2-2), "0||(2-2)");

  assert(0, 0&&1, "0&&1");
  assert(0, (2-2)&&5, "(2-2)&&5");
  assert(1, 1&&5, "1&&5");

  assert(3, ({ int x[2]; x[0]=3; param_decay(x); }), "int x[2]; x[0]=3; param_decay(x);");

  assert(8, ({ struct *foo; sizeof(foo); }), "struct *foo; sizeof(foo);");
  assert(4, ({ struct T *foo; struct T {int x;}; sizeof(struct T); }), "struct T *foo; struct T {int x;}; sizeof(struct T);");
  assert(1, ({ struct T { struct T *next; int x; } a; struct T b; b.x=1; a.next=&b; a.next->x; }), "struct T { struct T *next; int x; } a; struct T b; b.x=1; a.next=&b; a.next->x;");

  assert(3, ({ int i=0; for(;i<10;i++) { if (i == 3) break; } i; }), "int i=0; for(;i<10;i++) { if (i == 3) break; } i;");
  assert(4, ({ int i=0; while (1) { if (i++ == 3) break; } i; }), "int i=0; while { if (i == 3) break; } i;");
  assert(3, ({ int i=0; for(;i<10;i++) { for (;;) break; if (i == 3) break; } i; }), "int i=0; for(;i<10;i++) { if (i == 3) break; } i;");
  assert(4, ({ int i=0; while (1) { while(1) break; if (i++ == 3) break; } i; }), "int i=0; while { if (i == 3) break; } i;");

  assert(10, ({ int i=0; int j=0; for (;i<10;i++) { if (i>5) continue; j++; } i; }), "int i=0; int j=0; for (;i<10;i++) { if (i>5) continue; j++; } i;");
  assert(6, ({ int i=0; int j=0; for (;i<10;i++) { if (i>5) continue; j++; } j; }), "int i=0; int j=0; for (;i<10;i++) { if (i>5) continue; j++; } j;");
  assert(10, ({ int i=0; int j=0; for(;!i;) { for (;j!=10;j++) continue; break; } j; }), "int i=0; int j=0; for(;!i;) { for (;j!=10;j++) continue; break; } j;");
  assert(11, ({ int i=0; int j=0; while (i++<10) { if (i>5) continue; j++; } i; }), "int i=0; int j=0; while (i++<10) { if (i>5) continue; j++; } i;");
  assert(5, ({ int i=0; int j=0; while (i++<10) { if (i>5) continue; j++; } j; }), "int i=0; int j=0; while (i++<10) { if (i>5) continue; j++; } j;");
  assert(11, ({ int i=0; int j=0; while(!i) { while (j++!=10) continue; break; } j; }), "int i=0; int j=0; while(!i) { while (j++!=10) continue; break; } j;");

  assert(3, ({ int i=0; goto a; a: i++; b: i++; c: i++; i; }), "int i=0; goto a; a: i++; b: i++; c: i++; i;");
  assert(2, ({ int i=0; goto e; d: i++; e: i++; f: i++; i; }), "int i=0; goto d; d: i++; e: i++; f: i++; i;");
  assert(1, ({ int i=0; goto i; g: i++; h: i++; i: i++; i; }), "int i=0; goto g; h: i++; i: i++; j: i++; i;");

  assert(5, ({ int i=0; switch(0) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i; }), "int i=0; switch(0) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i;");
  assert(6, ({ int i=0; switch(1) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i; }), "int i=0; switch(1) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i;");
  assert(7, ({ int i=0; switch(2) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i; }), "int i=0; switch(2) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i;");
  assert(0, ({ int i=0; switch(3) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i; }), "int i=0; switch(3) { case 0:i=5;break; case 1:i=6;break; case 2:i=7;break; } i;");
  assert(5, ({ int i=0; switch(0) { case 0:i=5;break; default:i=7; } i; }), "int i=0; switch(0) { case 0:i=5;break; default:i=7; } i;");
  assert(7, ({ int i=0; switch(1) { case 0:i=5;break; default:i=7; } i; }), "int i=0; switch(1) { case 0:i=5;break; default:i=7; } i;");

  voidfn();

  assert(1, 1<<0, "1<<0");
  assert(8, 1<<3, "1<<3");
  assert(10, 5<<1, "5<<1");
  assert(2, 5>>1, "5>>1");
  assert(-1, -1>>1, "-1>>1");
  assert(1, ({ int i=1; i<<=0; i; }), "int i=1; i<<0;");
  assert(8, ({ int i=1; i<<=3; i; }), "int i=1; i<<3;");
  assert(10, ({ int i=5; i<<=1; i; }), "int i=5; i<<1;");
  assert(2, ({ int i=5; i>>=1; i; }), "int i=5; i>>1;");
  assert(-1, -1, "-1");
  assert(-1, ({ int i=-1; i; }), "int i=-1; i;");
  assert(-1, ({ int i=-1; i>>=1; i; }), "int i=1; i>>1;");

  assert(2, 0?1:2, "0?1:2");
  assert(1, 1?1:2, "0?1:2");

  assert(10, ({ enum { ten=1+2+3+4, }; ten; }), "enum { ten=1+2+3+4, }; ten;");
  assert(1, ({ int i=0; switch(3) { case 5-2+0*3: i++; } i; }), "int i=0; switch(3) { case 5-2+0*3: i++; ); i;");
  assert(8, ({ int x[1+1]; sizeof(x); }), "int x[1+1]; sizeof(x);");
  assert(2, ({ char x[1?2:3]; sizeof(x); }), "char x[0?2:3]; sizeof(x);");
  assert(3, ({ char x[0?2:3]; sizeof(x); }), "char x[1?2:3]; sizeof(x);");

  assert(1, ({ int x[3]={1,2,3}; x[0]; }), "int x[3]={1,2,3}; x[0];");
  assert(2, ({ int x[3]={1,2,3}; x[1]; }), "int x[3]={1,2,3}; x[0];");
  assert(3, ({ int x[3]={1,2,3}; x[2]; }), "int x[3]={1,2,3}; x[0];");
  assert(3, ({ int x[3]={1,2,3,}; x[2]; }), "int x[3]={1,2,3}; x[0];");

  assert(2, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[0][1]; }), "int x[2][3]={{1,2,3},{4,5,6}}; x[0][1];");
  assert(4, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][0]; }), "int x[2][3]={{1,2,3},{4,5,6}}; x[1][0];");
  assert(6, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][2]; }), "int x[2][3]={{1,2,3},{4,5,6}}; x[1][2];");

  assert(2, ({ int x[2][3]={{1,2}}; x[0][1]; }), "int x[2][3]={{1,2}}; x[0][1];");
  assert(0, ({ int x[2][3]={{1,2}}; x[1][0]; }), "int x[2][3]={{1,2}}; x[1][0];");
  assert(0, ({ int x[2][3]={{1,2}}; x[1][2]; }), "int x[2][3]={{1,2}}; x[1][2];");

  assert('a', ({ char x[4]="abc"; x[0]; }), "char x[4]=\"abc\"; x[0]; }");
  assert('c', ({ char x[4]="abc"; x[2]; }), "char x[4]=\"abc\"; x[2]; }");
  assert(0, ({ char x[4]="abc"; x[3]; }), "char x[4]=\"abc\"; x[3]; }");
  assert('a', ({ char x[2][4]={"abc","def"}; x[0][0]; }), "char x[2][4]=\"abc\",\"def\"}; x[0][0]; }");
  assert(0, ({ char x[2][4]={"abc","def"}; x[0][3]; }), "char x[2][4]=\"abc\",\"def\"}; x[0][3]; }");
  assert('d', ({ char x[2][4]={"abc","def"}; x[1][0]; }), "char x[2][4]=\"abc\",\"def\"}; x[1][0]; }");
  assert('f', ({ char x[2][4]={"abc","def"}; x[1][2]; }), "char x[2][4]=\"abc\",\"def\"}; x[1][2]; }");

  assert(4, ({ int x[]={1,2,3,4}; x[3]; }), "int x[]={1,2,3,4}; x[3];");
  assert(16, ({ int x[]={1,2,3,4}; sizeof(x); }), "int x[]={1,2,3,4}; sizeof(x);");
  assert(4, ({ char x[]="foo"; sizeof(x); }), "char x[]=\"foo\"; sizeof(x); }");

  assert(1, ({ struct {int a; int b; int c;} x={1,2,3}; x.a; }), "struct {int a; int b; int c;} x={1,2,3}; x.a;");
  assert(2, ({ struct {int a; int b; int c;} x={1,2,3}; x.b; }), "struct {int a; int b; int c;} x={1,2,3}; x.b;");
  assert(3, ({ struct {int a; int b; int c;} x={1,2,3}; x.c; }), "struct {int a; int b; int c;} x={1,2,3}; x.c;");
  assert(1, ({ struct {int a; int b; int c;} x={1}; x.a; }), "struct {int a; int b; int c;} x={1}; x.a;");
  assert(0, ({ struct {int a; int b; int c;} x={1}; x.b; }), "struct {int a; int b; int c;} x={1}; x.b;");
  assert(0, ({ struct {int a; int b; int c;} x={1}; x.c; }), "struct {int a; int b; int c;} x={1}; x.c;");

  assert(1, ({ struct {int a; int b;} x[2]={{1,2},{3,4}}; x[0].a; }), "struct {int a; int b;} x[2]={{1,2},{3,4}}; x[0].a;");
  assert(2, ({ struct {int a; int b;} x[2]={{1,2},{3,4}}; x[0].b; }), "struct {int a; int b;} x[2]={{1,2},{3,4}}; x[0].b;");
  assert(3, ({ struct {int a; int b;} x[2]={{1,2},{3,4}}; x[1].a; }), "struct {int a; int b;} x[2]={{1,2},{3,4}}; x[1].a;");
  assert(4, ({ struct {int a; int b;} x[2]={{1,2},{3,4}}; x[1].b; }), "struct {int a; int b;} x[2]={{1,2},{3,4}}; x[1].b;");

  assert(0, ({ struct {int a; int b;} x[2]={{1,2}}; x[1].b; }), "struct {int a; int b;} x[2]={{1,2}}; x[1].b;");

  assert(3, g3, "g3");
  assert(4, g4, "g4");
  assert(5, g5, "g5");
  assert(6, g6, "g6");
  assert(5, *g7, "*g7");
  assert(0, strcmp(g8, "abc"), "strcmp(g8, \"abc\")");

  assert(0, g9[0], "g9[0]");
  assert(1, g9[1], "g9[1]");
  assert(2, g9[2], "g9[2]");

  assert(0, strcmp(g10[0], "foo"), "strcmp(g10[0], \"foo\")");
  assert(0, strcmp(g10[1], "bar"), "strcmp(g10[1], \"bar\")");
  assert(0, g10[1][3], "g10[1][3]");
  assert(2, sizeof(g10) / sizeof(*g10), "sizeof(g10) / sizeof(*g10)");

  assert(1, g11[0].a, "g11[0].a");
  assert(2, g11[0].b, "g11[0].b");
  assert(3, g11[1].a, "g11[1].a");
  assert(4, g11[1].b, "g11[1].b");

  assert(1, g12[0].a[0], "g12[0].a[0]");
  assert(2, g12[0].a[1], "g12[0].a[1]");
  assert(3, g12[1].a[0], "g12[1].a[0]");
  assert(4, g12[1].a[1], "g12[1].a[1]");

  assert(1, g13[0].a[0], "g13[0].a[0]");
  assert(2, g13[0].a[1], "g13[0].a[1]");
  assert(3, g13[1].a[0], "g13[1].a[0]");
  assert(4, g13[1].a[1], "g13[1].a[1]");

  assert(1, g14[0].a[0], "g14[0].a[0]");
  assert(2, g14[0].a[1], "g14[0].a[1]");
  assert(3, g14[1].a[0], "g14[1].a[0]");
  assert(4, g14[1].a[1], "g14[1].a[1]");

  assert(0, ({ int x[2][3]={0,1,2,3,4,5,}; x[0][0]; }), "int x[2][3]={0,1,2,3,4,5,}; x[0][0];");
  assert(3, ({ int x[2][3]={0,1,2,3,4,5,}; x[1][0]; }), "int x[2][3]={0,1,2,3,4,5,}; x[1][0];");

  assert(0, ({ struct {int a; int b;} x[2]={0,1,2,3}; x[0].a; }), "struct {int a; int b;} x[2]={0,1,2,3}; x[0].a;");
  assert(2, ({ struct {int a; int b;} x[2]={0,1,2,3}; x[1].a; }), "struct {int a; int b;} x[2]={0,1,2,3}; x[1].a;");

  assert(0, strcmp(g15, "foo"), "strcmp(g15, \"foo\")");
  assert(0, strcmp(g16[0], "foo"), "strcmp(g16[0], \"foo\")");
  assert(0, strcmp(g16[1], "bar"), "strcmp(g16[1], \"bar\")");

  assert(7, sizeof(g17), "sizeof(g17)");
  assert(10, sizeof(g18), "sizeof(g18)");
  assert(3, sizeof(g19), "sizeof(g19)");

  assert(0, memcmp(g17, "foobar", 7), "memcmp(g17, \"foobar\", 7)");
  assert(0, memcmp(g18, "foobar\0\0\0", 10), "memcmp(g18, \"foobar\\0\\0\\0\", 10)");
  assert(0, memcmp(g19, "foo", 3), "memcmp(g19, \"foo\", 3)");

  assert(0, strcmp(g20, "foobar"), "strcmp(g20, \"foobar\")");
  assert(0, strcmp(g21, "bar"), "strcmp(g21, \"bar\")");
  assert(0, strcmp(g22+3, "foobar"), "strcmp(g22+3, \"foobar\")");

  assert(3, g23, "g23");
  assert(3, *g24, "*g24");

  assert(5, ext1, "ext1");
  assert(5, *ext2, "*ext2");
  assert(6, ext_fn1(6), "ext_fn1(6)");
  assert(7, ext_fn2(7), "ext_fn2(7)");

  printf("OK\n");
  return 0;
}