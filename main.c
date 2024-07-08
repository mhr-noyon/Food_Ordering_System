/*  01. Fried Rice         == foodList[0]   ----   190tk
    02. Burger             == foodList[1]   ----   170tk
    03. Cheese Pizza       == foodList[2]   ----   250tk
    04. Sandwitch Mini     == foodList[3]   ----   80tk
    05. Fried chicken      == foodList[4]   ----   180tk
    06. Thai Soup          == foodList[7]   ----   210tk
    07. Fish Cake          == foodList[10]  ----   70tk
    08. Mango Juice        == foodList[11]  ----   50tk*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct foods food;
typedef struct customers customer;
struct foods
{
    char name[20];
    int price;
    int count;
    food *prev;
    food *next;
}*head=NULL, *tail=NULL;

struct customers
{
    char nickName[20];
    int pass[6];
    char cell[12];
    int paid;
    customer *prev;
    customer *next;
}*firstInfo=NULL, *lastInfo=NULL, *logged=NULL;


//pass protection
int encMsz[6],passIndex=0;
char decMsz[7];
int key[2][2]= {{1,2},{3,1}};
int adjKey[2][2];
void encrypt(int temp[],customer *men)
{
    int sum;
    for(int i=0; i<2; i++)
    {
        sum=0;
        for(int j=0; j<2; j++)
        {
            sum+= temp[j]*key[j][i];
        }
        men->pass[passIndex]= sum;
        //printf("encrypt index: %d\n",passIndex);
       // printf("encrypt pass: %d\n",men->pass[passIndex]);
        passIndex++;
    }
}
void decrypt(int temp[])
{
    int det;
    det = (key[0][0]*key[1][1])-(key[0][1]*key[1][0]);
    adjKey[0][0] = key[1][1];
    adjKey[1][1] = key[0][0];
    adjKey[0][1] = -key[0][1];
    adjKey[1][0] = -key[1][0];
    int sum;
    for(int i=0; i<2; i++)
    {
        sum=0;
        for(int j=0; j<2; j++)
        {
            sum+= (temp[j]*adjKey[j][i])/det;
        }
        decMsz[passIndex]= sum;
        passIndex++;
    }
    return ;
}

void updateTempCustomersFile(customer* newC, int n);
void updateItemListFile();
void exitDisplay();
int stringToInt(char s[]);
int checkPhoneNumber(char number[12]);
void inputItemList();
void showMenuList();
void showSelectedItem();
void countItemsZero();
void countSelectedItems(int item, int quantity);
void billPage();
int order();
void addItem();
void updateItem();
void deleteItem();
void signUp();
void logIn();
int findNameExistance(char nameTemp[15]);
int matchPass(char passTemp[]);
int findCellExistance(char cellTemp[12]);
int deleteSpecificItem();
void adminPanel();
int adminLogIn();
int matchAdminPass();
void inputTempCustomers();
// void changePass();


void showCustomerList(int order);
void mergeSort(customer** head, int order);
void devide2Part(customer* head, customer** left, customer** right);
customer* conquer(customer* left, customer* right, int order);

char opt[4], quantity[4],optMainPanel[4], exits[4], optAdminPanel[4];
char address[15];
int availableItems=0,orderProcessRun,orderTime=1,logInTruth=0,adminLogInTruth=0,truthValueOfChoice,truthValueOfQuantity,quantityOfItem,option,showBill,money;
char nameTemp[15],passTemp[7];
//char adminPass[]="admin1";
int adminPass[]={199, 148, 207, 154, 215, 160}; //123456
int main()
{
    inputItemList();
    inputTempCustomers();
    int runConsole=1,run=1;
    while(runConsole && run)
    {
        system("cls");
        //printf("\nEnter in main func\n\n");

        printf("\t-----------------------\n");
        printf("\t\tHome Page\n");
        printf("\t-----------------------\n\n\n");
        if(logInTruth==0)
        {
            printf("\t1. Show Menu List\n\n");
            printf("\t2. Log in account\n\n");
            printf("\t3. Sign Up\n\n");
            printf("\t4. Admin panel\n\n");
            printf("\t5. Exit\n\n\n");
            printf("\t---> Choose option: ");
            fflush(stdin);
            scanf("%[^\n]s",optMainPanel);
            //printf("%d",stringToInt(optMainPanel));
            switch(stringToInt(optMainPanel))
            {
            case 1:
                system("cls");
                showMenuList();
                break;
            case 2: logIn();
                    break;
            case 3: signUp();
                    printf("You are now signed in.\n");
                    break;
            case 4:
                adminPanel();
                break;

            case 5:
                runConsole=0;
                run=0;
                break;
            default:
                printf("Invalid Option, Try again\n");
            }
        }
        else if(logInTruth==1)
        {
            showMenuList();
        }
        runConsole=1;
        system("cls");
    }

    return 0;
}

int stringToInt(char s[])
{
    if(s[0]=='\0')
        return -1;
    int num=0, i;
    for(i=0; s[i]!='\0'; i++)
    {
        if(s[i]<48 || s[i]>57) return -1;
        num = num*10 + (s[i]-48);
    }
    return num;
}
void showMenuList()
{
    showBill=0;
    while(showBill!=1)
    {
        system("cls");
        food *travers=head;
        printf("\t\t  ------------------------------\n");
        printf("\t\t             GUB-Food\n");
        printf("\t\t  ------------------------------\n");
        if(adminLogInTruth) printf("[Logged In as Admin]\n\n");
        else if(logInTruth) printf("[Account: %s]\n\n",logged->nickName);
        else printf("[You aren't logged in]\n\n");
        /*-----Show Menu list---*/
        printf("\n\t\t--------------MENU LIST--------------");
        printf("\n\n");

        int i=1;
        if(travers==NULL)
            printf("\t\tEmpty list\n");
        while(travers!=NULL)
        {
            if(i<10)
            printf("\t\t0%d. %s  ----   %d Taka\n\n", i, travers->name, travers->price);
            else
            printf("\t\t%d. %s  ----   %d Taka\n\n", i, travers->name, travers->price);
            travers=travers->next;
            i++;
        }
        if(adminLogInTruth==1)
        {
            printf("\t\t-------------------------------------\n\n");
            showBill=1;
        }
        else if(logInTruth)
        {
            showBill=order();
        }
        else
        {
            printf("\t\t-------------------------------------\n\n");
            printf("\t\t***Log in to your account to order***\n");
            exitDisplay();
            showBill=1;
        }
    }

    //printf("\n:Return from showMenulist func\n\n");
}
void showSelectedItem()
{
    food* travers=head;
    printf("\n");

    int i=1;

    printf("\t\t-------------------------------------\n\n\n");
    printf("\tYou have chosen,\n\n");
    while(travers!=NULL)
    {
        if(travers->count>0)
            printf("\t\t0%d. %s  ----   %d\n\n", i, travers->name, travers->count);
        travers=travers->next;
        i++;
    }
    printf("\n\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n\n\n");
}
int order()
{
    orderProcessRun=1;
    while(orderProcessRun!=0)
    {
        //printf("%d",orderTime);
        if(orderTime>1)
        {

            printf("\t\t0%d. Show BILL RECEIPT \t-->-->-->\n\n",availableItems+1);//Asking IF USER WANTS TO ORDER MORE ITEM?
            printf("\t\t00. LOG OUT   \t\t<--<--<--\n");
            //printf("\t\t99. Change Pass\t\t<--<--<--\n");
            printf("\n\t\t-------------------------------------");
            //To Print selected item
            showSelectedItem();
            //printf("\n\n\t***Choose more item or enter %d to get bill receipt**\n\n",availableItems+1);
        }
        else
        {
            printf("\n\t\t-------------------------------------\n\n");
            printf("\t\t00. LOG OUT   \t\t<--<--<--\n");
            //printf("\t\t99. Change Pass\t\t<--<--<--\n");
            printf("\n\t\t-------------------------------------\n\n");
        }
        // Customer input: choosing item and quantity
        truthValueOfChoice = 1;
        while(truthValueOfChoice)
        {
            option=-1;
            opt[0]='\0';
            printf("\t---> Choose option: ");
            fflush(stdin);
            scanf("%[^\n]s",opt);
            option = stringToInt(opt);
            printf("%d\n",option);
            if(option==0)
            {
                //printf("\n\t\t***Invalid OPTION***");
                truthValueOfChoice=0;
                orderProcessRun=0;
                logInTruth=0;
                orderTime=0;
                countItemsZero();
                continue;
            }
            /*
            else if(option==99)
            {
                //printf("\n\t\t***Invalid OPTION***");
                changePass();
                continue;
            }*/
            else if(orderTime>=2 && option==(availableItems+1))
            {
                billPage();
                //printf("\n:Return from order func with 1\n\n");
                return 1;
            }
            else if(option>0 && option<=availableItems)
            {
                orderProcessRun=0;
                truthValueOfChoice=0;
                int truthValueOfQuantity=0;
                while(truthValueOfQuantity!=1)
                {
                    printf("\n\t---> Quantity: ");
                    fflush(stdin);
                    scanf("%[^\n]s",quantity);
                    quantityOfItem = stringToInt(quantity);

                    if(quantityOfItem<1)
                    {
                        printf("\n\t\t***Invalid Quantity***");
                        continue;
                    }
                    else
                    {
                        printf("%d\n",quantityOfItem);
                        countSelectedItems(option, quantityOfItem);
                        truthValueOfQuantity=1;
                        orderTime++;
                        return 0;
                    }
                }
            }
            else
            {
                printf("\n\t\t***Invalid OPTION\n***");
            }
        }
    }
    return 0;
}
/*
void changePass()
{
    char passTempNew[7];
        do
        {
            printf("\n\t\tEnter new password(length=6): ");
            fflush(stdin);
            scanf("%[^\n]s",passTempNew);
        }while(strlen(passTempNew)!=6);

        int temp[2],j;
        j=0, passIndex=0;
        for(int i=0; i<6 ; i++)
        {
            temp[j]= passTempNew[i];
            j++;
            if(j%2==0)
            {
                j=0;
                encrypt(temp,logged);
            }
        }
    updateTempCustomersFile(head);
    exitDisplay();
}*/
void countSelectedItems(int item, int quantity)
{
    food *travers=head;
    int i=1;
    while(i!=item)
    {
        travers=travers->next;
        i++;
    }
    travers->count += quantity;
    return ;
}
void billPage()
{
    system("cls");
    printf("\t\t\t------------------------------\n");
    printf("\t\t\t          GUB-Food\n");
    printf("\t\t\t------------------------------\n\n");
    printf("\n\tEnter your address: ");
    fflush(stdin);
    scanf("%[^\n]s",address);
    system("cls");
    //BILL RECIEPT
    printf("\t\t\t------------------------------\n");
    printf("\t\t\t          GUB-Food\n");
    printf("\t\t\t------------------------------\n\n");

    printf("\t\t-----------------BILL RECEIPT-----------------\n\n\n");
    printf("\tCustomer Name: %s\n",logged->nickName);
    printf("\tCustomer Phone: +8801%s\n",logged->cell);
    printf("\tCustomer Address: %s\n\n",address);

    printf("\t\tItem             --         Quantity     --     Price\n");
    printf("\t\t-----                       --------           ------\n");

    food* travers=head;
    money=0;
    while(travers!=NULL)
    {
        if(travers->count>0)
        {
            printf("\t\t%s             %d                  %d Taka\n",travers->name, travers->count, travers->count*travers->price);
        }
        money += travers->price * travers->count;
        travers=travers->next;
    }
    printf("\t\t--------------------------------------------------------\n");
    //bill;
    printf("\t\t   Total                                     %d Taka\n\n",money);


    //For print BILL RECIEPT in file
    FILE *ptr;
    ptr = fopen("order_records.txt","a");
    fprintf(ptr,"\n\n\n\n\n\n\n\n\t\t-----------------BILL RECEIPT-----------------\n\n\n");
    fprintf(ptr,"\tCustomer Name: %s\n",logged->nickName);
    fprintf(ptr,"\tCustomer Phone: +8801%s\n",logged->cell);
    fprintf(ptr,"\tCustomer Address: %s\n\n",address);

    fprintf(ptr,"\t\tItem             --         Quantity     --     Price\n");
    fprintf(ptr,"\t\t-----                       --------           ------\n");

    travers=head;
    money=0;
    while(travers!=NULL)
    {
        if(travers->count>0)
        {

            fprintf(ptr,"\t\t%s             %d                  %d Taka\n",travers->name, travers->count, travers->count*travers->price);
        }
        money += travers->price * travers->count;
        travers=travers->next;
    }
    fprintf(ptr,"\t\t--------------------------------------------------------\n");
    //bill;
    fprintf(ptr,"\t\t   Total                                     %d Taka\n\n",money);
    logged->paid+=money;
    updateTempCustomersFile(firstInfo,0);
    fclose(ptr);
    //printf("\n\tThank you %s for choosing us.\n\tYour order will be placed in ",name);
    //printf(" at %s\n\n",address);

    printf("\n\tIf any issue occurred, contact: 01719767459.\n");
    printf("\n\n\t[***MUST COLLECT(take SS) YOUR BILL RECIEPT AND PAY MONEY IN COD SYSTEM WITH SHOWING IT***]\n\n");



    //printf("Bill=%d",money);
    exitDisplay();
    countItemsZero();
    orderTime=1;
}
void exitDisplay()
{
    printf("\n\t\t\tTo exit press any key\n");
    fflush(stdin);
    scanf("%[^\n]s",exits);
    system("cls");
}
int checkPhoneNumber(char number[12])
{
    int numb = stringToInt(number);
    if(findCellExistance(number)==0 && (numb/100000000==3 || numb/100000000==4 || numb/100000000==5 || numb/100000000==6 ||
        numb/100000000==7 || numb/100000000==8 || numb/100000000==9))
    {
        return 1;
    }
    else
    {
        printf("\n\t***Invalid contact number or, already used***\n");
        return 0;
    }
    return 0;
}
void signUp()
{
    customer *men = (customer*)malloc(sizeof(customer));
    fflush(stdin);
    system("cls");
        printf("\t\t  ------------------------------\n");
        printf("\t\t              GUB-Food\n");
        printf("\t\t  ------------------------------\n\n\n");
        printf("[TO EXIT ENTER '0']\n\n");
        printf("\n\t\t-------------SIGN UP--------------\n");

        do
        {
            logged = NULL;
            fflush(stdin);
            printf("\n\t\tEnter your nickname(that isn't used): ");
            scanf("%[^\n]s",men->nickName);
            if(stringToInt(men->nickName)==0)
            {
                free(men);
                return ;
            }
        }while(findNameExistance(men->nickName));
        char passTempNew[7];
        do
        {
            printf("\n\t\tEnter password(length=6): ");
            fflush(stdin);
            scanf("%[^\n]s",passTempNew);
            if(stringToInt(passTempNew)==0)
            {
                free(men);
                return ;
            }
        }while(strlen(passTempNew)!=6);

        int temp[2],j;
        j=0, passIndex=0;
        for(int i=0; i<6 ; i++)
        {
            temp[j]= passTempNew[i];
            j++;
            if(j%2==0)
            {
                j=0;
                encrypt(temp,men);
            }
        }
        do
        {
            logged=NULL;
            printf("\n\t\tEnter phone number: +8801");
            fflush(stdin);
            scanf("%[^\n]s",men->cell);
            if(stringToInt(men->cell)==0)
            {
                free(men);
                return ;
            }
            int number = stringToInt(men->cell);
        }while(checkPhoneNumber(men->cell)!=1);
        men->paid = 0;
        men->prev=lastInfo;
        men->next=NULL;
        lastInfo->next=men;
        lastInfo=men;
        logged=men;
        logInTruth=1;
        updateTempCustomersFile(men,1);
        printf("\n\n\n\t[Account has been created & You are signed In]\n");
    printf("\n\tTo reload page enter any key\n");
    fflush(stdin);
    scanf("%[^\n]s",exits);
    system("cls");
}
void logIn()
{
    logInTruth=0;
    int nameTrue=0;
    int passTrue=0;
    int cellTrue=0;
    system("cls");
        printf("\t\t  ------------------------------\n");
        printf("\t\t              GUB-Food\n");
        printf("\t\t  ------------------------------\n");
        printf("[TO EXIT ENTER '0']\n\n");
        printf("\n\t\t--------------LOG IN--------------\n");
        while(nameTrue!=1)
        {
            printf("\n\t\tEnter name: ");
            fflush(stdin);
            scanf("%[^\n]s",nameTemp);
            if(stringToInt(nameTemp)==0)
            {
                return ;
            }
            //printf("nameTemp: %d\n",strlen(nameTemp));
            if(findNameExistance(nameTemp))
                break;
            printf("Doesn't exist, Enter correct name.\n");
        }
        while(passTrue!=1)
        {
            printf("\n\t\tEnter pass: ");
            fflush(stdin);
            scanf("%[^\n]s",passTemp);
            if(stringToInt(passTemp)==0)
            {
                return ;
            }
            else if(strlen(passTemp)!=6)
                passTrue=0;
            else if(matchPass(passTemp))
                break;
            printf("Wrong Password, Enter correct password\n");
        }
    logInTruth=1;

}
int findNameExistance(char nameTemp[15])
{
    customer* travers=firstInfo;
    while(travers!=NULL)
    {
            if(strcmp(travers->nickName,nameTemp)==0)
            {
                logged=travers;
                return 1;
            }
        travers=travers->next;
    }
    return 0;
}
int matchPass(char passTemp[])
{
    int temp[2],j;
    j=0, passIndex=0;
    for(int i=0; i<6; i++)
    {
        temp[j]= logged->pass[i];
        j++;
        if(j%2==0)
        {
            j=0;
            decrypt(temp);
        }
    }
    if(strcmp(decMsz,passTemp)==0)
    {
        return 1;
    }
    return 0;
}
int findCellExistance(char cellTemp[12])
{
    customer* travers=firstInfo;
    while(travers!=NULL)
    {
            if(strcmp(travers->cell,cellTemp)==0)
            {
                logged=travers;
                return 1;
            }
        travers=travers->next;
    }
    return 0;
}
int adminLogIn()
{
    system("cls");
        printf("\t\t  ------------------------------\n");
        printf("\t\t              GUB-Food\n");
        printf("\t\t  ------------------------------\n\n\n");
        printf("[TO EXIT ENTER '0']\n\n");
        printf("\n\t\t----------ADMIN PANEL-----------\n");
    int passTrue=0;
    while(passTrue!=1)
    {
        printf("\n\tHello Admin,\n\n");
        printf("\tEnter password: ");
        fflush(stdin);
        scanf("%[^\n]s",passTemp);
        if(stringToInt(passTemp)==0)
            return 0;
        if(matchAdminPass())
            passTrue=1;
    }
    return 1;
}
void adminPanel()
{
    adminLogInTruth=adminLogIn();
    if(adminLogInTruth==0)
        return;
    while(adminLogInTruth)
    {
        system("cls");
        printf("\t  ------------------------------\n");
        printf("\t              GUB-Food\n");
        printf("\t--------------------------------\n\n\n");
        printf("\n\t----------ADMIN PANEL-----------\n\n");
        printf("\t1. Show Menu List\n\n");
        printf("\t2. Add Item\n\n");
        printf("\t3. Update Item\n\n");
        printf("\t4. Delete Item\n\n");
        printf("\t5. Show Customer List (alphabet ascending order)\n\n");
        printf("\t6. Show Customer List (paid descending order)\n\n");
        printf("\t7. Log Out\n\n");
        printf("\t  ------------------------------\n\n\n");
        printf("\t---> Choose option: ");
        fflush(stdin);
        scanf("%[^\n]s",optAdminPanel);
        switch(stringToInt(optAdminPanel))
        {
        case 1:
            system("cls");
            showMenuList();
            exitDisplay();
            break;
        case 2:
            addItem();
            break;
        case 3:
            updateItem();
            break;
        case 4:
            deleteItem();
            break;
        case 5:
            mergeSort(&firstInfo,1);
            showCustomerList(1);
            exitDisplay();
            break;
        case 6:
            mergeSort(&firstInfo,2);
            showCustomerList(2);
            exitDisplay();
            break;
        case 7:
            adminLogInTruth=0;
            break;
        default:
            printf("\nInvalid Option, Enter again\n");
        }
    }
}
void addItem()
{
    
    
    food* newNode=(food*)malloc(sizeof(food));
    if(newNode==NULL)
        printf("\t\tMEMORY IS FULL\n");
    else
    {
        system("cls");
        showMenuList();
        printf("\t\t00. Go BACK   \t\t<--<--<--\n");
        printf("\n\t\t-------------------------------------\n\n");
        printf("\tTo add, \n");
        printf("\t---> Enter item name: ");
        fflush(stdin);
        scanf("%[^\n]s",newNode->name);
        if(stringToInt(newNode->name)==0)
        {
            free(newNode);
            return ;
        }
        int len= strlen(newNode->name);
        //printf("%d len\n",len);
        if(len<15)
        {
            for(int i=len;i<15;i++)
            {
                newNode->name[i] = ' ';
            }
        }
        //fgets(newNode->name,15,stdin);
        printf("\t---> Enter item price: ");
        scanf("%d",&newNode->price);
        newNode->count=0;
        newNode->prev=tail;
        newNode->next=NULL;
        tail->next=newNode;
        tail=newNode;
        availableItems++;
        showMenuList();
        printf("\n\t\tItem has been added.\n");
    }

    updateItemListFile();
    exitDisplay();
}
void deleteItem()
{
    if(head==NULL)
    {
        printf("\t\tLIST IS EMPTY\n");
    }
    else
    {
        system("cls");
        showMenuList();
        int optionTruth=0;
        while(optionTruth!=1)
        {
            food *temp;
            printf("\t\t---------------------\n\n");
            printf("\tSELECT ONE OPTION: \n");
            printf("\t\t1. Delete first Item \n");
            printf("\t\t2. Delete Last Item \n");
            printf("\t\t3. Delete specific Item \n");
            printf("\t\t4. Exit\n\n");
            printf("\t---> Choose option: ");
            fflush(stdin);
            scanf("%[^\n]s",optMainPanel);
            //printf("%d",stringToInt(optMainPanel));
            int opt=stringToInt(optMainPanel);
            optionTruth=1;
            switch(opt)
            {
                case 1: 
                    temp = head;
                    head=head->next;
                    free(temp);
                    break;
                case 2:
                    temp = tail;
                    tail=tail->prev;
                    tail->next=NULL;
                    free(temp);
                    break;
                case 3:
                    if(!deleteSpecificItem()){
                        optionTruth=0;
                    }
                    break;
                case 4:
                    return;
                default: optionTruth=0;
                    printf("\n\t\tInvalid Option, Try again\n");
            }
        }

        availableItems--;
        showMenuList();
        printf("\n\t\tItem has been deleted successfully.\n");
    }

    updateItemListFile();
    exitDisplay();
}
int deleteSpecificItem()
{

    int position,delTruth=0,i;
    while(delTruth!=1)
    {
        printf("\n\t\t-------------------------------------\n\n");
        printf("\t\t00. Go BACK   \t\t<--<--<--\n");
        printf("\n\t\t-------------------------------------\n\n");
        printf("\tTo delete, \n");
        printf("\t\t---> Enter position of the item: ");
        char position[5];
        fflush(stdin);
        scanf("%[^\n]s",position);
        int positionInt = stringToInt(position);
        if(positionInt==0)
        {
            return 0;
        }
        food* travers=head;
        food* travers2;
        food* travers3;
        i=1;
        while(i+1!=positionInt && travers->next!=NULL)
        {
            travers=travers->next;
            i++;
            if(i>1000){
                printf("\n\t\tItem doesn't exist\n");
                return 0;
            }
        }
        if(i+1==positionInt && travers->next!=NULL)
        {
            travers2=travers->next;
            travers3=travers2->next;
            travers->next=travers3;
            travers2->prev = travers;
            free(travers2);

            delTruth=1;
        }
        else
        {
            printf("\n\t\tItem doesn't exist\n");
            delTruth=0;
        }
    }
    return 1;
}
void updateItem()
{
    if(head==NULL)
    {
        printf("\n\t\tEmpty list\n");
    }
    else
    {
        system("cls");
        showMenuList();
        printf("\t\t00. Go BACK   \t\t<--<--<--\n");
        printf("\n\t\t-------------------------------------\n\n");
        printf("\tTo update, \n");
        printf("\t\t---> Enter position of the item: ");
        char position[5];
        fflush(stdin);
        scanf("%[^\n]s",position);
        int positionInt = stringToInt(position);
        if(positionInt==0)
        {
            return;
        }
        int i=1;
        food* travers=head;
        while(i!=positionInt && travers!=NULL)
        {
            travers=travers->next;
            i++;
            if(i>1000){
                printf("\n\t\tItem doesn't exist\n");
                return;
            }
        }
        if(i==positionInt && travers!=NULL)
        {
            printf("\t\t---> Enter new item name: ");
            fflush(stdin);
            scanf("%[^\n]s",travers->name);
            int len= strlen(travers->name);
            //printf("%d len\n",len);
            if(len<15)
            {
                for(int i=len;i<15;i++)
                {
                    travers->name[i] = ' ';
                }
            }
            printf("\t\t---> Enter new price: ");
            scanf("%d",&travers->price);
            
            showMenuList();
            printf("\n\t\tList Updated\n");

            updateItemListFile();
            exitDisplay();
        }
        else
        {
            printf("\n\t\tItem doesn't exist\n");
        }
    }
}
int matchAdminPass()
{
    int temp[2],j;
    j=0, passIndex=0;
    for(int i=0; adminPass[i]!='\0'; i++)
    {
        temp[j]= adminPass[i];
        j++;
        if(j%2==0)
        {
            j=0;
            decrypt(temp);
        }
    }
    /*for(int i=0;i<6;i++)
        printf("Decrypt pass: %c\n",decMsz[i]);*/
    if(strcmp(decMsz,passTemp)==0)
    {
        return 1;
    }
    printf("\n\t\tWrong password. Try again, \n");
    return 0;
}
void countItemsZero()
{
    food *travers=head;
    while(travers!=NULL)
    {
        // printf("%d\n",travers->count);
        travers->count = 0;
        travers = travers->next;
    }
    return;
}
void inputItemList()
{
    char buff;
    FILE *fptr=fopen("Foods.txt","r");
    fscanf(fptr,"%c",&buff);
    do{
        buff=EOF;
        food *item = (food *)malloc(sizeof(food));
        int count=0;
       while(count<15)
        {
            //fgetc(item->name[count]);
            fscanf(fptr,"%c",&item->name[count]);
            count++;
        }
        fscanf(fptr,"%d",&item->price);

        fscanf(fptr,"%c",&buff);
        if(buff==EOF)
            break;
        item->next=NULL;
        if(head==NULL)
        {
            head = tail = item;
            item->prev=NULL;
        }
        else
        {
            tail->next=item;
            item->prev=tail;
            tail=item;
        }
        availableItems++;
    }while(buff!=EOF);
    fclose(fptr);
    countItemsZero();
   /* food *temp=head;

    while(temp!=NULL)
    {
        printf("%s \t",temp->name);
        printf("%d \n",temp->price);
        temp=temp->next;
    }
    exitDisplay();*/
}
void updateItemListFile()
{
    char buff;
    FILE *fptr=fopen("Foods.txt","w");

    food* travers=head;
    do{
        fprintf(fptr,"\n%s %d",travers->name,travers->price);
        travers=travers->next;
    }while(travers!=NULL);
    fclose(fptr);
}
void inputTempCustomers()
{
    int num;
    FILE *fptr=fopen("customerList.txt","r");
    //fscanf(fptr,"%d",&num);
    do{
        num=EOF;
        customer *men = (customer *)malloc(sizeof(customer));
        fscanf(fptr,"%s",men->nickName);
        int count=0;
        while(count<6)
        {
            fscanf(fptr,"%d",&men->pass[count]);
            count++;
        }
        fscanf(fptr,"%s",men->cell);
        fscanf(fptr,"%d",&num);
        men->paid=num;

        if(firstInfo==NULL)
        {
            firstInfo= lastInfo = men;
            men->next=NULL;
        }
        else
        {
            men->next=firstInfo;
            firstInfo=men;
        }
    }while(num!=EOF);
    fclose(fptr);

    customer *temp=firstInfo;

    firstInfo = firstInfo->next;
    free(temp);
  /*  temp=firstInfo;

    while(temp!=NULL)
    {
        printf("%s \t",temp->nickName);
        int count=0;
        while(count<6)
        {
            printf("%d \t",temp->pass[count]);
            count++;
        }
        printf("%s \t",temp->cell);
        printf("%d \n",temp->paid);
        temp=temp->next;
    }
    exitDisplay();*/
}
void updateTempCustomersFile(customer* newC,int n)
{
    FILE *fptr;
    if(n==1) fptr=fopen("customerList.txt","a");
    else fptr=fopen("customerList.txt","w");
    customer* travers=newC;
    while(travers!=NULL)
    {
    //printf("\n1: %s",travers->nickName);
        fprintf(fptr,"\n%s ",travers->nickName);
        fprintf(fptr,"%d ",travers->pass[0]);
        fprintf(fptr,"%d ",travers->pass[1]);
        fprintf(fptr,"%d ",travers->pass[2]);
        fprintf(fptr,"%d ",travers->pass[3]);
        fprintf(fptr,"%d ",travers->pass[4]);
        fprintf(fptr,"%d ",travers->pass[5]);
        fprintf(fptr,"%s ",travers->cell);
        fprintf(fptr,"%d",travers->paid);
        travers=travers->next;
    }
    fclose(fptr);
}

//customer list
void showCustomerList(int order)
{
    system("cls");
    if(order==1)
    printf("\n\n\t\t\t------------------ CUSTOMERS INFO ------------------\n(sorted in order of alphabet)\n\n\n");
    else
    printf("\n\n\t\t\t------------------ CUSTOMERS INFO ------------------\n(sorted in order of paid money)\n\n\n");
        printf("\n\n\t\t------------------------------------------------------------------------------\n\n");
    printf("\t\t NAME\t\t\t\tTOTAL PAID\t\t\tPHONE NUMBER\n");
    printf("\t\t------\t\t\t\t----------\t\t\t--------------\n\n");
    customer* travers=firstInfo;
    while(travers!=NULL)
    {
        printf("\t\t%s\t\t------  \t %d TAKA \t ------ \t01%s\n\n",travers->nickName,travers->paid, travers->cell);
        travers=travers->next;
    }

        printf("\n\t\t------------------------------------------------------------------------------\n");
}

//sorting
void mergeSort(customer** head,int order)
{
    if(*head==NULL || (*head)->next==NULL)
    {
        return;
    }

    customer* left;
    customer* right;

    devide2Part(*head,&left,&right);


    mergeSort(&left,order);
    mergeSort(&right,order);

    *head=conquer(left,right,order);
}
void devide2Part(customer* source, customer** left, customer** right)
{
    if(source==NULL || source->next==NULL)
    {
        *left = source;
        *right = NULL;
        return ;
    }
    customer* slow=source;
    customer* fast=source->next;

    while(fast!=NULL)
    {
        fast=fast->next;
        if(fast!=NULL)
        {
            slow=slow->next;
            fast=fast->next;
        }
    }

    *left = source;
    *right=slow->next;
    slow->next=NULL;
}
customer* conquer(customer* left, customer* right,int order)
{
    if(left==NULL)
    {
        return right;
    }
    else if(right==NULL)
    {
        return left;
    }
    customer* sorted=NULL;
    if(order==1)
    {
        if(strcmp(left->nickName,right->nickName)<=0)
        {
            sorted=left;
            sorted->next= conquer(left->next,right,order);
        }
        else
        {
            sorted=right;
            sorted->next= conquer(left,right->next,order);
        }
        return sorted;
    }
    else
    {
        if(left->paid >= right->paid)
        {
            sorted=left;
            sorted->next= conquer(left->next,right,order);
        }
        else
        {
            sorted=right;
            sorted->next= conquer(left,right->next,order);
        }
        return sorted;
    }
}
