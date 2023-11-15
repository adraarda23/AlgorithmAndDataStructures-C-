#include <stdio.h>
#include <stdlib.h>

// Soyut Veri Tipi (ADT) Yapısı
typedef struct {
    void *data;
} MyDataType;

// İşlev Tablosu (Function Table) Yapısı
typedef struct {
    void (*setData)(MyDataType *adt, void *data);
    void *(*getData)(const MyDataType *adt);
    void (*destroy)(MyDataType *adt);
} MyDataTypeOps;

// Soyut Veri Tipi İşlemleri İçin Yardımcı Fonksiyonlar
void setDataFunction(MyDataType *adt, void *data) {
    adt->data = data;
}

void *getDataFunction(const MyDataType *adt) {
    return adt->data;
}

void destroyFunction(MyDataType *adt) {
    free(adt->data);
    // İhtiyaca göre diğer temizleme işlemleri yapılabilir.
    free(adt);
}

// Soyut Veri Tipi Oluşturma Fonksiyonu
MyDataType *createMyDataType() {
    MyDataType *adt = (MyDataType *)malloc(sizeof(MyDataType));
    if (adt == NULL) {
        // Bellek tahsisi başarısız oldu
        exit(EXIT_FAILURE);
    }

    adt->data = NULL;

    return adt;
}

// Soyut Veri Tipi İşlev Tablosu Oluşturma Fonksiyonu
MyDataTypeOps *createMyDataTypeOps() {
    MyDataTypeOps *ops = (MyDataTypeOps *)malloc(sizeof(MyDataTypeOps));
    if (ops == NULL) {
        // Bellek tahsisi başarısız oldu
        exit(EXIT_FAILURE);
    }

    ops->setData = setDataFunction;
    ops->getData = getDataFunction;
    ops->destroy = destroyFunction;

    return ops;
}

int main() {
    // Soyut Veri Tipi Oluşturma
    MyDataType *myData = createMyDataType();

    // İşlev Tablosu Oluşturma
    MyDataTypeOps *ops = createMyDataTypeOps();

    // Veri Atama
    int *myInt = (int *)malloc(sizeof(int));
    *myInt = 42;
    ops->setData(myData, myInt);

    // Veriyi Alma ve Yazdırma
    int *retrievedData = (int *)ops->getData(myData);
    printf("Retrieved Data: %d\n", *retrievedData);

    // Soyut Veri Tipini Temizleme
    ops->destroy(myData);
    free(ops);

    return 0;
}
