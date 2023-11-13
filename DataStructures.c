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

struct Ogrenci* createDoublyLinkedList(int lengthOfLinkedList, int ogrenciNo[], char* ad[], char* soyAd[], char* bolum[], int sinif[]) {
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
            node->in = tail;
            tail = node;
        }
    }
    return head;
}

void destroyLinkedList(struct Ogrenci* firstAddressOfList) {
    while (firstAddressOfList != NULL) {
        struct Ogrenci* tempAddress = firstAddressOfList;
        firstAddressOfList = firstAddressOfList->out;

        if (firstAddressOfList != NULL) {
            firstAddressOfList->in = NULL;
        }

        free(tempAddress);
    }
    printf("Linked List deleted!\n");
}


struct Ogrenci* addNode(int indexNumber, struct Ogrenci* firstAddressOfList, int ogrenciNo, char* ad, char* soyAd, char* bolum, int sinif) {
    struct Ogrenci* node = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    int counter = 0;
    struct Ogrenci* checkDuplicates = firstAddressOfList;
    bool controlFlag = true;
    struct Ogrenci* nonZeroIndexAddress = firstAddressOfList;
    int lengthOfLinkedList = 0;

    // Duplicacy check
    while (checkDuplicates != NULL) {
        if (checkDuplicates->ogrenciNo == ogrenciNo) {
            printf("ogrenciNo is a PRIMARY KEY! %d already taken\n", ogrenciNo);
            controlFlag = false;
            free(node);
            break;
        }
        lengthOfLinkedList++;
        checkDuplicates = checkDuplicates->out;
    }

    if (indexNumber > lengthOfLinkedList)
        indexNumber = lengthOfLinkedList;
        
    if (indexNumber < 0) {
        printf("This method cannot take negative index values\n");
        controlFlag = false;
    } else {
        if (indexNumber == 0) {
            node->ogrenciNo = ogrenciNo;
            node->ad = malloc(strlen(ad) + 1);
            strcpy(node->ad, ad);
            node->soyAd = malloc(strlen(soyAd) + 1);
            strcpy(node->soyAd, soyAd);
            node->bolum = malloc(strlen(bolum) + 1); 
            strcpy(node->bolum, bolum);
            node->sinif = sinif;
            node->out = firstAddressOfList;
            firstAddressOfList->in = node; 
            return node;
        } else {
            while (indexNumber - 1 != counter && firstAddressOfList != NULL) {
                firstAddressOfList = firstAddressOfList->out;
                counter++;
            }
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

        if (firstAddressOfList != NULL) {
            node->out = firstAddressOfList->out;
            if (firstAddressOfList->out != NULL) {
                firstAddressOfList->out->in = node;
            }
            firstAddressOfList->out = node;
            node->in = firstAddressOfList;
        }
    }

    return nonZeroIndexAddress;
}


struct Ogrenci* deleteNode(int ogrenciNo, struct Ogrenci* firstAddressOfList) {
    if (firstAddressOfList == NULL) {
        printf("List is not exist.\n");
        return firstAddressOfList;
    }

    if (firstAddressOfList->ogrenciNo == ogrenciNo) {
        struct Ogrenci* temp = firstAddressOfList;
        firstAddressOfList = firstAddressOfList->out;
        printf("No: %d, %s %s is deleted\n", temp->ogrenciNo, temp->ad, temp->soyAd);
        free(temp);
        return firstAddressOfList;
    }

    struct Ogrenci* current = firstAddressOfList;
    while (current->out != NULL && current->out->ogrenciNo != ogrenciNo) {
        current = current->out;
    }

    if (current->out == NULL) {
        printf("Node with ogrenciNo: %d not found.\n", ogrenciNo);
        return firstAddressOfList;
    }
    
    struct Ogrenci* temp = current->out;
    current->out = temp->out; //current->out changed to current->out->out (skipped one node)

    printf("No: %d, %s %s is deleted\n", temp->ogrenciNo, temp->ad, temp->soyAd);
    free(temp);

    return firstAddressOfList;
}

struct Ogrenci* searchNode(int ogrenciNo , struct  Ogrenci* firstAddressOfList){
    
    while (firstAddressOfList != NULL) {
        if (ogrenciNo == firstAddressOfList->ogrenciNo) {
            return firstAddressOfList;
        }
        firstAddressOfList = firstAddressOfList->out;
    }
    printf("Ogrenci not found\n");
    return firstAddressOfList;
}
void displayLinkedList(struct Ogrenci* firstAddressOfList) {

    while (firstAddressOfList != NULL && firstAddressOfList->in != NULL) {
        firstAddressOfList = firstAddressOfList->in;
    }

    while (firstAddressOfList != NULL) {
        printf("ogrenciNo: %d, Ad: %s, Soyad: %s, Bolum: %s, Sinif: %d\n",
               firstAddressOfList->ogrenciNo, firstAddressOfList->ad, firstAddressOfList->soyAd, firstAddressOfList->bolum, firstAddressOfList->sinif);

        firstAddressOfList = firstAddressOfList->out;
    }
}


//return int because I dont want to get a compile warning
int main() { 

    int ogrenciNo[] = {1,2,3};
    char* ad[] = {"Ali","veli","deli"};
    char* soyAd[] = {"Yilmaz","yilar","yildi"};
    char* bolum[] = {"Bilgisayar Muhendisligi","bm","qcte"};
    int sinif[] = {2,1,3};

    struct Ogrenci* head = createDoublyLinkedList(3, ogrenciNo, ad, soyAd, bolum, sinif);
  
    
    head=addNode(0, head, 4, "Arda", "Kilinc", "Bilgisayar", 2);
    head=addNode(8, head, 5, "Arda", "Kilinc", "Bilgisayar", 2);
    struct Ogrenci* searchedNode = searchNode(2,head);
     printf("%d %s %s %s %d \n",searchedNode->ogrenciNo,searchedNode->ad,searchedNode->soyAd,searchedNode->bolum,searchedNode->sinif);
    //head = deleteNode(1, head);
    displayLinkedList(searchedNode);
    destroyLinkedList(searchedNode);
    
    return 0;
}





