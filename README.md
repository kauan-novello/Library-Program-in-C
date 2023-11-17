# Library-Program-in-C
Projeto Arquivos em C - Programa para Biblioteca

Informações de como o cliente pode executar seu código por linha de comando:

Bullet point: 

- Antes a main do código iniciava já inicializando o arquivo e usava um Do while pra ir chamando a função getLivro() até que o usuário digitasse 'n' como 'resp';
Como pedido, implementei uma lista encadeada para os livros, onde adicionei as novas funções pedidas de Inserir, Imprimir, Deletar, Buscar e diretamente na lista, e só então quando chamada a função salvarLivros() se inicializa o arquivo .dat;
- Tranformei o getLivro() em uma função recursiva na sendo chamada na Inserção;
- Mudei a sintaxe do getLivro(), ao invés de fgets(), passei a usar scanf(" %[^\n]", livro.Exemplo) para que não recebesse o \n na hora de ser printado;
- Por fim adicionei todas as funções a um switch case para que o usuário possa ter a liberdade de escolher que ação quer tomar;
