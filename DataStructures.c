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
        printf("\nlengthOfLinkedList cannot be a negative or zero number");
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
    printf("\nLinked List deleted!\n");
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
            printf("\nogrenciNo is a PRIMARY KEY! %d already taken\n", ogrenciNo);
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
        printf("\nThis method cannot take negative index values\n");
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
        printf("\nList is not exist.\n");
        return firstAddressOfList;
    }

    if (firstAddressOfList->ogrenciNo == ogrenciNo) {
        struct Ogrenci* temp = firstAddressOfList;
        firstAddressOfList = firstAddressOfList->out;
        printf("\nNo: %d, %s %s is deleted\n", temp->ogrenciNo, temp->ad, temp->soyAd);
        free(temp);
        return firstAddressOfList;
    }

    struct Ogrenci* current = firstAddressOfList;
    while (current->out != NULL && current->out->ogrenciNo != ogrenciNo) {
        current = current->out;
    }

    if (current->out == NULL) {
        printf("\nNode with ogrenciNo: %d not found.\n", ogrenciNo);
        return firstAddressOfList;
    }
    
    struct Ogrenci* temp = current->out;
    current->out = temp->out; //current->out changed to current->out->out (skipped one node)

    printf("\nNo: %d, %s %s is deleted\n", temp->ogrenciNo, temp->ad, temp->soyAd);
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
    printf("\nOgrenci not found\n");
    return firstAddressOfList;
}
void displayLinkedList(struct Ogrenci* firstAddressOfList) {

    while (firstAddressOfList != NULL && firstAddressOfList->in != NULL) {
        firstAddressOfList = firstAddressOfList->in;
    }

    while (firstAddressOfList != NULL) {
        printf("\nogrenciNo: %d, Ad: %s, Soyad: %s, Bolum: %s, Sinif: %d\n",
               firstAddressOfList->ogrenciNo, firstAddressOfList->ad, firstAddressOfList->soyAd, firstAddressOfList->bolum, firstAddressOfList->sinif);

        firstAddressOfList = firstAddressOfList->out;
    }
}


//return int because I dont want to get a compile warning
int main() {
    int ogrenciNo[] = {1, 2, 3};
    char *ad[] = {"Ali", "veli", "deli"};
    char *soyAd[] = {"Yilmaz", "yilar", "yildi"};
    char *bolum[] = {"Bilgisayar Muhendisligi", "bm", "qcte"};
    int sinif[] = {2, 1, 3};

    struct Ogrenci *head = createDoublyLinkedList(3, ogrenciNo, ad, soyAd, bolum, sinif);

    int choice;
    int index;
    int newOgrenciNo;
    char newAd[100];
    char newSoyAd[100];
    char newBolum[100];
    int newSinif;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Node\n");
        printf("2. Search Node\n");
        printf("3. Delete Node\n");
        printf("4. Display Linked List\n");
        printf("5. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter index to add: ");
                scanf("%d", &index);
                printf("Enter new data:\n");
                printf("Ogrenci No: ");
                scanf("%d", &newOgrenciNo);
                printf("Ad: ");
                scanf("%s", newAd);
                printf("Soyad: ");
                scanf("%s", newSoyAd);
                printf("Bolum: ");
                scanf("%s", newBolum);
                printf("Sinif: ");
                scanf("%d", &newSinif);
                head = addNode(index, head, newOgrenciNo, newAd, newSoyAd, newBolum, newSinif);
                break;
            case 2:
                printf("Enter Ogrenci No to search: ");
                scanf("%d", &newOgrenciNo);
                struct Ogrenci *searchedNode = searchNode(newOgrenciNo, head);
                if (searchedNode != NULL) {
                    printf("\nFound Node: %d %s %s %s %d\n", searchedNode->ogrenciNo, searchedNode->ad, searchedNode->soyAd, searchedNode->bolum, searchedNode->sinif);
                } else {
                    printf("\nNode not found.\n");
                }
                break;
            case 3:
                printf("Enter Ogrenci No to delete: ");
                scanf("%d", &newOgrenciNo);
                head = deleteNode(newOgrenciNo, head);
                break;
            case 4:
                displayLinkedList(head);
                break;
            case 5:
                destroyLinkedList(head);
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}





