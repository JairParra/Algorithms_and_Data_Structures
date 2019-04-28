/**
 * @author: Hair Albeiro Parra Barrera
 * The following program implements a doubly-linked list data structure in C, 
 * including various functions such as creation, insertions, deletions, 
 * and an extremely basic sorting function. 
 * CAUTION: The sorting algorithm employed is the infamous Bubble Sort. 
 * It is strongly recommended that this algorithm is replaced by a more 
 * efficient one. Merge sort or quick sort are suggested. 
 * */

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 

//***Structures***

typedef struct Node {
    int data; 
    struct Node* next; // have to define the type inside the structure
    struct Node* prev; 
    bool exists; 
} Node; 

//***other functions***

//Creates a new Node and returns pointer to it. 
Node* makeNode(int x) {
	Node* newNode = (struct Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
    newNode->exists = true; 
	return newNode;
}

// dummy nodes don't exist
Node* makeDummyNode() { 
    Node* dummyNode = (struct Node*)malloc(sizeof(Node)); 
    dummyNode->data = NULL; // it will always remain null 
    dummyNode->prev = NULL; 
    dummyNode->next = NULL; 
    dummyNode->exists = false; 
    return dummyNode;  
}

// inserts data at the head of the list
void InsertAtHead(Node *head, int x) {
    Node* temp = head; 
	Node* newNode = makeNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
    temp->prev = newNode; 
    newNode->prev = temp; 
}

// inserts an element at the tail of the LinkedList
void InsertAtTail(Node *head, int x) {
	Node* temp = head;
	Node* newNode = makeNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
    else if(head->next == NULL && head->data ==NULL) { 
        head->data =x ; 
        return; 
    }
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

//delete first item
Node* deleteFirst(Node* head) { 

    // printf("Deleting first node..."); 
    // change pointers and free memory 
    if(head->next==NULL){  
        printf("Lonely node deleted\n"); 
        // head ->data = NULL; 
        // Node* dummy = makeDummyNode(); 
        // dummy->exists = false; 
        // dummy = NULL; 
        // Node* prevHead = head; 
        // head = dummy; 
        // prevHead = NULL; 
        // free(prevHead); 
        head = NULL; 
        free(head);
        return makeDummyNode(); 
    }

    // printf("First node: %d\n",head->data); 
    // printf("Second node: %d\n",head->next->data); 
    *head = *head->next; 

   return head; 
}

// swaps data of two nodes 
void swap(Node *a, Node *b) { 
    int temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}


//***assignment functions***

Node* create_dll_from_array(int array[], int size) { 
    printf("***Creating list from array...***\n");
    Node *dll_head = makeNode(array[0]);  // assign the first element and save the reference
    Node *curr = dll_head; // start from head
    // printf("head element: %d\n",dll_head->data); 
    for(int i = 1; i <size; i++) { 
        Node* newNode = makeNode(array[i]); // make a node to append with the element
        curr->next = newNode; 
        newNode->prev = curr; 
        curr = curr->next; // move to the next node 
    }
    return dll_head; 
} 

// Function that loops over all the elmeents and prints their values 
// to the screen 
void print_dll(Node* head) { 

    printf("***PRINT CALLED:***\n"); 
    // printf("head->data = %d\n", head->data); 
    // printf("head->exists = %d\n",head->exists); 

    if(head->exists == false) {  
        printf("Doesn't exist. List is empty\n"); 
        return; 
    }
    else if(head == NULL ){ 
        printf("Head is null. List is empty\n"); 
        return; 
    }
    else if(head->data == NULL) { 
        printf("Head data is empty. List is empty\n"); 
        return; 
    }

    Node *curr = head; // change the pointer's reference
    // head = malloc(sizeof(head)); 
    while(curr != NULL) { 
        printf("%d <-> ",curr->data);
	    curr = curr->next; 
    }
    printf("\n"); 
}

// Inserts a new element in the linked list after the first occurrence 
// of the value provided by the second argument and having the value 
// provided in the third argument

void insert_after(struct Node* head, int valueToInsertAfter, int valueToBeInserted) { 
    printf("**Inserting %d after %d***\n", valueToBeInserted, valueToInsertAfter); 
    struct Node* newNode = makeNode(valueToBeInserted); 
    struct Node* curr = head; // start at head

	if(head == NULL) { //  TODO: FIX
		head = newNode; 
		return; 
	}

    while(curr != NULL) { // go through all the nodes 
		// printf("curr data: %d\n", curr->data); 
		// node not found, append to the end of the list
		if(curr->next == NULL) {
			curr->next = newNode; 
			newNode->prev = curr; 
			return; 
		}
		// else if value matches
        else if(curr->data == valueToInsertAfter) { 
            struct Node* currNext = curr->next; // save reference to curr next
            curr->next = newNode; 
            newNode->prev = curr; 
            newNode->next = currNext; 
            currNext->prev = newNode; 
            return; 
        }
		curr = curr->next; // advanced the pointer
    }

}

// deletes an element from the linked list
void delete_element(Node* head, int valueToBeDeleted) { 
    printf("---Deleting %d---\n", valueToBeDeleted); 
    Node* curr = head; // start at head   
    if(head->data == valueToBeDeleted || head->next == NULL) { 
        deleteFirst(head); 
        return; 
    }

    while( curr != NULL) { 
        // if data matches
        printf("curr->data %d\n", curr->data ); 
        if(curr->data == valueToBeDeleted) { 
            if(curr-> next == NULL) { // if it's the last node
                curr->prev->next = NULL; 
                curr->prev = NULL; 
                free(curr); 
                return ; // last node delted 
            }
            else { 
                curr->prev->next = curr->next; 
                curr->next->prev = curr->prev; 
                free(curr); // free memory of curr
                return; 
            }
        }
		curr = curr->next; // advance the pointer 
    }
}

// Use Bubble Sort to sort the array with pointers
void sort_dll(Node* head){ 
    printf("***SORT CALLED***\n"); 
    int swapped, i; 
    Node *ptr1; 
    Node *wall = NULL; // left pointer

    // Check if the list is empty
    if(head == NULL || head->data == NULL) { 
        return; // nothing to sort
    }
    
    do { 
        swapped = 0; // FALSE
        ptr1 = head; 
        while(ptr1->next != wall) { 
            if(ptr1->data > ptr1->next->data) {
                swap(ptr1, ptr1->next); 
                swapped = 1; // TRUE
            }
            ptr1 = ptr1->next; 
        }
        wall = ptr1; 
    }while(swapped); 
}

// deletes the linked list and frees memeory allocated to all nodes 
// this will also free the memory in the process and prevent memory leaks
void delete_dll(Node* head) { 
    printf("--DELETE DLL CALLED:-- \n"); 
    printf("attempting to delete\n"); 
    printf("head->next = %d\n",head->next->data); 
    if(head->next == NULL) {
        head = deleteFirst(head); 
        head->data = NULL; 
        printf("SUCCESSFUL\n"); 
        return; 
    }
    else { 
        Node *curr = head; 
        Node *next; 
        while(curr != NULL) { 
            // printf("curr->prev->data %d\n", curr->prev->data ); 
            printf("curr->data %d\n", curr->data ); 
            // printf("curr->next->data %d\n", curr->next->data ); 
            next = curr->next; 
            curr->data = NULL; 
            curr->prev = NULL; 
            curr->next = NULL; 
            free(curr); 
            curr = next; 
        } 
        head = makeDummyNode(); // otherwise this will go forever
    }

}

void free_dll(Node* head) { 
    if(head == NULL) { 
        return ; 
    }

    Node* temp; 

    while( head != NULL) { 
        temp = head; 
        head = head->next; 
        free(temp); 
    }
}

//***main***

int main(void) { 

    // Tester 
    // Note that we need to maintain a pointer to the head so that 
    // we can go through the linked list as many times as needed.
    int array [ 5 ] = { 11 , 2 , 7 , 22 , 4 };
    Node* head;
    // Create an a doubly linked list from an array
    head = create_dll_from_array( array , 5 ); //size of array is 5

    // Print the linked list 
    print_dll(head);

    // To insert 13 after the first occurence of 7
    insert_after(head, 7 , 13 );
    // To insert 29 after the first occurence of 21
    insert_after(head, 21 , 29 );
    print_dll(head);

    // Delete an element from the DLL
    delete_element(head, 22 );
    print_dll(head);
    delete_element(head, 11 );
    print_dll(head);

    // Sort the list 
    sort_dll(head); 
    print_dll(head);

    // Delete the DLL
    // add the call to your function here
    delete_dll(head); // deletes the dll 
    // free_dll(head); 
    print_dll(head); // list is now empty
    // proof
    printf("Head prev : %d\n", head->prev); 
    printf("Head data : %d\n", head->data); 
    printf("Head next : %d\n", head->next); 

    return 0; 
}
