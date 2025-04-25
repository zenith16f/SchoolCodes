
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// stack will have fixed size
#define STACK_SIZE 2048

#define PUSH(vm, v) vm->stack[++vm->sp] = v // push value on top of the stack
#define POP(vm) vm->stack[vm->sp--]         // pop value from top of the stack
#define NCODE(vm) vm->code[vm->pc++]        // get next bytecode
#define NCODE_(vm, pc) vm->code[pc]

enum {
  ADD_I32 = 1,   // int add
  SUB_I32 = 2,   // int sub
  MUL_I32 = 3,   // int mul
  LT_I32 = 4,    // int less than
  EQ_I32 = 5,    // int equal
  JMP = 6,       // branch
  JMPT = 7,      // branch if true
  JMPF = 8,      // branch if false
  CONST_I32 = 9, // push constant integer
  LOAD = 10,     // load from local
  GLOAD = 11,    // load from global
  STORE = 12,    // store in local
  GSTORE = 13,   // store in global memory
  PRINT = 14,    // print value on top of the stack
  POP = 15,      // throw away top of the stack
  HALT = 16,     // stop program
  CALL = 17,     // call procedure
  RET = 18,      // return from procedure
  OR = 19,
  WHILE = 20,
  MOD = 21
};

static struct {
  /* Constantes */
  char *name;
  int cval;
} consts[] = {"ADD_I32",   1,  // int add
              "SUB_I32",   2,  // int sub
              "MUL_I32",   3,  // int mul
              "LT_I32",    4,  // int less than
              "EQ_I32",    5,  // int equal
              "JMP",       6,  // branch
              "JMPT",      7,  // branch if true
              "JMPF",      8,  // branch if false
              "CONST_I32", 9,  // push constant integer
              "LOAD",      10, // load from local
              "GLOAD",     11, // load from global
              "STORE",     12, // store in local
              "GSTORE",    13, // store in global memory
              "PRINT",     14, // print value on top of the stack
              "POP",       15, // throw away top of the stack
              "HALT",      16, // stop program
              "CALL",      17, // call procedure
              "RET",       18, // return from procedure
              "OR",        19, "WHILE", 20, "MOD", 21};

typedef struct {
  int *locals; // local scoped data
  int *code;   // array od byte codes to be executed
  int *stack;  // virtual stack
  int pc;      // program counter (aka. IP - instruction pointer)
  int sp;      // stack pointer
  int fp;      // frame pointer (for local scope)
} VM;

typedef void (*Inst)(VM *vm);

void run(VM *vm, int p);
int returning;

void pop1(VM *vm) { --vm->sp; }

void whilecode(VM *vm) {
  int d;
  int savepc = vm->pc;
  vm->pc = savepc + 2;
  run(vm, savepc + 2); /*   condición   */
  d = POP(vm);
  while (d) {
    vm->pc = NCODE_(vm, savepc);
    run(vm, savepc); /*  cuerpo  */
    vm->pc = savepc + 2;
    run(vm, savepc + 2);
    d = POP(vm);
  }
  if (!returning)
    vm->pc = NCODE_(vm, savepc + 1);
}
void jmpf(VM *vm) {
  int addr;
  addr = NCODE(vm);
  if (!POP(vm)) {
    vm->pc = addr;
  }
}
void jmp(VM *vm) { vm->pc = NCODE(vm); }
void jmpt(VM *vm) {
  int addr;
  addr = NCODE(vm);
  if (POP(vm)) {
    vm->pc = addr;
  }
}
VM *newVM(int *code, // pointer to table containing a bytecode to be executed
          int pc,    // address of instruction to be invoked as first one -
                     // entrypoint/main func
          int datasize) { // total locals size required to perform a program
                          // operations
  VM *vm = (VM *)malloc(sizeof(VM));
  vm->code = code;
  vm->pc = pc;
  vm->fp = 0;
  vm->sp = -1;
  vm->locals = (int *)malloc(sizeof(int) * datasize);
  vm->stack = (int *)malloc(sizeof(int) * STACK_SIZE);

  return vm;
}

void delVM(VM *vm) {
  free(vm->locals);
  free(vm->stack);
  free(vm);
}

void constpush(VM *vm) {
  int v;
  v = NCODE(vm);
  PUSH(vm, v);
}

void call(VM *vm) {
  int addr, argc;
  addr = NCODE(vm); // get next instruction as an address of procedure jump ...
  argc = NCODE(vm); // ... and next one as number of arguments to load ...
  PUSH(vm, argc);   // ... save num args ...
  PUSH(vm, vm->fp); // ... save function pointer ...
  PUSH(vm, vm->pc); // ... save instruction pointer ...
  vm->fp = vm->sp;  // ... set new frame pointer ...
  vm->pc = addr;    // ... move instruction pointer to target
  run(vm, addr);
  returning = 0;
}
void ret(VM *vm) {
  int argc, rval;
  rval = POP(vm);   // pop return value from top of the stack
  vm->sp = vm->fp;  // ... return from procedure address ...
  vm->pc = POP(vm); // ... restore instruction pointer ...
  vm->fp = POP(vm); // ... restore framepointer ...
  argc = POP(vm);   // ... hom many args procedure has ...
  vm->sp -= argc;   // ... discard all of the args left ...
  PUSH(vm, rval);
  returning = 1;
}

void add(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, a + b);
}

void sub(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, a - b);
}
void mul(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, a * b);
}
void store(VM *vm) {
  int v, offset;
  v = POP(vm);
  offset = NCODE(vm);
  vm->locals[vm->fp + offset] = v;
}
void load(VM *vm) {
  int offset;
  offset = NCODE(vm);
  PUSH(vm, vm->stack[vm->fp + offset]);
}
void gstore(VM *vm) {
  int v, addr;
  v = POP(vm);
  addr = NCODE(vm);
  vm->locals[addr] = v;
}
void gload(VM *vm) {
  int v, addr;
  addr = POP(vm);
  v = vm->locals[addr];
  PUSH(vm, v);
}

void lt(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, (a < b) ? 1 : 0);
}

void eq(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, (a == b) ? 1 : 0);
}

void or (VM * vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  PUSH(vm, (a != 0 || b != 0) ? 1 : 0);
}
void mod(VM *vm) {
  int a, b;
  b = POP(vm);
  a = POP(vm);
  // printf("a=%d, b=%d mod=%d ", a, b,  a %  b);
  PUSH(vm, a % b);
  // exit(0);
}

void print(VM *vm) {
  int v;
  v = POP(vm);
  printf("( %d )\n", v);
}

Inst risc[] = {add, // 1
               sub, // 2
               mul, // 3
               lt,  // 4
               eq,        jmp,   jmpt,
               jmpf, // 8
               constpush, load,  gload,
               store, // 12
               gstore,    print, pop1,
               NULL,      // 16
               call,      // 17
               ret,       // 18
               or,        // 19
               whilecode, // 20
               mod};

void run(VM *vm, int p) {
  do {
    int opcode = NCODE(vm); // fetch
    if (opcode == HALT || returning) {
      if (returning) {
        vm->pc--;
      }
      return;
    }
    risc[opcode - 1](vm);
  } while (1);
}

const int fib = 0; // address of the fibonacci procedure
int program1[] = {
    // int fib(n) {
    //     if(n == 0) return 0;
    LOAD, -3,     // 0 - load last function argument N
    CONST_I32, 0, // 2 - put 0
    EQ_I32,       // 4 - check equality: N == 0
    JMPF, 10,     // 5 - if they are NOT equal, goto 10
    CONST_I32, 0, // 7 - otherwise put 0
    RET,          // 9 - and return it
    //     if(n < 3) return 1;
    LOAD, -3,     // 10 - load last function argument N
    CONST_I32, 3, // 12 - put 3
    LT_I32,       // 14 - check if 3 is less than N
    JMPF, 20,     // 15 - if 3 is NOT less than N, goto 20
    CONST_I32, 1, // 17 - otherwise put 1
    RET,          // 19 - and return it
    //     else return fib(n-1) + fib(n-2);
    LOAD, -3,     // 20 - load last function argument N
    CONST_I32, 1, // 22 - put 1
    SUB_I32,      // 24 - calculate: N-1, result is on the stack
    CALL, fib, 1, // 25 - call fib function with 1 arg. from the stack
    LOAD, -3,     // 28 - load N again
    CONST_I32, 2, // 30 - put 2
    SUB_I32,      // 32 - calculate: N-2, result is on the stack
    CALL, fib, 1, // 33 - call fib function with 1 arg. from the stack
    ADD_I32, // 36 - since 2 fibs pushed their ret values on the stack, just add
             // them
    RET,     // 37 - return from procedure
    // entrypoint - main function
    CONST_I32, 10, // 38 - put 6
    CALL, fib, 1,  // 40 - call function: fib(arg) where arg = 10;
    PRINT,         // 43 - print result
    HALT           // 44 - stop program
};

const int facto = 0; // address of the facto procedure
int program2[] = {
    LOAD, -3,       // 0 - load last function argument N
    CONST_I32, 0,   // 2 - put 0
    EQ_I32,         // 4 - check equality: N == 0
    JMPF, 10,       // 5 - if they are NOT equal, goto 10
    CONST_I32, 1,   // 7 - otherwise put 1
    RET,            // 9 - and return it
    LOAD, -3,       // 10 - load last function argument N
    CONST_I32, 1,   // 12 - put 1
    SUB_I32,        // 14 - calculate: N-1, result is on the stack
    CALL, facto, 1, // 15  - call fib function with 1 arg. from the stack
    LOAD, -3,       // 18  - load N again
    MUL_I32, // 20  - since 2 vals pushed their ret values on the stack, just
             // mul them
    RET,     // 21  - return from procedure
    // entrypoint - main function
    CONST_I32, 7,   // 22  - put 7
    CALL, facto, 1, // 24 - call function: facto(arg) where arg = 7;
    PRINT,          // 25   - print result
    HALT            // 26  - stop program
};

const int inc = 0; // address of the fibonacci procedure
int program3[] = {
    LOAD,      -3,     // 0 - load last function argument N
    CONST_I32, 1,      // 2
    ADD_I32,           // 4
    RET,               // 5
    CONST_I32, 66,     // 6 - put 66
    CALL,      inc, 1, // 8 - call function: inc where arg = 6;
    PRINT,             // 9  - print result
    HALT               // 10 - stop program
};

const int suma = 0; // address of the fibonacci procedure
int program4[] = {
    LOAD,      -3,      // 0 - load last function argument N
    LOAD,      -4,      // 2
    ADD_I32,            // 4
    RET,                // 5
    CONST_I32, 44,      // 6  - put 44
    CONST_I32, 33,      // 8 - put 33
    CALL,      suma, 2, // 10 - call function: suma where arg = 44, 33;
    PRINT,              // 11 - print result
    HALT                // 12 - stop program
};

const int ciclo = 0;
int program5[] = {
    CONST_I32, 0,  // 0 - put 0
    GSTORE,    0,  // 2
    CONST_I32, 0,  // 4 - put 0
    GLOAD,         // 6
    LOAD,      -3, // 7 - load last function argument N
    LT_I32,        // 9 - check equality: N == 0
    JMPF,      26, // 10 - if they are NOT equal, goto 10
    CONST_I32, 0,  // 12
    GLOAD,         // 14
    PRINT,         // 15
    CONST_I32, 0,  // 16
    GLOAD,         // 18
    CONST_I32, 1,  // 19 - otherwise put 1
    ADD_I32,       // 21
    GSTORE,    0,  // 22
    JMP,       4,  // 24

    RET, // 26 - and return it

    CONST_I32, 7,        // 27   - put 7
    CALL,      ciclo, 1, // 29 - call function: fib(arg) where arg = 6;
    PRINT,               // 31 - print result
    HALT                 // 32  - stop program*/
};

const int ciclo1 = 0; // address of the fibonacci procedure
int program5_1[] = {
    CONST_I32, 0,  // 0 - put 0
    GSTORE,    0,  // 2
    CONST_I32, 0,  // 4 - put 0
    GLOAD,         // 6
    LOAD,      -3, // 7 - load last function argument N
    LT_I32,        // 9 - check equality: N == 0
    JMPF,      26, // 10
    CONST_I32, 0,  // 12
    GLOAD,         // 14
    PRINT,         // 15
    CONST_I32, 0,  // 16
    GLOAD,         // 18
    CONST_I32, 1,  // 19 - otherwise put 1
    ADD_I32,       // 21
    GSTORE,    0,  // 22
    JMP,       4,  // 24
    CONST_I32, 0,  // 26
    GLOAD,         // 28
    PRINT,         // 29
    RET,           // 30 - and return it

    CONST_I32, 7,         // 31   - put 7
    CALL,      ciclo1, 1, // 33 - call function: fib(arg) where arg = 6;
    PRINT,                // 36 - print result
    HALT                  // 32   - stop program*/
};

const int whilebas = 0;
int program6[] = {
    WHILE,                  // 0
    6,                      // 1
    10,                     // 2
    CONST_I32, 1,           // 3
    HALT,                   // 5
    CONST_I32, 44,          // 6
    PRINT,                  // 8
    HALT,                   // 9
    RET,                    // 10
    CALL,      whilebas, 0, // 11 - call function: whilebas where arg = 6;
    PRINT,                  // 14   - print result
    HALT                    // 15   - stop program
};

const int while_ = 0;
int program6_1[] = {
    WHILE, // 0
    10,    // 1
    23,    // 2

    CONST_I32, 0,  // 3 - put 0
    GLOAD,         // 5
    LOAD,      -3, // 6 - load last function argument N
    LT_I32,        // 8
    HALT,          // 9

    CONST_I32, 0, // 10
    GLOAD,        // 12
    PRINT,        // 13
    CONST_I32, 0, // 14
    GLOAD,        // 16
    CONST_I32, 1, // 17 - otherwise put 1
    ADD_I32,      // 19
    GSTORE,    0, // 20
    HALT,         // 22

    CONST_I32, 0, // 23
    GLOAD,        // 25
    RET,          // 26

    CONST_I32, 10,        // 27
    CALL,      while_, 0, // 26 - call function: while(arg)_  where arg = 10;
    PRINT,                // 29   - print result
    HALT                  // 30   - stop program
};

// Funcion Suma N numeros(En este caso de 1 a 10)
const int sumaR = 0;
int program7[] = {
    LOAD, -3,       // 0 - load last function argument N
    CONST_I32, 1,   // 2 - put 0
    EQ_I32,         // 4 - check equality: N == 0
    JMPF, 10,       // 5 - if they are NOT equal, goto 10
    CONST_I32, 1,   // 7 - otherwise put 1
    RET,            // 9 - and return it
    LOAD, -3,       // 10 - load last function argument N
    CONST_I32, 1,   // 12 - put 1
    SUB_I32,        // 14 - calculate: N-1, result is on the stack
    CALL, sumaR, 1, // 15  - call fib function with 1 arg. from the stack
    LOAD, -3,       // 18  - load N again
    ADD_I32, // 20  - since 2 vals pushed their ret values on the stack, just
             // mul them
    RET,     // 21  - return from procedure
    // entrypoint - main function
    CONST_I32, 10,  // 22  - put 7
    CALL, sumaR, 1, // 24 - call function: facto(arg) where arg = 7;
    PRINT,          // 25   - print result
    HALT            // 26  - stop program
};

// Funcion Suma N numeros al cuadrado cada uno(En este caso de 1 a 10)
const int sumaCuadrados = 0;
int program8[] = {
    LOAD, -3,     // 0 - load last function argument N
    CONST_I32, 0, // 2 - put 0
    EQ_I32,       // 4 - check equality: N == 0
    JMPF, 10,     // 5 - if they are NOT equal, goto 10
    CONST_I32, 0, // 7 - otherwise put 1
    RET,          // 9 - and return it
    LOAD, -3,     // 10 - load last function argument N
    LOAD, -3,     // 12
    MUL_I32,      // 14
    LOAD, -3, CONST_I32, 1,
    SUB_I32, // 14 - calculate: N-1, result is on the stack
    CALL, sumaCuadrados,
    1,       // 15  - call fib function with 1 arg. from the stack
    ADD_I32, // 20  - since 2 vals pushed their ret values on the stack, just
             // mul them
    RET,     // 21  - return from procedure
    // entrypoint - main function
    CONST_I32, 10,          // 22  - put 7
    CALL, sumaCuadrados, 1, // 24 - call function: facto(arg) where arg = 7;
    PRINT,                  // 25   - print result
    HALT                    // 26  - stop program
};

// Funcion Suma N numeros al cubo cada uno (En este caso de 1 a 10)
const int sumaCubos = 0;
int program9[] = {
    LOAD, -3,     // 0 - load last function argument N
    CONST_I32, 0, // 2 - put 0
    EQ_I32,       // 4 - check equality: N == 0
    JMPF, 10,     // 5 - if they are NOT equal, goto 10
    CONST_I32, 0, // 7 - otherwise put 1
    RET,          // 9 - and return it

    LOAD, -3, // 10 - load last function argument N
    LOAD, -3, // 12
    MUL_I32,  // 14
    LOAD, -3,
    MUL_I32, // 16
    LOAD, -3, CONST_I32, 1,
    SUB_I32, // 14 - calculate: N-1, result is on the stack
    CALL, sumaCubos,
    1,       // 15  - call fib function with 1 arg. from the stack
    ADD_I32, // 20  - since 2 vals pushed their ret values on the stack, just
             // mul them
    RET,     // 21  - return from procedure
    // entrypoint - main function
    CONST_I32, 10,      // 22  - put 7
    CALL, sumaCubos, 1, // 24 - call function: facto(arg) where arg = 7;
    PRINT,              // 25   - print result
    HALT                // 26  - stop program
};

// Funcion Suma N numeros a la cuarta cada uno (En este caso de 1 a 10)
const int sumaCuartas = 0;
int program10[] = {
    LOAD, -3,     // 0 - load last function argument N
    CONST_I32, 0, // 2 - put 0
    EQ_I32,       // 4 - check equality: N == 0
    JMPF, 10,     // 5 - if they are NOT equal, goto 10
    CONST_I32, 0, // 7 - otherwise put 1
    RET,          // 9 - and return it

    LOAD, -3, // 10 - load last function argument #ifdef __cplusplus
    CONST_I32, 1, SUB_I32,
    CALL, sumaCuartas, 1,

    LOAD, -3, // 10 - load last function argument N
    LOAD, -3, // 12
    MUL_I32,  // 14
    LOAD, -3,
    MUL_I32, // 16
    LOAD, -3,
    MUL_I32, // 18
    ADD_I32, // 20
    RET,

    // entrypoint - main function
    CONST_I32, 10,      // 22  - put 7
    CALL, sumaCuartas, 1, // 24 - call function: facto(arg) where arg = 7;
    PRINT,              // 25   - print result
    HALT                // 26  - stop program
};

// Main
int main() {
  /*VM* vm = newVM(program1,   // program to execute
                  38,    // start address of main function
                  0);    // locals to be reserved, fib doesn't require them
   */
  /*
    VM *vm = newVM(program7, // program to execute
                   22,       // start address of main function
                   0);       // locals to be reserved, fib doesn't require them
                             // start address of main function
  */

  VM *vm = newVM(program10, // program to execute
                 31,        // start address of main function
                 10);       // locals to be reserved, fib doesn't require them

  /*
  VM* vm = newVM(program4,   // program to execute
                 6,    // start address of main function
                 0);    // locals to be reserved, fib doesn't require them
  */
  /*
     VM* vm = newVM(program5_1,   // program to execute
                 31,    // start address of main function
                 10);    // locals to be reserved, fib doesn't require them
  */
  /*
  VM* vm = newVM(program6,   // program to execute
                 11,    // start address of main function
                 10);    // locals to be reserved, fib doesn't require them
  */

  /*VM* vm = newVM(program6_1,   // program to execute
                 27,
                 10);    // locals to be reserved, fib doesn't require them
  */

  run(vm, 0);
  return 0;
}
