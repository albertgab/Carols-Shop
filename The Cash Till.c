#include <stdio.h>
#include <stdlib.h>

char file_name [150]="D:\\OneDrive - Aberystwyth University\\Projects\\Bio//RUG786.fa"; //store address of file
FILE *file;
int i=0, empty, cash[11], //save how many which denominations are in the till
owed, offered, amount_change, change[11]; //save how many which denominations are in the change
const  int denomination[11] = {5000, 2000, 1000, 500, 100, 50, 20, 10, 5, 2, 1};
char ch;

//loads till from a file





void loadData(){
    //ask for a file location
    printf("Tape input file path:\n");
    scanf("%s", file_name);
    //open file
    file = fopen(file_name, "r");
    //error checking
    if (file == NULL)
    {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
    }
//load cash
    for(i=0;i<11;i++) {
        ch = fgetc(file);
        //changing char in to int
        cash[i] = ch - '0';
        ch = fgetc(file);
        //if there are number after other number this loop merge these
        while (ch != ' ' && ch != EOF) {
            cash[i] = cash[i]*10 + ch - '0';
            ch = fgetc(file);
        }

    }
}
//computing how much is the change and what denominations should be given
void compute_change(int amount_owed, int amount_offered){

    amount_change = amount_offered-amount_owed;
    //change pence into pounds and pence
    printf("The change is %d pounds and %d pence\n",amount_change/100,amount_change%100);
    for(i=0;i<11;i++){
        //counting every denomination
        change[i] = amount_change/denomination[i];
        if(change[i] >= cash[i]){
            change[i] = cash[i];
        }
        //updating till
        cash[i] = cash[i] - change[i];
        //change left
        amount_change = amount_change-(change[i]*denomination[i]);
    }
    //printing how many of which denomination will be given
    printf("50 pounds notes: %d\n20 pounds notes: %d\n10 pounds notes: %d\n5 pounds notes: %d\n1 pounds coins: %d\n50 pence coins: %d\n20 pence coins: %d\n10 pence coins: %d\n"
           "5 pence coins: %d\n2 pence coins: %d\n1 pence coins: %d\n", change[0], change[1], change[2], change[3], change[4], change[5], change[6], change[7], change[8], change[9], change[10]);
    //if till is empty and some change left
    if(amount_change > 0){
        empty=1;
        for(i=0;i<11;i++){
            if(cash[i]!=0){
                empty=0;
                i=11;
            }
        }
        //giving a credit note
        if(empty==1){
            printf("Sorry, there is not enough money in the till!\nA credit note for %d pounds and %d pence will be issued.\n",amount_change/100,amount_change%100);
        } else{
            printf("Sorry, there is not enough in the required denominations\nA credit note for %d pounds and %d pence will be issued.\n",amount_change/100,amount_change%100);
        }
    }
}

int main() {

    printf("Tape input file path:\n");
    //scanf("%s", file_name);
    //open file
    file = fopen(file_name, "r");
    //error checking
    if (file == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
//load cash
    double A=0.0;
    double G=0.0;
    double C=0.0;
    double T=0.0;
    ch = fgetc(file);

    //if there are number after other number this loop merge these
    while (ch != EOF) {
        switch (ch) {
            case 'A':
                A++;
                break;
            case 'G':
                G++;
                break;
            case 'C':
                C++;
                break;
            case 'T':
                T++;
                break;
        }
        ch = fgetc(file);
    }
    double res=((G+C)/(A+T+G+C))*100;
    printf("A=%f  T=%f  G=%f  C=%f  GC content=%f",A,T,G,C,res);


/*
    loadData();
    //asking about an owed and payment
    printf("How much the customer owe? (in pence)\n");
    scanf("%d", &owed);
    printf("How much the customer offer as payment? (in pence)\n");
    scanf("%d", &offered);
    if(offered<owed){
        printf("Sorry, you did not give enough money");
    } else{
        compute_change(owed, offered);
    }
*/
    return 0;
}
