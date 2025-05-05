📚 Sistema de Gerenciamento de Livros com Múltiplas Listas Dinâmicas
Este projeto em linguagem C++ implementa um sistema de gerenciamento de livros com listas encadeadas múltiplas e uso de arquivos binários para persistência de dados. Desenvolvido como exercício de estrutura de dados, ele permite importar livros de um arquivo texto e manipulá-los dinamicamente na memória, oferecendo recursos de exclusão, geração de relatórios e organização por autor e editora.

🔧 Funcionalidades implementadas
Importação de dados
Leitura de um arquivo texto (livros.txt) contendo dados de livros e gravação em um arquivo binário (livros.dat).

Construção da estrutura dinâmica
Leitura dos dados do arquivo binário e criação de listas encadeadas múltiplas, com livros organizados por autor e editora, conforme estrutura previamente definida.

Exclusão de livro
Busca e remoção de um livro, tanto no arquivo binário quanto nas listas encadeadas, a partir do título.

Geração de relatórios

Todos os livros de cada autor

Todos os livros de cada editora

Autores que não possuem livros cadastrados

Menu interativo
Interface de menu no terminal que permite ao usuário acessar todas as funcionalidades implementadas.
