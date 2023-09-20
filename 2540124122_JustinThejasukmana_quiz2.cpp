#include <iostream>
#include <string.h>

using namespace std;

int count = 0;

struct node{

    int height;

    char name[20];
    char owner[20];
    char street[20];
    char type[10];

    char id[8];

    struct node *left, *right;

} *root;

struct node *createNode(char name[], char owner[], char street[], char type[], int idNum){

    struct node *newNode = (node*)malloc(sizeof(node));

    newNode->height = 1;

    strcpy(newNode->name, name);
    strcpy(newNode->owner, owner);
    strcpy(newNode->street, street);
    strcpy(newNode->type, type);
    
    sprintf(newNode->id, "ST%03d", idNum);

    newNode->left = newNode->right = NULL;

    return newNode;

}

int max(int a, int b){

    return(a > b) ? a : b;

}

int getHeight(struct node *node){

    if(!node)
        return 0;
    
    return node->height;

}

int balanceFact(struct node *node){

    if(!node)
        return 0;
    
    return getHeight(node->left) - getHeight(node->right);

}

void updateHeight(struct node *node){

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

}

struct node *leftRotate(struct node *node){

    struct node *child = node->right;
    struct node *childLeft = child->left;

    child->left = node;
    node->right = childLeft;

    updateHeight(node);
    updateHeight(child);

    return child;

}

struct node *rightRotate(struct node *node){

    struct node *child = node->left;
    struct node *childRight = child->right;

    child->right = node;
    node->left = childRight;

    updateHeight(node);
    updateHeight(child);

    return child;

}

struct node *balance(struct node *node){

    if(!node)
        return 0;
    
    updateHeight(node);
    int bf = balanceFact(node);

    // L
    if(bf > 1){
        // LR
        if(balanceFact(node->left) < 0)
            node->left = leftRotate(node->left);
        // LL
        return rightRotate(node);

    }
    // R
    else if(bf < -1){
        // RL
        if(balanceFact(node->right) > 0)
            node->right = rightRotate(node->right);

        return leftRotate(node);

    }

    return(node);

}

struct node *insertNode(struct node *root, struct node *newNode){

    if(!root)
        return newNode;
    
    else if(strcmp(newNode->id, root->id) < 0)
        root->left = insertNode(root->left, newNode);
    
    else
        root->right = insertNode(root->right, newNode);

    return balance(root);

}

bool checkOwner(char owner[]){

    char mr[5] = "Mr. ";
    char mrs[8] = "Mrs. ";
    
    if((owner[0] == mr[0]) && (owner[1] == mr[1]) && (owner[2] == mr[2]) && (owner[3] == mr[3]))
        return true;
    
    else if((owner[0] == mrs[0]) && (owner[1] == mrs[1]) && (owner[2] == mrs[2]) && (owner[3] == mrs[3]) && (owner[4] == mrs[4]) && (owner[5] == mrs[5]))
        return true;

    return false;

}

// bool checkStore(char street[]){

//     char street[10] = "Street";

//     if()

// }

void insertMenu(){

    char name[20];
    char owner[20];
    char street[20];
    char type[10];

    int idNum;

    printf("Input store name: ");
    scanf("%s", &name); getchar();

    while(strlen(name) < 5){

        printf("Store name length must be at least 5\n");
        printf("Input store name: ");
        scanf("%s", &name); getchar();

    }

    printf("Input store owner name: ['Mr. ' or 'Mrs. ']: ");
    scanf("%s", &owner); getchar();

    while(!checkOwner(owner) == false){

        printf("Owner name must either start with ['Mr. ' or 'Mrs. ]'\n");
        printf("Input store owner name: ['Mr. ' or 'Mrs. ']: ");
        scanf("%s", &owner); getchar();

    }

    printf("Input store location: [must end with ' Street' (case sensitive)]");
    scanf("%s", &street); getchar();

    // while(checkStore(street) == false){

    //     printf("Store location must end with ' Street'\n");
    //     printf("Input store location: [must end with ' Street' (case sensitive)]");
    //     scanf("%s", &street); getchar();

    // }

    printf("Input store type ['Daily Needs' | 'Clothing' | 'F&B' | 'Electronics' | 'Kitchenware']: ");
    scanf("%[^\n]", &type); getchar();
    
    while(strcmp(type, "Daily Needs") != 0 && strcmp(type, "Clothing") != 0 && strcmp(type, "F&B") != 0 && strcmp(type, "Electronics") != 0 && strcmp(type, "Kitchenware")){

        puts("Store type must be between ['Daily Needs' | 'Clothing' | 'F&B' | 'Electronics' | 'Kitchenware'] !");
        printf("Input store type ['Daily Needs' | 'Clothing' | 'F&B' | 'Electronics' | 'Kitchenware']: ");
        scanf("%[^\n]", &type); getchar();

    }

    count++;
    idNum = count;
    root = insertNode(root, createNode(name, owner, street, type, idNum));
    balance(root);
    printf("Successfully inserted asdfasdf with ID [ST%03d]\n", idNum);
    puts("Press enter to continue...");
    getchar();

}

void preOrder(struct node *root){

    if(root){

        printf("%s - %s - %s - %s - %s\n", root->id, root->name, root->owner, root->street, root->type);
        preOrder(root->left);
        preOrder(root->right);

    }

}

void inOrder(struct node *root){

    if(root){

        preOrder(root->left);
        printf("%s - %s - %s - %s - %s\n", root->id, root->name, root->owner, root->street, root->type);
        preOrder(root->right);

    }

}

void postOrder(struct node *root){

    if(root){

        preOrder(root->left);
        preOrder(root->right);
        printf("%s - %s - %s - %s - %s\n", root->id, root->name, root->owner, root->street, root->type);

    }

}

void viewMenu(){

    int choice;

    do{

        puts("view menu");
        puts("1. preOrder");
        puts("2. inOrder");
        puts("3. postOrder");

        printf("choice >> ");
        scanf("%d", &choice); getchar();

    }while(choice > 3);

    switch(choice){

        case 1:
            preOrder(root);
            break;
        
        case 2:
            inOrder(root);
            break;
        
        case 3:
            postOrder(root);
            break;

        default:
            viewMenu();

    }

}

struct node *removeNode(struct node *node, char id[]){

    if(!node){

        printf("id not found");
        // goto label: menu;
        return 0;

    }
    else if(strcmp(id, node->id) < 0)
        node->left = removeNode(node->left, id);
    
    else if(strcmp(id, node->id) > 0)
        node->right = removeNode(node->right, id);
    
    else{

        // no anak
        if(!node->left && !node->right){

            free(node);
            node = NULL;

        }
        // 1 anak
        else if(!node->left || !node->right){

            struct node *child = (node->left) ? node->left : node->right;

            free(node);
            node = child;

        }
        // 2 anak
        else{

            struct node *pre = node->left;

            while(pre->right)
                pre = pre->right;

            strcpy(node->name, pre->name);
            strcpy(node->owner, pre->owner);
            strcpy(node->street, pre->street);
            strcpy(node->type, pre->type);

            node->left = removeNode(node->left, id);

        }

    }

    count--;

    return balance(node);

}

bool search(struct node *root, char id[]){

    if(!root)
        return false;
    
    else if(strcmp(id, root->id) < 0)
        search(root->left, id);
    
    else
        search(root->right, id);

    return true;

}

void deleteMenu(){

    char choice[8];

    if(count == 0)
        printf("No store yet...\n");
    
    else{

        inOrder(root);
        printf("Input store id: ");
        scanf("%s", &choice); getchar();

        if(search(root, choice) == false){

            printf("ID NOT FOUND\n");
            return;

        }

        root = removeNode(root, choice);

        puts("Successfully deleted");
        puts("Press enter to continue...");
        getchar();

    }

}

void deleteAll(){

    if(count == 0)
        printf("No store yet...\n");

    char choice[5];

    do{

        puts("All stores data will be deleted");
        printf("Would you like to proceed [Yes | No]: ");
        scanf("%s", &choice); getchar();

    }while(strcmp(choice, "Yes") != 0 && strcmp(choice, "No") != 0);

    while(root)
        root = removeNode(root, root->id);
    
    puts("Successfully deleted");
    puts("Press enter to continue...");
    getchar(); 

}

void menu(){

    // label: menu;

    int choice;

    do{

        puts("<        Amasun       >");
        puts("<=====================>");
        puts("1. View all stores");
        puts("2. Insert new store");
        puts("3. Delete a store");
        puts("4. Delete all stores");
        puts("5. Exit");

        printf("Choose >> ");
        scanf("%d", &choice); getchar();

    }while(choice > 5);

    switch(choice){

        case 1:
            viewMenu();
            break;
        
        case 2:
            insertMenu();
            break;
        
        case 3:
            deleteMenu();
            break;
        
        case 4:
            deleteAll();
            break;
        
        case 5:
            return;

    }

    menu();

}

int main(){

    root = NULL;

    system("cls");

    menu();


    return 0;
}