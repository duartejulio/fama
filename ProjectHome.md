A machine learning framework for several tasks.

# People #

## Project Manager ##

Julio Cesar Duarte, PhD

## Developers ##

Felipe de Almeida Oliveira, Undergraduate Student

Joilson Cisne dos Santos, Undergraduate Student

Geraldo Avelino de Oliveira Neto, Undergraduate Student

# Documentation #

In FAMA, one must use its four main abstract classes, which are:

## Corpus ##

This class deals with the datasets. In order to use it, one must
implement a descendant class of corpus that implements two pure virtual
methods

**carregarCorpus:**

This method is responsible for loading the corpus in to a matrix structure
of the data.

**gravarCorpus:**

This method is responsible for saving the contents of the data structure of
the matrix into a file.

In FAMA, a class CorpusMatrix is already implemented that can read from common text
dataset files.

## Avaliador ##

This class is used in order to evaluate the performance of a classifier applied
to a data set. In order to use it, one must
implement a descendant class of avaliador that implements one pure virtual
method

**calcularDesempenho:**

This method is responsible evaluating the performance of the classifier, by comparing
the values of two attributes of the corpus, the correct answer and the guessed answer.

In FAMA, a class AvaliadorAcuracia is already implemented that can evaluate the accuracy of the classifier.

## Treinador ##

This is the base class for the machine learning that will be used.

In order to use it, one must implement a pure virtual method called

**executarTreinamento:**

which using the provided corpus generates a classifier
by applying the machine learning technique wanted.

Several Machine Learning algorithms are already implemented, which are

**HMM**

**TBL**

**Logistic Regression**

**Linear Regression**

**Decision Stump**

## Classificador ##

This is the base class for the classifier returned by machine learning training process.

In order to use it, one must implement a pure virtual method called

**executarClassificacao:**

which applies the classification to a new provide corpus, by creating a new atribute.

All Classifiers from the machine learning algorithms implemented in FAMA are available.

TODO:

- Add classes for cross validation;

- Add more algorithms, like SVM and C4.5;

- Implement an interface for experimentation.