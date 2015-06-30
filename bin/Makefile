#Variaveis e diretórios

CXX=g++
LIBS=-lm

OBJ_DIR=dir/

CLASS_DIR=../classificador
TREIN_DIR=../treinador
CORPU_DIR=../corpus
AVALI_DIR=../avaliador
VALID_DIR=../validador
TESTE_DIR=../testes

#Arquivos

CLASS_NAMES=classificador classificador_adaboost_m1 classificadorhmm
TREIN_NAMES=treinador treinador_adaboost_m1 hmm
CORPU_NAMES=corpus corpusmatriz
AVALI_NAMES=Avaliador avaliador_prob
VALID_NAMES=validador validadorkdobras
TESTE_NAMES="AdaBoostM1 com HMM"

ALL_FILES=$(addsuffix .o, $(CLASS_NAMES) $(TREIN_NAMES) $(CORPU_NAMES) $(AVALI_NAMES) $(VALID_NAMES) $(TESTE_NAMES))

#Regras

all: teste

teste: $(addprefix $(OBJ_DIR), $(ALL_FILES))
	$(CXX) -o $@ $^ $(LIBS)
	
# Compila os arquivos do Corpus
$(OBJ_DIR)/$(addsuffix .o, $(CORPU_NAMES)): $(addprefix $(CORPU_DIR),$(addsuffix .cpp, $(CORPU_NAMES)))
	$(CXX) -c -o $@ $^ -I$(CORPU_DIR)

# Compila os arquivos do Treinador
$(OBJ_DIR)/$(addsuffix .o, $(TREIN_NAMES)): $(addprefix $(TREIN_DIR),$(addsuffix .cpp, $(TREIN_NAMES)))
	$(CXX) -c -o $@ $^ -I$(CORPU_DIR) -I$(CLASS_DIR) -I$(TREIN_DIR)

# Compila os arquivos do Classificador
$(OBJ_DIR)/$(addsuffix .o, $(CLASS_NAMES)): $(addprefix $(CLASS_DIR),$(addsuffix .cpp, $(CLASS_NAMES)))
	$(CXX) -c -o $@ $^ -I$(CORPU_DIR) -I$(CLASS_DIR)

# Compila os arquivos do Avaliador
$(OBJ_DIR)/$(addsuffix .o, $(AVALI_NAMES)): $(addprefix $(AVALI_DIR),$(addsuffix .cpp, $(AVALI_NAMES)))
	$(CXX) -c -o $@ $^ -I$(AVALI_DIR) -I$(CORPU_DIR)

# Compila os arquivos do Validador
$(OBJ_DIR)/$(addsuffix .o, $(VALID_NAMES)): $(addprefix $(VALID_DIR),$(addsuffix .cpp, $(VALID_NAMES)))
	$(CXX) -c -o $@ $^ -I$(VALID_DIR) -I$(CORPU_DIR) -I$(AVALI_DIR)

# Compila os arquivos de teste
$(OBJ_DIR)/$(addsuffix .o, $(TESTE_NAMES)): $(addprefix $(TESTE_DIR),$(addsuffix .cpp, $(TESTE_NAMES)))
	$(CXX) -c -o $@ $^ -I$(TREIN_DIR) -I$(CLASS_DIR) -I$(VALID_DIR) -I$(CORPU_DIR) -I$(AVALI_DIR)

clean:
	rm -f $(ODIR)/*.o *~
