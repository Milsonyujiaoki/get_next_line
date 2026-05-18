# ─── Identidade do projeto ───────────────────────────────────────────────────
NAME         = libgetnextline
STATIC_LIB   = $(NAME).a
LIST_NAME    = libgetnextline_list
LIST_LIB     = $(LIST_NAME).a
SHARED_LIB   = build/shared/$(NAME).so.1.0.1
SHARED_SONAME = $(NAME).so.1
SHARED_LINK  = $(NAME).so

# ─── Compilador / flags ──────────────────────────────────────────────────────
CC      = cc
AR      = ar
ARFLAGS = rcs
BUFFER_SIZE ?= 42
CFLAGS  = -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)

# ─── Diretórios ──────────────────────────────────────────────────────────────
SRC_DIR  = src
INC_DIR  = include
OBJ_DIR  = build/obj
TEST_BINS_DIR = build/tests
TEST_DIR = tests

# ─── Fontes ──────────────────────────────────────────────────────────────────
# abordagem remainder (padrão — submeter)
SRC_REM  = $(SRC_DIR)/get_next_line.c
OBJ_REM  = $(OBJ_DIR)/get_next_line.o

# abordagem linked-list (alternativa)
SRC_LIST = $(SRC_DIR)/gnl_list.c $(SRC_DIR)/slist.c
OBJ_LIST = $(OBJ_DIR)/gnl_list.o $(OBJ_DIR)/slist.o

# ─── Targets principais ──────────────────────────────────────────────────────
.PHONY: all list shared test test_list clean fclean re re_list

all: $(STATIC_LIB)
	@echo "→ biblioteca remainder: $(STATIC_LIB)"

list: $(LIST_LIB)
	@echo "→ biblioteca linked-list: $(LIST_LIB)"

# ─── Bibliotecas estáticas ───────────────────────────────────────────────────
$(STATIC_LIB): $(OBJ_REM)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built static library (remainder): $@"

$(LIST_LIB): $(OBJ_LIST)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built static library (linked-list): $@"

# ─── Biblioteca compartilhada (remainder) ────────────────────────────────────
shared: $(SHARED_LIB)
	@cd $(dir $(SHARED_LIB)) && \
	  ln -sf $(notdir $(SHARED_LIB)) $(SHARED_SONAME) && \
	  ln -sf $(notdir $(SHARED_LIB)) $(SHARED_LINK)
	@echo "Built shared library: $(SHARED_LIB)"

$(SHARED_LIB): $(SRC_REM)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -fPIC -shared \
	  -Wl,-soname,$(SHARED_SONAME) \
	  -I$(INC_DIR) $^ -o $@

# ─── Objetos ─────────────────────────────────────────────────────────────────
$(OBJ_DIR)/get_next_line.o: $(SRC_DIR)/get_next_line.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/gnl_list.o: $(SRC_DIR)/gnl_list.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/slist.o: $(SRC_DIR)/slist.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# ─── Testes ──────────────────────────────────────────────────────────────────
# make test              → compila e executa com abordagem remainder
# make test_list         → compila e executa com abordagem linked-list
# make test BUFFER_SIZE=1 → testa com buffer de 1 byte

test: $(STATIC_LIB) $(TEST_DIR)/test_getnextline.c
	@mkdir -p $(TEST_BINS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) \
	  $(TEST_DIR)/test_getnextline.c $(STATIC_LIB) -o $(TEST_BINS_DIR)/test_gnl
	@echo "─────────────────────────────────────────"
	@echo "Rodando testes — abordagem remainder"
	@echo "─────────────────────────────────────────"
	./$(TEST_BINS_DIR)/test_gnl

test_list: $(LIST_LIB) $(TEST_DIR)/test_getnextline.c
	@mkdir -p $(TEST_BINS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) \
	  $(TEST_DIR)/test_getnextline.c $(LIST_LIB) -o $(TEST_BINS_DIR)/test_gnl_list
	@echo "─────────────────────────────────────────"
	@echo "Rodando testes — abordagem linked-list"
	@echo "─────────────────────────────────────────"
	./$(TEST_BINS_DIR)/test_gnl_list

# ─── Limpeza ─────────────────────────────────────────────────────────────────
clean:
	rm -rf $(OBJ_DIR)
	@echo "Objetos removidos"

re:      fclean all
re_list: fclean list

# ─── Testers externos ────────────────────────────────────────────────────────
.PHONY: prepare-testers clean-testers tripouille sloquet testers

# Prepara arquivos na raiz do projeto para testers externos
prepare-testers:
	@echo "Arquivos prontos na raiz do projeto ✓"

# gnlTester (Tripouille)
tripouille: prepare-testers
	@echo "════════════════════════════════════════════"
	@echo "  Rodando gnlTester (Tripouille)"
	@echo "════════════════════════════════════════════"
	@cd gnlTester && sed -i 's/clang++/g++/g' Makefile && $(MAKE) m
	@echo ""
	@echo "Testes mandatory concluídos ✓"

# 42test-gnl (sloquet)
sloquet: prepare-testers
	@echo "════════════════════════════════════════════"
	@echo "  Rodando 42test-gnl (sloquet)"
	@echo "════════════════════════════════════════════"
	@cd 42test-gnl && $(MAKE) all
	@echo ""
	@echo "Testes sloquet concluídos ✓"

# Roda ambos os testers
testers: tripouille sloquet
	@echo ""
	@echo "════════════════════════════════════════════"
	@echo "  Todos os testers executados com sucesso!"
	@echo "════════════════════════════════════════════"

# Remove arquivos copiados para testers
clean-testers:
	@cd gnlTester 2>/dev/null && $(MAKE) fclean || true
	@cd 42test-gnl 2>/dev/null && $(MAKE) fco || true
	@echo "Testers limpos (arquivos de submissão preservados)"

# Limpa tudo incluindo testers
fclean: clean clean-testers
	rm -f $(STATIC_LIB) $(LIST_LIB)
	rm -f $(TEST_BINS_DIR)/test_gnl $(TEST_BINS_DIR)/test_gnl_list
	rm -f $(SHARED_LIB) \
	      $(dir $(SHARED_LIB))$(SHARED_SONAME) \
	      $(dir $(SHARED_LIB))$(SHARED_LINK)
	@echo "Tudo limpo"
