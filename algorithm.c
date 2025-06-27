//SARE EKEN 22100022016 ALGORİTMALAR ÖDEV2
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Dugum {
    int dugumNumarasi;
    int uzunluk;
    struct Dugum* sonraki;
} Dugum;


typedef struct Graf {
    int dugumSayisi;
    Dugum** komsulukListeleri;
} Graf;


Dugum* dugumOlustur(int dugumNumarasi, int uzunluk) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum));
    yeniDugum->dugumNumarasi = dugumNumarasi;
    yeniDugum->uzunluk = uzunluk;
    yeniDugum->sonraki = NULL;
    return yeniDugum;
}


Graf* grafOlustur(int dugumSayisi) {
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->dugumSayisi = dugumSayisi;
    graf->komsulukListeleri = (Dugum**)malloc(dugumSayisi * sizeof(Dugum*));

    for (int i = 0; i < dugumSayisi; i++) {
        graf->komsulukListeleri[i] = NULL;
    }
    return graf;
}


void kenarEkle(Graf* graf, int kaynak, int hedef, int uzunluk) {
    // Kaynak düğüme yeni bir hedef düğüm ekle
    Dugum* yeniDugum = dugumOlustur(hedef, uzunluk);
    yeniDugum->sonraki = graf->komsulukListeleri[kaynak];
    graf->komsulukListeleri[kaynak] = yeniDugum;

}


void grafYazdir(Graf* graf) {
    for (int i = 0; i < graf->dugumSayisi; ++i) {
        Dugum* suankiDugum = graf->komsulukListeleri[i];
        printf("%c -> ", i + 'A');
        while (suankiDugum != NULL) {
            printf("%c(%d) ", suankiDugum->dugumNumarasi + 'A', suankiDugum->uzunluk);
            suankiDugum = suankiDugum->sonraki;
        }
        printf("\n");
    }
}


void dijkstra(Graf* graf, int baslangic) {
    int* mesafe = (int*)malloc(graf->dugumSayisi * sizeof(int));
    char* onceki = (char*)malloc(graf->dugumSayisi * sizeof(char));
    bool* ziyaretEdildi = (bool*)malloc(graf->dugumSayisi * sizeof(bool));

    for (int i = 0; i < graf->dugumSayisi; i++) {
        mesafe[i] = INT_MAX;
        onceki[i] = '\0';
        ziyaretEdildi[i] = false;
    }

    mesafe[baslangic] = 0;

    for (int i = 0; i < graf->dugumSayisi - 1; i++) {
        int enKisaDugum = -1;
        int enKisaMesafe = INT_MAX;

        for (int j = 0; j < graf->dugumSayisi; j++) {
            if (!ziyaretEdildi[j] && mesafe[j] < enKisaMesafe) {
                enKisaMesafe = mesafe[j];
                enKisaDugum = j;
            }
        }

        ziyaretEdildi[enKisaDugum] = true;

        Dugum* iter = graf->komsulukListeleri[enKisaDugum];
        while (iter != NULL) {
            int hedef = iter->dugumNumarasi;
            int uzaklik = iter->uzunluk;
            if (!ziyaretEdildi[hedef] && mesafe[enKisaDugum] != INT_MAX && mesafe[enKisaDugum] + uzaklik < mesafe[hedef]) {
                mesafe[hedef] = mesafe[enKisaDugum] + uzaklik;
                onceki[hedef] = enKisaDugum + 'A';
            }
            iter = iter->sonraki;
        }
    }


    printf("Dijkstra Algoritması:\n");
    printf("Dugum Uzaklik Onceki Dugum\n");
    for (int i = 0; i < graf->dugumSayisi; ++i) {
        if (mesafe[i] == INT_MAX)
            printf("%c\t\t∞\t\t%c\n", i + 'A', onceki[i]);
        else
            printf("%c\t\t%d\t\t\t%c\n", i + 'A', mesafe[i], onceki[i]);
    }

    free(mesafe);
    free(onceki);
    free(ziyaretEdildi);
}


void bellmanFord(Graf* graf, int baslangic) {
    int* mesafe = (int*)malloc(graf->dugumSayisi * sizeof(int));
    char* onceki = (char*)malloc(graf->dugumSayisi * sizeof(char));

    for (int i = 0; i < graf->dugumSayisi; i++) {
        mesafe[i] = INT_MAX;
        onceki[i] = '\0';
    }
    mesafe[baslangic] = 0;

    for (int count = 0; count < graf->dugumSayisi - 1; count++) {
        for (int u = 0; u < graf->dugumSayisi; u++) {
            Dugum* iter = graf->komsulukListeleri[u];
            while (iter != NULL) {
                int hedef = iter->dugumNumarasi;
                int uzaklik = iter->uzunluk;
                if (mesafe[u] != INT_MAX && mesafe[u] + uzaklik < mesafe[hedef]) {
                    mesafe[hedef] = mesafe[u] + uzaklik;
                    onceki[hedef] = u + 'A';
                }
                iter = iter->sonraki;
            }
        }
    }

    for (int u = 0; u < graf->dugumSayisi; u++) {
        Dugum* iter = graf->komsulukListeleri[u];
        while (iter != NULL) {
            int hedef = iter->dugumNumarasi;
            int uzaklik = iter->uzunluk;
            if (mesafe[u] != INT_MAX && mesafe[u] + uzaklik < mesafe[hedef]) {
                printf("HATA\n");
                free(mesafe);
                free(onceki);
                return;
            }
            iter = iter->sonraki;
        }
    }


    printf("Bellman-Ford Algoritması:\n");
    printf("Dugum Uzaklik Onceki Dugum\n");
    for (int i = 0; i < graf->dugumSayisi; ++i) {
        if (mesafe[i] == INT_MAX)
            printf("%c\t\t\t∞\t\t%c\n", i + 'A', onceki[i]);
        else
            printf("%c\t\t%d\t\t\t%c\n", i + 'A', mesafe[i], onceki[i]);
    }

    free(mesafe);
    free(onceki);
}

int main() {
    FILE* dosya = fopen("graf.txt", "r");
    if (!dosya) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    int dugumSayisi;
    fscanf(dosya, "%d\n", &dugumSayisi);

    Graf* graf = grafOlustur(dugumSayisi);

    char kaynak, hedef;
    int uzunluk;
    while (fscanf(dosya, "%c-%c-%d\n", &kaynak, &hedef, &uzunluk) == 3) {
        kenarEkle(graf, kaynak - 'A', hedef - 'A', uzunluk);
    }

    fclose(dosya);

    grafYazdir(graf);

    char baslangic;
    printf("\nBaslangic dugumunu girin (A,B,C,D): ");
    scanf(" %c", &baslangic);
    int baslangicIndex = baslangic - 'A';

    dijkstra(graf, baslangicIndex);
    bellmanFord(graf, baslangicIndex);

    for (int i = 0; i < dugumSayisi; i++) {
        Dugum* iter = graf->komsulukListeleri[i];
        while (iter != NULL) {
            Dugum* temp = iter;
            iter = iter->sonraki;
            free(temp);
        }
    }
    free(graf->komsulukListeleri);
    free(graf);

    return 0;
}
