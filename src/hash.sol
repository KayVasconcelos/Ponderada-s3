// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract MercadoriaRegister {
    // Define um tipo de dado para armazenar o nome da mercadoria
    struct Mercadoria {
        string nome;
        bool exists;
    }

    // Um mapping de índices para Mercadorias
    mapping(uint => Mercadoria) private tabela;

    // Mantem o controle do número de mercadorias
    uint private count = 0;
    uint private constant TAM = 10;

    // Insere uma nova mercadoria
    function inserir(string memory nome) public {
        require(count < TAM, "Tabela cheia");
        uint id = funcaoHash(nome);
        require(!tabela[id].exists, unicode"Colisão detectada");
        tabela[id] = Mercadoria({nome: nome, exists: true});
        count++;
    }

    // Função hash
    function funcaoHash(string memory str) private pure returns (uint) {
        return uint(keccak256(abi.encodePacked(str))) % TAM;
    }

    // Busca uma mercadoria pelo nome
    function busca(string memory nome) public view returns (bool, uint) {
        uint id = funcaoHash(nome);
        if (tabela[id].exists && keccak256(abi.encodePacked(tabela[id].nome)) == keccak256(abi.encodePacked(nome))) {
            return (true, id);
        } else {
            return (false, 0);
        }
    }

    // Verifica se a posição está ocupada
    function isOcupada(uint id) public view returns (bool) {
        return tabela[id].exists;
    }
}
