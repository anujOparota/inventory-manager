#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
    char Item_Name[100];
    float Quantity;
    char Unit[10];
    float Rate;            
    float Amount;
    struct Node* link;
}Node;

//To add new item detail in list
int add_data(Node** head,char It_name[],float Quantity,char Unit[],float Rate){
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        return 0;
    }
    strcpy(temp->Item_Name,It_name);
    temp->Quantity=Quantity;
    strcpy(temp->Unit,Unit);
    temp->Rate=Rate;
    temp->Amount=Quantity*Rate;
    temp->link=*head;
    *head=temp;
    return 1;
}

//To delete a existing item from list
int delete_data(Node**head,char It_name[]){
    if(*head==NULL){
        return 0;
    }
    if(strcmp((*head)->Item_Name,It_name)==0){
        Node*ptr=*head;
        *head=(*head)->link;
        free(ptr);
        return 1;
    }
    Node*temp=(*head);
    while (temp->link!=NULL){
        if(strcmp(temp->link->Item_Name,It_name)==0){
            Node*ptr=temp->link;
            temp->link=temp->link->link;
            free(ptr);
            return 1;
        }
        temp=temp->link;
    }
    return 0;
}

// To print item list 
void print(Node*head){
    if (head==NULL){
        printf("Item list empty\n");
        return;
    }
    Node*temp=head;
    while (temp!=NULL){
        printf("\n*****ITEM DETAIL*****\n\n");
        printf("Item Name     : %s\n",temp->Item_Name);
        printf("Item Quantity : %.3f\n",temp->Quantity);
        printf("Item Unit     : %s\n",temp->Unit);
        printf("Item Rate     : Rs %.2f\n",temp->Rate);
        printf("Item Amount   : Rs %.2f\n",temp->Amount);
        printf("----------------------------------\n");
        temp=temp->link;
    }
    
}

// To check for existing item
int item_exists(Node* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->Item_Name, name) == 0)
            return 1;
        head = head->link;
    }
    return 0;
}

//To search and print existing item
void search_nameIn_list(Node*head,char search_name[]){
    if(head==NULL){
        printf("List is Empty\n");
        return;
    }
    else{
        Node*temp=head;
        while(temp!=NULL){
            if(strcmp(temp->Item_Name,search_name)==0){
                printf("\n*****ITEM DETAIL*****\n\n");
                printf("Item Name     : %s\n",temp->Item_Name);
                printf("Item Quantity : %.3f\n",temp->Quantity);
                printf("Item Unit     : %s\n",temp->Unit);
                printf("Item Rate     : Rs %.2f\n",temp->Rate);
                printf("Item Amount   : Rs %.2f\n",temp->Amount);
                printf("----------------------------------\n");
                return;
            }
            temp=temp->link;
        }
        printf("Item not found.\nCheck name and try again.\n");
    }
}

int update_item(Node* head, char name[], float newQty, float newRate) {
    Node* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->Item_Name, name) == 0) {
            temp->Quantity = newQty;
            temp->Rate = newRate;
            temp->Amount = newQty * newRate;
            return 1;
        }
        temp = temp->link;
    }
    return 0;
}

//To calculat total amount of all item
float check_amount(Node*head){
    if(head==NULL)
    return -1;
    Node*temp=head;
    float Total_Amount=0;
    while(temp!=NULL){
        Total_Amount += temp->Amount;
        temp=temp->link;
    }
    return Total_Amount;
}

//To free list
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

//save to file
void save_to_file(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    fprintf(fp, "Item_Name|Quantity|Unit|Rate|Amount\n");

    Node* temp = head;
    while (temp != NULL) {
        fprintf(fp, "%s|%.3f|%s|%.2f|%.2f\n",
                temp->Item_Name,
                temp->Quantity,
                temp->Unit,
                temp->Rate,
                temp->Amount);
        temp = temp->link;
    }

    fclose(fp);
}

//load from file
int load_from_file(Node** head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;
    }

    free_list(*head);
    *head = NULL;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char name[100], unit[10];
        float qty, rate;

        if (sscanf(line, "%99[^|]|%f|%9[^|]|%f",
                   name, &qty, unit, &rate) == 4) {
            add_data(head, name, qty, unit, rate);
        }
    }

    fclose(fp);
    return 1;
}

int main() {
    Node* head = NULL;
    int check;

    do {
        printf("\n******MENU******\n");
        printf("1. For add item\n");
        printf("2. For delete item\n");
        printf("3. For print list of items\n");
        printf("4. For other options\n");
        printf("5. For update item\n");
        printf("6. Load data from file\n");
        printf("7. Save data to file\n");
        printf("Any other numeric key to Exit\n");
        printf("\nEnter choice: ");
        scanf("%d", &check);
        getchar();

        switch (check) {

        case 1: {   // ADD ITEM
            printf("\n**Enter Item details\n\n");

            char It_name[100];
            printf("Enter item name: ");
            fgets(It_name, sizeof(It_name), stdin);
            It_name[strcspn(It_name, "\n")] = '\0';

            float Quantity, Rate;
            printf("Enter QUANTITY of item: ");
            scanf("%f", &Quantity);
            getchar();

            char Unit[10];
            printf("Enter UNITs of item: ");
            fgets(Unit, sizeof(Unit), stdin);
            Unit[strcspn(Unit, "\n")] = '\0';

            printf("Enter RATE of item: RS ");
            scanf("%f", &Rate);
            getchar();

            if (Quantity < 0 || Rate < 0) {
                printf("Error in input. Try again.\n");
            } else if (item_exists(head, It_name)) {
                printf("Item already exists.\nUse a different name or delete the existing one.\n");
            } else {
                if (add_data(&head, It_name, Quantity, Unit, Rate)) {
                    printf("Data added successfully.\n");
                } else {
                    printf("Memory allocation failed. Item not added.\n");
                }
            }
            break;
        }

        case 2: {   // DELETE ITEM
            char It_name[100];
            printf("Enter name of item to delete: ");
            fgets(It_name, sizeof(It_name), stdin);
            It_name[strcspn(It_name, "\n")] = '\0';

            if (delete_data(&head, It_name))
                printf("Item deleted successfully.\n");
            else
                printf("Item not found or list is empty.\n");
            break;
        }

        case 3: {   // PRINT LIST
            print(head);
            break;
        }

        case 4: {   // OTHER OPTIONS
            int t;
            printf("1. For print Total Amount of all item\n");
            printf("2. For search/check item by name\n");
            printf("Any other numeric key to exit\n");
            printf("\nEnter choice: ");
            scanf("%d", &t);
            getchar();

            if (t == 1) {
                float Total_Amount = check_amount(head);
                if (Total_Amount == -1)
                    printf("Item list is empty.\n");
                else
                    printf("The total amount of all items is Rs %.2f\n", Total_Amount);
            } 
            else if (t == 2) {
                char search_name[100];
                printf("Enter item you want to search: ");
                fgets(search_name, sizeof(search_name), stdin);
                search_name[strcspn(search_name, "\n")] = '\0';
                search_nameIn_list(head, search_name);
            }
            break;
        }

        case 5: {   // UPDATE ITEM
            char name[100];
            float newQty, newRate;

            printf("Enter item name to update: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter new quantity: ");
            scanf("%f", &newQty);
            getchar();

            printf("Enter new rate: ");
            scanf("%f", &newRate);
            getchar();

            if (newQty < 0 || newRate < 0) {
                printf("Invalid input. Quantity and rate must be non-negative.\n");
            } else if (update_item(head, name, newQty, newRate)) {
                printf("Item updated successfully.\n");
            } else {
                printf("Item not found.\n");
            }
            break;
        }

        case 6: {
            if (load_from_file(&head, "inventory-input.txt")) {
                printf("Data loaded successfully.\n");
            } else {
                printf("Error: Source file not found or unreadable.\n");
            }
            break;
        }

        case 7: {
            save_to_file(head, "inventory-output.txt");
            printf("Data saved successfully.\n");
            break;
        }

        default:    // EXIT
            printf("Exiting...\n");
            free_list(head);
            exit(0);
        }

    } while (1);

    return 0;
}