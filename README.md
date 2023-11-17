# Library System

## Descrição
O projeto consiste em um sistema simples para gerenciar o estoque de livros de uma livraria. O programa permite ao usuário inserir novos livros, visualizar a lista de livros, excluir livros, buscar livros por título ou número de registro, salvar a lista em um arquivo e sair do programa.

## Funcionalidades Adicionais
1. **Inserção Ordenada:** Os livros são inseridos na lista de forma ordenada pelo título.
2. **Busca por Livro:** Permite ao usuário buscar um livro pelo título ou número de registro.
3. **Exclusão de Livro:** Oferece a opção de excluir livros do estoque.
4. **Salvar em Arquivo:** Permite salvar a lista de livros em um arquivo "livros.dat".

## Como Executar
Para compilar e executar o programa, siga os passos abaixo:

1. Abra o terminal.
2. Navegue até o diretório onde o código-fonte está localizado.
3. Compile o código utilizando um compilador C, por exemplo:
    
    gcc -o library_system Leitura.c
    
4. Execute o programa:
    
    ./library_system
    

## Mudanças Realizadas no Código Original
- Adição de uma lista encadeada para armazenar informações dos livros.
- Implementação de funções de inserção, busca e remoção de elementos na lista.
- Aprimoramento da interface do usuário e inclusão de instruções claras.
- Ordenação dos livros por título durante a inserção.
- Opção de salvar a lista em um arquivo.
- Correção de erros de execução.
