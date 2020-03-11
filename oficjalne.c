//Marta Markocka
//zadanie 'zycie'
//27.12.2018r.

#include <stdio.h>
#include <stdlib.h>

#define INF 1000*1000*1000
#define TAK 1
#define NIE 0

typedef struct lista_komorek {
	int w;
	struct lista_komorek *nast;
} LK;

typedef struct lista_wierszy {
	LK *w;
	struct lista_wierszy *nast;
} LW;

int min (int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

int max (int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

void wstaw_za_wiersz (LW *wsk, LK *x) {
	LW *pom;
	pom = malloc(sizeof(LW));
	pom->nast = wsk->nast;
	pom->w = x;
	wsk->nast = pom;
}

void wstaw_za_komorke (LK *wsk, int x) {
	LK *pom;
	pom = malloc(sizeof(LK));
	pom->nast = wsk->nast;
	pom->w = x;
	wsk->nast = pom;
}


void nowy_pusty (LK **nk2, LK *k1, LK *k3, int *czy_sa) {
	LK *nk2_pocz;
	nk2_pocz = *nk2;
	LK *pk1, *pk3;
	int x, licz;
	
	if (k1 !=  NULL)
		k1 = k1->nast;
	if (k3 !=  NULL)
		k3 = k3->nast;
	int poprzedni= -INF;
	
	while (k1 != NULL || k3 != NULL) {
		if (k1 != NULL) {
			if (k3 != NULL)
				x = min(k1->w, k3->w);
			else
				x = k1->w;
		} else {
			x = k3->w;
		}
		licz = 0;
		pk1 = k1;
		pk3 = k3;
		while (pk1 != NULL && pk1->w <= x+1) {
			licz++;
			pk1 = pk1->nast;
		}
		while (pk3 != NULL && pk3->w <= x+1) {
			licz++;
			pk3= pk3->nast;
		}
		if (poprzedni < x-1 && licz == 3) {
			wstaw_za_komorke(*nk2, x);
			(*nk2) = (*nk2)->nast;
			*czy_sa = TAK;
		}
		if (pk1 != NULL && pk1->w <= x+2) {
			licz++;
			pk1 = pk1->nast;
		}
		if (pk3 != NULL && pk3->w <= x+2) {
			licz++;
			pk3= pk3->nast;
		}
		if (licz == 3) {
			wstaw_za_komorke(*nk2, x+1);
			(*nk2) = (*nk2)->nast;
			*czy_sa = TAK;
		}
		if (k1 != NULL && k1->w == x)
			k1 = k1->nast;
		if (k3 != NULL && k3->w == x)
			k3 = k3->nast;
		poprzedni = x;
	}
	*nk2 = nk2_pocz;
}

void nowy_niepusty (LK **nk2, LK *k2, LK *k1, LK *k3, int *czy_sa) {
	LK *b1=NULL, *b2=NULL, *b3=NULL; //b to o 1 wczesniejsze od aktualnie rozpatrywanego w k
	LK *nk2_pocz; nk2_pocz = *nk2;
	k2 = k2->nast;
	if (k1 != NULL) k1 = k1->nast; 
	if (k3 != NULL) k3 = k3->nast;
	int x, licz;
	
	while (k1 != NULL || k2 != NULL || k3 != NULL) {
		if (k1 != NULL) {
			x = k1->w;
			if (k2 != NULL)
				x = min(x, k2->w);
			if (k3 != NULL)
				x = min(x, k3->w);
		} else if (k2 != NULL) {
			x = k2->w;
			if (k3 != NULL)
				x = min(x, k3->w);
		} else {
			x = k3->w;
		}
		//czy powstanie dla x-1?
		if ((b1==NULL || b1->w < x-2) && (b2==NULL || b2->w < x-2) && (b3==NULL || b3->w < x-2)) {
			if ((k1 != NULL && k1->w == x) && (k2 != NULL && k2->w == x) && (k3 != NULL && k3->w == x)) {
				wstaw_za_komorke(*nk2, x-1);
				(*nk2) = (*nk2)->nast;
				*czy_sa = TAK;
			}
		}
		//czy powstanie dla x?
		licz=0;
		if (b1 != NULL && b1->w == x-1) {
			licz++;
		}
		if (k1 != NULL && k1->w == x) {
			licz++;
		}
		if (k1 != NULL && (k1->w == x+1 || (k1->nast != NULL && (k1->nast)->w == x+1))) {
			licz++;
		}
		if (b3 != NULL && b3->w == x-1) {
			licz++;
		}
		if (k3 != NULL && k3->w == x) {
			licz++;
		}
		if (k3 != NULL && (k3->w == x+1 || (k3->nast != NULL && (k3->nast)->w == x+1))) {
			licz++;
		}
		if (b2 != NULL && b2->w == x-1) {
			licz++;
		}
		if (k2 != NULL && (k2->w == x+1 || (k2->nast != NULL && (k2->nast)->w == x+1))) {
			licz++;
		}
		if (licz == 3 || (licz == 2 && k2 != NULL && k2->w == x)) {
			wstaw_za_komorke(*nk2, x);
			(*nk2) = (*nk2)->nast;
			*czy_sa = TAK;
		}
		//czy powstanie x+1?
		if ((k1 != NULL && k1->w == x+1) || (k1 != NULL && k1->nast != NULL && (k1->nast)->w == x+1) ||
			(k2 != NULL && k2->w == x+1) || (k2 != NULL && k2->nast != NULL && (k2->nast)->w == x+1) ||
			(k3 != NULL && k3->w == x+1) || (k3 != NULL && k3->nast != NULL && (k3->nast)->w == x+1)) { //czyli gdzies jest x+1
		} else {																						//czyli nie ma x+1 nigdzie
			licz=0;
			if (k1 != NULL && k1->w == x) {
				licz++;
			}
			if (k2 != NULL && k2->w == x) {
				licz++;
			}
			if (k3 != NULL && k3->w == x) {
				licz++;
			}
			if (k1 != NULL && (k1->w == x+2 || (k1->nast != NULL && (k1->nast)->w == x+2))) {
				licz++;
			}
			if (k2 != NULL && (k2->w == x+2 || (k2->nast != NULL && (k2->nast)->w == x+2))) {
				licz++;
			}
			if (k3 != NULL && (k3->w == x+2 || (k3->nast != NULL && (k3->nast)->w == x+2))) {
				licz++;
			}
			if (licz == 3) {
				wstaw_za_komorke(*nk2, x+1);
				(*nk2) = (*nk2)->nast;
				*czy_sa = TAK;
			}
		}
		
		if (k1 != NULL && k1->w == x) {
			b1 = k1;
			k1 = k1->nast;
		}
		if (k2 != NULL && k2->w == x) {
			b2 = k2;
			k2 = k2->nast;
		}
		if (k3 != NULL && k3->w == x) {
			b3 = k3;
			k3 = k3->nast;
		}
	}
	*nk2 = nk2_pocz;
}


void zwolnij_liste_wierszy(LW *l){
	if (l != NULL) {
		zwolnij_liste_wierszy(l->nast);
		free(l);
	}
}

void zwolnij_wiersz(LK *k){
	if (k != NULL) {
		zwolnij_wiersz(k->nast);
		free(k);
	}
}

void zwolnij_calosc(LW *l){
	LW * pom = l;
	while(l != NULL) {
		zwolnij_wiersz(l->w);
		l = l->nast;
	}
	zwolnij_liste_wierszy(pom);	
}					
			

void tylko_jeden_wiersz (LW **nl, LK *k1) {
	LK *nk, *nk1, *mk;
	int czy_sa;
	
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k1->w -1;
	czy_sa = NIE;
	nowy_pusty(&nk, k1, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk);
		*nl = (*nl)->nast;
	} else
		free(nk);
	
	nk1 = malloc(sizeof(LK));
	nk1->nast = NULL;
	nk1->w = k1->w;
	czy_sa = NIE;
	nowy_niepusty(&nk1, k1, NULL, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk1);
		*nl = (*nl)->nast;
	} else
		free(nk1);
	
	mk = malloc(sizeof(LK));
	mk->nast = NULL;
	mk->w = k1->w +1;
	czy_sa = NIE;
	nowy_pusty(&mk, k1, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, mk);
		*nl = (*nl)->nast;
	} else
		free(mk);
	
}

void licz_pierwszy_wiersz ( LW **nl, LK *k1, LK *k2) {
	LK *nk1, *nk, *mk;
	int czy_sa;
	
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k1->w -1;
	czy_sa = NIE;
	nowy_pusty(&nk, k1, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk);
		*nl = (*nl)->nast;
	} else
		free(nk);
	
	nk1 = malloc(sizeof(LK));
	nk1->nast = NULL;
	nk1->w = k1->w;
	czy_sa = NIE;
	if (k1->w + 1 == k2->w) { //czyli pierwszy i drugi sasiaduja
		nowy_niepusty(&nk1, k1, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk1);
			*nl = (*nl)->nast;
		} else
			free(nk1);
	} else if (k1->w + 2 == k2->w) { //czyli pierwszy i drugi dzieli jeden pusty
		nowy_niepusty(&nk1, k1, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk1);
			*nl = (*nl)->nast;
		} else
			free(nk1);
		
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k1->w +1;
		czy_sa = NIE;
		nowy_pusty(&mk, k1, k2, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
	} else { //czyli pierwszy i drugi dzieli wiecej pustych
		nowy_niepusty(&nk1, k1, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk1);
			*nl = (*nl)->nast;
		} else
			free(nk1);
		
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k1->w +1;
		czy_sa = NIE;
		nowy_pusty(&mk, k1, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
	}
}

void tylko_dwa_wiersze ( LW **nl, LK *k1, LK *k2 ) {
	LK *nk2, *nk, *mk;
	int czy_sa = NIE;
	nk2 = malloc(sizeof(LK));
	nk2->nast = NULL;
	nk2->w = k2->w;
	
	if (k1->w + 1 == k2->w) { //czyli pierwszy i drugi sasiaduja
		nowy_niepusty(&nk2, k2, k1, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);

	} else if (k1->w + 2 == k2->w) { //czyli 1,2 dzieli jeden wiersz
		
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
	} else { //czyli 1,2 dzieli wiecej niz jeden wiersz
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k2->w -1;
		nowy_pusty(&mk, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
		
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
	}
	
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k2->w +1;
	czy_sa = NIE;
	nowy_pusty (&nk, k2, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk);
		*nl = (*nl)->nast;
	} else
		free(nk);
}

void k1_k2_dzieli_wiecej_niz_jeden_wiersz (LW **nl, LK *k2, LK *k3) {
	LK *nk, *nk2, *mk;
	int czy_sa = NIE;
	
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k2->w -1;
	nowy_pusty(&nk, k2, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk);
		*nl = (*nl)->nast;
	} else
		free(nk);
	
	czy_sa = NIE;
	nk2 = malloc(sizeof(LK));
	nk2->nast = NULL;
	nk2->w = k2->w;
	if (k2->w + 1 == k3->w) { //czyli 2,3 sasiaduja
		nowy_niepusty(&nk2, k2, k3, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
	} else if (k2->w + 2 == k3->w) { // czyli 2,3 dzieli jeden wiersz
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
		czy_sa = NIE;
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k2->w +1;
		nowy_pusty(&mk, k2, k3, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
	} else { // czyli 2,3 dzieli wiecej niz 1 wiersz
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);

		czy_sa = NIE;
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k2->w +1;
		nowy_pusty(&mk, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
	}
}

void k1_k2_dzieli_dokladnie_jeden_wiersz (LW **nl, LK *k2, LK *k3) {
	LK *nk, *nk2;
	int czy_sa = NIE;
	nk2 = malloc(sizeof(LK));
	nk2->nast = NULL;
	nk2->w = k2->w;
	
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k2->w +1;

	if (k2->w + 1 == k3->w) { //czyli 2,3 sasiaduja
		nowy_niepusty(&nk2, k2, k3, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		free(nk);
	} else if (k2->w + 2 == k3->w) { //czyli 2,3 dzieli dokladnie 1 wiersz
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
		czy_sa = NIE;
		
		nowy_pusty(&nk, k2, k3, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk);
			*nl = (*nl)->nast;
		} else
			free(nk);
	} else { //czyli 2,3 dzieli wiecej niz 1 wiersz
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
		czy_sa = NIE;
		nowy_pusty(&nk, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk);
			*nl = (*nl)->nast;
		} else
			free(nk);
	}
}

void k1_k2_sasiaduja (LW **nl, LK *k1, LK *k2, LK *k3) {
	LK *nk, *nk2;
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k2->w +1;
	
	nk2 = malloc(sizeof(LK));
	nk2->nast = NULL;
	nk2->w = k2->w;
	int czy_sa = NIE;
	
	if (k2->w + 1 == k3->w) { //czyli 2,3 sasiaduja
		nowy_niepusty(&nk2, k2, k1, k3, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		free(nk);
		
	} else if (k2->w + 2 == k3->w) { //czyli 2,3 dzieli dokladnie jeden wiersz
		nowy_niepusty(&nk2, k2, k1, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
		czy_sa = NIE;
		
		nowy_pusty(&nk, k2, k3, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk);
			*nl = (*nl)->nast;
		} else
			free(nk);
		
	} else { //czyli 2,3 dzieli wiecej niz jeden wiersz
		nowy_niepusty(&nk2, k2, k1, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
		czy_sa = NIE;
		nowy_pusty(&nk, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk);
			*nl = (*nl)->nast;
		} else
			free(nk);
	}
}

void ostatni_wiersz (LW **nl, LK *k1, LK *k2) {
	LK *nk, *nk2, *mk;
	nk2 = malloc(sizeof(LK));
	nk2->nast = NULL;
	nk2->w = k2->w;
	int czy_sa = NIE;
	
	if (k1->w + 1 == k2->w) { //1,2 sasiaduja
		nowy_niepusty(&nk2, k2, k1, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
	} else if (k1->w + 2 == k2->w) { //1,2 dzieli jeden wiersz
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
		
	} else { //1,2 dzieli wiecej niz jeden wiersz
		mk = malloc(sizeof(LK));
		mk->nast = NULL;
		mk->w = k2->w -1;
		nowy_pusty(&mk, k2, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, mk);
			*nl = (*nl)->nast;
		} else
			free(mk);
		
		czy_sa = NIE;
		nowy_niepusty(&nk2, k2, NULL, NULL, &czy_sa);
		if (czy_sa == TAK) {
			wstaw_za_wiersz(*nl, nk2);
			*nl = (*nl)->nast;
		} else
			free(nk2);
	}
	
	czy_sa = NIE;
	nk = malloc(sizeof(LK));
	nk->nast = NULL;
	nk->w = k2->w +1;
	nowy_pusty(&nk, k2, NULL, &czy_sa);
	if (czy_sa == TAK) {
		wstaw_za_wiersz(*nl, nk);
		*nl = (*nl)->nast;
	} else
		free(nk);
}


LW *nowa_generacja (LW *l) {
	LW *nl;
	nl = malloc(sizeof(LW));
	nl->w = NULL;
	nl->nast = NULL;
	LW *nl_pocz;
	nl_pocz = nl;
	if (l == NULL)
		return l;
	l = l->nast;
	
	if (l == NULL) { //lista nie ma zadnego wiersza
		return l;
		
	} else if (l->nast == NULL) { //lista ma jeden wiersz
		LK *k;
		k = l->w;
		tylko_jeden_wiersz(&nl, k);
		return nl_pocz;
		
	} else { //lista ma co najmniej dwa wiersze, wiec moge policzyc pierwszy wiersz z pewnoscia
		LK *k1, *k2;
		k1 = l->w;
		l = l->nast;
		k2 = l->w;
		licz_pierwszy_wiersz(&nl, k1, k2);
		l = l->nast;
		
		if (l == NULL) { //czyli lista ma dokladnie dwa wiersze
			
			tylko_dwa_wiersze (&nl, k1, k2);
			return nl_pocz;
			
		} else { //czyli lista ma co najmniej 3 wiersze
			LK *k3;
			while (l != NULL) {
				k3 = l->w;
				
				if (k1->w + 2 < k2->w) { //czyli 1,2 dzieli wiecej niz jeden wiersz
					k1_k2_dzieli_wiecej_niz_jeden_wiersz (&nl, k2, k3);
					
				} else if (k1->w + 2 == k2->w) { //czyli 1,2 dzieli dokladnie 1 wiersz
					k1_k2_dzieli_dokladnie_jeden_wiersz (&nl, k2, k3);
					
				} else { //czyli 1,2 sasiaduja
					k1_k2_sasiaduja (&nl, k1, k2, k3);	
				}
							   
				k1 = k2;
				k2 = k3;
				l = l->nast;
			}
			//dla ostatniego wiersza
			ostatni_wiersz (&nl, k1, k2);
			return nl_pocz;
		}
	}
}


LW *czytaj_dane (int *ile_zywych, int *ile_wierszy, int *ile_kolumn, int *C, int *D, int *E, int *F) {
	LW *l, *l_pocz;
	l = malloc(sizeof(LW));
	l->w = NULL;
	l->nast = NULL;
	l_pocz = l;
	char znak;
	
	while ((znak=getchar()) != '\n' && znak != '\r' && znak != EOF) {
		ungetc(znak, stdin);
		LK *k, *k_pocz;
		k = malloc(sizeof(LK));
		k->nast = NULL;
		k_pocz = k;
		int zywe = 0; //zywe w tym wierszu
		int kolumny=0;
		while ((znak=getchar()) != '\n' && znak != '\r') {
			kolumny++;
			if (znak == '0') {
				wstaw_za_komorke(k, kolumny);
				k = k->nast;
				zywe++;
				*D = min(*D, kolumny);
				*F = max(*F, kolumny);
			}	
		}
		if (kolumny > *ile_kolumn)
			*ile_kolumn = kolumny;
		(*ile_wierszy)++;
		k_pocz->w = *ile_wierszy;
		if (zywe > 0) {
			*ile_zywych += zywe;
			zywe = 0;
			wstaw_za_wiersz(l, k_pocz);
			l = l->nast;
			*C = min(*C, *ile_wierszy);
			*E = max(*E, *ile_wierszy);
		} else
			free(k);
	}
	if (*ile_zywych == 0) {
		*C = 0;
		*D = 0;
	}
	return l_pocz;
 }

void wypisz (LW *l, int A, int B, int C, int D, int E, int F, int G, int H, int I, int J) {
	int i=G, x;
	LK *k;
	
	while (l != NULL && l->nast != NULL) {
		l = l->nast;
		k = l->w;
		if (k->w >= G && k->w <= I) {
			while (k->w > i) { //wypisuje ew puste wiersze w obrebie okna miedzy poprzednim a wlasnie znalezionym
				for (int j=1; j<=J-H+1; j++) {
					printf(".");
				}
				printf("\n");
				i++;
			}
			x=H;
			while(k!= NULL && k->nast != NULL) {
				k = k->nast;
				if (k->w >= H && k->w <= J) {
					while (k->w > x) {
						printf(".");
						x++;
					}
					printf("0");
					x++;
				}
			}
			while(x <= J) {
				printf(".");
				x++;
			}
			printf("\n");
			i++;
		}
	}
	while (i<=I) {
		for (int j=1; j<=J-H+1; j++) {
			printf(".");
		}
		printf("\n");
		i++;
	}
	printf("%d {%d} (%d:%d) (%d:%d) [%d:%d] [%d:%d]\n", A, B, C, D, E, F, G, H, I, J);
}

void status (LW *l, int *B, int *C, int *D, int *E, int *F) {
	(*B) = 0;
	if (l == NULL) {
		*B = 0; *C = 0; *D = 0; *E = 0; *F = 0;
		
	} else {
		l = l->nast;
		if (l != NULL) {
			LK *k;
			k = l->w;
			*C = k->w;
			k = k->nast;
			*D = k->w;
			while (k->nast != NULL) {
				k = k->nast;
				(*B)++;
			}
			(*B)++;
			*F = k->w;
			l = l->nast;
			while (l->nast != NULL) {
				k = l->w;
				k = k->nast;
				if (k->w < *D)
					*D = k->w;
				while (k->nast != NULL) {
					k = k->nast;
					(*B)++;
				}
				(*B)++;
				if (k->w > *F)
					*F = k->w;
				l = l->nast;
			}
			k = l->w;
			*E = k->w;
			k = k->nast;
			if (k->w < *D)
				*D = k->w;
			while (k->nast != NULL) {
				k = k->nast;
				(*B)++;
			}
			(*B)++;
			if (k->w > *F)
				*F = k->w;		
		}
	}
}

int liczba (char *T, int *iz) {
	int wynik=0;
	int potega=1;
	
	while (*iz > 0 && *(T + *iz-1) != ' ' && *(T + *iz-1) != '\n') {
		(*iz)--;
		if (*(T + *iz) != '-') {
			int cyfra = (int)(*(T + *iz)) - (int)('0');
			cyfra *= potega;
			potega *= 10;
			wynik += cyfra;
		} else {
			wynik = -wynik;
		}
	}
	
	if (*iz > 0 && *(T + *iz-1) == ' ') (*iz)--;
	return wynik;
}

void czytaj_polecenia (LW *l, int *A, int *B, int *C, int *D, int *E, int *F, int *G, int *H, int *I, int *J) {
	char znak;
	int iz=0; //ile znakow
	int is=0; //ile spacji
	
	while ((znak=getchar()) != EOF) {
		ungetc(znak, stdin);
		char *T; T = malloc(50*sizeof(char));
		znak=getchar();
		
		while (znak != '\n' && znak != EOF) {
			iz++;
			T[iz-1] = znak; //indeksuje od 0
			if (znak == ' ')
				is++;
			znak = getchar();
		}
		
		if (iz == 0) { //polecenie puste
			LW *poprz = l;
			l = nowa_generacja(l);
			zwolnij_calosc(poprz);
			(*A)++;
			status(l, B, C, D, E, F);
			wypisz(l, *A, *B, *C, *D, *E, *F, *G, *H, *I, *J);
			
		} else if (is == 0) { //jedna liczba
			int ile = liczba(T, &iz);
			for (int i=0; i<ile; i++) {
				LW *poprz = l;
				l = nowa_generacja(l);
				zwolnij_calosc(poprz);
				(*A)++;
			}
			status(l, B, C, D, E, F);
			wypisz(l, *A, *B, *C, *D, *E, *F, *G, *H, *I, *J);
			
		} else if (is == 1) { //dwie liczby
			int nH = liczba(T, &iz);
			int nG = liczba(T, &iz);
			*I = *I + nG - *G;
			*J = *J + nH - *H;
			*G = nG;
			*H = nH;
			wypisz(l, *A, *B, *C, *D, *E, *F, *G, *H, *I, *J);		
			
		} else if (is == 3) { //cztery liczby
			*J = liczba(T, &iz);
			*I = liczba(T, &iz);
			*H = liczba(T, &iz);
			*G = liczba(T, &iz);
			wypisz(l, *A, *B, *C, *D, *E, *F, *G, *H, *I, *J);	
		}
		iz=0;
		is=0;
		free(T);
	}
	zwolnij_calosc(l);
}


int main () {
	LW *l;
	int A = 0; //ktora generacja
	int B = 0; //ile zywych komorek
	int C = INF, D = INF, E = 0, F = 0; //teren gdzie istnieja zywe komorki
	int G = 1, H = 1, I = 0, J = 0; //wspolrzedne okna, poczatkowo I - ile wierszy, J - ile kolumn
	
	l = czytaj_dane(&B, &I, &J, &C, &D, &E, &F);
	wypisz(l, A, B, C, D, E, F, G, H, I, J);
	
	czytaj_polecenia(l, &A, &B, &C, &D, &E, &F, &G, &H, &I, &J);
	
	return 0;
}