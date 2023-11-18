#include <stdio.h>
#include <stdlib.h>

// Basit Soyut Veri Tipi (ADT) Yapısı
typedef struct {
    int data; // Sadece bir tane veri elemanı
} SimpleDataType;

// Soyut Veri Tipi Oluşturma Fonksiyonu
SimpleDataType *createSimpleDataType() {
    SimpleDataType *adt = (SimpleDataType *)malloc(sizeof(SimpleDataType));
    if (adt == NULL) {
        // Bellek tahsisi başarısız oldu
        exit(EXIT_FAILURE);
    }

    adt->data = 0; // Varsayılan değeri 0 olarak ayarla

    return adt;
}

// Veri Atama Fonksiyonu
void setDataFunction(SimpleDataType *adt, int data) {
    adt->data = data;
}

// Veriyi Alma ve Yazdırma Fonksiyonu
int getDataFunction(const SimpleDataType *adt) {
    return adt->data;
}

// Soyut Veri Tipini Temizleme Fonksiyonu
void destroyFunction(SimpleDataType *adt) {
    free(adt);
}

int main() {
    // Soyut Veri Tipi Oluşturma
    SimpleDataType *myData = createSimpleDataType();

    // Veri Atama
    setDataFunction(myData, 42);

    // Veriyi Alma ve Yazdırma
    int retrievedData = getDataFunction(myData);
    printf("Retrieved Data: %d\n", retrievedData);

    // Soyut Veri Tipini Temizleme
    destroyFunction(myData);

    return 0;
}
