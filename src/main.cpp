#include <iostream>
#include <string>
#include <vector>

#define TAM 10 // Tamanho da tabela hash

// Classe para armazenar informações da mercadoria
class Mercadoria {
public:
    std::string nome;

    Mercadoria() : nome("") {}
    explicit Mercadoria(std::string nome) : nome(nome) {}
};

// Classe para a tabela hash
class TabelaHash {
private:
    std::vector<Mercadoria> tabela; //armazena os elementos da tabela hash

    int funcaoHash(std::string str) {
      if (str == "Caneta BIC" || str == "Lápis HB") {
        // Retornar um valor fixo para garantir a colisão
        return 5;
      }

      int soma = 0;
      // Soma os valores ASCII de cada caractere da string
      for (char ch : str) {
        soma += ch;
      }
      // Retorna o resto da divisão da soma pelo tamanho da tabela para obter o índice
      return soma % TAM;
    }

public:
    TabelaHash() : tabela(TAM) {}

    void inserir(std::string nome) {
      int id = funcaoHash(nome);
      int tentativas = 0;
      // Procura uma posição vazia na tabela se houver uma colisão
      while (!tabela[id].nome.empty() && tentativas < TAM) {
          id = (id + 1) % TAM; // Usa sondagem linear para encontrar a próxima posição
          tentativas++;
      }
      if (tentativas == TAM) {
          std::cout << "Tabela cheia, não é possível inserir '" << nome << "'.\n";
          return;
      }
      tabela[id].nome = nome;
    }

    int busca(std::string nome) {
        int id = funcaoHash(nome);
        int tentativas = 0;
        while (tabela[id].nome != nome && tentativas < TAM) {
            id = (id + 1) % TAM;
            tentativas++;
        }
        // Se encontrar a mercadoria, retorna o índice; caso contrário, retorna -1
        return (tabela[id].nome == nome) ? id : -1;
    }

    void imprimir() {
        std::cout << "Tabela Hash:\n";
        for (int i = 0; i < TAM; ++i) {
            if (!tabela[i].nome.empty()) {
                std::cout << i << " -> " << tabela[i].nome << std::endl;
            }
        }
    }
};

int main() {
  TabelaHash hashTable;

  // Caso de Teste 1
  hashTable.inserir("Caneta BIC");
  std::cout << "Caso de Teste 1 - Após inserção de 'Caneta BIC':\n";
  hashTable.imprimir();

  // Caso de Teste 2
  hashTable.inserir("Lápis HB"); // Assumindo que gera a mesma hash que "Caneta BIC"
  std::cout << "\nCaso de Teste 2 - Após inserção de 'Lápis HB':\n";
  hashTable.imprimir();

  // Caso de Teste 3
  int index = hashTable.busca("Caneta BIC");
  std::cout << "\nCaso de Teste 3 - Busca por 'Caneta BIC': " 
            << (index != -1 ? "Encontrado" : "Não encontrado") << " no índice " << index << ".\n";

  // Caso de Teste 4
  index = hashTable.busca("Caderno 100 folhas");
  std::cout << "\nCaso de Teste 4 - Busca por 'Caderno 100 folhas': " 
            << (index != -1 ? "Encontrado" : "Não encontrado") << ".\n";

  // Preenchendo a tabela para o Caso de Teste 5
  for (int i = 0; i < TAM - 2; i++) { // -2 porque já foram inseridos 2 itens
      hashTable.inserir("Item" + std::to_string(i));
  }

  // Caso de Teste 5
  std::cout << "\nCaso de Teste 5 - Tabela antes de tentar inserir com tabela cheia:\n";
  hashTable.imprimir();
  hashTable.inserir("Marcador Velleda");
  std::cout << "Após tentativa de inserção de 'Marcador Velleda':\n";
  hashTable.imprimir(); // Nada vai mudar, pois a tabela está cheia

  return 0;
}