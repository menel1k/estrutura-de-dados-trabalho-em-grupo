#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados para representar uma fruta
typedef struct Fruta {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Fruta *proxima;
} Fruta;

// Função para criar uma nova fruta
Fruta* criarFruta(int codigo, char nome[], int quantidade, float preco) {
    Fruta *nova = (Fruta *)malloc(sizeof(Fruta));
    nova->codigo = codigo;
    strcpy(nova->nome, nome);
    nova->quantidade = quantidade;
    nova->preco = preco;
    nova->proxima = NULL;
    return nova;
}

// Função para adicionar uma fruta à lista
void adicionarFruta(Fruta **lista, Fruta *nova) {
    if (*lista == NULL) {
        *lista = nova;
    } else {
        Fruta *temp = *lista;
        while (temp->proxima != NULL) {
            temp = temp->proxima;
        }
        temp->proxima = nova;
    }
}

// Função para verificar se o código da fruta já existe
int codigoExistente(Fruta *lista, int codigo) {
    Fruta *temp = lista;
    while (temp != NULL) {
        if (temp->codigo == codigo) {
            return 1;
        }
        temp = temp->proxima;
    }
    return 0;
}

// Função para cadastrar uma nova fruta
void cadastrarFruta(Fruta **lista) {
    int codigo, quantidade;
    char nome[50];
    float preco;
    printf("Digite o codigo da fruta: ");
    scanf("%d", &codigo);

    if (codigoExistente(*lista, codigo)) {
        printf("Codigo ja cadastrado!\n");
        return;
    }

    printf("Digite o nome da fruta: ");
    scanf("%s", nome);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o preco: ");
    scanf("%f", &preco);

    Fruta *nova = criarFruta(codigo, nome, quantidade, preco);
    adicionarFruta(lista, nova);
    printf("Fruta cadastrada com sucesso!\n");
}

// Função para listar todas as frutas
void listarFrutas(Fruta *lista) {
    if (lista == NULL) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }
    
    Fruta *temp = lista;
    while (temp != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
               temp->codigo, temp->nome, temp->quantidade, temp->preco);
        temp = temp->proxima;
    }
}

// Função para buscar uma fruta pelo código
Fruta* buscarFruta(Fruta *lista, int codigo) {
    Fruta *temp = lista;
    while (temp != NULL) {
        if (temp->codigo == codigo) {
            return temp;
        }
        temp = temp->proxima;
    }
    return NULL;
}

// Função para alterar os dados de uma fruta
void alterarFruta(Fruta *lista) {
    int codigo, quantidade;
    char nome[50];
    float preco;
    printf("Digite o codigo da fruta a ser alterada: ");
    scanf("%d", &codigo);
    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta == NULL) {
        printf("Fruta nao encontrada!\n");
        return;
    }
    printf("Digite o novo nome da fruta: ");
    scanf("%s", nome);
    printf("Digite a nova quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o novo preco: ");
    scanf("%f", &preco);
    strcpy(fruta->nome, nome);
    fruta->quantidade = quantidade;
    fruta->preco = preco;
    printf("Fruta alterada com sucesso!\n");
}

// Função para excluir uma fruta
void excluirFruta(Fruta **lista, int codigo) {
    Fruta *temp = *lista;
    Fruta *anterior = NULL;
    while (temp != NULL) {
        if (temp->codigo == codigo) {
            if (temp->quantidade == 0) {
                if (anterior == NULL) {
                    *lista = temp->proxima;
                } else {
                    anterior->proxima = temp->proxima;
                }
                free(temp);
                printf("Fruta excluida com sucesso!\n");
            } else {
                printf("Nao e possivel excluir frutas com estoque!\n");
            }
            return;
        }
        anterior = temp;
        temp = temp->proxima;
    }
    printf("Fruta nao encontrada!\n");
}

// Função para registrar uma venda de fruta
void registrarVenda(int codigo, char nome[], int quantidade, float preco) {
    FILE *arquivo = fopen("vendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return;
    }
    fprintf(arquivo, "Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", 
            codigo, nome, quantidade, preco);
    fclose(arquivo);
}

// Função para vender uma fruta
void venderFruta(Fruta *lista) {
    int codigo, quantidade;
    printf("Digite o codigo da fruta a ser vendida: ");
    scanf("%d", &codigo);
    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta == NULL) {
        printf("Fruta nao encontrada!\n");
        return;
    }
    printf("Digite a quantidade a ser vendida: ");
    scanf("%d", &quantidade);
    if (quantidade > fruta->quantidade) {
        printf("Quantidade em estoque insuficiente!\n");
        return;
    }
    fruta->quantidade -= quantidade;
    registrarVenda(codigo, fruta->nome, quantidade, fruta->preco);
    printf("Venda realizada com sucesso!\n");
}

int main() {
    Fruta *lista = NULL;
    int opcao;
    do {
        printf("\n1. Cadastrar fruta\n2. Listar frutas\n3. Buscar fruta\n4. Alterar fruta\n5. Excluir fruta\n6. Vender fruta\n7. Sair\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarFruta(&lista);
                break;
            case 2:
                listarFrutas(lista);
                break;
            case 3: {
                int codigo;
                printf("Digite o codigo da fruta: ");
                scanf("%d", &codigo);
                Fruta *fruta = buscarFruta(lista, codigo);
                if (fruta != NULL) {
                    printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", 
                           fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
                } else {
                    printf("Fruta nao encontrada!\n");
                }
                break;
            }
            case 4:
                alterarFruta(lista);
                break;
            case 5: {
                int codigo;
                printf("Digite o codigo da fruta a ser excluida: ");
                scanf("%d", &codigo);
                excluirFruta(&lista, codigo);
                break;
            }
            case 6:
                venderFruta(lista);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);
    return 0;
}