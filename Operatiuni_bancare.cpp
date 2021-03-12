#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <bits/stdc++.h>
#include <exception>
using namespace std;

class myexception: public exception
{
    public:
    string err;
    myexception(const string& eroare): err(eroare){}
    virtual ~myexception() throw(){}
  virtual const char* what() const throw()
  {
    return err.c_str();
  }
};

class Cont
{
    public:
    string nume_cont;
    string PIN;
    double Bani;
};
class Banca
{
    public:

    vector<Cont> conturi;
    void executaOperatiune(string const & operatiune);
    Banca(string nume_fisier);
    void afisare_conturi();
};

vector<string> split(string text)
{
    vector<string> cuvinte;
    stringstream verificare(text);
    string aux;
    while(getline(verificare, aux, ' '))
            cuvinte.push_back(aux);
    return cuvinte;
}
Banca::Banca(string  nume_fisier)
{
    int i;
    string cont;
    Cont c;
    ifstream file;
    vector<string> cuvinte;

    file.open(nume_fisier.c_str());

    while(getline(file, cont))
    {

        cuvinte = split(cont);
        c.nume_cont = cuvinte[0];
        c.PIN = cuvinte[1];
        c.Bani = atof(cuvinte[2].c_str());
        conturi.push_back(c);
    }
}

void Banca::executaOperatiune(string const & operatiune)
{
    int i, j;
    bool ok = false;
    vector<string> cuvinte = split(operatiune);
    string exceptie;
    for(i = 0; i < conturi.size(); i++)
        if(conturi[i].nume_cont.compare(cuvinte[1]) == 0)
            ok = true;

    if(!ok)
        throw myexception("Contul " + cuvinte[1] + " nu exista");

    if(cuvinte[0].compare("DEPOZIT") == 0 && ok)
    {
        for(i = 0; i < conturi.size();i++)
            if(conturi[i].nume_cont.compare(cuvinte[1]) == 0)
            {
                if(conturi[i].PIN.compare(cuvinte[2]) == 0)
                {
                    if(atof(cuvinte[3].c_str()) < 10)
                        throw myexception("Suma " + cuvinte[3] + " este prea mica pentru a realiza " + cuvinte[0]);
                    else
                        conturi[i].Bani += atof(cuvinte[3].c_str());
                }
                else
                    throw myexception("Pinul pentru " + cuvinte[1] + " este gresit");
            }

    }

    if(cuvinte[0].compare("RETRAGERE") == 0 && ok)
    {
         for(i = 0; i < conturi.size();i++)
            if(conturi[i].nume_cont.compare(cuvinte[1]) == 0)
            {
                if(conturi[i].PIN.compare(cuvinte[2]) == 0)
                    {
                        if(atof(cuvinte[3].c_str()) < 15)
                            throw myexception("Suma " + cuvinte[3] + " este prea mica pentru a realiza " + cuvinte[0]);
                        else
                            if(conturi[i].Bani < atof(cuvinte[3].c_str()))
                                throw myexception("Contul " + cuvinte[1] + " nu poate retrage " + cuvinte[3]);
                            else
                                conturi[i].Bani -= atof(cuvinte[3].c_str());
                    }

                    else
                        throw myexception("Pinul pentru " + cuvinte[1] + " este gresit");
            }
    }





    if(cuvinte[0].compare("TRANSFER") == 0 && ok)
    {


            for(i = 0; i < conturi.size();i++)
            {
                if(conturi[i].nume_cont.compare(cuvinte[1]) == 0)
                {


                        if(conturi[i].PIN.compare(cuvinte[2]) == 0)
                        {
                            if(atof(cuvinte[4].c_str()) < 50)
                                throw myexception("Suma " + cuvinte[4] + " este prea mica pentru a realiza " + cuvinte[0]);
                            else
                                if(conturi[i].Bani < atof(cuvinte[4].c_str()))
                                    throw myexception("Contul " + cuvinte[1] + " nu poate transfera " + cuvinte[4]);
                            else
                            {
                                conturi[i].Bani -= atof(cuvinte[4].c_str());
                                for(j = 0; j < conturi.size(); j++)
                                    if(conturi[j].nume_cont.compare(cuvinte[3]) == 0)
                                        conturi[j].Bani += atof(cuvinte[4].c_str());
                            }

                        }
                        else
                            throw myexception("Pinul pentru " + cuvinte[1] + " este gresit");


                }

            }


    }

}

void Banca::afisare_conturi()
{
    int i;
    for(i = 0; i < conturi.size(); i++)
        cout<<conturi[i].nume_cont<<" "<<conturi[i].PIN<<" "<<conturi[i].Bani<<endl;
}
int main()
{
    Banca banca("conturi.txt");
    banca.afisare_conturi();
    cout<<endl;
    try
    {
        banca.executaOperatiune("TRANSFER 1 12 7");
    }

    catch(exception &e)
    {
        cout<<e.what();
    }

    banca.afisare_conturi();
    cout<<endl;
    banca.executaOperatiune("RETRAGERE 3 1235 500");
    banca.afisare_conturi();
    cout<<endl;
    banca.executaOperatiune("TRANSFER 2 0000 4 200");
    banca.afisare_conturi();
}
