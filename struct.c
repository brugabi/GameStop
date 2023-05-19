#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

typedef struct {
    int index;
    char name[255];
    char description[255];
    char rating[10];
    int quantity;
} Game;

int menu(){
    int opcao;
    //scanear arquivo
    do{
        printf("\n----- Menu -----\n");
        printf("1. Cadastrar T�tulo\n");
        printf("2. Mostrar T�tulos Cadastrados\n");
        printf("3. Consultar T�tulos Cadastrados\n"); // funcao para alterar o que o usu�rio quiser, nome, quantidade, etc.
        printf("4. Alterar Titulo\n"); //
        printf("0. Sair\n");
        printf("Op��o: ");
        scanf("%d",&opcao);
        if (opcao<0 || opcao>5) {
            printf("Entrada inv�lida.\n");
            system("pause");
            system("cls");
        }
    }while(opcao<0 || opcao>5);
    system("cls");
    return opcao;
}

void Cadastro(Game *inventario,int tamanho){
        inventario[tamanho-1].index = inventario[tamanho-2].index + 1;
        printf("Digite o t�tulo do jogo:\n");
        scanf(" %[^\n]",&inventario[tamanho-1].name);
        printf("Digite a descricao:\n");
        scanf(" %[^\n]",&inventario[tamanho-1].description);
        printf("Digite a classifica��o indicativa:\n");
        scanf(" %[^\n]",&inventario[tamanho-1].rating);
        printf("Digite a quantidade dispon�vel:\n");
        scanf("%d",&inventario[tamanho-1].quantity);
        system("cls");
        printf("FIM DO CADASTRO\n");
        system("pause");
        system("cls");
    }

void Mostrar_Inventario(Game *inventario,int tamanho){
    printf("| %-10s | %-10s |\n", "C�digo", "T�tulo");
    printf("|------------|------------|\n");
    for (int i = 0; i < tamanho; i++) {
    if(inventario[i].index != 0) printf("| %-10d | %-10s |\n", inventario[i].index, inventario[i].name);
    }
    system("pause");
    system("cls");
}

void Consultar (Game *inventario){
    int index;
    printf("Digite o C�digo do jogo:\n");
    scanf("%d",&index);
    for(int i=0;;i++){
        if(inventario[i].index == index){
            printf("Nome: %s\n",inventario[i].name);
            printf("Classifica��o Indicativa: %s\n",inventario[i].rating);
            printf("Quantidade: %d\n",inventario[i].quantity);
            printf("Descri��o:\n\t%s\n",inventario[i].description);
            break;
        }
        else {
            printf("Op��o Inv�lida\n");
            break;
        }
    }
    system("pause");
    system("cls");

}
//void Alterar (Game*inventario){
    //int index;
    //int afirmacao;
    //printf("Digite o C�digo do jogo:\n");
    //scanf("%d",&index);
    //for (int i=0;;i++){
        //if(inventario[i].index == index){

    }
}

// Carregar Dados
void Carregar_Dados(Game **Inventario, int *tamanho){
    FILE *arquivo = fopen("dados.txt","r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Ignorar a primeira linha (cabe�alho)
    char line[255];
    fgets(line, sizeof(line), arquivo);

    int i = 0;
    while (fgets(line, sizeof(line), arquivo) != NULL) {
        Game jogo; // Cria uma inst�ncia tempor�ria da estrutura Game

        sscanf(line, "%d,%[^,],%[^,],%[^,],%d",
               &jogo.index,
               jogo.name,
               jogo.description,
               jogo.rating,
               &jogo.quantity);

        *Inventario = realloc(*Inventario, (i + 1) * sizeof(Game));
        (*Inventario)[i] = jogo;

        i++;
        *tamanho = i; // Atualizar o tamanho do invent�rio
    }

    fclose(arquivo);
}


void Salvar_Dados(Game *Inventario,int tamanho){
    FILE *arquivo = fopen("dados.txt","w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "Codigo,Nome,Descricao,Classifica��o Indicativa,Quantidade\n");
    for(int i=0;i<tamanho;i++){
        if(Inventario[i].index != 0){
            fprintf(arquivo, "%d,%s,%s,%s,%d\n", Inventario[i].index, Inventario[i].name, Inventario[i].description, Inventario[i].rating, Inventario[i].quantity);
        }
    }
    fclose(arquivo);
}

void Fim() {
    printf("\n------------------\n");
    printf("Programa finalizado!\n");
    printf("------------------\n");
}

int main(){
    setlocale(LC_ALL, "portuguese"); // Permitindo o uso de acentos e �
    int tamanho = 0;
    //Game *Inventario = calloc(tamanho, sizeof(Game));
    Game *Inventario = NULL;
    Carregar_Dados(&Inventario, &tamanho);

    while(1){
        switch(menu()){
        case 1:
            tamanho ++;
            Inventario = (Game*) realloc(Inventario,tamanho*sizeof(Game));
            Cadastro(Inventario,tamanho); // Cadastrando os jogos
            break;
        case 2:
            Mostrar_Inventario(Inventario,tamanho); // Mostrando o invent�rio
            break;
        case 3:
            Consultar(Inventario);
            break;
        case 0:
            Salvar_Dados(Inventario,tamanho);
            Fim();
            return 0;
        }
    }
    return 0;
}
