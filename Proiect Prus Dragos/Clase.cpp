#include <iostream>
#include<string>
#include<fstream>

using namespace std;
#pragma warning(disable:4996)
#define CRT_SECURE_NO_WARNINGS

struct loc
{
    int nrRand, nrCol, nrZona;
};
struct zona
{
    char den[15];
    int rand_prim, rand_ultim, locuri_rand_prim;
};

class Locatie
{
public:
    char* denumire;
    int nrLocuri, nrZone;
    loc* locuri;
    zona* zone;
    char status[20];
public:
    virtual int numarTotalLocuri() = 0;
    virtual void afiseazaLocatia() = 0;
    Locatie()
    {
        this->denumire = NULL;
        this->nrLocuri = 0;
        this->nrZone = 0;
        this->locuri = NULL;
        this->zone = NULL;
        strcpy_s(status, strlen("Disponibil") + 1, "Disponibil");
    }
    Locatie(char* den)
    {
        this->denumire = new char[strlen(den) + 1];
        strcpy_s(this->denumire, strlen(den) + 1, den);
        this->nrLocuri = 0;
        this->nrZone = 0;
        this->locuri = NULL;
        this->zone = NULL;
        strcpy_s(status, strlen("Disponibil") + 1, "Disponibil");
    }

    int getnrLoc()
    {
        return this->nrLocuri;
    }

    void setnrLoc(int numarLocuri)
    {
        this->nrLocuri = numarLocuri;
    }

    loc* getLocuri()
    {
        return locuri;
    }

    void setLocuri(loc* l, int nrl)
    {
        if (nrl == 0)
        {
            locuri = NULL;
        }
        else
        {
            locuri = new loc[nrl];
            for (int i = 0; i < nrl; i++)
            {
                locuri[i] = l[i];
            }
        }
    }

    int getNrZone()
    {
        return this->nrZone;
    }

    void setnrZone(int numarZone)
    {
        this->nrZone = numarZone;
    }

    zona* getZone()
    {
        return this->zone;
    }

    void setZone(zona* z, int nrz)
    {
        if (nrz == 0)
        {
            zone = NULL;
        }
        else
        {
            zone = new zona[nrz];
            for (int i = 0; i < nrz; i++)
            {
                zone[i] = z[i];
            }
        }
    }


    char* getDenumire()
    {
        return this->denumire;
    }

    void setDenumire(char* denum)
    {
        if (denum != NULL)
        {
            this->denumire = new char[strlen(denum) + 1];
            strcpy_s(this->denumire, strlen(denum) + 1, denum);
        }
        else
        {
            denumire = NULL;
        }
    }

    char* getStatus()
    {
        return status;
    }

    void setStatus(char stat[20])
    {
        if (strcmp(stat, "Disponibil") == 0)
        {
            strcpy_s(status, strlen("Disponibil") + 1, "Disponibil");
        }
        else if (strcmp(stat, "Indisponibil") == 0)
        {
            strcpy_s(status, strlen("Indisponibil") + 1, "Indisponibil");
        }
        else if (strcmp(stat, "Ocupat") == 0)
        {
            strcpy_s(status, strlen("Ocupat") + 1, "Ocupat");
        }
        else
        {
            cout << "Statusul setat nu este valabil.\n";
        }
    }
};

//**************************************************************************************************************************************

class Locatie_Stadion : public Locatie
{
    int difLocuri;
public:
    Locatie_Stadion(char* den, int difL, int nrZon, zona* z) :Locatie(den)
    {
        this->difLocuri = difL;
        this->nrZone = nrZon;
        this->zone = new zona[nrZon];
        for (int i = 0; i < nrZon; i++)
        {
            this->zone[i] = z[i];
        }

        nrLocuri = numarTotalLocuri();
        locuri = new loc[nrLocuri];
        int x = 0;
        for (int k = 0; k < nrZon; k++)
        {
            int m = zone[k].locuri_rand_prim;
            for (int i = zone[k].rand_prim; i <= zone[k].rand_ultim; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    locuri[x].nrZona = k;
                    locuri[x].nrRand = i;
                    locuri[x].nrCol = j;
                    x++;
                }
                m = m + difLocuri;
            }
        }
    }

    int numarTotalLocuri()
    {
        int x = 0;
        for (int k = 0; k < nrZone; k++)
        {
            int m = zone[k].locuri_rand_prim;
            for (int i = zone[k].rand_prim; i <= zone[k].rand_ultim; i++)
            {
                x += m;
                m = m + difLocuri;
            }
        }
        return x;
    }
    void afiseazaLocatia() {
        cout << "Locatie Stadion ==> Denumire Locatie: " << denumire << endl;
        cout << "Numar Zone: " << nrZone << endl;
        for (int i = 0; i < nrZone; i++)
        {
            cout << "  " << zone[i].den << " cu  rand de la " << zone[i].rand_prim << " la " << zone[i].rand_ultim <<
                " si " << zone[i].locuri_rand_prim << " locuri pe primul rand, in crestere cu " << difLocuri << ".\n";
        }
        cout << endl;
    }
};

//**************************************************************************************************************************************

class Locatie_Cinema : public Locatie
{
private:


public:
    Locatie_Cinema(char* den, int nrZon, zona* z) :Locatie(den)
    {
        this->nrZone = nrZon;
        this->zone = new zona[nrZon];
        for (int i = 0; i < nrZon; i++)
        {
            this->zone[i] = z[i];
        }
        nrLocuri = numarTotalLocuri();
        locuri = new loc[nrLocuri];
        int x = 0;
        for (int k = 0; k < nrZon; k++)
        {
            int m = zone[k].locuri_rand_prim;
            for (int i = zone[k].rand_prim; i <= zone[k].rand_ultim; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    locuri[x].nrZona = k;
                    locuri[x].nrRand = i;
                    locuri[x].nrCol = j;
                    x++;
                }
            }
        }
    }

    int numarTotalLocuri()
    {
        int x = 0;
        for (int k = 0; k < nrZone; k++)
        {
            x += (zone[k].rand_ultim - zone[k].rand_prim + 1) * zone[k].locuri_rand_prim;
        }
        return x;
    }
    void afiseazaLocatia() {
        cout << "Locatie Cinema ==> Denumire Locatie: " << denumire << endl;
        cout << "Numar Zone: " << nrZone << endl;
        for (int i = 0; i < nrZone; i++)
        {
            cout << "  " << zone[i].den << " cu  rand de la " << zone[i].rand_prim << " la " << zone[i].rand_ultim <<
                " si " << zone[i].locuri_rand_prim << " nr. locuri pe rand.\n";
        }
        cout << endl;
    }
};

//**************************************************************************************************************************************

class Eveniment
{
private:
    char* denumire;
    Locatie* locatie;
    string ora;
    string data;
public:
    friend class Locatie;

    Eveniment()
    {
        denumire = NULL;
        locatie = NULL;
        ora = "";
        data = "";
    }


    Eveniment(char* den1, Locatie* a, string ora1, string data1)
    {
        if (den1 != NULL)
        {
            denumire = new char[strlen(den1) + 1];
            strcpy_s(denumire, (strlen(den1) + 1), den1);
        }
        locatie = a;
        ora = ora1;
        data = data1;
    }

    char* getDenumire() {
        return this->denumire;
    }
    Locatie* getLocatie() {
        return locatie;
    }

    void afisareEveniment()
    {
        cout << "Eveniment:" << denumire << endl;
        cout << "Data: " << data << " Ora: " << ora << endl;
        cout << "Se desfasoara in locatia:\n";
        locatie->afiseazaLocatia();
        cout << endl;
    }

    ~Eveniment()
    {
        if (denumire != NULL)
        {
            delete[] denumire;
        }
    }

};

//**************************************************************************************************************************************

class Bilet
{
private:
    int id;
    int nrRand, nrLoc;
    char* zona = NULL;
    int pret;
    Eveniment* eveniment;
    char status[20] = "";
    // static int idMaxim;
public:

    Bilet() {
        id = 0;
        nrRand = nrLoc = 0;
        zona = NULL;
        pret = 0;
        eveniment = NULL;
    }
    Bilet(int id, int nrr, int nrl, char* z, int p, Eveniment* ev) {
        this->id = id;
        this->nrRand = nrr;
        this->nrLoc = nrl;
        if (z != NULL) {
            zona = new char[strlen(z) + 1];
            strcpy_s(zona, strlen(z) + 1, z);
        }

        this->pret = p;
        this->eveniment = ev;
    }
    /*
    static void incId() {
        idMaxim++;
    }
    static int getIdMaxim() {
        return idMaxim;
    }
    */
    Eveniment* getEveniment() {
        return this->eveniment;
    }
    int getId() {
        return id;
    }
    int getNrLoc() {
        return nrLoc;
    }
    int getNrRand() {
        return nrRand;
    }
    char* getZona() {
        return zona;
    }
    int getPret() {
        return pret;
    }
    void afisareBilet() {
        cout << "Seria: " << id << " zona: " << zona << " rand: " << nrRand << " loc: " << nrLoc << " status bilet: " << status << endl;
    }

};
//int Bilet::idMaxim = 1000000;
