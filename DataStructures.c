#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Ogrenci {
    int ogrenciNo;
    char* ad;
    char* soyAd;
    char* bolum;
    int sinif;
    struct Ogrenci* in;
    struct Ogrenci* out;
};

struct Ogrenci* createLinkedList(int lengthOfLinkedList, int ogrenciNo[], char* ad[], char* soyAd[], char* bolum[], int sinif[]) {
    if (lengthOfLinkedList <= 0) {
        printf("lengthOfLinkedList cannot be a negative or zero number");
        return NULL;
    }

    struct Ogrenci* head = NULL;
    struct Ogrenci* tail = NULL;

    for (int i = 0; i < lengthOfLinkedList; i++) {
        struct Ogrenci* node = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
        node->ogrenciNo = ogrenciNo[i];
        node->ad = ad[i];
        node->soyAd = soyAd[i];
        node->bolum = bolum[i];
        node->sinif = sinif[i];
        node->in = NULL;
        node->out = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            
            tail->out = node;
            tail = node;
        }
    }
    return head;
}

void destroyLinkedList(struct Ogrenci* firstAddressOfList){
    while(firstAddressOfList!=NULL){
    struct Ogrenci* tempAddress=firstAddressOfList;
    firstAddressOfList=firstAddressOfList->out;
    printf("deleted\n");
    free(tempAddress);
    }
}

struct Ogrenci* addNode(int indexNumber, struct Ogrenci* firstAddressOfList, int ogrenciNo, char* ad, char* soyAd, char* bolum, int sinif) {
    struct Ogrenci* node = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    int counter = 0;
    struct Ogrenci* checkDuplicates = firstAddressOfList;
    bool controlFlag = true;
    struct Ogrenci* nonZeroIndexAddress = firstAddressOfList;

    while (checkDuplicates != NULL) { //out of range mistake !!
        if (checkDuplicates->ogrenciNo == ogrenciNo) {
            printf("ogrenciNo is a PRIMARY KEY! %d already taken\n",ogrenciNo);
            controlFlag = false;
            break;
        }
        checkDuplicates = checkDuplicates->out;
    }

    if (indexNumber < 0) {
        printf("This method cannot take negative index values\n");
        controlFlag = false;
    } else {
        if(indexNumber==0){
        node->ogrenciNo = ogrenciNo;
        node->ad = malloc(strlen(ad) + 1);
        strcpy(node->ad, ad);
        node->soyAd = malloc(strlen(soyAd) + 1);
        strcpy(node->soyAd, soyAd);
        node->bolum = malloc(strlen(bolum) + 1); 
        strcpy(node->bolum, bolum);
        node->sinif = sinif;
        node->out=firstAddressOfList;
        return node;
        }
        else
        while (indexNumber - 1 != counter && firstAddressOfList != NULL) {
            firstAddressOfList = firstAddressOfList->out;
            counter++;
        
        }
    }

    if (controlFlag) {
        node->ogrenciNo = ogrenciNo;
        node->ad = malloc(strlen(ad) + 1);
        strcpy(node->ad, ad);
        node->soyAd = malloc(strlen(soyAd) + 1);
        strcpy(node->soyAd, soyAd);
        node->bolum = malloc(strlen(bolum) + 1); 
        strcpy(node->bolum, bolum);
        node->sinif = sinif;
        node->out = firstAddressOfList->out;
        firstAddressOfList->out = node;
    }
    return nonZeroIndexAddress;
}

struct Ogrenci* deleteNode(int indexNumber, struct Ogrenci* firstAddressOfList) {
    if (indexNumber == 0 && firstAddressOfList != NULL) {
        struct Ogrenci* temp = firstAddressOfList;
        firstAddressOfList = firstAddressOfList->out;
        free(temp);
    } else if (indexNumber > 0) {
        struct Ogrenci* current = firstAddressOfList;
        for (int i = 0; i < indexNumber - 1 && current != NULL && current->out != NULL; i++) {
            current = current->out;
        }
        if (current != NULL && current->out != NULL) {
            struct Ogrenci* temp = current->out;
            printf("No: %d , %s %s deleted\n",temp->ogrenciNo,temp->ad,temp->soyAd);
            current->out = current->out->out;
            free(temp);
        } else {
            printf("Index %d is out of range. Cannot delete a node.\n", indexNumber);
        }
    }

    return firstAddressOfList;
}
struct Ogrenci* searchNode(int indexNumber , struct  Ogrenci* firstAddressOfList){
    int counter =0;
    while(counter!=indexNumber){
        firstAddressOfList=firstAddressOfList->out;
        counter++;
    }
    return firstAddressOfList;
}
void displayLinkedList(struct  Ogrenci* firstAddressOfList){
        while (firstAddressOfList != NULL) {
        printf("Ogrenci No: %d, Ad: %s, Soyad: %s, Bolum: %s, Sinif: %d\n",
               firstAddressOfList->ogrenciNo, firstAddressOfList->ad, firstAddressOfList->soyAd, firstAddressOfList->bolum, firstAddressOfList->sinif);
        firstAddressOfList =firstAddressOfList->out;
    }
}


int main() { //return int because I dont want to get a compile warning

    int ogrenciNo[] = {1, 2, 3};
    char* ad[] = {"Ali", "Ayse", "Mehmet"};
    char* soyAd[] = {"Yilmaz", "Kara", "Ozturk"};
    char* bolum[] = {"Bilgisayar Muhendisligi", "Elektrik Muhendisligi", "Makine Muhendisligi"};
    int sinif[] = {2, 3, 1};

    struct Ogrenci* head = createLinkedList(3, ogrenciNo, ad, soyAd, bolum, sinif);
  
    head=addNode(4, head, 5, "Arda", "Kilinc", "Bilgisayar", 2);
    struct Ogrenci* searchedNode = searchNode(2,head);
    printf("%d %s %s %s %d \n",searchedNode->ogrenciNo,searchedNode->ad,searchedNode->soyAd,searchedNode->bolum,searchedNode->sinif);
    head = deleteNode(1, head);

    displayLinkedList(head);
    destroyLinkedList(head);
    return 0;
}





