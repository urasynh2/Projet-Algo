#include <stdio.h>
#include <stdlib.h>

/*************************************************************/
/* Nom: OUHAIBIA                                             */
/* Prénom: Mohamed Amine                                     */
/* Email: mohamed-amine.ouhaibia@universite-paris-saclay.fr  */
/*************************************************************/


typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


typedef enum { FALSE, TRUE} bool;


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
    *L = ajoute(x,*L) ;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

void affiche(Liste l)
{
    printf("[");
    Liste L2 = l;
    if (!estVide(L2)) {
        printf("%d", premier(L2));
        L2 = suite(L2);
    }
    while(!estVide(L2))
    {
        printf(", %d", premier(L2));
        L2 = suite(L2);
    }
    printf("]");
}
//========================================================================

typedef struct BlocP
{
    Liste liste;
    struct BlocP *liste_suivante;
} BlocP;

typedef BlocP *ListeP ;


void initVideP( ListeP *L)
{
    *L = NULL ;
}

bool estVideP(ListeP l)
{
    return l == NULL ;
}

Liste premierP(ListeP l)
{
    return l->liste ;
}

ListeP ajouteP(Liste x, ListeP l)
{
    ListeP tmp = (ListeP) malloc(sizeof(BlocP)) ;
    tmp->liste = x ;
    tmp->liste_suivante = l ;
    return tmp ;
}

void empileP(Liste x, ListeP *L)
{
    *L = ajouteP(x,*L) ;
}

ListeP suiteP(ListeP l)
{
    return l->liste_suivante ;
}

//void depile(ListeP *L)
//{
//    ListeP tmp = *L ;
//    *L = suite(*L) ;
//    free(tmp) ;
//}


void afficheP(ListeP l)
{
    printf("[  ");
    ListeP L2 = l;
    if (!estVideP(L2)) {
        affiche(premierP(L2));
        L2 = suiteP(L2);
    }
    while(!estVideP(L2))
    {
        printf(" , ");
        affiche(premierP(L2));
        L2 = suiteP(L2);
    }
    printf("  ]\n");
}
//******************************************************************************
ListeP ATLTP(int x, ListeP l);
ListeP ATP(int x, Liste l);
ListeP Concat(ListeP l1, ListeP l2);
ListeP AETTL (int x, ListeP l);


ListeP Permutations(int n){
    if(n==0){
        ListeP res;
        initVideP(&res);
        return res;
    }else{
        return ATLTP(n, Permutations(n-1));
    }
}

void testPermutations(){
    afficheP(Permutations(3));
}

ListeP ATLTP(int x, ListeP l){
    if(estVideP(l)){
        Liste tmp;
        initVide(&tmp);
        empile(x,&tmp);
        ListeP res;
        initVideP(&res);
        return ajouteP(tmp,res);
    }else {
        if (!estVideP(suiteP(l))) {
            return Concat(ATP(x, premierP(l)), ATLTP(x, suiteP(l)));
        }else{
            return ATP(x, premierP(l));
        }
    }
}
/* la version donnée dans le cours
ListeP ATLTP(int x, ListeP l){
    if(estVideP(l)){
        ListeP res;
        initVideP(&res);
        return res;
    }else {
        return Concat(ATP(x, premierP(l)), ATLTP(x, suiteP(l)));
    }
}
*/

void testATLTP() {
    Liste l1, l2,l3,l4;
    initVide(&l1);
    initVide(&l2);
    initVide(&l3);
    initVide(&l4);

    empile(9,&l1);
    empile(7,&l1);
    empile(5,&l1);

    empile(2,&l2);

    empile(8,&l3);
    empile(3,&l3);


    ListeP T;
    initVideP(&T);
    empileP(l4,&T);
    empileP(l3,&T);
    empileP(l2,&T);
    empileP(l1,&T);
    afficheP(T);
    afficheP(ATLTP(4,T));
}


ListeP Concat(ListeP l1, ListeP l2){
    if(estVideP(l1)){
        return l2;
    }else{
        return ajouteP(premierP(l1), Concat(suiteP(l1),l2));
    }
}

void testConcat() {
    Liste l1, l2,l3;
    initVide(&l1);
    initVide(&l2);
    initVide(&l3);

    empile(3,&l1);
    empile(2,&l1);
    empile(1,&l1);

    empile(6,&l2);
    empile(5,&l2);
    empile(4,&l2);

    empile(9,&l3);
    empile(8,&l3);
    empile(7,&l3);

    ListeP T, P;
    initVideP(&T);
    initVideP(&P);
    empileP(l1,&T);
    empileP(l3,&P);
    empileP(l2,&P);


    afficheP(Concat(T,P));
}

ListeP ATP(int x, Liste l){
    if(estVide(l)){
        Liste tmp;
        initVide(&tmp);
        empile(x,&tmp);
        ListeP res;
        initVideP(&res);
        return ajouteP(tmp,res);
    }else{
        return ajouteP(ajoute(x,l), AETTL(premier(l),ATP(x, suite(l))));
    }
}
void testATP() {
    Liste l1;
    initVide(&l1);

    empile(9, &l1);
    empile(7, &l1);
    afficheP(ATP(4, l1));

    empile(5, &l1);
    afficheP(ATP(4, l1));
}

ListeP AETTL (int x, ListeP l){
    if(estVideP(l)){
        ListeP res;
        initVideP(&res);
        return res;
    }else{
        return ajouteP(ajoute(x, premierP(l)),AETTL(x, suiteP(l)));
    }
}

void testAETTL(){
    Liste l1, l2,l3;
    initVide(&l1);
    initVide(&l2);
    initVide(&l3);

    empile(8,&l2);
    empile(4,&l2);

    empile(2,&l3);

    ListeP T;
    initVideP(&T);
    empileP(l1,&T);
    empileP(l2,&T);
    empileP(l3,&T);
    afficheP(T);
    afficheP(AETTL(6,T));

}




int main(int argc, char** argv) {
    printf("test AETTL:\n");
    testAETTL();

    printf("\ntest ATP:\n");
    testATP();

    printf("\ntest Concat:\n");
    testConcat();

    printf("\ntest ATLTP:\n");
    testATLTP();

    printf("\ntest Permutations:\n");
    testPermutations();


//    Liste l1, l2;
//    initVide(&l1);
//    initVide(&l2);
//
//    empile(5,&l1);
//    empile(4,&l1);
//    empile(6,&l1);
//    empile(18,&l1);
//
//    empile(7,&l2);
//    empile(9,&l2);
//    empile(14,&l2);
//    empile(6,&l2);
//
//    ListeP T;
//    initVideP(&T);
//    empileP(l1,&T);
//    empileP(l2,&T);
//
//    afficheP(T);


}

