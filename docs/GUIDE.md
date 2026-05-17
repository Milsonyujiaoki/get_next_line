# get_next_line

## O que é

Implementar uma função `get_next_line()` que lê uma linha de um file descriptor a cada chamada.
Ao ser chamada em loop, permite ler um arquivo inteiro, uma linha por vez, sem limite de tamanho de linha ou arquivo.

```c
int  get_next_line(int fd, char **line);
/* retorna  1 → leu uma linha
            0 → EOF atingido
           -1 → erro */
```

## Conceitos-chave

- **`read()`** — leitura parcial de fd com buffer fixo (`BUFFER_SIZE` definido via `-D`)
- **Variável estática** — guardar o "resto" entre chamadas consecutivas ao fd
- **Buffer dinâmico** — concatenar o que foi lido até encontrar `\n` ou EOF
- **Memory management** — sem vazamentos; liberar resto ao alcançar EOF
- **`open()` / `close()`** — lidar com múltiplos fds (bonus)

## Como começar

1. Entender como `read()` funciona com buffers pequenos
2. Implementar uma versão simples que lê até `\n` em um único fd
3. Usar `static char *remainder[FD_MAX]` para suportar múltiplos fds no bonus
4. Testar com `BUFFER_SIZE=1`, `BUFFER_SIZE=42`, arquivos vazios, sem `\n` no final
5. Verificar com `valgrind` para garantir zero memory leaks

### Fluxo básico

```
chamada → ler fd em buffer → juntar com resto anterior →
→ encontrou '\n'? → extrair linha, salvar resto → retornar 1
→ EOF?            → retornar resto como última linha → retornar 0
→ erro?           → retornar -1
```

## Funções permitidas

`read`, `malloc`, `free`

## Referências

### Man pages
- `man 2 read`
- `man 2 open`
- `man 3 malloc`

### Artigos e tutoriais
- [42Docs — get_next_line](https://harm-smits.github.io/42docs/projects/get_next_line.html)
- [Entendendo static em C (GeeksForGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Ler arquivo linha por linha em C (StackOverflow)](https://stackoverflow.com/questions/3501338/c-read-file-line-by-line)

### Testers
- [gnl-unit-test (harm-smits)](https://github.com/harm-smits/gnl-unit-test)
- [gnlTester (Tripouille)](https://github.com/Tripouille/gnlTester)
- [42cursus_gnl_tests (mrjvs)](https://github.com/mrjvs/42cursus_gnl_tests)

### YouTube
- *"Get Next Line — 42 Project Explained"* — pesquise no YouTube por `get_next_line 42 school`
