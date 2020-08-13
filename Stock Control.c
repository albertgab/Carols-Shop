#include <stdio.h>
#include <stdlib.h>

char file_name[150];  //store address of file
FILE *file;
int i = 0, total = 0;
char ch;
int done;  //marks when some operation was already done

//structure of every node in linked list
typedef struct node {
    char name[80];
    char unit_of_sale[12];
    int current_stock;
    int reorder_level;
    int item_price;
    struct node *next;
} node;
//head of the linked list
node *our_stock = NULL;


//the function is used in loadStock to check which product should be first in alphabetic order
//returns number of word which is first
int firstInAlphabet(const char *first, const char *second) {
    i = 0;
    do {
        if (first[i] < second[i]) {
            return 1;
        } else if (first[i] > second[i]) {
            return 2;
        } else {          //if letters are the same, next letter will be checked
            i++;
        }
    } while (&free);
}

//loads stock from a file
void loadStock() {

    //file = fopen(file_name, "r");
    ch = fgetc(file);
    while (ch != EOF) {
        //allocate space for new node of linked list
        node *n = malloc(sizeof(node));
        //add new item
        i = 0;
        //storing name
        while (ch != ',') {
            n->name[i] = ch;
            i++;
            ch = fgetc(file);
        }
        //put 0 at the end of a name in case to correctly printing this
        n->name[i] = 0;
        ch = fgetc(file);
        i = 0;
        //storing unit of sale
        while (ch != ',') {
            n->unit_of_sale[i] = ch;
            i++;
            ch = fgetc(file);
        }
        //put 0 at the end same as above
        n->unit_of_sale[i] = 0;
        ch = fgetc(file);
        n->current_stock = 0;
        while (ch != ',') {
            //storing current stock number after number
            n->current_stock = n->current_stock * 10 + ch - '0';
            ch = fgetc(file);
        }
        ch = fgetc(file);
        n->reorder_level = 0;
        while (ch != ',') {
            n->reorder_level = n->reorder_level * 10 + ch - '0';
            ch = fgetc(file);
        }
        ch = fgetc(file);
        n->item_price = 0;
        while (ch != '\n' && ch != EOF) {
            //storing price of item
            n->item_price = n->item_price * 10 + ch - '0';
            ch = fgetc(file);
        }
        n->next = NULL;
        done = 0;
        //check if linked list already exist
        if (our_stock) {
            //going through the list
            for (node *ptr = our_stock; !done; ptr = ptr->next) {
                //when last element wil be reached actual node is placed before or after last element in alphabetic order
                if (ptr->next == NULL) {
                    //checking alphabetic order
                    if (firstInAlphabet(n->name, ptr->name) == 2) {
                        ptr->next = n;
                        done = 1;
                    } else {                 //this else case could happen only if there is exactly one node in the linked list,
                        n->next = ptr;
                        our_stock = n;      //that is why this line will never overwrite any meaningful data
                        done = 1;
                    }
                } else {
                    //when next element from the pointer is higher in alphabetic order, actual node is placed before or after last element
                    if (firstInAlphabet(n->name, ptr->next->name) == 1) {
                        //if is greater than pointer, node goes after pointer
                        if (firstInAlphabet(n->name, ptr->name) == 2) {
                            n->next = ptr->next;
                            ptr->next = n;
                            done = 1;
                            //if smaller goes before
                        } else {
                            n->next = ptr;
                            our_stock = n;
                            done = 1;
                        }
                    }
                }
            }
        } else {
            //creating new list
            our_stock = n;
        }
        ch = fgetc(file);
    }
    //close the file after loading
    fclose(file);
}

//this function prints all linked list
void printStock(node *head_of_list) {
    //prints an element of list
    printf("%s   %s\n%d\t%d\t%d\t", head_of_list->name, head_of_list->unit_of_sale,
           head_of_list->current_stock, head_of_list->reorder_level, head_of_list->item_price);
    //check if re-order is needed
    if (head_of_list->current_stock <= head_of_list->reorder_level) {
        printf("Should be re-ordered\n\n");
    } else {
        printf("Doesn't have to be re-ordered\n\n");
    }
    //recursively print next element of list
    if (head_of_list->next != NULL) {
        printStock(head_of_list->next);
    }
}

//this function allow us to buy items from the shop
int shopping(node *head_of_list) {
    do {
        //ask user for quantity
        printf("How many %s would you like to buy?\n", head_of_list->name);
        scanf("%d", &i);
        //if there are not enough items program let us know
        if (i > head_of_list->current_stock) {
            printf("Not enough products, you can buy up to %d products.\n", head_of_list->current_stock);
        }
    } while (i > head_of_list->current_stock);
    //update stock
    head_of_list->current_stock = head_of_list->current_stock - i;
    //recursively adding price from every item and returns total
    if (head_of_list->next != NULL) {
        return i * head_of_list->item_price + shopping(head_of_list->next);
    } else {
        return i * head_of_list->item_price;
    }
}
//this function save all changes in file chosen before (main function)
void saveStock(node *head_of_list) {
    fprintf(file, "%s,%s,%d,%d,%d", head_of_list->name, head_of_list->unit_of_sale,
            head_of_list->current_stock, head_of_list->reorder_level, head_of_list->item_price);
    //recursively save all elements
    if (head_of_list->next != NULL) {
        fprintf(file, "\n");
        saveStock(head_of_list->next);
    }
}

int main() {
    //endless loop, which ends only when we tape "q" or "Q"
    while (&free) {
        printf("What do you want to do?\n1. Load data\n2. Print out summary of all the stock\n"
               "3. Go shopping\n4. Save data\nQ. Quit\n");
        do {
            scanf("%c", &ch);
        } while (ch == '\n');
        switch (ch) {
            case '1':
                //ask for file to load stock
                printf("Tape input file path:\n");
                scanf("%s", file_name);
                file = fopen(file_name, "r");
                //check for errors
                if (file == NULL) {
                    perror("Error while opening the file.\n");
                    exit(EXIT_FAILURE);
                }
                loadStock();
                break;
            case '2':
                printStock(our_stock);
                break;
            case '3':
                total = shopping(our_stock);
                printf("You spent %d pounds and %d pence\n", total / 100, total % 100);
                break;
            case '4':
                //ask for file to save changes
                printf("Tape input file path:\n");
                scanf("%s", file_name);
                file = fopen(file_name, "w");
                //check for errors
                if (file == NULL) {
                    perror("Error while opening the file.\n");
                    exit(EXIT_FAILURE);
                }
                saveStock(our_stock);
                //close after saving
                fclose(file);
                break;
                //quit
            case 'q':
            case 'Q':
                return (0);
            default:
                printf("Invalid character entered\n");
        }
    }
}
