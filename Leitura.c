/*
    QUESTÃO 1 - O arquivo Leitura.c [1] consiste em um simples programa capaz de armazenar
    dados do estoque de livros de uma livraria. O programa é capaz de coletar diversas informações
    de diferentes títulos, como nome do autor e preço, e as salva em um arquivo de dados
    (extensão .dat). Ao final de sua execução, o programa também imprime na tela todos os
    exemplares inseridos até o momento.

    Você foi recentemente contratado por uma empresa de TI que presta serviços para esta livraria
    e sua primeira tarefa é melhorar este código de acordo com as requisições do cliente. As
    principais funcionalidades que o cliente gostaria de adicionar ao atual sistema são:

    1. Função de buscar certos livros através do título ou número de registro e retornar o
    preço na tela;
    2. Opção de deletar certos títulos caso eles estejam em falta no estoque;
    3. Os títulos devem ser inseridos em ordem alfabética;
    4. Uma opção de salvar em arquivo caso o usuário deseje;
    Baseado nos requisitos acima, faça as seguintes modificações no código:

    a) Implemente uma lista encadeada para armazenar as informações dos livros
    inseridos pelo usuário;
    b) Implemente funções de inserção, busca e remoção de elementos desta lista;
    c) Implemente funções de salvar os dados da estrutura no arquivo .dat, caso o
    usuário precise;
    d) Melhore a atual interface, tornando-a mais amigável e incluído breve instruções
    de todas as funcionalidades listadas acima;
    e) Concerte erros de execução caso existam;

    Além do código, escreva um arquivo README no formato .txt contendo 
    (1) informações de como o cliente pode executar seu código por linha de comando e 
    (2) uma listagem de todas as mudanças feitas no código original (bullet points). 
    Tanto o código (arquivo .c) quanto o README devem ser enviados na pasta zipada via classroom. Caso seu código tenha algum arquivo de
    biblioteca (.c e/ou .h) também os inclua na pasta zipada (e deixe claro no README qualquer arquivo extra incluído no seu projeto).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char Titulo[50];
  char Autor[50];
  int NumReg;
  double Preco;
} Livro;

typedef struct Node
{
  Livro livro;
  struct Node *next;
} Node;

typedef struct
{
  Node *head;
} ListaLivros;

Livro GetLivro(){
  Livro livro;
  printf("\nADICIONANDO NOVO LIVRO\n ");

  printf("\nDigite o titulo: ");
  scanf(" %[^\n]", livro.Titulo);
  printf("\nDigite o nome do autor: ");
  scanf(" %[^\n]", livro.Autor);
  printf("\nDigite o numero do registro: ");
  scanf("%d", &livro.NumReg);
  printf("\nDigite o preco do livro: ");
  scanf("%lf", &livro.Preco);
  fflush(stdin);

  return livro;
}

void PrintLivro(Livro livro)
{
  printf("\nTitulo: %s\n", livro.Titulo);
  printf("Autor: %s\n", livro.Autor);
  printf("No.Reg: %d\n", livro.NumReg);
  printf("Preco: %.2lf\n", livro.Preco);
}

ListaLivros *criarLista()
{
  ListaLivros *lista = (ListaLivros *)malloc(sizeof(ListaLivros));
  if (lista == NULL)
  {
    exit(1);
  }
  lista->head = NULL;
  return lista;
}

void inserirLivro(ListaLivros *lista, Livro livro)
{
  Node *novoNode = (Node *)malloc(sizeof(Node));
  if (novoNode == NULL)
  {
    exit(1);
  }
  novoNode->livro = livro;
  novoNode->next = NULL;

  if (lista->head == NULL)
  {
    lista->head = novoNode;
  }
  else
  {
    Node *current = lista->head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = novoNode;
  }
  printf("Livro inserido com sucesso\n");
}

void imprimirLista(ListaLivros *lista)
{
  Node *current = lista->head;
  printf("\n\nLISTA DE LIVROS\n");
  printf("==============================\n");
  while (current != NULL)
  {
    PrintLivro(current->livro);
    current = current->next;
  }
  printf("\n");
}

void deletarLivro(ListaLivros *lista, char *tituloOuNumReg){
  Node *current = lista->head;
  Node *previous = NULL;

  while (current != NULL)
  {
    if (strcmp(current->livro.Titulo, tituloOuNumReg) == 0 || current->livro.NumReg == atoi(tituloOuNumReg))
    {
      if (previous == NULL)
      {
        lista->head = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      free(current);
      printf("Livro deletado com sucesso.\n");
      return;
    }
    previous = current;
    current = current->next;
  }
  printf("Livro nao encontrado.\n");
}
void deletarLivroMenu(ListaLivros *lista)
{
  char deleteResp;
  do
  {
    printf("Deseja deletar algum livro? (s/n): ");
    scanf(" %c", &deleteResp);
    if (deleteResp == 's' || deleteResp == 'S')
    {
      char tituloOuNumReg[50];
      printf("Digite o titulo ou numero de registro do livro que deseja deletar: ");
      scanf("%s", tituloOuNumReg);
      deletarLivro(lista, tituloOuNumReg);
      imprimirLista(lista);
    }
  } while (deleteResp == 's' || deleteResp == 'S');
}

void buscarLivro(ListaLivros *lista, char *tituloOuNumReg)
{
  Node *current = lista->head;
  while (current != NULL)
  {
    if (strcmp(current->livro.Titulo, tituloOuNumReg) == 0 || current->livro.NumReg == atoi(tituloOuNumReg))
    {
      PrintLivro(current->livro);
      return;
    }
    current = current->next;
  }
  printf("Livro nao encontrado.\n");
}

void salvarEmArquivo(ListaLivros *lista)
{
  FILE *fptr = fopen("livros.dat", "wb");
  if (fptr == NULL)
  {
    exit(1);
  }

  Node *current = lista->head;
  while (current != NULL)
  {
    if (fwrite(&(current->livro), sizeof(Livro), 1, fptr) != 1){
      break;
    }
    current = current->next;
  }
  fclose(fptr);
  printf("Lista de livros salva no arquivo com sucesso.\n");

}

int main(void){
  Livro livro;
  ListaLivros *lista = criarLista();
  int comand = 0;

  do
  {
    printf("\nOla, seja bem-vindo a Library System\n");
    printf("O que voce deseja fazer?\n\n");
    
    printf("1 - Inserir um novo Livro\n");
    printf("2 - Ver Lista de Livros\n");
    printf("3 - Excluir Livro\n");
    printf("4 - Buscar Livros\n");
    printf("5 - Salvar\n");
    printf("6 - Sair\n\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &comand);

    switch (comand)
    {
    case 1:
      livro = GetLivro();
      inserirLivro(lista, livro);
      break;
    case 2:
      imprimirLista(lista);
      break;
    case 3:
      deletarLivroMenu(lista);
      break;
    case 4:
      buscarLivro(lista, " "); 
      break;
    case 5:
      salvarEmArquivo(lista);
      break;
    case 6:
      break;
    default:
      printf("Opção inválida\n");
      break;
    }

  } while (comand != 6);

  return 0;
}
