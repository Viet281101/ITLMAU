#include"triqq.h" 
#include<stdlib.h> 

#define OOO0l0ll0OO00lIlI QUEFAISJENUMMAX 

static int iniF=0; 
typedef void (*pointTri_t)(int,int*); 
static pointTri_t I1OlIl00OllO[OOO0l0ll0OO00lIlI]; 
static int OI11O10I1lOO00Ol1=0; 
static unsigned int lII0llI10O0I(unsigned int a,unsigned int n,unsigned int m) { 
    unsigned int O01ll0Il0llO1lOI1=1u; 
    while(n>0) { 
        if(n&1u) O01ll0Il0llO1lOI1=(a*O01ll0Il0llO1lOI1)%m; 
        n>>=1u; a=(a*a)%m; 
    } 
    return O01ll0Il0llO1lOI1; 
} 
static int l100IO01lIIl(int OOOII1OlO11101) { 
    if(OOOII1OlO11101==0) return 0; 
    return lII0llI10O0I(620,OOOII1OlO11101,OOO0l0ll0OO00lIlI); 
} 
static int O00O100I1lOIIOO1O(int OOOII1OlO11101) { 
    if(OOOII1OlO11101==0) return 0; 
    return lII0llI10O0I(902,OOOII1OlO11101,OOO0l0ll0OO00lIlI); 
} 
static void* IO0OI0O10IOl1Ol(size_t u) { 
    void* r=malloc(u); 
    if(r==NULL) { 
        exit(-1); 
    } 
    OI11O10I1lOO00Ol1++; 
    return r; 
} 
void OOlO1lIOOIIlIIOlO0O(void* z) { 
    OI11O10I1lOO00Ol1--; 
    free(z); 
} 
static void O0lll10I0IOOI1I00OI1(int n,int* d,int* s) { 
    while(n-->0) *d++=*s++; 
} 
static int O1IOO1lOOlIl1l(int a,int b) { 
    return a>b?b:a; 
} 
static void OOI0O0l0l00I11lOI1l(int* a,int* b) { 
    int O0I001lI101IOlI11I0=*a; 
    *a=*b; 
    *b=O0I001lI101IOlI11I0;
} 
static void echangePointTri_t(pointTri_t* a,pointTri_t* b) { 
    pointTri_t O0I001lI101IOlI11I0=*a; 
    *a=*b; 
    *b=O0I001lI101IOlI11I0; 
} 
static void lll01l1l0Ol(int n,int* t) { 
    int i; 
    for(i=0;i<n/2;i++) { 
        OOI0O0l0l00I11lOI1l(t+i,t-i+n-1);
    } 
} 
static void II10lIlIlIO0O1(int n,int* t) { 
    int c=1; 
    int* l1O0IOOIOI1=NULL; 
    int* O011001I000I1l0OII=t+n; 
    while(c) { 
        c=0; 
        O011001I000I1l0OII--; 
        for(l1O0IOOIOI1=t;l1O0IOOIOI1<O011001I000I1l0OII;l1O0IOOIOI1++) if(*l1O0IOOIOI1>*(l1O0IOOIOI1+1)) { 
            OOI0O0l0l00I11lOI1l(l1O0IOOIOI1,l1O0IOOIOI1+1); 
            c=1; 
        } 
    } 
} 
static void lI0III00100O0l(int n,int* t) { 
    int i; 
    for(i=0;i<n;i++) t[i]=i; 
} 
static void IIOI0I11001OI(int n,int* t) { 
    int i; 
    int a; 
    if(n>0) a=rand()%n; 
    for(i=0;i<n;i++) t[i]=i+a; 
} 
static int IlllIIIO1I1I11l0IO(int n,int* t) { 
    int i; 
    int OIOI01II0l1l1OI=0; 
    for(i=0;i<n;i++) { 
        if(t[i]>t[OIOI01II0l1l1OI]) OIOI01II0l1l1OI=i; 
    } 
    return OIOI01II0l1l1OI; 
} 
static void l1I1IIOlIlOOI(int n,int* t) { 
    int OIOI01II0l1l1OI; 
    for(;n>1;n--) { 
        OIOI01II0l1l1OI=IlllIIIO1I1I11l0IO(n,t); 
        OOI0O0l0l00I11lOI1l(t+OIOI01II0l1l1OI,t+n-1); 
    } 
} 
static void O01lIOlOlllOOI(int n,int* t) { 
    int i; 
    for(i=0;i<n;i++) t[i]=rand()%99999-99999/2; 
} 
static void I1OI1IOl110l1(int n,int* t) { 
    int IlOI01II0l1l1OI; 
    int IOII10IIlO101O1lIO; 
    for(IlOI01II0l1l1OI=1;IlOI01II0l1l1OI<n;IlOI01II0l1l1OI++) { 
        IOII10IIlO101O1lIO=rand()%IlOI01II0l1l1OI; 
        OOI0O0l0l00I11lOI1l(t+IlOI01II0l1l1OI,t+IOII10IIlO101O1lIO); 
    } 
} 
static void melangePointTri_t(int n,pointTri_t* t) { 
    int IlOI01II0l1l1OI; 
    int IOII10IIlO101O1lIO; 
    for(IlOI01II0l1l1OI=1;IlOI01II0l1l1OI<n;IlOI01II0l1l1OI++) { 
        IOII10IIlO101O1lIO=rand()%IlOI01II0l1l1OI; 
        echangePointTri_t(t+IlOI01II0l1l1OI,t+IOII10IIlO101O1lIO); 
    } 
} static int IOl01OIl1IOIOOIl(int n,int* t,int q) { 
    int v=t[q]; 
    int* d=t; 
    int* f=t+n-2; 
    OOI0O0l0l00I11lOI1l(t+q,t+n-1); 
    while(d<=f) { 
        if(*d<v) d++; 
        else { 
            OOI0O0l0l00I11lOI1l(d,f); 
            f--; 
        } 
    } 
    OOI0O0l0l00I11lOI1l(d,t+n-1); 
    return d-t; 
} 
static void lI0Il0I0OO1l1O(int n,int* t) { 
    if(n<2) return; 
    int q=rand()%n; 
    q=IOl01OIl1IOIOOIl(n,t,q); 
    lI0Il0I0OO1l1O(q,t); 
    lI0Il0I0OO1l1O(n-q-1,t+q+1); 
} 
static int I0Il1lI101011I(int n,int* t,int q) { 
    int v=t[q]; 
    int* d=t; 
    int* f=t+n-2; 
    OOI0O0l0l00I11lOI1l(t+q,t+n-1); 
    while(d<=f) { 
        if(*d>v) d++; 
        else { 
            OOI0O0l0l00I11lOI1l(d,f); 
            f--; 
        } 
    } 
    OOI0O0l0l00I11lOI1l(d,t+n-1); 
    return d-t; 
} 
static void O1O1IIll1I00OI101Ol1(int n,int* t) { 
    if(n<2) return; 
    int q=rand()%n; 
    q=I0Il1lI101011I(n,t,q); 
    lI0Il0I0OO1l1O(q,t); 
    lI0Il0I0OO1l1O(n-q-1,t+q+1); 
} 
static void l0OO1Oll0l0OIO00O01O(int* Ill10OO0lI0lI,int* OlIl01l1000I1I1,int* O0I0l01IlOOlIl, int* IOI1ll1O0Il0,int* d) { 
    while(Ill10OO0lI0lI<OlIl01l1000I1I1 && O0I0l01IlOOlIl < IOI1ll1O0Il0) { 
        if(*Ill10OO0lI0lI<*O0I0l01IlOOlIl) *d++=*Ill10OO0lI0lI++; 
        else *d++=*O0I0l01IlOOlIl++; 
    } 
    O0lll10I0IOOI1I00OI1(OlIl01l1000I1I1-Ill10OO0lI0lI,d,Ill10OO0lI0lI); 
    O0lll10I0IOOI1I00OI1(IOI1ll1O0Il0-O0I0l01IlOOlIl,d,O0I0l01IlOOlIl); 
} 
static void Il0I1lOI11lI0(int n,int* t) { 
    int lOllOIlIOOI00l; 
    int a; 
    int lIOI01II0l1l1OI; 
    int* l1O0OIl01IllO[2]; 
    int *s=NULL; 
    int *d=NULL; 
    l1O0OIl01IllO[1]=(int*)IO0OI0O10IOl1Ol(sizeof(*t)*n); 
    l1O0OIl01IllO[0]=t; 
    for(lOllOIlIOOI00l=1,lIOI01II0l1l1OI=0;!(lOllOIlIOOI00l>=n && lIOI01II0l1l1OI%2==0);lOllOIlIOOI00l*=2,lIOI01II0l1l1OI++) { 
        s=l1O0OIl01IllO[lIOI01II0l1l1OI%2]; 
        d=l1O0OIl01IllO[(lIOI01II0l1l1OI+1)%2]; 
        for(a=0;a<n;a+=2*lOllOIlIOOI00l) { 
            l0OO1Oll0l0OIO00O01O( s+a,s+O1IOO1lOOlIl1l(n,a+lOllOIlIOOI00l), s+a+lOllOIlIOOI00l,s+O1IOO1lOOlIl1l(n,a+2*lOllOIlIOOI00l), d+a); 
        } 
    } 
    OOlO1lIOOIIlIIOlO0O(l1O0OIl01IllO[1]);
} 
static void O1OllIO1lI0O10l1O(int n,int* t) { 
    Il0I1lOI11lI0(n,t); 
    if(n>5) OOI0O0l0l00I11lOI1l(t+0,t+5); 
} 
static void O1OO1OIOlO0(int n,int* t) { 
    int c=1; 
    int* l1O0IOOIOI1=NULL; 
    int* O011001I000I1l0OII=t+n; 
    while(c) { 
        c=0; 
        O011001I000I1l0OII--; 
        for(l1O0IOOIOI1=t;l1O0IOOIOI1<O011001I000I1l0OII;l1O0IOOIOI1++) if(*l1O0IOOIOI1<*(l1O0IOOIOI1+1)) { 
            OOI0O0l0l00I11lOI1l(l1O0IOOIOI1,l1O0IOOIOI1+1); 
            c=1; 
        } 
    } 
} 
static void l00Ill01011(int n,int* t) { 
    int a; 
    Il0I1lOI11lI0(n,t); 
    if(n>0) a=rand()%n; 
    OOI0O0l0l00I11lOI1l(t,t+a); 
} 
static void I0100lIlO0IOlI00(int n,int* t) { 
    l1I1IIOlIlOOI(n,t); 
    if(n>0) t[0]=5; 
} 
static void Ill0llIO0I1O(int n,int* t) { 
    if(n>0) t[0]=t[0]; 
} 
static void I0II0I0lII1O1III(void) { 
    int i; 
    int O0IO1II1lO1lI1O; 
    for(i=0;i<OOO0l0ll0OO00lIlI;i++) I1OlIl00OllO[i]=Ill0llIO0I1O; 
    i=0; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=Ill0llIO0I1O; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=lI0Il0I0OO1l1O; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=Il0I1lOI11lI0; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=II10lIlIlIO0O1; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=l1I1IIOlIlOOI; 
    O0IO1II1lO1lI1O=i; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=lI0III00100O0l; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=lll01l1l0Ol; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=I1OI1IOl110l1; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=O01lIOlOlllOOI; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=I0100lIlO0IOlI00; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=Ill0llIO0I1O; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=O1OllIO1lI0O10l1O; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=l00Ill01011; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=O1OO1OIOlO0; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=O1O1IIll1I00OI101Ol1; 
    I1OlIl00OllO[O00O100I1lOIIOO1O(i++)]=IIOI0I11001OI; 
    O0IO1II1lO1lI1O=i-O0IO1II1lO1lI1O ; 
    for(;i<OOO0l0ll0OO00lIlI;i++) I1OlIl00OllO[O00O100I1lOIIOO1O(i)]=I1OlIl00OllO[O00O100I1lOIIOO1O(i-O0IO1II1lO1lI1O)]; 
    O0IO1II1lO1lI1O=rand(); 
    srand(3141592); 
    melangePointTri_t(OOO0l0ll0OO00lIlI,I1OlIl00OllO); 
    srand(O0IO1II1lO1lI1O); 
} 
void queFaisJe(int IO010I1IlII01lO000II,int* T,int OOOII1OlO11101) { 
    static int OO111OIO01lI001=-1,lIO1OlI0000llO=-1;; 
    if(!iniF) { 
        I0II0I0lII1O1III(); 
        iniF=1; 
    } 
    if(OOOII1OlO11101!=OO111OIO01lI001) lIO1OlI0000llO=l100IO01lIIl(OOOII1OlO11101); 
    I1OlIl00OllO[lIO1OlI0000llO](IO010I1IlII01lO000II,T); 
} 

