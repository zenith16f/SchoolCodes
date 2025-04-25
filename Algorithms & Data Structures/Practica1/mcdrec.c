//b=aq0+r0       d ! b d ! a -> d ! r0
//a=r0q1+r1      d ! a d ! r0 -> d ! r1
//r0=r1q2+r2     d ! r0 d ! r1 -> d ! r2
#include <stdio.h>
int mcd (int a, int b){
   if(b == 0 ) return a;
   return mcd( b, a % b);
}
void main(){
	printf("(%d)",mcd(7854, 4746));
}
