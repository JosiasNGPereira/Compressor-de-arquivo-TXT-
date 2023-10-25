#include <iostream>
#include "lde_modificado.hpp"
#include <fstream>

using namespace std;

#define TAM 256

void inicializar(letra <char>r[TAM]){
    for(int i=0;i<TAM;i++){
        r[i].info=NULL;
    }
}
void mostrarQtdLetras(letra <char> r[TAM]){
    int cont=0;
    for(int i=0;i<TAM;i++){
        if(r[i].info!=NULL){
            cont++;
        }
    }
    for(int i=0;i<cont;i++){
        cout << "Letra: " << r[i].info << " - Quantidade: " << r[i].cont << endl;
    }
}
void contarLetras(string texto, letra <char> r[TAM]){
    int cont=0;
    int aux = texto.length();
    for(int i=0;i<aux;i++){
        bool flag=false;
        for(int j=0;j<TAM;j++){
            if(r[j].info == texto[i]){
                r[j].cont++;
                flag=true;
            }
        }
        if(flag==false){
            r[cont].info = texto[i];
            r[cont].cont = 1;
            cont++;
        }
    }
}

void transformar_LDE( letra <char> vetor_letra[TAM], LDE <char> &lista){
    for(int i=0;i<TAM;i++){
        if(vetor_letra[i].cont >0){
            letra <char> *letra_aux = new letra <char>;
            letra_aux->info = vetor_letra[i].info;
            letra_aux->cont = vetor_letra[i].cont;
            inserirLDE(lista,letra_aux);
        };
    }
}

letra <char>juntar_dupla(LDE <char> &lista){
    letra <char> *letra_aux = new letra <char>;

    letra_aux->cont=lista.comeco->info->cont+lista.comeco->eloP->info->cont;
    letra_aux->eloleft=lista.comeco->info;
    letra_aux->eloright=lista.comeco->eloP->info;
    letra_aux->info=NULL;

    return letra <char> (*letra_aux);
}

void calcular_dupla(LDE <char> &lista){

    while(lista.comeco!=lista.fim){
        letra <char> *letra_aux = new letra <char>;
        *letra_aux=juntar_dupla(lista);
        retirarLDE(lista,lista.comeco);
        retirarLDE(lista,lista.comeco);
        inserirLDE(lista,letra_aux);
    };

};
template <typename T>
bool transformar_binario(letra <T> *raiz, char valor, string &binario, bool &flag){

    if( raiz == NULL ) return false;
    if( raiz->info == valor ){
        flag = true;
        return true;
    };
    if( raiz->eloleft!=NULL ){
        transformar_binario(raiz->eloleft, valor, binario, flag);
        if(flag){
            binario = binario + "0";
            return true;
        };
    }
    if( raiz->eloright!=NULL ){
        transformar_binario(raiz->eloright, valor, binario, flag);
        if(flag){
            binario = binario + "1";
            return true;
        };
    }
}
void inverter_binario(string &binario){

    string aux;
    for (int var = binario.length()-1; var >=0; --var) {
        aux+=binario[var];
    }
    binario = aux;
}
static int cont =0;

bool escrever_texto(letra <char>lista, string binario ){

    if(lista.info != NULL){
        cout<<lista.info;
        return true;
    }
    if(binario[cont] == '1' ){
        cont++;
        escrever_texto(*lista.eloright, binario);

    }
    else if(binario[cont]=='0'){
        cont++;
        escrever_texto(*lista.eloleft, binario);

    }
}
void percorrer_arvore(letra <char> lista, string binario){
    while(cont<binario.length()){
        escrever_texto(lista, binario);
    }
}
int main(){

    letra <char> *vetor_letras = new letra <char> [TAM];
    int opc=0;
    string texto = "", binario= "";
    bool flag = false;
    LDE <char>lista;

    inicializar(vetor_letras);
    inicializarLDE(lista);

    ifstream meu_arquivo;
    string frase;
    meu_arquivo.open("etherium.txt");
    while(meu_arquivo.eof()==false){
        getline(meu_arquivo, frase);
    };

    do{
        switch (opc) {
        case 0:
            cout<<endl;
            cout<<"\tCOMPRESSOR DE ARQUIVO .TXT "<<endl<<endl
            <<"\t1 - ESCREVER TEXTO"<<endl
            <<"\t2 - ESCOLHER TEXTOS"<<endl;
            cin>>opc;
            cin.ignore();
            break;
        case 1:
            cout<<"DIGITE SEU TEXTO: "<<endl;
            getline(cin, texto);
            cout<<endl;
            contarLetras(texto, vetor_letras);
            mostrarQtdLetras(vetor_letras);
            transformar_LDE(vetor_letras,lista);
            calcular_dupla(lista);
            for (int i = 0; i < texto.length(); ++i) {
                string binario_aux="";
                transformar_binario(lista.comeco->info,texto[i],binario_aux,flag);
                inverter_binario(binario_aux);
                flag = false;
                binario += binario_aux;
            }
            cout<<endl<<"CODIGO BINARIO: "<<binario<<endl;
            cout<<endl<<"CODIGO BINARIO REMONTADO: ";
            percorrer_arvore(*lista.comeco->info,binario);
            cout<<endl<<endl;
            opc=0;
            system("PAUSE");
            system("CLS");
            break;
        case 2:
            contarLetras(frase, vetor_letras);
            mostrarQtdLetras(vetor_letras);
            transformar_LDE(vetor_letras,lista);
            inicializar(vetor_letras);
            calcular_dupla(lista);
            for (int i = 0; i < frase.length(); ++i) {
                string binario_aux="";
                transformar_binario(lista.comeco->info,frase[i],binario_aux,flag);
                inverter_binario(binario_aux);
                flag = false;
                binario += binario_aux;
            }
            cout<<endl<<"CODIGO BINARIO: "<<binario<<endl;
            cout<<endl<<"CODIGO BINARIO REMONTADO: ";
            percorrer_arvore(*lista.comeco->info,binario);
            cout<<endl<<endl;
            opc=0;
            system("PAUSE");
            system("CLS");
            break;
        default:
            cout<<"OPCAO INVALIDA !"<<endl;
            system("PAUSE");
            system("CLS");
            opc= 0;
            break;
        }
    }while(opc!=5);

    return 0;
}
