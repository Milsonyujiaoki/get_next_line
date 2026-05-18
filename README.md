# get_next_line

Implementação do projeto get_next_line da 42 School - função que lê uma linha de um file descriptor.

## 📋 Descrição

`get_next_line` é uma função que retorna uma linha lida de um file descriptor. Chamadas sucessivas permitem ler o arquivo linha por linha até o final.

## 🎯 Objetivos

- Aprender programação de sistemas
- Gerenciar memória dinâmica em C
- Trabalhar com file descriptors e buffers
- Desenvolver práticas de engenharia de software

## 📁 Estrutura

```
get_next_line/
├── src/
│   ├── get_next_line.c          # Implementação principal (para submissão)
│   ├── gnl_list.c               # Implementação alternativa (linked-list)
│   ├── slist.c                  # Funções auxiliares da linked-list
│   └── get_next_line_linkedl.c  # Outra implementação de linked-list
├── include/
│   ├── get_next_line.h          # Header principal
│   └── gnl_list.h               # Header da implementação linked-list
├── tests/
│   └── test_getnextline.c       # Testes internos
├── gnlTester/                   # Tester externo (Tripouille)
├── 42test-gnl/                  # Tester externo (sloquet)
├── get_next_line.c              # Arquivo para submissão (raiz)
├── get_next_line.h              # Header para submissão (raiz)
└── get_next_line_utils.c        # Utils para submissão (raiz)
```

## 🔨 Compilação

### Biblioteca estática (abordagem remainder)
```bash
make                    # Compila libgetnextline.a
make BUFFER_SIZE=1      # Define tamanho do buffer
```

### Biblioteca linked-list
```bash
make list               # Compila libgetnextline_list.a
```

### Biblioteca compartilhada (.so)
```bash
make shared             # Gera build/shared/libgetnextline.so.1.0.1
```

## ✅ Testes

### Testes internos
```bash
make test               # Testa abordagem remainder
make test_list          # Testa abordagem linked-list
make test BUFFER_SIZE=1 # Testa com buffer mínimo (stress test)
```

### Testers externos

#### gnlTester (Tripouille)
```bash
make tripouille         # Roda todos os testes mandatory
                        # Testa BUFFER_SIZE: 1, 42, 10000000
```

#### 42test-gnl (sloquet)
```bash
make sloquet            # Roda testes com valgrind
                        # Testa BUFFER_SIZE: 0, 1, 2, 42, 42000
```

#### Ambos os testers
```bash
make testers            # Executa gnlTester + 42test-gnl
```

## 🧹 Limpeza

```bash
make clean              # Remove objetos compilados
make clean-testers      # Remove arquivos temporários dos testers
make fclean             # Remove tudo (objetos + bibliotecas + testers)
make re                 # Recompila do zero
```

## 📝 Abordagens Implementadas

### 1. Remainder (Padrão - para submissão)
- **Arquivo**: `src/get_next_line.c`
- **Estratégia**: Usa `static char *remainder` para armazenar sobras
- **Vantagens**: Simples, eficiente, fácil de entender
- **Funções auxiliares**:
  - `gnl_strlen()` - calcula tamanho da string
  - `gnl_strjoin()` - concatena buffer com remainder
  - `gnl_extract()` - extrai linha até `\n`
  - `gnl_trim()` - remove porção consumida do remainder

### 2. Linked-list
- **Arquivo**: `src/gnl_list.c` + `src/slist.c`
- **Estratégia**: Lista encadeada armazena chunks lidos
- **Vantagens**: Demonstra manipulação de estruturas de dados
- **Funções auxiliares**:
  - `fill_list()` - lê chunks até encontrar `\n`
  - `line_len()` - conta bytes até `\n`
  - `build_line()` - monta string a partir dos nós
  - `trim_list()` - remove nós consumidos

## 🔍 Características

- ✅ **Sem vazamentos de memória** (testado com valgrind)
- ✅ **Funciona com BUFFER_SIZE variável** (1 a 10000000)
- ✅ **Suporta múltiplos file descriptors** (usando `static` por fd)
- ✅ **100% norminette compliant**
- ✅ **Sem libft** (conforme exigido pelo subject)
- ✅ **Apenas funções permitidas**: read(), malloc(), free()

## 📊 Resultados dos Testers

### gnlTester (Tripouille)
- ✅ BUFFER_SIZE=1: 100% OK (2 timeouts esperados em linhas muito grandes)
- ✅ BUFFER_SIZE=42: 100% OK
- ✅ BUFFER_SIZE=10000000: 100% OK

### 42test-gnl (sloquet)
- ✅ BUFFER_SIZE=0: 100% OK
- ✅ BUFFER_SIZE=1: 100% OK
- ✅ BUFFER_SIZE=2: 100% OK
- ✅ BUFFER_SIZE=42: 100% OK
- ✅ BUFFER_SIZE=42000: 100% OK
- ✅ **Zero memory leaks** em todos os testes

## 🚀 Uso Rápido

```bash
# Compilar e testar tudo
make && make test

# Rodar todos os testers externos
make testers

# Limpar tudo
make fclean
```

## 📚 Recursos

- [Subject oficial](https://cdn.intra.42.fr/pdf/pdf/960/en.subject.pdf)
- [gnlTester (Tripouille)](https://github.com/Tripouille/gnlTester)
- [42test-gnl (sloquet)](https://github.com/mrxx0/42test-gnl)

