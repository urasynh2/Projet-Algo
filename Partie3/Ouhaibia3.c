#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct bloc_image
{ bool quatre ;
    struct bloc_image *hg, *hd, *bg, *bd ;
} bloc_image ;
typedef bloc_image *image ;

//=====================================================================

image Blanc(){
    image blanc = (image) malloc(sizeof(bloc_image)) ;
    blanc->quatre = false;
    blanc->hg = NULL;
    blanc->hd = NULL;
    blanc->bg = NULL;
    blanc->bd = NULL;
    return blanc;
}

image Noir(){
    return NULL;
}

image Compose(image i0,image i1,image i2, image i3){
    image comp = (image) malloc(sizeof(bloc_image)) ;
    comp->quatre = true;
    comp->hg = i0;
    comp->hd = i1;
    comp->bg = i2;
    comp->bd = i3;
    return comp;
}

void libererMemoire(image img) {
    if (img != NULL) {
        libererMemoire(img->hg);
        libererMemoire(img->hd);
        libererMemoire(img->bg);
        libererMemoire(img->bd);
        free(img);
    }
}

//=====================================================================


void Affichage(image i){
    if(i==NULL){
        printf("X");
    }else if(!i->quatre){
        printf("o");
    }else{
        Affichage(i->hg);
        Affichage(i->hd);
        Affichage(i->bg);
        Affichage(i->bd);
        printf("*");
    }
}

void AffichageParenthese(image i){
    if(i==NULL){
        printf("X");
    }else if(!i->quatre){
        printf("o");
    }else{
        printf("(");
        AffichageParenthese(i->hg);
        AffichageParenthese(i->hd);
        AffichageParenthese(i->bg);
        AffichageParenthese(i->bd);
        printf("*)");
    }
}

void Aux(image i,int prof){
    if(i==NULL){
        printf("X%d ",prof);
    }else if(!i->quatre){
        printf("o%d ",prof);
    }else{
        Aux(i->hg,prof+1);
        Aux(i->hd,prof+1);
        Aux(i->bg,prof+1);
        Aux(i->bd,prof+1);
        printf("*%d ",prof);
    }
}

void AffichageProfondeur(image i) {
    Aux(i,0);
}

void AuxParenthese(image i,int prof){
    if(i==NULL){
        printf("X%d ",prof);
    }else if(!i->quatre){
        printf("o%d ",prof);
    }else{
        printf("(");
        AuxParenthese(i->hg,prof+1);
        AuxParenthese(i->hd,prof+1);
        AuxParenthese(i->bg,prof+1);
        AuxParenthese(i->bd,prof+1);
        printf("*)%d ",prof);
    }
}

void AffichageProfondeurParenthese(image i) {
    AuxParenthese(i,0);
}

//=====================================================================


typedef struct Bloc
{
    char c;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Pile ;


void initVide( Pile *L)
{
    *L = NULL ;
}

bool estVide(Pile l)
{
    return l == NULL ;
}

int premier(Pile l)
{
    return l->c ;
}

Pile ajoute(char x, Pile l)
{
    Pile tmp = (Pile) malloc(sizeof(Bloc)) ;
    tmp->c = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(char x, Pile *L)
{
    *L = ajoute(x,*L) ;
}

Pile suite(Pile l)
{
    return l->suivant ;
}

void depile(Pile *L)
{
    Pile tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

image Lec(Pile *pile){
    if (premier(*pile) == 'X') { // Image noire
        depile(pile);
        return Noir();
    } else if (premier(*pile) == 'o') { // Image blanche
        depile(pile);
        return Blanc();
    } else if (premier(*pile) == '*') { // Image composée
        depile(pile);
        image bd = Lec(pile);
        image bg = Lec(pile);
        image hd = Lec(pile);
        image hg = Lec(pile);
        return Compose(hg, hd, bg, bd);
    } else {
        depile(pile);
        return Lec(pile);
    }
}

image Lecture() {
    Pile pile;
    initVide(&pile);
    char c;
    while ((c = getchar()) != '!') {
        empile(c, &pile);
    }
    return Lec(&pile);
}

//====================================================================

image LectureStr(const char* img ) {
    Pile pile;
    initVide(&pile);
    int i = 0;
    while (img[i] != '\0') {
        empile(img[i], &pile);
        i++;
    }
    return Lec(&pile);
}

//=====================================================================
bool EstNoire(image i){
    if(i==NULL){
        return true;
    }else if(!i->quatre){
        return false;
    }else{
        return EstNoire(i->hg) &&
        EstNoire(i->hd) &&
        EstNoire(i->bg) &&
        EstNoire(i->bd);
    }
}

bool EstBlanche(image i){
    if(i==NULL){
        return false;
    }else if(!i->quatre){
        return true;
    }else{
        return EstBlanche(i->hg) &&
                EstBlanche(i->hd) &&
                EstBlanche(i->bg) &&
                EstBlanche(i->bd);
    }
}

//=====================================================================

double Aire(image img){
    if(EstNoire(img)){
        return 1;
    }else if(EstBlanche(img)){
        return 0;
    }else{
        return (Aire(img->hg) + Aire(img->hd) + Aire(img->bg) + Aire(img->bd))/4;
    }
}

//=====================================================================

image TriangleBD(int p){
    if (p==0){
        return Blanc();
    }else{
        image ii = TriangleBD(p-1);
        return Compose(Blanc(), ii,ii,Noir());
    }
}

//=====================================================================

void Arrondit(image *img, int p){
    if (*img != NULL) {
        if (p == 0) {
            if (Aire(*img) > 0.5) {
                *img = Noir();
            } else {
                *img = Blanc();
            }
        } else {
            Arrondit(&(*img)->hg, p - 1);
            Arrondit(&(*img)->hd, p - 1);
            Arrondit(&(*img)->bg, p - 1);
            Arrondit(&(*img)->bd, p - 1);
        }
    }
}

//=====================================================================

bool MemeDessin(image img1, image img2){
    if(EstNoire(img1) || EstNoire(img2)){
        if (EstNoire(img1)) {
            return EstNoire(img2);
        }else{
            return false;
        }
    }else if(EstBlanche(img1) || EstBlanche(img2)){
        if (EstBlanche(img1)) {
            return EstBlanche(img2);
        }else{
            return false;
        }
    }else{
        return MemeDessin(img1->hg, img2->hg) &&
        MemeDessin(img1->hd, img2->hd) &&
        MemeDessin(img1->bg, img2->bg) &&
        MemeDessin(img1->bd, img2->bd);

    }
}
//=====================================================================

void InterUnion(image *inter, image *unio) {
    if(!EstBlanche(*inter) && !EstNoire(*unio)){
        if (EstNoire(*inter)) {
            *inter = *unio;
            *unio = Noir();
        } else{
            if (EstBlanche(*unio)) {
                *unio = *inter;
                *inter = Blanc();
            } else{
                InterUnion(&((*inter) -> hg), &((*unio) -> hg));
                InterUnion(&((*inter) -> hd), &((*unio) -> hd));
                InterUnion(&((*inter) -> bg), &((*unio) -> bg));
                InterUnion(&((*inter) -> bd), &((*unio) -> bd));
            }
        }
    }
}
//=====================================================================




//=====================================================================


int main(){
    printf("DEBUT MAIN\n");


    if(true){//ESTNOIRE ET ESTBLANCHE
        printf("L'image ooooo*oooo*o*oooooo** est blanche: %s \n", EstBlanche(LectureStr("ooooo*oooo*o*oooooo**")) ? "vrai" : "faux");
        printf("L'image XXXXX*XXXXX** est noire: %s\n", EstNoire(LectureStr("XXXXX*XXXXX**")) ? "vrai" : "faux");
    }

    if(true){//AIRE
        printf("Le taux de noir de l'image XoXoo*XXXXo** est: %f (doit afficher 0.75) \n", Aire(LectureStr(" XoXoo*XXXXo**")));
    }


    if(true){ //TRIANGLEBD
        printf("TriangleBD(0)=");Affichage(TriangleBD(0));printf("\n");
        printf("TriangleBD(1)=");Affichage(TriangleBD(1));printf("\n");
        printf("TriangleBD(3)=");Affichage(TriangleBD(3));printf("\n");
    }

    if(true){ //ARRONDIT

        image i = LectureStr("XXXooX*oXXo*oooX**oXo*oXXoooXXX**oX**");
        printf("Arrondit(");Affichage(i);printf(",2) arrondit l'image en ");
        Arrondit( &i,2);
        Affichage(i);
        libererMemoire(i);
    }

    if(true){ //MEMEDESSIN
        printf("\nXooooo*ooo*oooo*o*XoooXXXX*** et XXXXXXXXXX***oooo*Xooooo*oX** ont le meme dessin: %s \n",
               MemeDessin(LectureStr("Xooooo*ooo*oooo*o*XoooXXXX***"),LectureStr("XXXXXXXXXX***oooo*Xooooo*oX**")) ? "vrai" : "faux");

    }

    if(true){//INTERUNION
        image i1 = LectureStr("oXoXXo*oXoX*oXX**");
        image i2 = LectureStr("XoXoXooX*ooXX*X**");
        Affichage(i1); printf(" et ");
        Affichage(i2); printf("donne\n");
        InterUnion(&i1,&i2);
        printf("Intersection:");Affichage(i1);printf("\n");
        printf("Union:");Affichage(i2);printf("\n");
        libererMemoire(i1);
        libererMemoire(i2);
    }

    printf("\nFIN MAIN\n");
    return 0;
}