#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
// Arda Aydin Kilinc || 21360859039

//Random kütüphanesi kullanılarak rastgele cevap anahtari yaratiliyor
void cevap_anahtari_uret(char cevap_anahtari[],int S){
    char anahtar[5]={'A','B','C','D','E'};
    for(int i=0;i<S;i++){
        cevap_anahtari[i] = anahtar[rand() % 5];
 }
//Rastgele yaratilan cevap anahtarini ekrana yazdiriyor
}
void cevap_anahtari_yazdir(char cevap_anahtari[ ], int S){
    printf("\nSinavin cevap anahtari\n");
    for(int i=1;i<S+1;i++){
    printf("%3.d-)%c\t",i,cevap_anahtari[i-1]);
    if(i%5==0)
    printf("\n");
 }
 printf("\n");
}
//Dogru , Bos ve Yanlis oranina göre ogrenci cevabi olusturuyor
void sinavi_uygula(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], int N, int S, double B, double D){
    for(int i=0;i<N;i++)
        for(int j=0;j<S;j++){
            if((rand() % 1000000)<(B*1000000)){   //10^6 ile carpilarak ondalikli double degerini bir tamsayiya donusturuyor
            ogrenci_cevaplari[i][j]=88;}          //tamsayilar uzerinden aralik kontrolu yapiyor ve ona göre siklari belirliyor
            else{
                if((rand() % 1000000)<(D*1000000)) 
                    ogrenci_cevaplari[i][j]=cevap_anahtari[j]; 
                else{
                    /*Dogru sikkin ascii degeri ve iterasyon rakami arasindaki iliski kullanilarak
                    dogru secenegin aralarinda olmadigi bir yanlis siklar listesi olusturup
                    oradan rastgele bir sik seciliyor */
                    char siklar[4]={66,67,68,69};    
                    for(int k=0;k<5;k++){
                        if(cevap_anahtari[j]==65+k){
                            ogrenci_cevaplari[i][j]=siklar[rand() % 4];
                            break;
                        }
                        else{
                            siklar[k]=siklar[k]-1;
     }
    }
   }
  }
 }
}
//Ogrencilerin verdigi cevaplari yazdiriyor
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[ ][100], int ogrenci_ID, int S){
    printf("\n%d. ögrencinin cevap anahtari\n",ogrenci_ID+1);
    for(int i=1;i<S+1;i++){
    printf("%d-)%c\t",i,ogrenci_cevaplari[ogrenci_ID][i-1]);
    if(i%5==0)
    printf("\n");
 }
}
//ogrencilerin dogru , yanlis ve boslari hesaplanip 4 yanlis bir dogruyu goturecek sekilde hesaplaniyor 
void ogrencileri_puanla(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], double HBN[ ], int N, int S){
    for(int i=0;i<N;i++){
        double sonuc=0;
        for(int j=0;j<S;j++){
            if(ogrenci_cevaplari[i][j]=='X')
                sonuc=sonuc;
            else if(ogrenci_cevaplari[i][j]==cevap_anahtari[j])
                sonuc+=1;
            else
                sonuc-=0.25;
            }
            if (sonuc<=0) //sonucu sifirin altinda olan notlar sifira esitleniyor
                sonuc=0;
            HBN[i]=sonuc*100/S;  //yüzdesel not hesaplamak icin 100 sayisi , soru sayisina bolunerek sonucla carpiliyor
 }
}
//formule bagli sinif ortalamasi hesaplaniyor
double sinif_ortalamasi_hesapla(double HBN[ ], int N){
    double sinif_ortalamasi=0;
    for(int i=0;i<N;i++)
        sinif_ortalamasi += HBN[i];

    sinif_ortalamasi = sinif_ortalamasi /N;
    return sinif_ortalamasi;
}

//formule bagli standart sapma hesaplaniyor
double standart_sapma_hesapla(double ortalama, double HBN[ ], int N){
    double sonuc;
    for(int i=0;i<N;i++){
       sonuc += pow((HBN[i]-(ortalama)),2);       
    }
    sonuc = sqrt(sonuc / (N-1));
    return sonuc;
}
//Elde edilen ortalama ve standart sapma degerleri kullanilarak herbir ogrencinin T skoru hesaplanıyor
void T_skoru_hesapla(double ortalama, double HBN[ ], int N, double std, double T_skoru[ ]){
    for(int i=0;i<N;i++){
        T_skoru[i]=(((HBN[i]-ortalama)/std)*10)+60;
 }
}

/*Main fonksiyonunun icindeki islemler sayesinde x degeri belirleniyor.Bu x degeri notlamanin sistemini degistiriyor
y degiskeni sayesindeyse notlamnin araliklari belirlenerek ogrencilerin harf notu belirleniyor*/
void T_skoru_bul(double T_skoru[],int N,int x,char *Harf_Skoru[]){
    printf("\n");
    char *skorlar[7]={"BA","BB","CB","CC","DC","DD","FD"};
    for(int i=1;i<N+1;i++){
        int y=0;
        if(T_skoru[i-1]>=67+x){
            Harf_Skoru[i-1]="AA";
        }
        if(T_skoru[i-1]<=32+x){
            Harf_Skoru[i-1]="FF";
    }
    for(int j=0;j<7;j++){
        if((T_skoru[i-1]>=(62-y+x))&&(T_skoru[i-1]<=(66.99-y+x))){
            Harf_Skoru[i-1]=skorlar[j];
            break;
        }
        else{
            y+=5;
   }
  } 
 } 
}
//ogrenci HBN , T skoru ve Harf Skorunu  yazdirir
void ogrenci_sonuc_yazdir(double HBN[],double T_skoru[],char *Harf_Skoru[],int N){
    printf("\n");
    for(int i=1;i<N+1;i++){
        printf("%03d.Ogrencinin HBN: %05.2lf | T-Skoru: %05.2lf | Harf Notu: %s \n",i,HBN[i-1],T_skoru[i-1],Harf_Skoru[i-1]);
 }
}
int main(){
    //Gerekli degerlerin tanimlandigi alan
    srand(time(NULL));
    int N,S,ogrenci_ID=0;
    double B,D,ortalama,std;
    printf("Ogrenci Sayisi giriniz(0~100): ");scanf("%d",&N);
    printf("\nSoru Sayisi giriniz(0~100): ");scanf("%d",&S);
    printf("\nBos birakma ihtimali giriniz(0~1): ");scanf("%lf",&B);
    printf("\nDogru yapma ihtimali giriniz(0~1): ");scanf("%lf",&D);
    char cevap_anahtari[100]={};
    char ogrenci_cevaplari[100][100]={};
    double HBN[100]={};
    double T_skoru[100]={};
    char *Harf_Skoru[100]={};

    //MODUL 1
    cevap_anahtari_uret(cevap_anahtari,S);
    cevap_anahtari_yazdir(cevap_anahtari,S);
    sinavi_uygula(ogrenci_cevaplari,cevap_anahtari,N,S,B,D);
    ogrencileri_puanla(ogrenci_cevaplari,cevap_anahtari,HBN, N,S);
    for(;ogrenci_ID<N;ogrenci_ID++)
        ogrenci_cevabini_yazdir(ogrenci_cevaplari,ogrenci_ID,S);

    //MODUL 2
    ortalama=sinif_ortalamasi_hesapla(HBN,N);
    std=standart_sapma_hesapla(ortalama,HBN,N);
    printf("\n%.2lf sinif ortalamasi ",ortalama);
    printf(" Standart Sapma %.2lf \n\n",std);
    T_skoru_hesapla(ortalama,HBN,N,std,T_skoru);



    /*Sinifin Genel ortalamasi burada kontrol ediliyor , sinifin ait oldugu aralik belirleniyor ve yazdiriliyor
    y ve z degerleri bu iterasyonun araliklarini belirleyen degiskenler.Bu degiskenlere bagli olarak
    x degeri ve sinifin durumu belirleniyor.x degeri T_skoru_yazdir fonksiyonuna gönderiliyor
    (x T_skoru_yazdir fonkisyonunun aralik belirleyici degiskeni).
    
    !! ISTISNAI DURUM !! sinif ortalamasinin 0(sifir) olmasi sonucunda olusacak hatayi önlemek icin iterasyondan bagimsiz
    bir sekilde belirleniyor cunku ortalamanin 0(sifir) olabilmesi icin herkesin 0(sifir) almis olmasi gerekiyor ve buda
    harf notu yazdirmada harf notunun yazdirilamamasi gibi bir soruna yol aciyor.herkesin 60(Ti) Puan aldigi "Kotu" araliginda
    butun hepsinin DC alacagi anlamina geliyor olmasini kullanilrak bu hata onlenmis oluyor.
    */
    double degerler[8]={20,10,7.5,5,5,5,5,42.5}; // not araliklarindaki farklarin tutuldugu liste
    char *sinif_durumu[8]={"Ustun Basari","Mukemmmel","Cok Iyi","Iyi","Ortanin Ustu","Orta","Zayif","Kotu"}; //harf notu listesi
    int x=0 ; double y=0;double z=0;double g;double h;
    for(int i=0;i<8;i++){
        if(ortalama==0){
            printf("Sinifin Genel Durumu: %s\n",sinif_durumu[7]);
            for(int k=1;k<N+1;k++){
                printf("%d. Ogrencinin Skoru DC\n",k);
            }
            break;
        }
        else if(ortalama<=(100-y)&&ortalama>(80-z)){
            printf("Sinifin Genel Durumu: %s",sinif_durumu[i]);
            T_skoru_bul(T_skoru,N,x,Harf_Skoru);
            break;
           }
        else{
            y+=degerler[i];
            z+=degerler[i+1];
            x+=2;
  }
 }
 ogrenci_sonuc_yazdir(HBN,T_skoru,Harf_Skoru,N);
}
