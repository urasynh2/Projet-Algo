

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

//Definition d'assert
#define assertEquals(a,b) assert(a==b);printf("\033[32massertEquals reussi a la ligne %d \n\n\033[0m",__LINE__)
#define assertTrue(a) assert(a);printf("\033[32massertTrue reussi a la ligne %d \n\n\033[0m",__LINE__)
#define assertFalse(a) assert(!a);printf("\033[32massertFalse reussi a la ligne %d \n\n\033[0m",__LINE__)

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long long fact (int n)
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long long * r)
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long long fact2 (int n)
{ long long r ;
  bisfact(n,&r) ;
  return r ;
}

//================================================================================================================================================================

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () {
    float e = 1;
    //printf(" premiere valeur e3 =   %.20f \n", e) ;

    int n = 1;
    int factn = 1;

    float tmp;

    //printf(" n = %d ", n) ;
    //printf(" n! = %d ", factn) ;
    //printf(" e3 = %.20f \n", e) ;
    do{
        tmp = e;
        factn *= n ;
        e += 1.0L/factn;
        n++;
        //printf(" n = %d ", n) ;
        //printf(" n! = %d ", factn) ;
        //printf(" e3 = %.20f \n", e) ;
    }while(tmp<e);
    return e;
}

/*************************************************/

double Edouble() {
    double e = 1.;
    //printf(" premiere valeur e3 =   %.20f \n", e) ;

    int n = 1;
    int factn = 1.0L;

    double tmp;

    //printf(" n = %d ", n) ;
    //printf(" n! = %d ", factn) ;
    //printf(" e3 = %.20f \n", e) ;
    do{
        tmp = e;
        factn *= n ;
        e += 1.0L/factn;
        n++;
        //printf(" n = %d ", n) ;
        //printf(" n! = %d ", factn) ;
        //printf(" e3 = %.20f \n", e) ;
    }while(tmp<e);
    return e;
}

  
/*************************************************/
/* les long double ne s'affichent pas sur mon  pc je ne sais pourquoi */
long double Elongdouble () {
    long double e = 1;
    //printf(" premiere valeur e3 =   %.20Lf \n", e) ;

    int n = 1;
    int factn = 1.0L;

    long double tmp;

    //printf(" n = %d ", n) ;
    //printf(" n! = %d ", factn) ;
    //printf(" e3 = %.20Lf \n", e) ;
    do{
        tmp = e;
        factn *= n ;
        e += 1.0L/factn;
        n++;
        //printf(" n = %d ", n) ;
        //printf(" n! = %d ", factn) ;
        //printf(" e3 = %.20Lf \n", e) ;
    }while(tmp<e);
    return e;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) {
    printf("Suite Yn en float: \n");
    float Yn = Efloat() - 1.0f;
    printf("Y0= %.20f \n",Yn);
    for(int nn= 1; nn<=n ;nn++){
        Yn = nn * Yn - 1.0f;
        printf("Y%d= %.20f \n",nn,Yn);
    }
}

/*************************************************/

void afficheYdouble (int n) {
    printf("Suite Yn en double: \n");
    double Yn = Edouble() - 1.0;
    printf("Y0= %.30lf \n",Yn);
    for(int nn= 1; nn<=n ;nn++){
        Yn = (nn * Yn) - 1.0;
        printf("Y%d= %.30lf \n",nn,Yn);
    }
}

/*************************************************/

void afficheYlongdouble (int i) {
    long double e = Efloat();
    long double y = e - 1.0L;

    printf("Suite y0 = %.20Lf\n", y);

    for (int n = 1; n <= i; n++) {
        y = n * y - 1.0L;
        printf("y%d = %.20Lf\n", n, y);
    }
}


/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/


double power1 (double x,long long n) {
    if(n==0){
        return 1;
    }else{
        return power1(x,n-1)*x;
    }
}

/*************************************************/

double power2a (double x, long long n) {
    int r = 1;
    for(long long i=1;i<=n;i++){
        r =r*x;
    }
    return r;
}

/*************************************************/

double power2b (double x, long long n) {
    int r = 1;
    while(n>0){
        r =r*x;
        n--;
    }
    return r;
}

/*************************************************/

void pow3(double x, long long n,double *res){
    if (n != 0) {
        *res = *res * x;
        pow3(x,n-1,res);
    }
}

double power3 (double x, long long n) {
    double res = 1.0;
    pow3(x,n,&res);
    return res;
}

/*************************************************/


double pow4(double x, long long n,double res){
    if (n == 0) {
        return res;
    }else{
        return pow4(x,n-1,res*x);
    }
}

double power4 (double x, long long n) {
    return pow4(x,n,1);
}
/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long long n){
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long long n) {
    if (n == 0){
        return 1 ;
    }
    double y = power6(x,n/2);
    if (n % 2 == 0){
        return y*y;
    }else{
        return y*y*x ;
    }
}

/*************************************************/

double power7 (double x, long long n) {
    if (n==0){
        return 1;
    }else if (n%2==0){
        return power7(x*x ,n/2);
    }else{
        return power7(x*x,n/2) * x;
    }
}

/*************************************************/
double pow8(double x, long long n, double res){
    if (n==0){
        return res;
    }else if (n%2==0){
        return pow8(x*x ,n/2,res);
    }else{
        return pow8(x*x,n/2, res * x);
    }
}

double power8 (double x, long long n) {
    return pow8(x,n,1);
}

/*************************************************/
void pow9 (double x, long long n, double *res) {
    if(n!=0){
        if (n%2!=0){
            *res *= x;
        }
        pow9(x*x,n/2,res);
    }
}


double power9 (double x, long long n) {
    double res = 1.0;
    pow9(x,n,&res);
    return res;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ;
   case 2 : return power2a(x,n) ;   // 2 pour 2a
   case 0 : return power2b(x,n) ;  // 0 pour 2b
   case 3 : return power3(x,n) ;
   case 4 : return power4(x,n) ;
   case 5 : return power5(x,n) ;
   case 6 : return power6(x,n) ;
   case 7 : return power7(x,n) ;
   case 8 : return power8(x,n) ;
   case 9 : return power9(x,n) ;
  case 10 : return power10(x,n) ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


int A1(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else {
        if (n == 0) {
            return A1(m - 1, 1);
        } else {
            return A1(m - 1, A1(m, n - 1));
        }
    }
}


int Ackermann1 (int m) {
    return A1(m,0);
}

/*************************************************/

int A2(int m, int n) {
    if (m==0){
        return n+1;
    }else{
        int r=1;
        for(int i=1; i<=n+1;i++){
            r= A2(m-1,r);
        }
        return r;
    }

}

int Ackermann2 (int m) {
    return A2(m,0);
}

/*************************************************/

int A3(int m, int n) {
    int mm=m;
    while(mm!=0){
        if(n==0){
            n=1;
        }else{
            n= A3(mm,n-1);
        }
        mm--;
    }
    return n+1;
}

int Ackermann3 (int m) {
    return A3(m,0);
}

/*************************************************/

int Ackermann4 (int m) { return 0 ; }

/*************************************************/

int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

/*************************************************/
/*                                               */
/*             Suite Xn                          */
/*                                               */
/*************************************************/

int logEntier(int n, int cpt){
    if(n==1){
        return cpt;
    }else{
        return logEntier(n/2,cpt+1);
    }
}

int ln2(int n){
    return logEntier(n,0);
}

int X1(int n){
    int i = 0;
    int res = 2;
    while(i!=n){
        i++;
        res = res + ln2(res);
    }
    return res;
}

int X2(int n){
    if(n==0){
        return 2;
    }else{
        int tmp = X2(n-1);
        return tmp + ln2(tmp);
    }
}

int xn3(int n, int cpt){
    if(n==0){
        return cpt;
    }else{
        return xn3(n-1, cpt + ln2(cpt));
    }
}
int X3(int n){
    return xn3(n,2);
}

int xn4(int n, int *cpt){
    if(n!=0){
        *cpt = *cpt + ln2(*cpt);
        xn4(n-1, cpt);
    }
}


int X4(int n){
    int cpt = 2;
    xn4(n,&cpt);
    return cpt;
}


int X (int n, int i){
    switch (i){
        case 1 : return X1 (n) ;
        case 2 : return X2 (n) ;
        case 3 : return X3 (n) ;
        case 4 : return X4 (n) ;
        default : return 0 ;
    }
}

//===========================================================================================================================================================

/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv){
    system("cls");
    printf("DEBUT MAIN\n");
       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof( long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%lld \n",fact(5)) ;
     printf("%lld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {

    //printf("e = 2,7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274\n");
    printf("e1 = %.20f \n", Efloat()) ;
    printf("e2 = %.30lf \n", Edouble()) ;
    printf("e3 = %.40Lf \n", Elongdouble()) ;
}

if (false) {
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            //afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (false) {
    double X = -2;
    long N = 2;
    //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
    printf("Power 1 dit que power(%f,%ld) vaut %.0lf \n", X,N, power(X,N,1) ) ;
    printf("Power 2a dit que power(%f,%ld) vaut %.0lf \n", X,N, power(X,N,2) ) ;
    printf("Power 2b dit que power(%f,%ld) vaut %.0lf \n", X,N, power(X,N,0) ) ;
    for(i=3 ; i<=10 ; i++)
        printf("Power %d dit power(%f,%ld) vaut %.0lf \n", i,X,N, power(X,N,i) ) ;
        printf("\n") ;
      
}

        
if (false) {

        i=9;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++){
            printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
            x = x/10 ;
            nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/

if (false) {

        for(i=1 ; i<=5 ; i++) { // numéro de version
            for (j = 0; j <= 5; j++) {
                // test de A(j,0) pour j de 0 à 5
                printf("Ack%d(%d) = %d \n", i, j, Ackermann(j, i));
            }
            printf("\n");
        }
}

/***********************    Xn        ********************************/


    if (true) {

        for(i=1 ; i<=4 ; i++) { // numéro de version
            for (j = 0; j <= 100; j++) {
                // test de A(j,0) pour j de 0 à 5
                printf("X%d(%d) = %d \n", i, j, X(j,i));
            }
            printf("\n");
        }
    }

/*******************************************************************************/
    printf("FIN MAIN\n");
    return 0;
}






