#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
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

Livro GetLivro()
{
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
    Node *previous = NULL;
    while (current != NULL && strcmp(livro.Titulo, current->livro.Titulo) > 0)
    {
      previous = current;
      current = current->next;
    }

    if (previous == NULL)
    {
      novoNode->next = lista->head;
      lista->head = novoNode;
    }
    else
    {
      previous->next = novoNode;
      novoNode->next = current;
    }
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

void deletarLivro(ListaLivros *lista, char *tituloOuNumReg)
{
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
    if (fwrite(&(current->livro), sizeof(Livro), 1, fptr) != 1)
    {
      break;
    }
    current = current->next;
  }
  fclose(fptr);
  printf("Lista de livros salva no arquivo com sucesso.\n");
}

int main(void)
{
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
    printf("4 - Buscar Livros (Digite o nome do livro ao lado)\n");
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
      printf("Digite o titulo ou numero de registro do livro que deseja buscar: ");
      char tituloOuNumReg[50];
      scanf("%s", tituloOuNumReg);
      buscarLivro(lista, tituloOuNumReg);
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
