# 🧪 Guia de Testes - get_next_line

Este projeto integra dois dos melhores testers da comunidade 42 para validação completa da implementação.

## 📦 Testers Incluídos

### 1. gnlTester (Tripouille)
- **Autor**: Tripouille
- **Linguagem**: C++ (usa g++ ao invés de clang++)
- **Repositório**: https://github.com/Tripouille/gnlTester
- **Características**:
  - Testa com BUFFER_SIZE: 1, 42, 10000000
  - Testes de arquivos vazios, com/sem newline final
  - Testes de múltiplas linhas
  - Testes de file descriptors inválidos
  - Testes com stdin
  - Testes de linhas muito grandes (podem dar timeout com BUFFER_SIZE=1)

### 2. 42test-gnl (sloquet)
- **Autor**: sloquet (mrxx0)
- **Linguagem**: C
- **Repositório**: https://github.com/mrxx0/42test-gnl
- **Características**:
  - Testa com BUFFER_SIZE: 0, 1, 2, 42, 42000
  - Integração com valgrind (detecção de memory leaks)
  - Testes de norminette
  - Múltiplos arquivos de teste (brouette, otarie, bigben, etc.)
  - Validação de edge cases

## 🚀 Como Usar

### Opção 1: Rodar ambos os testers (recomendado)
```bash
make testers
```
Este comando irá:
1. Preparar os arquivos necessários na raiz
2. Executar gnlTester (Tripouille)
3. Executar 42test-gnl (sloquet)
4. Exibir resultados consolidados

### Opção 2: Rodar individualmente

#### gnlTester apenas:
```bash
make tripouille
```

#### 42test-gnl apenas:
```bash
make sloquet
```

## 📋 Estrutura de Arquivos para Testers

Os testers externos esperam encontrar:
- `get_next_line.h` - header na raiz
- `get_next_line.c` - implementação principal na raiz
- `get_next_line_utils.c` - funções auxiliares na raiz (pode ser vazio)

**Nota**: O Makefile copia automaticamente os arquivos de `src/` e `include/` para a raiz antes de executar os testers. Você não precisa fazer nada manualmente!

## 📊 Interpretando Resultados

### gnlTester

#### Sucesso ✅
```
[BUFFER_SIZE = 42]:
Invalid fd: 1.OK 2.OK 3.OK
files/empty: 1.OK 2.OK
files/nl: 1.OK 2.OK
...
```

#### Falha ❌
```
files/some_test: 1.KO 2.OK
```
Quando aparecer `KO`, o teste falhou. Verifique a implementação.

#### Timeout ⏱️
```
files/big_line_no_nl: TIMEOUT
```
Com BUFFER_SIZE=1, linhas muito grandes podem causar timeout (isso é esperado e aceitável).

### 42test-gnl

#### Sucesso ✅
```
BUFFER SIZE = 42
 1.OK  1.MOK ==123456== leaks summary: 0 errors from 0 contexts
 2.OK  2.MOK ==123457== leaks summary: 0 errors from 0 contexts
```
- `OK` = teste passou
- `MOK` = teste mandatory passou
- `leaks summary: 0 errors` = sem vazamentos de memória

#### Falha ❌
```
 3.KO  3.MKO
```
Teste falhou. Execute manualmente para ver detalhes:
```bash
cd 42test-gnl
make all
```

## 🔧 Troubleshooting

### Problema: "clang++ not found"
**Solução**: O Makefile já corrige isso automaticamente usando `sed` para substituir `clang++` por `g++`.

### Problema: Memory leaks detectados
**Solução**: Verifique:
1. Todas as chamadas de `malloc()` têm um `free()` correspondente
2. O `remainder` está sendo liberado corretamente em casos de erro
3. Não há vazamentos em loops

### Problema: Testers não encontram arquivos
**Solução**: Execute `make prepare-testers` manualmente para copiar os arquivos para a raiz.

### Problema: KO em testes específicos
**Solução**:
1. Identifique qual BUFFER_SIZE está falhando
2. Teste manualmente com esse valor:
   ```bash
   make test BUFFER_SIZE=1
   ```
3. Use valgrind para detectar problemas:
   ```bash
   valgrind ./build/tests/test_gnl
   ```

## 🧹 Limpeza Após Testes

Após executar os testers, arquivos temporários ficam na raiz. Para limpar:

```bash
make clean-testers
```

Isso remove:
- `get_next_line.h`
- `get_next_line.c`
- `get_next_line_utils.c`
- Binários compilados pelos testers

Ou limpe tudo de uma vez:
```bash
make fclean
```

## ✅ Checklist de Validação

Antes de submeter seu projeto, execute:

- [ ] `make` - compila sem erros
- [ ] `make test` - testes internos passam
- [ ] `make test BUFFER_SIZE=1` - testa edge case de buffer mínimo
- [ ] `make tripouille` - gnlTester passa 100%
- [ ] `make sloquet` - 42test-gnl passa sem leaks
- [ ] `norminette src/*.c include/*.h` - norminette OK
- [ ] Verificar que `get_next_line.c` na raiz está atualizado

## 📈 Resultados Esperados

### ✅ Implementação Atual

```
gnlTester (Tripouille):
✅ BUFFER_SIZE=1: 100% (2 timeouts esperados em big_line_*)
✅ BUFFER_SIZE=42: 100%
✅ BUFFER_SIZE=10M: 100%

42test-gnl (sloquet):
✅ BUFFER_SIZE=0: 100%
✅ BUFFER_SIZE=1: 100%
✅ BUFFER_SIZE=2: 100%
✅ BUFFER_SIZE=42: 100%
✅ BUFFER_SIZE=42000: 100%
✅ Memory leaks: 0 em todos os testes
✅ Norminette: OK
```

## 🎯 Dicas

1. **Teste com BUFFER_SIZE=1 primeiro** - se funcionar com buffer mínimo, funcionará com qualquer tamanho
2. **Use valgrind sempre** - `make sloquet` já faz isso automaticamente
3. **Não modifique os testers** - eles são padrão da comunidade 42
4. **Mantenha os arquivos da raiz atualizados** - são eles que você deve submeter no Git da 42

## 📚 Recursos Adicionais

- [gnlTester Wiki](https://github.com/Tripouille/gnlTester/wiki)
- [42 Cursus - get_next_line](https://harm-smits.github.io/42docs/projects/get_next_line)
- [Memory leaks tutorial](https://valgrind.org/docs/manual/quick-start.html)
