#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

#include<bits/stdc++.h>

using namespace std;


class Polinom {
private:
    int nrelemente;                                 ///numarul de elemente
    double *coeficienti;                            ///vectorul de coeficienti double;

public:
    Polinom (int nrelemente, double *coeficienti);  ///constructor initializare
    Polinom (Polinom&);                             ///constructor copiere
    ~Polinom ();                                    ///destructor
    double valoare(int x);                          ///metoda pentru calculul valorii unui polinom intr-un punct
    void CitireMemorareAfisare(int &pcurent,bool *Exista,Polinom *P[]); ///metoda publica pentru citirea a n obiecte,memorarea si afisarea acestora
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, Polinom& z);  ///supraincarcare pe >>
    friend ostream& operator<<(ostream &out, Polinom& z); ///supraincarcare pe <<


    Polinom& operator=(Polinom &z); ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)
    friend Polinom& operator+(Polinom& z1, Polinom& z2); ///suma a doua polinoame,implementata prin supraincarcarea operatorului +
    friend Polinom& operator-(Polinom& z1, Polinom& z2); ///diferenta a doua polinoame,implementata prin supraincarcarea operatorului -
    friend Polinom& operator*(Polinom& z1, Polinom& z2); ///produsul a doua polinoame,implementat prin supraincarcarea operatorului *
};

Polinom::Polinom(int nrelemente = 0, double *coeficienti=NULL)
{

    this->nrelemente = nrelemente;
    this->coeficienti=new double [nrelemente];

}

Polinom::Polinom(Polinom &z){
    this->nrelemente = z.nrelemente;
    this->coeficienti = z.coeficienti;
}

Polinom::~Polinom(){
    this->nrelemente=0;
    delete[] coeficienti;
}

double Polinom::valoare(int x){
    double val=0;
    for(int i=0;i<nrelemente;i++)
    {
        val=val+coeficienti[i]*pow(x,i);
    }
    return val;
}

void Polinom::CitireMemorareAfisare(int &pcurent,bool *Exista,Polinom *P[])
{
    int nrpolinoame,grad;
            cout<<"Introduceti numarul de polinoame"<<endl;
            cin>>nrpolinoame;

            if(nrpolinoame>0)
            {
                for(int i=pcurent;i<pcurent+nrpolinoame;i++)
                {
                    cout<<"Introduceti gradul polinomului numarul "<<i-pcurent+1<<endl;
                    cin>>grad;
                    P[i] = new Polinom(grad+1);
                    cin>>*P[i];
                    Exista[i]=true;
                }

                cout<<"Polinoamele sunt:"<<endl;
                for(int i=pcurent;i<pcurent+nrpolinoame;i++)
                    cout<<*P[i];

                    pcurent=pcurent+nrpolinoame;
            }
            else
                cout<<"Nu se pot citi "<<nrpolinoame<<" polinoame"<<endl;



}

void Polinom::citire(istream &in){
    for(int i=nrelemente;i>0;i--)
    {
        cout<<"Cititi coeficientul lui X^"<<i-1<<endl;
        cin>>coeficienti[i-1];
    }
}
istream& operator>>(istream& in,Polinom& z){
    z.citire(in);
    return in;
}

void Polinom::afisare(ostream &out){
   for(int i=nrelemente-1;i>=1;i--)
   {
        cout<<coeficienti[i]<<"X^"<<i<<" + ";
   }
        cout<<coeficienti[0]<<endl;
}
ostream& operator<<(ostream& out, Polinom& z){
    z.afisare(out);
    return out;
}

Polinom& Polinom::operator=(Polinom &z){
    nrelemente=z.nrelemente;
    coeficienti=z.coeficienti;
}
inline Polinom& operator+(Polinom &z1, Polinom& z2){
    int nrelm,n;

    if (z1.nrelemente >= z2.nrelemente)
    {
        nrelm=z1.nrelemente;
        n = z2.nrelemente;
    }

    else
    {
        nrelm=z2.nrelemente;
        n = z1.nrelemente;
    }

    Polinom *z = new Polinom(nrelm);

    for(int i = 0; i < n; i++)
    {
        z->coeficienti[i] = z1.coeficienti[i] + z2.coeficienti[i];
    }

    if (z1.nrelemente > z2.nrelemente)
    {
        z->nrelemente = z1.nrelemente;

        for(int i=n;i<z->nrelemente;i++)
        z->coeficienti[i]=z1.coeficienti[i];
    }

    else
    {
        z->nrelemente = z2.nrelemente;

        for(int i=n; i < z->nrelemente; i++)
        z->coeficienti[i]=z2.coeficienti[i];
    }

    return *z;
}

inline Polinom& operator-(Polinom &z1, Polinom& z2){
    int nrelm,n;

    if (z1.nrelemente >= z2.nrelemente)
    {
        nrelm=z1.nrelemente;
        n = z2.nrelemente;
    }

    else
    {
        nrelm=z2.nrelemente;
        n = z1.nrelemente;
    }

    Polinom *z = new Polinom(nrelm);

    for(int i = 0; i < n; i++)
    {
        z->coeficienti[i] = z1.coeficienti[i] - z2.coeficienti[i];
    }

    if (z1.nrelemente > z2.nrelemente)
    {
        z->nrelemente = z1.nrelemente;

        for(int i=n;i<z->nrelemente;i++)
        z->coeficienti[i]=z1.coeficienti[i];
    }

    else
    {
        z->nrelemente = z2.nrelemente;

        for(int i=n; i < z->nrelemente; i++)
        z->coeficienti[i]=-z2.coeficienti[i];
    }

    return *z;
}

inline Polinom& operator*(Polinom &z1, Polinom& z2){
    int nrelm,n;

    nrelm=z1.nrelemente+z2.nrelemente;


    Polinom *z = new Polinom(nrelm);
    for(int i=0;i<nrelm;i++)
        z->coeficienti[i]=0;


    for(int i=0;i<z1.nrelemente;i++)
        for(int j=0;j<z2.nrelemente;j++)
            z->coeficienti[i+j]=z->coeficienti[i+j]+z1.coeficienti[i]*z2.coeficienti[j];

    for(int i=nrelm-1;i>=1;i--)
        if(z->coeficienti[i]==0)            // daca coeficientul puterii e 0 nu se va mai afisa la final
            z->nrelemente=z->nrelemente-1;
        else if(z->coeficienti[i]>0)
            break;

    return *z;
}


void menu_output(int pcurent)
{
    cout<<"\n Vasile Andrei-Valentin 211 - Proiect - Clasa Polinom: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    if(pcurent>0)
    {
        cout<<"Polinoame citite: ";
        for(int i=1;i<=pcurent;i++)
            cout<<"P"<<i<<" ";
        cout<<endl;
    }
    else
        cout<<"Nu s-a citit inca niciun polinom"<<endl;
    cout<<"\n";
    cout<<"1. Citire Polinom"; cout<<"\n";
    cout<<"2. Afisare Polinom"; cout<<"\n";
    cout<<"3. Citire si afisare pentru mai multe polinoame"; cout<<"\n";
    cout<<"4. Valoarea polinomului intr-un punct"; cout<<"\n";
    cout<<"5. Suma a doua polinoame"; cout<<"\n";
    cout<<"6. Diferenta a doua polinoame"; cout<<"\n";
    cout<<"7. Produsul a doua polinoame"; cout<<"\n";

    cout<<endl;
    cout<<"0. Iesire."; cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int x,nr,pcurent=0;
    bool Exista[50] = { false };
    Polinom *P[50] = { NULL };

    do
    {
        menu_output(pcurent);

        cout<<"\nIntroduceti numarul actiunii: ";
        scanf("%d", &option);

        if (option==1)
        {
            int grad;
            cout<<"Introduceti gradul polinomului numarul "<<pcurent+1<<endl;
            cin>>grad;
            P[pcurent] = new Polinom(grad+1);
            cin>>*P[pcurent];
            Exista[pcurent]=true;
            pcurent++;
        }


        if (option==2)
        {
            int j;
            cout<<"Introduceti numarul polinomului care trebuie afisat ";
            cin>>j;
            if (Exista[j-1]==true && j>0)
            cout<<*P[j-1];
            else
            cout<<"Polinomul cu numarul "<<j<<" nu a fost citit";
        }


        if(option==3)
        {
           P[pcurent]->CitireMemorareAfisare(pcurent,Exista,P);
        }


        if (option==4)
        {
            int k;
            int x;
            cout<<"Introduceti numarul polinomului pentru care sa se calculeze valoarea ";
            cin>>k;
            if (Exista[k-1]==true && k > 0)
            {
                cout<<"Introduceti valoarea lui X pentru care sa se calculeze polinomul ";
                cin>>x;
                cout<<P[k-1]->valoare(x);
            }
            else
            cout<<"Polinomul cu numarul "<<k<<" nu a fost citit";
        }


        if (option==5)
        {
            int unu,doi;
            cout<<"Introduceti numerele Polinoamelor pe care vreti sa le adunati"<<endl;
            cout<<"Numarul primul Polinom = ";
            cin>>unu;

            if (Exista[unu-1]==true  && unu>0)
            {
                cout<<"Numarul celui de-al doilea Polinom = ";
                cin>>doi;
                if (Exista[doi-1]==true  && doi>0)
                    cout<<"P"<<unu<<" + P"<<doi<<" = "<<*P[unu-1]+*P[doi-1];
                else
                    cout<<"Polinomul cu numarul "<<doi<<" nu a fost citit";
            }
            else
                cout<<"Polinomul cu numarul "<<unu<<" nu a fost citit";
        }


        if (option==6)
        {
            int unu,doi;
            cout<<"Introduceti numerele Polinoamelor intre care sa se faca diferenta"<<endl;
            cout<<"Numarul primul Polinom = ";
            cin>>unu;

            if (Exista[unu-1]==true && unu>0)
            {
                cout<<"Numarul celui de-al doilea Polinom = ";
                cin>>doi;
                if (Exista[doi-1]==true  && doi>0)
                cout<<"P"<<unu<<" - P"<<doi<<" = "<<*P[unu-1]-*P[doi-1];
                else
                    cout<<"Polinomul cu numarul "<<doi<<" nu a fost citit";
            }
            else
                cout<<"Polinomul cu numarul "<<unu<<" nu a fost citit";
        }


        if (option==7)
        {
           int unu,doi;
            cout<<"Introduceti numerele Polinoamelor pe care vreti sa le inmultiti"<<endl;
            cout<<"Numarul primul Polinom = ";
            cin>>unu;

            if (Exista[unu-1]==true  && unu>0)
            {
                cout<<"Numarul celui de-al doilea Polinom = ";
                cin>>doi;
                if (Exista[doi-1]==true  && doi>0)
                    cout<<"P"<<unu<<" * P"<<doi<<" = "<<*P[unu-1] * *P[doi-1];
                else
                    cout<<"Polinomul cu numarul "<<doi<<" nu a fost citit";
            }
            else
                cout<<"Polinomul cu numarul "<<unu<<" nu a fost citit";
        }

        if (option==0)
        {
            cout<<endl;
            cout<<"EXIT!"<<endl;

        for(int i=0;i<50;i++)
            if(P[i]!= NULL)
                delete P[i];
        }

        if (option<0||option>7)
        {
            cout<<endl;
            cout<<"Selectie invalida"<<endl;
        }
        cout<<endl;
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}


int main()
{
    menu();
    return 0;
}
