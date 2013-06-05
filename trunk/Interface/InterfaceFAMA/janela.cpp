#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
    corpus = NULL;
    treinador = NULL;
    treinadorAba3 = NULL;
    avaliador = new AvaliadorAcuracia();
    corpusTeste = NULL;
    classificador = NULL;
    numExperimento = 0;
    importado = false;

    //a adição de novos tipos de Corpus deve ser feita identicamente ao modelo abaixo
    ui->comboBox_corpus->addItem( "CorpusMatriz" );

    //a adição de novos tipos de Classificadores deve ser feita identicamente ao modelo abaixo
    ui->comboBox_metodo->addItem( "Mais Provavel" );
    ui->comboBox_metodo->addItem( "Hidden Markov Model - HMM" );
    ui->comboBox_metodo->addItem( "Transformation Based Learning - TBL" );

    ui->comboBox_metodoTreinador->addItem( "Mais Provavel" );
    ui->comboBox_metodoTreinador->addItem( "Hidden Markov Model - HMM" );
    ui->comboBox_metodoTreinador->addItem( "Transformation Based Learning - TBL" );
    ui->comboBox_metodoClassificador->addItem( "Mais Provavel" );
    ui->comboBox_metodoClassificador->addItem( "Hidden Markov Model - HMM" );
    ui->comboBox_metodoClassificador->addItem( "Transformation Based Learning - TBL" );

    //a adição de novos tipos de Avaliadores deve ser feita identicamente ao modelo abaixo
    ui->comboBox_avaliador->addItem( "Acurácia" );

    //todas as inicializações feitas nos tópicos anteriores devem ter atualizações nos switches de incialização das funções abaixo

    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "Ordem" << "Nome" );
    ui->tableWidget_resultadosValidacao->setHorizontalHeaderLabels( QStringList() << "Experimento" << "Tempo/Resultado" );
}

Janela::~Janela()
{
    delete ui;
    if( corpus != NULL ) delete corpus;
    if( treinador != NULL ) delete treinador;
    if( treinadorAba3 != NULL ) delete treinadorAba3;
    if( avaliador != NULL ) delete avaliador;
    if( corpusTeste != NULL ) delete corpusTeste;
}

void Janela::abrirArquivo()
{
    if( ( s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
    {
        logicaDeAbertura();
        ui->comboBox_metodo->setEnabled( true );
        ui->comboBox_metodoTreinador->setEnabled( true );
        ui->comboBox_metodoClassificador->setEnabled( true );
    }
}

void Janela::logicaDeAbertura()
{
    //coloca seta do mouse em espera
    QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

    QString aux;
    string a = s.toStdString();
    int n, posBarra;

    corpus->carregarArquivo( a );

    if( (unsigned)( posBarra = a.rfind( '/' ) ) != string::npos)
        a = a.substr( posBarra + 1 );

    ui->lineEdit_relatorio->setText( QString::fromStdString( a ) );
    ui->lineEdit_atributos->setText( QString( "%1" ).arg( n = corpus->pegarQtdAtributos() ) );
    ui->lineEdit_instancias->setText( QString( "%1" ).arg( corpus->pegarQtdTotalExemplos() ) );

    //limpador da janela de atributos
    ui->tableWidget_atributos->clearContents();
    ui->comboBox_atributoTreino->clear();
    ui->comboBox_atributoTreino2->clear();

    ui->tableWidget_atributos->setRowCount( n );
    QTableWidgetItem *item;
    for( int i = 0; i < n; ++i )
    {
        item = new QTableWidgetItem( QString( "%1" ).arg( i ) );
        ui->tableWidget_atributos->setItem( i, 0, item );
        item = new QTableWidgetItem( aux = QString( "%1" ).arg( QString::fromStdString(corpus->pegarAtributo(i)) ) );
        ui->tableWidget_atributos->setItem( i, 1, item );
        ui->comboBox_atributoTreino->insertItem( i, aux );
        ui->comboBox_atributoTreino2->insertItem( i, aux );
    }

    //retorna seta normal do mouse
    QApplication::restoreOverrideCursor();
}

void Janela::habilitarBotao(int index)
{
    if( corpus != NULL )
    {
        delete corpus;

        ui->lineEdit_relatorio->setText( "Nenhum" );
        ui->lineEdit_atributos->setText( "Nenhum" );
        ui->lineEdit_instancias->setText( "Nenhum" );
        ui->lineEdit_nome->setText( "Nenhum" );
        ui->lineEdit_tipo->setText( "Nenhum" );
        ui->lineEdit_distintos->setText( "Nenhum" );

        //limpador da janela de atributos
        ui->tableWidget_atributos->clearContents();
        ui->tableWidget_atributos->setRowCount( 0 );

        //limpador da janela de estatistica
        ui->tableWidget_estatistica->clearContents();
        ui->tableWidget_estatistica->setRowCount( 0 );

        ui->comboBox_metodo->setEnabled( false );
        ui->pushButton_start->setEnabled( false );

    }
    switch( index )
    {
        case 0 :
            corpus = NULL;
            ui->pushButton_abrir->setEnabled( false );
            ui->toolButton_construtor->setEnabled( false );
            return;
        case 1 :
            corpus = new CorpusMatrizUI();
            break;
    }
    ui->pushButton_abrir->setEnabled( true );
    ui->toolButton_construtor->setEnabled( true );
}

void Janela::atributoSelecionado( int row, int column )
{
    //coloca seta do mouse em espera
    QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

    int atributo = ui->tableWidget_atributos->item( row, 0 )->text().toInt();
    int i, j, k, distintos, unicos = 0, conjEx = corpus->pegarQtdConjExemplos(), qtdEx, totalSimbolos = corpus->pegarQtdSimbolos(), tam_string, contador = 0;
    double maximo = -999999, minimo = 999999, media, mediaQuadrados, stdDev, auxNum;
    string aux, tipo = "Numerico";
    vector< int > estatistica( totalSimbolos ), indices;
    QTableWidgetItem *item;

    ui->lineEdit_nome->setText( ui->tableWidget_atributos->item( row, 1 )->text() );

    //para definir se o atributo é Nominal ou Numérico varre-se os 10 primeiros Conj. de Exemplos
    for( i = 0; i < conjEx && i < 10; ++i )
    {
        qtdEx = corpus->pegarQtdExemplos( i );
        for( j = 0; j < qtdEx; ++j )
        {
            aux = corpus->pegarSimbolo( corpus->pegarValor( i, j, atributo ) );
            tam_string = aux.size();
            for( k = 0; k < tam_string; ++k )
                if( aux[k] != 44 && aux[k] != 46 && aux[k] != 48 && aux[k] != 49 && aux[k] != 50 && aux[k] != 51 &&
                    aux[k] != 52 && aux[k] != 53 && aux[k] != 54 && aux[k] != 55 && aux[k] != 56 && aux[k] != 57)
                {
                    tipo = "Nominal";
                    break;
                }
            if( tipo == "Nominal" ) break;
        }
        if( tipo == "Nominal" ) break;
    }

    //limpador da janela de estatistica
    ui->tableWidget_estatistica->clearContents();

    //calculo estatistico de Nominal
    if( tipo == "Nominal" )
    {
        ui->tableWidget_estatistica->setHorizontalHeaderLabels( QStringList() << "Label" << "Quantidade" );

        for( i = 0; i < conjEx; ++i )
        {
            qtdEx = corpus->pegarQtdExemplos( i );
            for( j = 0; j < qtdEx; ++j )
                ++estatistica[corpus->pegarValor( i, j, atributo )];
        }

        for( i = 0; i < totalSimbolos; ++i  )
            if( estatistica[i] )
            {
                indices.push_back( i );
                if( estatistica[i] == 1 ) ++unicos;
            }

        distintos = indices.size();

        ui->tableWidget_estatistica->setRowCount( distintos );

        for( i = 0; i < distintos; ++i )
        {
            item = new QTableWidgetItem( QString( "%1" ).arg( QString::fromStdString(corpus->pegarSimbolo( indices[i] ) ) ) );
            ui->tableWidget_estatistica->setItem( i, 0, item );
            item = new QTableWidgetItem( QString( "%1" ).arg( estatistica[indices[i]] ) );
            ui->tableWidget_estatistica->setItem( i, 1, item );
        }
    }

    //calculo estatistico Numerico
    if( tipo == "Numerico" )
    {
        ui->tableWidget_estatistica->setHorizontalHeaderLabels( QStringList() << "Estatística" << "Valor" );

        for( i = 0; i < conjEx; ++i )
        {
            qtdEx = corpus->pegarQtdExemplos( i );
            for( j = 0; j < qtdEx; ++j )
            {
                auxNum = atof( corpus->pegarSimbolo( k = corpus->pegarValor( i, j, atributo ) ).c_str() );
                if( auxNum >= maximo ) maximo = auxNum;
                if( auxNum <= minimo ) minimo = auxNum;
                ++contador;
                media = media*( (contador - 1)/(double)contador ) + auxNum/contador;
                mediaQuadrados = mediaQuadrados*( (contador - 1)/(double)contador ) + auxNum*auxNum/contador;
                ++estatistica[k];
            }
        }
        stdDev = sqrt( mediaQuadrados - ( media*media ) );

        for( i = 0; i < totalSimbolos; ++i  )
            if( estatistica[i] )
            {
                indices.push_back( i );
                if( estatistica[i] == 1 ) ++unicos;
            }

        distintos = indices.size();

        ui->tableWidget_estatistica->setRowCount( distintos + 5 );

        item = new QTableWidgetItem( "Mínimo" );
        ui->tableWidget_estatistica->setItem( 0, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( minimo ) );
        ui->tableWidget_estatistica->setItem( 0, 1, item );

        item = new QTableWidgetItem( "Máximo" );
        ui->tableWidget_estatistica->setItem( 1, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( maximo ) );
        ui->tableWidget_estatistica->setItem( 1, 1, item );

        item = new QTableWidgetItem( "Média" );
        ui->tableWidget_estatistica->setItem( 2, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( media ) );
        ui->tableWidget_estatistica->setItem( 2, 1, item );

        item = new QTableWidgetItem( "Desvio Padrão" );
        ui->tableWidget_estatistica->setItem( 3, 0, item );
        item = new QTableWidgetItem( QString( "%1" ).arg( stdDev ) );
        ui->tableWidget_estatistica->setItem( 3, 1, item );

        item = new QTableWidgetItem( "Número" );
        item->setBackgroundColor( QColor( "green" ) );
        ui->tableWidget_estatistica->setItem( 4, 0, item );
        item = new QTableWidgetItem( "Ocorrências" );
        item->setBackgroundColor( QColor( "green" ) );
        ui->tableWidget_estatistica->setItem( 4, 1, item );

        for( i = 0; i < distintos; ++i )
        {
            item = new QTableWidgetItem( QString( "%1" ).arg( QString::fromStdString(corpus->pegarSimbolo( indices[i] ) ) ) );
            ui->tableWidget_estatistica->setItem( i + 5, 0, item );
            item = new QTableWidgetItem( QString( "%1" ).arg( estatistica[indices[i]] ) );
            ui->tableWidget_estatistica->setItem( i + 5, 1, item );
        }
    }


    ui->lineEdit_tipo->setText( QString::fromStdString( tipo ) );
    ui->lineEdit_distintos->setText( QString( "%1" ).arg( distintos ) );
    ui->lineEdit_unicos->setText( QString( "%1" ).arg( unicos ) );

    //retorna seta normal do mouse
    QApplication::restoreOverrideCursor();
}

void Janela::definirParametros()
{
    //Janela construida na classe Corpus por um método virtual
    Corpus *temp = corpus->construirJanela( &popUp );
    if( temp != corpus )
    {
        delete corpus;
        corpus = temp;
        if( s != "" ) logicaDeAbertura();
    }
}

void Janela::definirParametrosTreinador()
{
    //Janela construida na classe Treinador por um método virtual
    Treinador *temp = treinador->construirJanela( &popUp, *corpus );
    if( temp != treinador )
    {
        if( treinador != dados.restaurarTreinador() && treinador != treinadorAba3 ) delete treinador; //verifica se treinador nao foi exportado
        treinador = temp;
    }
}

void Janela::definirParametrosTreinadorAba3()
{
    //Janela construida na classe Treinador por um método virtual
    Treinador *temp = treinadorAba3->construirJanela( &popUp, *corpus );
    if( temp != treinadorAba3 )
    {
        if( treinadorAba3 != dados.restaurarTreinador() && treinadorAba3 != treinador )delete treinadorAba3;
        treinadorAba3 = temp;
    }
}

void Janela::escolherMetodo( int index )
{
    if( treinador != NULL && treinador != dados.restaurarTreinador() && treinador != treinadorAba3 ) delete treinador; //verifica se treinador nao foi exportado
    switch( index )
    {
        case 0 :
            treinador = NULL;
            ui->toolButton_treinador->setEnabled( false );
            ui->pushButton_start->setEnabled( false );
            ui->pushButton_exportarDados->setEnabled( false );
            return;
        case 1 :
            treinador = new MaisProvavelUI();
            break;
        case 2 :
            treinador = new HMMUI();
            break;
        case 3 :
            treinador = new TBLUI();
            break;
    }
    ui->toolButton_treinador->setEnabled( true );
    ui->pushButton_start->setEnabled( true );
    ui->pushButton_exportarDados->setEnabled( true );
    if( !importado ) definirParametrosTreinador();
    importado = false;
}

void Janela::escolherTreinador( int index )
{
    if( treinadorAba3 != NULL && treinadorAba3 != treinador && treinadorAba3 != dados.restaurarTreinador() ) delete treinadorAba3;
    switch( index )
    {
        case 0 :
            treinadorAba3 = NULL;
            ui->toolButton_treinador2->setEnabled( false );
            ui->pushButton_guardarConhecimento->setEnabled( false );
            ui->pushButton_treinar->setEnabled( false );
            return;
        case 1 :
            treinadorAba3 = new MaisProvavelUI();
            break;
        case 2 :
            treinadorAba3 = new HMMUI();
            break;
        case 3 :
            treinadorAba3 = new TBLUI();
            break;
    }
    ui->toolButton_treinador2->setEnabled( true );
    ui->pushButton_treinar->setEnabled( true );
    if( !importado )definirParametrosTreinadorAba3();
    importado = false;
}

void Janela::escolherClassificador( int index )
{
    if( classificador != NULL ) delete classificador;
    if( !index )
    {
        classificador = NULL;
        ui->pushButton_carregarConhecimento->setEnabled( false );
        ui->pushButton_classificar->setEnabled( false );
        return;
    }
    ui->pushButton_carregarConhecimento->setEnabled( true );
}

void Janela::escolherAvaliador( int index )
{
    if( avaliador != NULL && avaliador != dados.restaurarAvaliador() ) delete avaliador; //verifica se avaliador nao foi exportado
    switch( index )
    {
        case 0 :
            avaliador = new AvaliadorAcuracia();
            break;
    }
}

void Janela::executarValidacao()
{
    //inicialização do temporizador
    clock_t t0;

    //tempo local para nome do atributo classificado (unico)
    time_t tempoLocal;
    time( &tempoLocal );

    Validador *validador;
    vector< vector< float > > resultados;

    if(ui->radioButton_treino->isChecked())
    {
        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        validador = new ValidadorTreino(*avaliador);
        t0 = clock();
        resultados = validador->executarExperimento( *treinador, *corpus, corpus->pegarPosAtributo( ui->comboBox_atributoTreino->currentText().toStdString() ), corpus->criarAtributo( ctime( &tempoLocal ) ) );
    }
    else if(ui->radioButton_teste->isChecked())
    {
        if( corpusTeste == NULL ) return;

        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        validador = new ValidadorTeste( *avaliador, *corpusTeste );

        t0 = clock();
        resultados = validador->executarExperimento( *treinador, *corpus, corpus->pegarPosAtributo( ui->comboBox_atributoTreino->currentText().toStdString() ), corpusTeste->criarAtributo( ctime( &tempoLocal ) ) );
    }
    else if(ui->radioButton_kDobras->isChecked())
    {
        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        validador = new ValidadorKDobras(*avaliador, ui->spinBox_kDobras->value());
        t0 = clock();
        resultados = validador->executarExperimento( *treinador, *corpus, corpus->pegarPosAtributo( ui->comboBox_atributoTreino->currentText().toStdString() ), corpus->criarAtributo( ctime( &tempoLocal ) ) );
    }
    else if(ui->radioButton_divisao->isChecked())
    {
        //começo da criação da interface de pop Up para definir numero de Iterações do método
        ModeloParam model;
        int ok;
        model.inserirDados( 0, 0, "Número de Iterações:" );
        popUp.ajustarModelo( model );

        QSpinBox *sbox = new QSpinBox();
        sbox->setMinimum( 1 );
        model.inserirDados( 0, 1, popUp, sbox );

        ok = popUp.iniciarDialog();
        if( !ok ) return;
        //fim da interface

        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        validador = new ValidadorDivisao(*avaliador, sbox->value(), (float)ui->doubleSpinBox_divisao->value()/100);
        t0 = clock();
        resultados = validador->executarExperimento( *treinador, *corpus, corpus->pegarPosAtributo( ui->comboBox_atributoTreino->currentText().toStdString() ), corpus->criarAtributo( ctime( &tempoLocal ) ) );
    }

    QTableWidgetItem *item;
    int i, tam_resultados = resultados.size(), antigoTam = ui->tableWidget_resultadosValidacao->rowCount();

    //limpa tabela de resultados
    //ui->tableWidget_resultadosValidacao->clearContents();

    ui->tableWidget_resultadosValidacao->setRowCount( antigoTam + tam_resultados + 1 );

    item = new QTableWidgetItem( QString( "Experimento %1" ).arg( ++numExperimento ) );
    item->setBackgroundColor( QColor( "green" ) );
    ui->tableWidget_resultadosValidacao->setItem( antigoTam, 0, item );
    item = new QTableWidgetItem( QString( "%1" ).arg( ( ( double )( clock() - t0 )/(double)CLOCKS_PER_SEC ) ) + " s" );
    item->setBackgroundColor( QColor( "green" ) );
    ui->tableWidget_resultadosValidacao->setItem( antigoTam, 1, item );

    for( i = 0; i < tam_resultados; ++i )
    {
        item = new QTableWidgetItem( QString( "Resultado %1" ).arg( i + 1 ) );
        ui->tableWidget_resultadosValidacao->setItem( antigoTam + i + 1, 0, item );
        item = new QTableWidgetItem( QString( "%1%" ).arg( resultados[i][0]*100 ) );
        ui->tableWidget_resultadosValidacao->setItem( antigoTam + i + 1, 1, item );
    }

    delete validador;

    //retorna seta normal do mouse
    QApplication::restoreOverrideCursor();
}

void Janela::abrirArquivoTeste()
{
    if( !ui->radioButton_teste->isChecked() ) return;

    string t;
    if( ( t = QFileDialog::getOpenFileName( this, "Abrir Corpus de Teste","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ).toStdString() ) == "" )
    {
        ui->radioButton_treino->setChecked( true );
        return;
    }

    //gera uma pop Up para configuração do Corpus
    corpusTeste = corpus->construirJanela( &popUp );
    if( corpusTeste == corpus )
    {
        corpusTeste = NULL;
        ui->radioButton_treino->setChecked( true );
        return;
    }

    QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );
    corpusTeste->carregarArquivo( t );
    QApplication::restoreOverrideCursor();
}

void Janela::treinar()
{
     //coloca seta do mouse em espera
    QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

    clock_t t0 = clock();

    classificador = treinadorAba3->executarTreinamento( *corpus, corpus->pegarPosAtributo( ui->comboBox_atributoTreino2->currentText().toStdString() ) );
    ui->pushButton_guardarConhecimento->setEnabled( true );

    ui->lineEdit_tempoTreino->setText( QString( "%1" ).arg( ( ( double )( clock() - t0 )/(double)CLOCKS_PER_SEC )/corpus->pegarQtdTotalExemplos()*1000 ) + " ms/exemplo" );

    //retorna seta normal do mouse
    QApplication::restoreOverrideCursor();
}

void Janela::classificar()
{
    //coloca seta do mouse em espera
    QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

    clock_t t0 = clock();

    classificador->executarClassificacao( *corpus, corpus->criarAtributo( ui->lineEdit_novoAtributo->text().toStdString(), "" ) );
    ui->pushButton_gravarCorpus->setEnabled( true );

    ui->lineEdit_tempoClassificacao->setText( QString( "%1" ).arg( ( ( double )( clock() - t0 )/(double)CLOCKS_PER_SEC )/corpus->pegarQtdTotalExemplos()*1000 ) + " ms/exemplo" );

    //retorna seta normal do mouse
    QApplication::restoreOverrideCursor();
}

void Janela::gravarCorpus()
{
    if( ( s = QFileDialog::getOpenFileName( this, "Gravar Corpus","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
    {
        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        corpus->gravarArquivo( s.toStdString() );

        //retorna seta normal do mouse
        QApplication::restoreOverrideCursor();
    }
}

void Janela::guardarConhecimento()
{
    if( ( s = QFileDialog::getOpenFileName( this, "Gravar Conhecimento","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
    {
        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        classificador->gravarConhecimento( s.toStdString() );

        //retorna seta normal do mouse
        QApplication::restoreOverrideCursor();
    }
}

void Janela::carregarConhecimento()
{
    if( ( s = QFileDialog::getOpenFileName( this, "Carregar Conhecimento","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
    {
        //coloca seta do mouse em espera
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        switch( ui->comboBox_metodoClassificador->currentIndex() )
        {
            case 1 :
                classificador = new ClassificadorMaisProvavel( s.toStdString() );
                break;
            case 2 :
                classificador = new ClassificadorHMM( s.toStdString() );
                break;
            case 3 :
                //classificador = new ClassificadorTBL( s.toStdString() );
                break;
        }

        ui->pushButton_classificar->setEnabled( true );

        //retorna seta normal do mouse
        QApplication::restoreOverrideCursor();
    }
}

void Janela::exportarDados()
{
    Treinador *treinadorTemp = dados.restaurarTreinador();
    Avaliador *avaliadorTemp = dados.restaurarAvaliador();

    //delete do treinador e avaliador exportados antigamente
    if( treinadorTemp != NULL && treinadorTemp != treinador && treinadorTemp != treinadorAba3 ) delete treinadorTemp;
    if( avaliadorTemp != NULL && avaliadorTemp != avaliador ) delete avaliadorTemp;


    if(ui->radioButton_treino->isChecked())
        dados.definirDados( treinador, ui->comboBox_metodo->currentText(), 0, -1, avaliador, ui->comboBox_avaliador->currentText(), ui->comboBox_atributoTreino->currentText() );
    else if(ui->radioButton_teste->isChecked())
        dados.definirDados( treinador, ui->comboBox_metodo->currentText(), 1, -1, avaliador, ui->comboBox_avaliador->currentText(), ui->comboBox_atributoTreino->currentText() );
    else if(ui->radioButton_kDobras->isChecked())
        dados.definirDados( treinador, ui->comboBox_metodo->currentText(), 2, ui->spinBox_kDobras->value(), avaliador, ui->comboBox_avaliador->currentText(), ui->comboBox_atributoTreino->currentText() );
    else if(ui->radioButton_divisao->isChecked())
        dados.definirDados( treinador, ui->comboBox_metodo->currentText(), 3, ui->doubleSpinBox_divisao->value(), avaliador, ui->comboBox_avaliador->currentText(), ui->comboBox_atributoTreino->currentText() );

    ui->pushButton_importarDados->setEnabled( true );
    ui->pushButton_importarDadosAba3->setEnabled( true );

    dados.show();
}

void Janela::importarDados()
{
    Treinador *treinadorTemp;
    Avaliador *avaliadorTemp;
    int index;

    switch( dados.restaurarValidador() )
    {
        case 0 :
            ui->radioButton_treino->setChecked( true );
            break;
        case 1 :
            ui->radioButton_teste->setChecked( true );
            break;
        case 2 :
            ui->radioButton_kDobras->setChecked( true );
            ui->spinBox_kDobras->setValue( ( int )dados.restaurarExtra() );
            break;
        case 3 :
            ui->radioButton_divisao->setChecked( true );
            ui->doubleSpinBox_divisao->setValue( dados.restaurarExtra() );
    }

    //seta importado como true somente quando tiver certeza que o slot currentIndexChanged será executado
    if( ui->comboBox_metodo->currentIndex() != ( index = ui->comboBox_metodo->findText( dados.restaurarNomeTr() ) ) )
        importado = true;

    ui->comboBox_metodo->setCurrentIndex( index );
    ui->comboBox_avaliador->setCurrentIndex( ui->comboBox_avaliador->findText( dados.restaurarNomeAv() ) );
    ui->comboBox_atributoTreino->setCurrentIndex( ui->comboBox_atributoTreino->findText( dados.restaurarAtrbTr() ) );

    if( treinador != ( treinadorTemp = dados.restaurarTreinador() ) && treinador != treinadorAba3 && treinador != NULL ) delete treinador;
    if( avaliador != ( avaliadorTemp = dados.restaurarAvaliador() ) && avaliador != NULL ) delete avaliador;
    treinador = treinadorTemp;
    avaliador = avaliadorTemp;

    dados.close();

    ui->pushButton_importarDados->setEnabled( false );
    ui->pushButton_importarDadosAba3->setEnabled( false );
}

void Janela::importarDadosAba3()
{
    int index;

    //seta importado como true somente quando tiver certeza que o slot currentIndexChanged será executado
    if( ui->comboBox_metodoTreinador->currentIndex() != ( index = ui->comboBox_metodoTreinador->findText( dados.restaurarNomeTr() ) ) )
        importado = true;

    ui->comboBox_metodoTreinador->setCurrentIndex( index );
    ui->comboBox_atributoTreino2->setCurrentIndex( ui->comboBox_atributoTreino2->findText( dados.restaurarAtrbTr() ) );

    if( treinadorAba3 != NULL && treinadorAba3 != dados.restaurarTreinador() && treinadorAba3 != treinador ) delete treinadorAba3;
    treinadorAba3 = dados.restaurarTreinador();

    dados.close();

    ui->pushButton_importarDados->setEnabled( false );
    ui->pushButton_importarDadosAba3->setEnabled( false );
}
