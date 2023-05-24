#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int index;
    char name[255];
    char description[1000];
    char rating[10];
    int quantity;
} Game;

int menu(){
    int option;
    //scanear arquivo
    do{
        printf("\n----- Menu -----\n");
        printf("1. Register a Title\n");
        printf("2. Show Registered Titles\n");
        printf("3. Consult Registered Titles\n");
        printf("4. Change a Title\n");
        printf("0. END\n");
        printf("Option: ");
        scanf("%d",&option);
        if (option<0 || option>5) {
            printf("Invalid entry.\n");
            system("pause");
            system("cls");
        }
    }while(option<0 || option>5);
    system("cls");
    return option;
}

void Registry(Game *inventory,int size){
        inventory[size-1].index = inventory[size-2].index + 1;
        printf("Enter the title of the game:\n");
        scanf(" %[^\n]",&inventory[size-1].name);
        printf("Enter the discription:\n");
        scanf(" %[^\n]",&inventory[size-1].description);
        printf("Enter the rating:\n");
        scanf(" %[^\n]",&inventory[size-1].rating);
        printf("Enter the avaible quantity:\n");
        scanf("%d",&inventory[size-1].quantity);
        system("cls");
        printf("END OF REGISTRY\n");
        system("pause");
        system("cls");
    }

void Show_Inventory(Game *inventory,int size){
    printf("| %-10s | %-10s |\n", "INDEX", "TITLE");
    printf("|------------|------------|\n");
    for (int i = 0; i < size; i++) {
    if(inventory[i].index != 0) printf("| %-10d | %-10s |\n", inventory[i].index, inventory[i].name);
    }
    system("pause");
    system("cls");
}

void Consult (Game *inventory, int size){
    int index, flag=0;
    printf("Enter the index of the game:\n");
    scanf("%d",&index);
    for(int i=0;i<size;i++){
        if(inventory[i].index == index){
            printf("Name: %s\n",inventory[i].name);
            printf("Age Rating: %s\n",inventory[i].rating);
            printf("Quantity: %d\n",inventory[i].quantity);
            printf("Description:\n\t%s\n",inventory[i].description);
            flag = 1;
            break;
        }
    }
    if (flag == 0) printf("Game doesn't exist or not found\n");
    system("pause");
    system("cls");

}
void Change (Game*inventory, int size){
    int index;
    int afirmation;
    //inventory[size-1].index = inventory[size-2].index + 1;
    printf("Enter the index of the game:\n");
    scanf("%d",&index);
    for (int i=0;i<size;i++){
        if(inventory[i].index == index){
                printf("Game to be changed: '%d' -  %s\n", inventory[i].index, inventory[i].name);
                printf("What you'd like to change?\n1 - Name\t 2 - Description\t 3 - Age rating\t 4 - Quantity avaible\n");
                scanf("%d", &afirmation);
                switch(afirmation)
                {
                    case 1:
                        printf("Enter a new name:\n");
                        scanf(" %[^\n]",&inventory[i].name);
                        break;
                    case 2:
                        printf("Enter a new discription:\n");
                        scanf(" %[^\n]",&inventory[i].description);
                        break;
                    case 3:
                       printf("Enter a new age rating:\n");
                       scanf(" %[^\n]",&inventory[i].rating);
                       break;
                    case 4:
                       printf("Enter a new avaible quanitty:\n");
                       scanf(" %[^\n]",&inventory[i].quantity);
                       break;
                    default:
                        printf("INVALID OPTION\n");
                        break;
                }

    }
  }
  printf("END OF THE MODIFICATION\n");
  system("pause");
  system("cls");
}
//Deletar


// Carregar Dados
void Load_File(Game **Inventory, int *size){
    FILE *arquivo = fopen("data.txt","r");
    if (arquivo == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    // Ignorar a primeira linha (cabe�alho)
    char line[255];
    fgets(line, sizeof(line), arquivo);

    int i = 0;
    while (fgets(line, sizeof(line), arquivo) != NULL) {
        Game game; // Cria uma inst�ncia tempor�ria da estrutura Game

        sscanf(line, "%d,%[^,],%[^,],%[^,],%d",
               &game.index,
               game.name,
               game.description,
               game.rating,
               &game.quantity);

        *Inventory = realloc(*Inventory, (i + 1) * sizeof(Game));
        (*Inventory)[i] = game;

        i++;
        *size = i; // Atualizar o size do invent�rio
    }

    fclose(arquivo);
}


void Save_File(Game *Inventory,int size){
    FILE *arquivo = fopen("data.txt","w");
    if (arquivo == NULL) {
        printf("Error to open the file.\n");
        return;
    }
    fprintf(arquivo, "Index,Name,Description,Age Ration,Quantity\n");
    for(int i=0;i<size;i++){
        if(Inventory[i].index != 0){
            fprintf(arquivo, "%d,%s,%s,%s,%d\n", Inventory[i].index, Inventory[i].name, Inventory[i].description, Inventory[i].rating, Inventory[i].quantity);
        }
    }
    fclose(arquivo);
}

void END() {
    printf("\n------------------\n");
    printf("Programa finalizado!\n");
    printf("------------------\n");
}

int main(){

    int size = 0;
    //Game *Inventory = calloc(size, sizeof(Game));
    Game *Inventory = NULL;
    Load_File(&Inventory, &size);

    while(1){
        switch(menu()){
        case 1:
            size ++;
            Inventory = (Game*) realloc(Inventory,size*sizeof(Game));
            Registry(Inventory,size); // Cadastrando os games
            break;
        case 2:
            Show_Inventory(Inventory,size); // Mostrando o invent�rio
            break;
        case 3:
            Consult(Inventory, size);
            break;
        case 4:
            Change(Inventory, size);
            break;
        case 0:
            Save_File(Inventory,size);
            END();
            return 0;
        }
    }
    return 0;
}