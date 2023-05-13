#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ODA_SAYISI 10
#define TC_KIMLIK_UZUNLUK 11
#define AD_UZUNLUK 50
#define SOYAD_UZUNLUK 50
#define GIRIS_TARIHI_UZUNLUK 11

struct Musteri {
    int odaNumarasi;
    char tcKimlik[TC_KIMLIK_UZUNLUK];
    char ad[AD_UZUNLUK];
    char soyad[SOYAD_UZUNLUK];
    char girisTarihi[GIRIS_TARIHI_UZUNLUK];
};

struct Musteri odalar[MAX_ODA_SAYISI];
bool doluOdalar[MAX_ODA_SAYISI];

void initialize() {
    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        doluOdalar[i] = false;
    }
}

void yeniMusteriKayit() {
    int odaNo;
    char tcKimlik[TC_KIMLIK_UZUNLUK];
    char ad[AD_UZUNLUK];
    char soyad[SOYAD_UZUNLUK];
    char girisTarihi[GIRIS_TARIHI_UZUNLUK];

    printf("Oda Numarasi: ");
    scanf("%d", &odaNo);

    if (odaNo < 1 || odaNo > MAX_ODA_SAYISI) {
        printf("Gecersiz oda numarasi girdiniz!\n");
        return;
    }

    if (doluOdalar[odaNo - 1]) {
        printf("Girilen odada kalan bir musterimiz bulunmaktadir!\n");
        return;
    }

    printf("T.C. Kimlik Numarasi: ");
    scanf("%s", tcKimlik);

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i] && strcmp(odalar[i].tcKimlik, tcKimlik) == 0) {
            printf("Girilen TC kimlik numarali bir kayit zaten bulunmaktadir!\n");
            return;
        }
    }

    printf("Ad: ");
    scanf("%s", ad);

    printf("Soyad: ");
    scanf("%s", soyad);

    printf("Gelis Tarihi (gg.aa.yyyy): ");
    scanf("%s", girisTarihi);

    struct Musteri yeniMusteri;
    yeniMusteri.odaNumarasi = odaNo;
    strcpy(yeniMusteri.tcKimlik, tcKimlik);
    strcpy(yeniMusteri.ad, ad);
    strcpy(yeniMusteri.soyad, soyad);
    strcpy(yeniMusteri.girisTarihi, girisTarihi);

    odalar[odaNo - 1] = yeniMusteri;
    doluOdalar[odaNo - 1] = true;

    printf("Musterimiz basariyla kaydedildiniz.\n");
}

void odaDegisikligi() {
    char tcKimlik[TC_KIMLIK_UZUNLUK];
    int hedefOdaNo;

    printf("T.C. Kimlik Numarasi: ");
    scanf("%s", tcKimlik);

    int mevcutOdaNo = -1;
    bool musteriBulundu = false;

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i] && strcmp(odalar[i].tcKimlik, tcKimlik) == 0) {
            mevcutOdaNo = i + 1;
            musteriBulundu = true;
            break;
        }
    }

    if (!musteriBulundu) {
        printf("Girilen TC kimlik numarali bir kayit bulunamadi,üzgünüz !\n");
        return;
    }

    printf("Hedef Oda Numarasi: ");
    scanf("%d", &hedefOdaNo);

    if (hedefOdaNo < 1 || hedefOdaNo > MAX_ODA_SAYISI) {
        printf("Gecersiz oda numarasi!\n");
        return;
    }

    if (doluOdalar[hedefOdaNo - 1]) {
        printf("Girilen hedef oda doludur!\n");
        return;
    }

    odalar[hedefOdaNo - 1] = odalar[mevcutOdaNo - 1];
    doluOdalar[hedefOdaNo - 1] = true;
    doluOdalar[mevcutOdaNo - 1] = false;

    printf("Oda degisikligi basariyla gerceklesti.\n");
}

void kayitlariGoster() {
    bool doluOdaVar = false;
    printf("--- Kayitlar ---\n");

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i]) {
            printf("Oda Numarasi: %d\n", i + 1);
            printf("T.C. Kimlik Numarasi: %s\n", odalar[i].tcKimlik);
            printf("Ad: %s\n", odalar[i].ad);
            printf("Soyad: %s\n", odalar[i].soyad);
            printf("Gelis Tarihi: %s\n\n", odalar[i].girisTarihi);
            doluOdaVar = true;
        }
    }

    if (!doluOdaVar) {
        printf("Dolu oda bulunmamaktadir.\n");
    }
}

void musteriCikis() {
    char tcKimlik[TC_KIMLIK_UZUNLUK];
    printf("T.C. Kimlik Numarasi: ");
    scanf("%s", tcKimlik);

    int cikisOdaNo = -1;
    bool musteriBulundu = false;

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i] && strcmp(odalar[i].tcKimlik, tcKimlik) == 0) {
            cikisOdaNo = i + 1;
            musteriBulundu = true;
            break;
        }
    }

    if (!musteriBulundu) {
        printf("Girilen TC kimlik numarali bir kayit bulunamadi!\n");
        return;
    }

    doluOdalar[cikisOdaNo - 1] = false;
    printf("Musteri kaydi basariyla silindi.\n");
}

void odaNumarasinaGoreArama() {
    int odaNo;
    printf("Oda Numarasi: ");
    scanf("%d", &odaNo);

    if (odaNo < 1 || odaNo > MAX_ODA_SAYISI) {
        printf("Gecersiz oda numarasi!\n");
        return;
    }

    if (!doluOdalar[odaNo - 1]) {
        printf("Girilen odada kalan musteri bulunmamaktadir!\n");
        return;
    }

    printf("--- Arama Sonucu ---\n");
    printf("Oda Numarasi: %d\n", odaNo);
    printf("T.C. Kimlik Numarasi: %s\n", odalar[odaNo - 1].tcKimlik);
    printf("Ad: %s\n", odalar[odaNo - 1].ad);
    printf("Soyad: %s\n", odalar[odaNo - 1].soyad);
    printf("Gelis Tarihi: %s\n", odalar[odaNo - 1].girisTarihi);
}

void soyadaGoreArama() {
    char soyad[SOYAD_UZUNLUK];
    bool musteriBulundu = false;
    printf("Soyad: ");
    scanf("%s", soyad);

    printf("--- Arama Sonucu ---\n");

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i] && strcmp(odalar[i].soyad, soyad) == 0) {
            printf("Oda Numarasi: %d\n", i + 1);
            printf("T.C. Kimlik Numarasi: %s\n", odalar[i].tcKimlik);
            printf("Ad: %s\n", odalar[i].ad);
            printf("Soyad: %s\n", odalar[i].soyad);
            printf("Gelis Tarihi: %s\n\n", odalar[i].girisTarihi);
            musteriBulundu = true;
        }
    }

    if (!musteriBulundu) {
        printf("Girilen soyada sahip musteri bulunamadi!\n");
    }
}

void gelisTarihineGoreArama() {
    char girisTarihi[GIRIS_TARIHI_UZUNLUK];
    bool musteriBulundu = false;
    printf("Gelis Tarihi (gg.aa.yyyy): ");
    scanf("%s", girisTarihi);

    printf("--- Arama Sonucu ---\n");

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i] && strcmp(odalar[i].girisTarihi, girisTarihi) == 0) {
            printf("Oda Numarasi: %d\n", i + 1);
            printf("T.C. Kimlik Numarasi: %s\n", odalar[i].tcKimlik);
            printf("Ad: %s\n", odalar[i].ad);
            printf("Soyad: %s\n", odalar[i].soyad);
            printf("Gelis Tarihi: %s\n\n", odalar[i].girisTarihi);

            musteriBulundu = true;
        }
    }

    if (!musteriBulundu) {
        printf("Girilen tarihte gelen musteri bulunamadi!\n");
    }
}

void dolulukOrani() {
    int doluOdaSayisi = 0;
    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i]) {
            doluOdaSayisi++;
        }
    }

    float dolulukOrani = (float)doluOdaSayisi / MAX_ODA_SAYISI * 100;

    printf("Doluluk Orani: %.2f%%\n", dolulukOrani);
}

void bosOdaNumaralari() {
    bool bosOdaVar = false;

    printf("Bos Oda Numaralari: ");

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (!doluOdalar[i]) {
            printf("%d ", i + 1);
            bosOdaVar = true;
        }
    }

    printf("\n");

    if (!bosOdaVar) {
        printf("Bos oda bulunmamaktadir.\n");
    }
}

void doluOdaNumaralari() {
    bool doluOdaVar = false;
    printf("Dolu Oda Numaralari: ");

    for (int i = 0; i < MAX_ODA_SAYISI; i++) {
        if (doluOdalar[i]) {
            printf("%d ", i + 1);
            doluOdaVar = true;
        }
    }

    printf("\n");

    if (!doluOdaVar) {
        printf("Dolu oda bulunmamaktadir.\n");
    }
}

int main() {
    initialize();
    int secim;

    do {
        printf("\n--- Butik Otel Yonetim Sistemi ---\n");
        printf("1) Yeni Musteri Kayit\n");
        printf("2) Oda Degisikligi\n");
        printf("3) Kayitlari Goster\n");
        printf("4) Musteri Cikis\n");
        printf("5) Arama\n");
        printf("6) Doluluk\n");
        printf("7) Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                yeniMusteriKayit();
                break;
            case 2:
                odaDegisikligi();
                break;
            case 3:
                kayitlariGoster();
                break;
            case 4:
                musteriCikis();
                break;
            case 5:
                printf("\n--- Arama ---\n");
                printf("a) Oda Numarasina Gore\n");
                printf("b) Soyada Gore\n");
                printf("c) Gelis Tarihine Gore\n");

                char aramaSecim;
                printf("Seciminizi yapin: ");
                scanf(" %c", &aramaSecim);

                switch (aramaSecim) {
                    case 'a':
                        odaNumarasinaGoreArama();
                        break;
                    case 'b':
                        soyadaGoreArama();
                        break;
                    case 'c':
                        gelisTarihineGoreArama();
                        break;
                    default:
                        printf("Gecersiz bir secim yaptiniz!\n");
                        break;
                }

            case 6:
                printf("\n--- Doluluk ---\n");
                printf("a) Doluluk Orani\n");
                printf("b) Bos Oda Numaralari\n");
                printf("c) Dolu Oda Numaralari\n");

                char dolulukSecim;
                printf("Seciminizi yapin: ");
                scanf(" %c", &dolulukSecim);

                switch (dolulukSecim) {
                    case 'a':
                        dolulukOrani();
                        break;
                    case 'b':
                        bosOdaNumaralari();
                        break;
                    case 'c':
                        doluOdaNumaralari();
                        break;
                    default:
                        printf("Gecersiz bir secim yaptiniz!\n");
                        break;
                }

            case 7:
                printf("Programdan cikis yapiliyor...\n");
                break;

            default:
                printf("Gecersiz bir secim yaptiniz!\n");
                break;
        }

    } while (secim != 7);

    return 0;
}
