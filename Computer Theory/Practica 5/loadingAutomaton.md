# How the automatons are loaded

## Automaton File

```md
A B C D E F G H I -> AFN states string( string)\* \n
A
H I
a b c

- - - B
      C - - -
- - - D,B
- - - E,G
- F - -
- - - E,G
- - H -
- - - I
- - - I
```

1. First we read the AFN states described on the first line, we take the complete line and then we split it by " "
