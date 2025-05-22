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

void add_data(Node** head,char It_name[],float Quantity,char Unit[],float Rate){
    Node*temp=(Node*)malloc(sizeof(Node));
    strcpy(temp->Item_Name,It_name);
    temp->Quantity=Quantity;
    strcpy(temp->Unit,Unit);
    temp->Rate=Rate;
    temp->Amount=Quantity*Rate;
    temp->link=*head;
    *head=temp;
}

void delete_data(Node**head,char It_name[]){
    if(*head==NULL){
        printf("Item List is already Empty\n");
        return;
    }
    if(strcmp((*head)->Item_Name,It_name)==0){
        Node*ptr=*head;
        *head=(*head)->link;
        free(ptr);
        printf("Item deleted successfully from list\n");
        return;
    }
    Node*temp=(*head);
    while (temp->link!=NULL){
        if(strcmp(temp->link->Item_Name,It_name)==0){
            Node*ptr=temp->link;
            temp->link=temp->link->link;
            free(ptr);
            printf("Item deleted successfully from list\n");
            return;
        }
        temp=temp->link;
    }
    printf("Item not found in the list.\n");
}

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

int item_exists(Node* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->Item_Name, name) == 0)
            return 1;
        head = head->link;
    }
    return 0;
}


void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

int main(){
    Node* head=NULL;

    int check;
    do
    {
        printf("\n******MENU******\n");
        printf("1.For add item\n");
        printf("2.For delete item\n");
        printf("3.For print list of items\n");
        printf("Any other key to Exit\n");
        printf("\nEnter choice: ");
        scanf("%d",&check);

        if(check==1){
            printf("\n**Enter Item details\n\n");
            char It_name[100];
            printf("Enter item name: ");
            scanf(" %[^\n]",It_name);
            float Quantity,Rate;
            printf("Enter QUANTITY of item: ");
            scanf("%f",&Quantity);
            char Unit[10];
            printf("Enter UNITs of item: ");
            scanf(" %[^\n]",Unit);
            printf("Enter RATE of item: RS ");
            scanf("%f",&Rate);
            if(Quantity<0 || Rate<0){
                printf("Erorr in Input\n");
                printf("Try again\n\n");
            }
            else{
                if (item_exists(head, It_name)) {
                printf("Item already exists.\nUse a different name or delete the existing one.\n");
                } else {
                add_data(&head,It_name,Quantity,Unit,Rate);
                printf("\nData added successfully\n");
                printf("-----------------------------------\n");
                }
            }           
        }
        else{
            if(check==2){
                char It_name[100];
                printf("Enter name of item to delete: ");
                scanf(" %[^\n]",It_name);
                delete_data(&head,It_name);
            }
            else{
                if(check==3){
                    print(head);

                }
                else{
                    printf("Exiting.....");
                    free_list(head);
                    exit(0);
                }
            }
        }
    } while (check!=4);
    return 0;
}