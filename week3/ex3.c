// BS19-02 Alukaev Danis
// Task 3.

#include <stdio.h>


/**
 * Structure Node.
 * Represents a node in a linked list of integers.
 */
typedef struct Node{
    int data;
    struct Node *next;
}Node_t;

/**
 * Prints linked list of integers.
 *
 * @param head - the starting node in linked list.
 * @param length - the length of a single linked list.
 */
void print_list(Node_t* head, int* length) {
    Node_t* current_node=head;
    if(*length==0)
        printf("NULL\n");
    else{
        while(current_node!=NULL){
            printf("%d -> ",current_node->data);
            current_node=current_node->next;
        }
        if(current_node==NULL)
            printf("NULL\n");
    }
}

/**
 * Inserts an element with an index <index> and data <value>.
 *
 * @param head - the starting node in linked list.
 * @param length - the length of a single linked list.
 * @param index - index of new node.
 * @param value - value of new node.
 * @return head - new starting node in linked list.
 */
Node_t* insert_node(Node_t* head, int* length, int index, int value) {
    Node_t* temp_node=(Node_t*)malloc(sizeof(Node_t));
    if(index== 0){
        temp_node->data=head->data;
        temp_node->next=head->next;
        head->data=value;
        head->next=temp_node;
        (*length)++;
        return head;
    }
    Node_t* current_node=head;
    for (int i=0; i<index-1; i++) {
        if(current_node->next==NULL)
            return head;
        current_node=current_node->next;
    }
    Node_t* left=current_node;
    Node_t* right=current_node->next;
    temp_node->next=right;
    temp_node->data=value;
    left->next=temp_node;
    (*length)++;
    return head;
}

/**
 * Removes an element with an index <index>.
 *
 * @param head - the starting node in linked list.
 * @param length - the length of a single linked list.
 * @param index - index of node to be removed.
 * @return head - new starting node in linked list.
 */
Node_t* delete_node(Node_t* head, int* length, int index) {
    if(index==0) {
        if (head==NULL)
            return head;
        if (head->next==NULL){
            head=NULL;
            (*length)--;
            return head;
        }
        Node_t* head_next=NULL;
        head_next=head->next;
        head->data=head->next->data;
        head->next=head->next->next;
        free(head_next);
        (*length)--;
        return head;
    }
    Node_t* current_node=head;
    Node_t* temp_node=NULL;
    for(int i=0; i<index-1; i++) {
        if(current_node->next==NULL)
            return head;
        current_node=current_node->next;
    }
    temp_node=current_node->next;
    current_node->next=current_node->next->next;
    free(temp_node);
    (*length)--;
    return head;
}

/**
 * Structure SingleLinkedList.
 * Represents a single linked list of integers.
 */
typedef struct SingleLinkedList{
    Node_t* head;
    int length;
}SingleLinkedList_t;

int main(){
    // create single linked list
    SingleLinkedList_t sll;
    sll.head=malloc(sizeof(Node_t));
    sll.head->data=1;
    sll.head->next=NULL;
    sll.length=1;
    // insert 2,3,4,0
    insert_node(sll.head,&sll.length,1,2);
    insert_node(sll.head,&sll.length,2,3);
    insert_node(sll.head,&sll.length,3,4);
    insert_node(sll.head,&sll.length,0,0);
    // output preliminary list
    print_list(sll.head,&sll.length);
    // remove elements with indexes 1,2,3,0
    delete_node(sll.head,&sll.length,1);
    delete_node(sll.head,&sll.length,2);
    delete_node(sll.head,&sll.length,2);
    delete_node(sll.head,&sll.length,0);
    // output resultant list
    print_list(sll.head,&sll.length);
    // remove last element in list
    delete_node(sll.head,&sll.length,0);
    // output empty list
    print_list(sll.head,&sll.length);
}
