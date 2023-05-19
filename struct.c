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
        printf("4. Deletar Titulo\n"); //
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
        //printf("Digite o c�digo do game:\n");
        //scanf("%d",&inventario[tamanho-1].index);
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
    printf("| %-10s | %-10s | %-10s |\n", "C�digo", "T�tulo", "Quantidade");
    printf("|------------|------------|------------|\n");
    for (int i = 0; i < tamanho; i++) {
    if(inventario[i].index != 0) printf("| %-10d | %-10s | %-10d |\n", inventario[i].index, inventario[i].name, inventario[i].quantity);
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
    }
    system("pause");
    system("cls");

}

//void Carregar_Dados

void Salvar_Dados(Game *Inventario, int tamanho){
    FILE *arquivo = fopen("dados.txt","w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "Codigo,Descricao,Quantidade\n");
    for(int i=0;i<tamanho;i++){
        if(Inventario[i].index != 0){
            fprintf(arquivo, "%d,%s,%d\n", Inventario[i].index, Inventario[i].description, Inventario[i].quantity);
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
    int tamanho = 1;
    Game *Inventario = calloc(tamanho, sizeof(Game));
    while(1){
        switch(menu()){
        case 1:
            tamanho ++;
            Inventario = (Game*) realloc(Inventario,tamanho*sizeof(Game));
            Inventario[tamanho-2].index = 0;
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
