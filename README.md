# Huffman Coding - Compressor de Texto

*Sistema de compressão e descompressão de texto usando o algoritmo de Huffman em C*

![C](https://img.shields.io/badge/C-99+-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)
![License](https://img.shields.io/badge/license-MIT-blue)

## 📋 Visão Geral

Implementação completa do **algoritmo de Huffman** para compressão de texto utilizando estruturas de dados avançadas. O projeto realiza análise de frequência, construção de árvore binária, geração de códigos binários e compressão/descompressão de arquivos.

**Principais características:**
- 📊 Análise de frequência de palavras
- 🌳 Construção automática de árvore de Huffman
- 🔢 Geração de códigos binários otimizados
- 💾 Compressão de texto em arquivos binários
- 🔓 Descompressão com reconstrução da árvore
- 📝 Manipulação de bits com unions

---

## 🚀 Tecnologias

- **C Standard (C99+)**
- **Estruturas de dados**: Árvores binárias, listas encadeadas, pilhas, floresta, unions
- **Bibliotecas**: stdio.h, stdlib.h, string.h, ctype.h, conio2.h
- **Técnicas**: Manipulação de bits, arquivos binários, algoritmo de Huffman

---

## 🏗️ Estrutura do Projeto

```
├── codificacao.c          # Programa principal de compressão
├── decodificacao.c        # Programa principal de descompressão
├── tabela.h               # Gerenciamento de tabela de frequências
├── arvore_floresta.h      # Estruturas de árvore e floresta
├── pilha.h                # Implementação de pilhas
├── byte.h                 # Manipulação de bits e bytes
├── frase.txt              # Arquivo de análise (corpus)
├── fraseCodificar.txt     # Texto a ser comprimido
├── tabela.dat             # Tabela serializada (gerada)
└── fraseCodificada.dat    # Arquivo comprimido (gerado)
```

---

## 📊 Estruturas de Dados

### Tabela de Frequências
```c
typedef struct dados {
    int simbolo, frequencia;
    char palavra[50], codigo[50];
} Dados;

typedef struct tabela {
    Dados dados;
    struct tabela *prox;
} Tabela;
```

### Árvore de Huffman
```c
typedef struct arvore {
    int simbolo, frequencia;
    struct arvore *esq, *dir;
} Arvore;
```

### Floresta (Lista de Árvores)
```c
typedef struct floresta {
    Arvore *no;
    struct floresta *prox;
} Floresta;
```

### Manipulação de Bits
```c
struct bits {
    unsigned char b7:1;
    unsigned char b6:1;
    // ... b5 até b0
};

union byte {
    struct bits bi;
    unsigned char num;
} Byte;
```

### Pilhas Auxiliares
- **PilhaArvore**: Armazena nós durante travessia
- **PilhaCodigo**: Armazena códigos binários em construção
- **PilhaArvoreNivel**: Exibição hierárquica da árvore

---

## 🔧 Funcionalidades

### Codificação
- Análise de frequência de palavras em corpus (frase.txt)
- Construção automática da árvore de Huffman ordenada por frequência
- Geração de códigos binários otimizados (esquerda = '0', direita = '1')
- Compressão de texto em bytes com padding automático
- Serialização da tabela e arquivo comprimido em formato binário

### Decodificação
- Reconstrução da árvore a partir da tabela serializada
- Descompressão bit a bit com travessia da árvore
- Recuperação completa do texto original

---

## 🎯 Fluxo de Execução

**Codificação**: Análise do corpus → Criação da tabela de frequências → Construção da árvore de Huffman → Geração de códigos → Compressão do texto em bytes → Gravação dos arquivos binários

**Decodificação**: Leitura da tabela serializada → Reconstrução da árvore → Descompressão bit a bit → Recuperação do texto original

---

## 📄 Licença

MIT License

---

**Projeto educacional - Estruturas de Dados e Algoritmos**
