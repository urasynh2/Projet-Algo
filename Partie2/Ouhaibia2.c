
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*************************************************************/
/* Nom: OUHAIBIA                                             */
/* Prénom: Mohamed Amine                                     */
/* Email: mohamed-amine.ouhaibia@universite-paris-saclay.fr  */
/*************************************************************/

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

//Definition d'assert
#define assertEquals(a,b) assert(a==b);printf("\033[32massertEquals reussi a la ligne %d \n\n\033[0m",__LINE__)
#define assertTrue(a) assert(a);printf("\033[32massertTrue reussi a la ligne %d \n\n\033[0m",__LINE__)
#define assertFalse(a) assert(!a);printf("\033[32massertFalse reussi a la ligne %d \n\n\033[0m",__LINE__)


typedef enum { FALSE, TRUE} bool;

/*
void assertEquals(int a, int b){
    assert(a==b);
    printf("test reussi a la ligne %d \n",__LINE__);
}

void assertTrue(bool a){
    assert(a);
    printf("test reussi a la ligne %d\n",__LINE__);
}

void assertFalse(bool a){
    assert(!a);
    printf("test reussi a la ligne %d\n",__LINE__);
}
*/

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);
void VideListe(Liste *L);

void poup(Liste l);

/*===================================================================================================*/
void affiche(Liste l);
bool sontEgales(Liste l1, Liste l2);
Liste *PointeurSuite(Liste *l);



bool UnPlusDeuxEgalTrois(Liste l);
void testUnPlusDeuxEgalTrois();


bool Croissante(Liste l);
void testCroissante();


int NombreMemePosition_rec(Liste l1, Liste l2);
int NombreMemePosition_iter(Liste l1, Liste l2);
int NombreMemePosition_rec_sf(Liste l1, Liste l2);
int aux_NMPI_sf(Liste l1, Liste l2, int cpt);
int NombreMemePosition_rec_sp(Liste l1, Liste l2);
void aux_NMPI_sp(Liste l1, Liste l2, int *cpt);
void testNombreMemePosition(int (*operation)(Liste, Liste));


Liste FonctVireDernier_rec(Liste l);
Liste FonctVireDernier_iter(Liste l);
void testFonctVireDernier(Liste (*operation)(Liste));

void AjouteDevantPremierZero(Liste *l, int x);
void testAjouteDevantPremierZero();

void AjouteDevantDernierZero_rec(Liste *l, int x);
void AjouteDevantDernierZero_rec_term(Liste *l, int x);
void AjouteDevantDernierZero_iter(Liste *l, int x);
void testAjouteDevantDernierZero(void (*operation)(Liste*,int));

void Tic(Liste *l);
void testTic();




/*===================================================================================================*/

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


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

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}


/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
        return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
// *L non NULL ie liste non vide
{
    if ( ((**L).suivant) == NULL )
        depile(L) ;   // moralement : depile(& (*L)) ;
    else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
    if ( (*L) ISNOT NULL )
        VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
            L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
    }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }

}
/*===================================================================================================*/
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
    printf("]\n");
}


bool sontEgales(Liste l1, Liste l2) {
    if (estVide(l1) && estVide(l2)) return TRUE;
    if (estVide(l1) || estVide(l2)) return FALSE;
    if (premier(l1) != premier(l2)) return FALSE;
    return sontEgales(suite(l1), suite(l2));
}

Liste *PointeurSuite(Liste *l){
    return &(*l)->suivant;
}

/*************************************************/
/*                                               */
/*             UnPlusDeuxEgalTrois               */
/*                                               */
/*************************************************/



bool UnPlusDeuxEgalTrois(Liste l){
    if (estVide(l)) {
        return TRUE;
    } else if(estVide(suite(l))) {
        return premier(l) == 0;
    } else if( estVide(suite(suite(l)))) {
        return premier(l)+premier(suite(l)) == 0;
    } else {
        return premier(l) + premier(suite(l)) == premier(suite(suite(l)));
    }
}

void testUnPlusDeuxEgalTrois(){
    Liste l1,l2,l3 ;

    initVide (&l1) ;
    affiche(l1);
    assertTrue(UnPlusDeuxEgalTrois(l1));

    empile(0, &l1);
    affiche(l1);
    assertTrue(UnPlusDeuxEgalTrois(l1));

    initVide (&l2) ;
    empile(-5, &l2);
    affiche(l2);
    assertFalse(UnPlusDeuxEgalTrois(l2));

    empile(5, &l2);
    affiche(l2);
    assertTrue(UnPlusDeuxEgalTrois(l2));

    initVide (&l3) ;
    empile(10, &l3);
    empile(5, &l3);
    affiche(l3);
    assertFalse(UnPlusDeuxEgalTrois(l3));

    empile(5, &l3);
    affiche(l3);
    assertTrue(UnPlusDeuxEgalTrois(l3));

    depile(&l3);
    empile(2, &l3);
    affiche(l3);
    assertFalse(UnPlusDeuxEgalTrois(l3));

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
}


/*************************************************/
/*                                               */
/*             Croissante                        */
/*                                               */
/*************************************************/

bool Croissante(Liste l){
    if (estVide(l) OR estVide(suite(l))){
        return TRUE;
    }else{
        if(premier(l)<= premier(suite(l))){
            return Croissante(suite(l));
        }else{
            return FALSE;
        }
    }
}


void testCroissante(){
    Liste l1,l2,l3 ;

    initVide (&l3) ;
    affiche(l3);
    assertTrue(Croissante(l3));

    empile(5, &l3);
    affiche(l3);
    assertTrue(Croissante(l3));

    initVide (&l1) ;
    for(int i=5; i>=1;i--) {
        empile(i, &l1);
    }
    affiche(l1);
    assertTrue(Croissante(l1));

    initVide (&l2) ;
    for(int i=1; i<=5;i++) {
        empile(i, &l2);
    }
    affiche(l2);
    assertFalse(Croissante(l2));

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
}


/*************************************************/
/*                                               */
/*             NombreMemePosition                */
/*                                               */
/*************************************************/


int NombreMemePosition_rec(Liste l1, Liste l2){
    if (estVide(l1) OR  estVide(l2)){
        return 0;
    } else {
        if (premier(l1) == premier(l2)){
            return 1 + NombreMemePosition_rec(suite(l1), suite(l2));
        }else{
            return NombreMemePosition_rec(suite(l1), suite(l2));
        }
    }
}


int NombreMemePosition_iter(Liste l1, Liste l2){
    Liste ll1 = l1;
    Liste ll2 = l2;
    int cpt = 0;
    while(  NOT estVide(ll1) AND NOT estVide(ll2)){
        if (premier(ll1) == premier(ll2)){
            cpt++;
        }
        ll1 = suite(ll1);
        ll2 = suite(ll2);
    }
    return cpt;
}


int NombreMemePosition_rec_sf(Liste l1, Liste l2){
    return aux_NMPI_sf(l1,l2,0);
}

int aux_NMPI_sf(Liste l1, Liste l2, int cpt){
    if(estVide(l1) OR estVide(l2)){
        return cpt;
    }
    if(premier(l1)== premier(l2)){
        return aux_NMPI_sf(suite(l1), suite(l2),cpt+1);
    }else{
        return aux_NMPI_sf(suite(l1), suite(l2),cpt);
    }
}

int NombreMemePosition_rec_sp(Liste l1, Liste l2){
    int cpt = 0;
    aux_NMPI_sp(l1,l2,&cpt);
    return cpt;
}

void aux_NMPI_sp(Liste l1, Liste l2, int *cpt){
    if( NOT estVide(l1) AND  NOT estVide(l2)) {
        if (premier(l1) == premier(l2)) {
            *cpt= *cpt+1;
        }
        aux_NMPI_sp(suite(l1), suite(l2), cpt);
    }
}
void testNombreMemePosition(int (*operation)(Liste, Liste)){
    Liste l1,l2,l3;

    initVide (&l1) ;
    initVide (&l2) ;
    affiche(l1);
    affiche(l2);
    assertEquals(operation(l1,l2),0);

    empile(5, &l1);
    empile(6, &l1);
    empile(8, &l1);
    empile(2, &l1);
    affiche(l1);
    affiche(l2);
    assertEquals(operation(l1,l2),0);

    empile(0, &l2);
    empile(1, &l2);
    empile(5, &l2);
    empile(3, &l2);
    empile(8, &l2);
    empile(7, &l2);
    affiche(l1);
    affiche(l2);
    assertEquals(operation(l1,l2),2);

    initVide (&l3);
    empile(2, &l3);
    empile(6, &l3);
    empile(2, &l3);
    empile(9, &l3);
    affiche(l3);
    affiche(l2);
    assertEquals(operation(l3,l2),0);

    affiche(l1);
    assertEquals(operation(l1,l1), longueur_rec(l1));

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
}

/*************************************************/
/*                                               */
/*             FonctVireDernier                  */
/*                                               */
/*************************************************/

Liste FonctVireDernier_rec(Liste l){
    if(estVide(l) OR estVide(suite(l))){
        Liste LV;
        initVide(&LV);
        return LV;
    }else{
        return ajoute(premier(l), FonctVireDernier_rec(suite(l)));
    }
}


/*
Liste FonctVireDernier_iter(Liste l) {

    Liste res;
    initVide(&res);
    if (estVide(l)) {
        return res;
    }

    Liste copie = l;
    while (NOT estVide(suite(copie))) {
        res = ajoute(premier(copie), res);
        affiche(res);
        copie = suite(copie);
    }
    return res;
}
*/

/*
Liste FonctVireDernier_iter(Liste l) {
    Liste res;
    if (estVide(l) OR estVide(suite(l))) {
        initVide(&res);
        return res;
    }

    Liste *dernier;
    dernier =&res;
    while (NOT estVide(suite(*dernier))) {
        dernier = PointeurSuite(dernier);
    }

    return res

*/
Liste FonctVireDernier_iter(Liste l) {
    Liste res;
    initVide(&res);
    if (estVide(l) OR estVide(suite(l))) {
        return res;
    }
    Liste *pl, *pres;
    pl = &l;
    pres = &res;
    while (NOT estVide(suite(*pl))) {
        empile(premier(*pl),pres);
        pl  = PointeurSuite(pl);
        pres  = PointeurSuite(pres);
    }
    return res;
}

void testFonctVireDernier(Liste (*operation)(Liste)){
    Liste l1, l2, l3, res3attendu;

    initVide (&l1);
    affiche(l1);
    affiche(operation(l1));
    assertTrue( sontEgales(l1,operation(l1)) );

    initVide (&l2) ;
    empile(5, &l2);
    affiche(l2);
    affiche(operation(l2));
    assertTrue( sontEgales(l1,operation(l2)) );

    initVide (&l3) ;
    initVide (&res3attendu) ;

    empile(2, &l3);
    empile(5, &l3);
    empile(4, &l3);
    empile(8, &l3);

    empile(5, &res3attendu);
    empile(4, &res3attendu);
    empile(8, &res3attendu);

    affiche(l3);
    affiche(operation(l3));
    assertTrue( sontEgales(operation(l3),res3attendu) );


    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&res3attendu);
}

/*************************************************/
/*                                               */
/*           AjouteDevantPremierZero             */
/*                                               */
/*************************************************/

void AjouteDevantPremierZero(Liste *l, int x){
    if (estVide(*l) OR premier(*l)==0){
        empile(x, l);
    }else {
        AjouteDevantPremierZero(PointeurSuite(l),x);
    }
}

void testAjouteDevantPremierZero() {
    Liste l1;
    initVide(&l1);

    affiche(l1);
    AjouteDevantPremierZero(&l1, 69);
    affiche(l1);
    printf("\n");
    depile(&l1);

    empile(0, &l1);
    affiche(l1);
    AjouteDevantPremierZero(&l1, 69);
    affiche(l1);
    printf("\n");
    depile(&l1);
    depile(&l1);


    empile(2, &l1);
    empile(2, &l1);
    empile(2, &l1);
    empile(3, &l1);
    empile(6, &l1);
    empile(5, &l1);
    empile(8, &l1);
    affiche(l1);
    AjouteDevantPremierZero(&l1, 69);
    affiche(l1);

    VideListe(&l1);
    printf("\n");

    Liste l2;
    initVide(&l2);

    empile(2, &l2);
    empile(2, &l2);
    empile(2, &l2);
    empile(0, &l2);
    empile(6, &l2);
    empile(0, &l2);
    empile(8, &l2);
    affiche(l2);
    AjouteDevantPremierZero(&l2, 69);
    affiche(l2);

    VideListe(&l2);
}
/*************************************************/
/*                                               */
/*           AjouteDevantDernierZero             */
/*                                               */
/*************************************************/

void Bis(Liste *l,int x,bool* vu){
    if(estVide(*l)){
        if (!*vu){
            empile(x,l);
        }
    }else{
        if (premier(*l)==0){
            *vu = TRUE;
        }
        Bis(PointeurSuite(l),x,vu);
        if(premier(*l)==0 AND *vu){
            *vu = FALSE;
            empile(x,l);
        }
    }
}

void AjouteDevantDernierZero_rec(Liste *l,int x){
    bool vu = FALSE;
    Bis(l,x,&vu);
}

void Bis2(Liste *l,int x,Liste* m) {
    if(estVide(*l)){
        if(m!=NULL){
            empile(x,m);
        }else{
            empile(x,l);
        }
    }else{
        if(premier(*l)==0){
            m = l;
        }
        Bis2(PointeurSuite(l),x,m);
    }
}


void AjouteDevantDernierZero_rec_term(Liste *l,int x){
    Liste *m;
    m = NULL;
    Bis2(l, x, m);
}

void AjouteDevantDernierZero_iter(Liste *l, int x){
    Liste* p,m;
    p = l;
    m = NULL;
    while( NOT estVide(*p)){
        if(premier(*p)==0){
            m = p;
        }
        p = PointeurSuite(p);
    }
    if(m==NULL){
        empile(x,p);
    }else{
        empile(x,m);
    }
}

void testAjouteDevantDernierZero(void (*operation)(Liste*,int)){
    Liste l1;
    initVide (&l1) ;

    affiche(l1);
    operation(&l1,69);
    affiche(l1);
    printf("\n");
    depile(&l1);

    empile(0, &l1);
    affiche(l1);
    operation(&l1,69);
    affiche(l1);
    printf("\n");
    depile(&l1);
    depile(&l1);


    empile(2, &l1);
    empile(2, &l1);
    empile(2, &l1);
    empile(3, &l1);
    empile(6, &l1);
    empile(5, &l1);
    empile(8, &l1);
    affiche(l1);
    operation(&l1,69);
    affiche(l1);

    VideListe(&l1);
    printf("\n");

    Liste l2;
    initVide (&l2) ;

    empile(2, &l2);
    empile(2, &l2);
    empile(2, &l2);
    empile(0, &l2);
    empile(6, &l2);
    empile(0, &l2);
    empile(8, &l2);
    affiche(l2);
    operation(&l2,69);
    affiche(l2);

    VideListe(&l2);
}


/*************************************************/
/*                                               */
/*           Tic                                 */
/*                                               */
/*************************************************/
/*
void Tic(Liste *l){
    if(NOT estVide(*l)){
        if(NOT estVide(suite(*l))) {
            if (premier(*l) == 0 AND premier(suite(*l)) == 0) {
                depile(l);
                Tic(l);
            } else if (premier(*l) == 0 AND premier(suite(*l)) != 0) {
                depile(l);
            } else if (premier(*l) != 0) {
                empile(0, l);
                Tic(PointeurSuite(PointeurSuite(l)));
            }
        }else{
            if (premier(*l) == 0){
                depile(l);
            }else if (premier(*l)!=0){
                empile(0, l);
            }
        }
    }
}
*/


void Tic(Liste *l){
    if(NOT estVide(*l)){
        if(NOT estVide(suite(*l))) {
            if (premier(*l) == 0){      //Si on tombe sur un 0
                depile(l);              //on le retire
                if(premier(*l) == 0){   //si le nombre d'apres est aussi un 0
                    Tic(l);             //on continue (appel recursif)
                }                       //sinon on s'arrete la (pas d'appel recursif)
            }else{                      //si on tombe sur un non nul
                empile(0, l);        //on met un 0 devant
                Tic(PointeurSuite(PointeurSuite(l))); //on continue (appel recursif)
            }
        }else{                          //si on est sur la derniere case du tableau
            if (premier(*l) == 0){      //si cest un 0
                depile(l);              //on le retire
            }else{                      //sinon
                empile(0, l);        //on met un 0 devant
            }
        }
    }
}



void testTic(){
    Liste l1, res1attendu,l2, res2attendu;
    initVide (&l1) ;
    initVide (&l2) ;
    initVide (&res1attendu) ;
    initVide (&res2attendu) ;

    affiche(l1);
    Tic(&l1);
    affiche(l1);
    assertTrue(sontEgales(l1,res1attendu));

    empile(0, &l1);

    affiche(l1);
    Tic(&l1);
    affiche(l1);
    assertTrue(sontEgales(l1,res1attendu));

    empile(4, &l1);

    empile(4, &res1attendu);
    empile(0, &res1attendu);

    affiche(l1);
    Tic(&l1);
    affiche(l1);
    assertTrue(sontEgales(l1,res1attendu));

    depile(&l1);

    empile(3, &l1);
    empile(5, &l1);
    empile(6, &l1);
    empile(7, &l1);

    empile(3, &res1attendu);
    empile(0, &res1attendu);
    empile(5, &res1attendu);
    empile(0, &res1attendu);
    empile(6, &res1attendu);
    empile(0, &res1attendu);
    empile(7, &res1attendu);
    empile(0, &res1attendu);


    affiche(l1);
    Tic(&l1);
    affiche(l1);
    assertTrue(sontEgales(l1,res1attendu));

    VideListe(&l1);
    VideListe(&res1attendu);

    empile(4, &l1);
    empile(0, &l1);
    empile(0, &l1);
    empile(4, &l1);
    empile(4, &l1);
    empile(3, &l1);
    empile(0, &l1);
    empile(0, &l1);
    empile(0, &l1);
    empile(7, &l1);
    empile(5, &l1);
    empile(5, &l1);

    empile(4, &res1attendu);
    empile(0, &res1attendu);
    empile(0, &res1attendu);
    empile(4, &res1attendu);
    empile(4, &res1attendu);
    empile(3, &res1attendu);
    empile(7, &res1attendu);
    empile(0, &res1attendu);
    empile(5, &res1attendu);
    empile(0, &res1attendu);
    empile(5, &res1attendu);
    empile(0, &res1attendu);

    affiche(l1);
    Tic(&l1);
    affiche(l1);
    assertTrue(sontEgales(l1,res1attendu));

    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);

    affiche(l2);
    Tic(&l2);
    affiche(l2);
    assertTrue(sontEgales(l2,res2attendu));


    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);
    empile(0, &l2);
    empile(7, &l2);
    empile(5, &l2);
    empile(5, &l2);

    empile(7, &res2attendu);
    empile(0, &res2attendu);
    empile(5, &res2attendu);
    empile(0, &res2attendu);
    empile(5, &res2attendu);
    empile(0, &res2attendu);

    affiche(l2);
    Tic(&l2);
    affiche(l2);
    assertTrue(sontEgales(l2,res2attendu));



    VideListe(&l1);
    VideListe(&res1attendu);
    VideListe(&l2);
    VideListe(&res2attendu);
}

/*===================================================================================================*/

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
    printf("Double Affichage \n") ;
    affiche_rec(l) ;
    affiche_iter(l) ;

    printf("Longueur en double %d %d \n\n",
           longueur_rec(l),
           longueur_iter(l)
    ) ;
}


int main(int argc, char** argv){
    system("cls");
    printf("DEBUT MAIN \n");
    if(TRUE) {
        printf("============================TEST UnPlusDeuxEgalTrois============================\n");
        testUnPlusDeuxEgalTrois();
    }
    if(TRUE) {
        printf("============================TEST Croissante============================\n");
        testCroissante();
    }
    if(TRUE) {
        printf("============================TEST NombreMemePosition_rec============================\n");
        testNombreMemePosition(NombreMemePosition_rec);
    }
    if(TRUE) {
        printf("============================TEST NombreMemePosition_iter============================\n");
        testNombreMemePosition(NombreMemePosition_iter);
    }
    if(TRUE) {
        printf("============================TEST NombreMemePosition_rec_sf============================\n");
        testNombreMemePosition(NombreMemePosition_rec_sf);
    }
    if(TRUE) {
        printf("============================TEST NombreMemePosition_rec_sp============================\n");
        testNombreMemePosition(NombreMemePosition_rec_sp);
    }
    if(TRUE) {
        printf("============================TEST FonctVireDernier_rec============================\n");
        testFonctVireDernier(FonctVireDernier_rec);
    }
    if(TRUE) {
        printf("============================TEST FonctVireDernier_iter============================\n");
        testFonctVireDernier(FonctVireDernier_iter);
    }
    if(TRUE) {
        printf("============================TEST AjouteDevantPremierZero============================\n");
        testAjouteDevantPremierZero();
    }
    if(TRUE) {
        printf("============================TEST AjouteDevantDernierZero_rec============================\n");
        testAjouteDevantDernierZero(AjouteDevantDernierZero_rec);
        }
    if(TRUE) {
        printf("============================TEST AjouteDevantDernierZero_rec_term============================\n");
        testAjouteDevantDernierZero(AjouteDevantDernierZero_rec_term);

    }
    if(TRUE) {
        printf("============================TEST AjouteDevantDernierZero_iter============================\n");
        testAjouteDevantDernierZero(AjouteDevantDernierZero_iter);
    }
    if(TRUE) {
        printf("============================TEST Tic============================\n");
        testTic();
    }



    printf("FIN MAIN\n");
    return 0;
}

#pragma clang diagnostic pop