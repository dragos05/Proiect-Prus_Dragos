#include <iostream>
#include <cstring>
#include <conio.h>
#include <vector>
#include "Clase.cpp"
#include <set>
#include <stdlib.h>
#include <time.h>


using namespace std;

ifstream fin("date.txt");

void citireFisierLocatii(vector <Locatie*>& vLocatie, int& nrLocatii) {


	int nrLoc, tip, nrZone, difLocuri;
	char den[20] = "";
	zona vz[10];
	fin >> nrLoc;
	for (int k = 0; k < nrLoc; k++) {
		fin >> tip;
		fin >> den;
		if (tip == 1) {
			fin >> difLocuri;
		}
		fin >> nrZone;
		for (int i = 0; i < nrZone; i++)
		{
			fin >> vz[i].den;
			fin >> vz[i].rand_prim;
			fin >> vz[i].rand_ultim;
			fin >> vz[i].locuri_rand_prim;
		}
		if (tip == 1) {
			Locatie_Stadion* ls;
			ls = new Locatie_Stadion(den, difLocuri, nrZone, vz);
			vLocatie.push_back(ls);
		}
		else {
			Locatie_Cinema* ls;
			ls = new Locatie_Cinema(den, nrZone, vz);
			vLocatie.push_back(ls);
		}
		nrLocatii++;
	}

}

void citireFisierEvenimente(vector <Eveniment*>& vEveniment, vector <Locatie*>& vLocatie) {

	char den[20], status[20];
	Locatie* loc = NULL, * auxLoc[10];
	int nrEv, nrLoc, j = 0;
	string data, ora;
	char stat[20] = "Ocupat";
	fin >> nrEv;

	for (int k = 0; k < nrEv; k++) {
		fin >> den;
		fin >> nrLoc;
		for (int i = 0; i < vLocatie.size(); i++)
		{
			if (i + 1 == nrLoc)
			{
				loc = vLocatie[i];
			}
		}

		if (loc != NULL) {
			loc->setStatus(stat);
		}
		fin >> data;
		fin >> ora;
		Eveniment* ev;
		ev = new Eveniment(den, loc, ora, data);
		vEveniment.push_back(ev);
	}
}

void adaugareLocatie(vector <Locatie*>& vLocatie, int& nrLocatii)
{
	int tip, nrZone, difLocuri;
	char den[20];
	zona vz[10];
	cout << "Tip Locatie(1.Stadion/2.Cinema):";
	cin >> tip;
	cout << "Denumire Locatie:";
	cin >> den;
	if (tip == 1) {
		cout << "Diferenta de locuri intre randuri(1/2):";
		cin >> difLocuri;
	}
	cout << "Numar Zone:";
	cin >> nrZone;
	for (int i = 0; i < nrZone; i++)
	{
		cout << "Denumire zona:";
		cin >> vz[i].den;
		cout << "Numarul primului rand:";
		cin >> vz[i].rand_prim;
		cout << "Numarul ultimului rand:";
		cin >> vz[i].rand_ultim;
		cout << "Numarul de locuri pe primul rand:";
		cin >> vz[i].locuri_rand_prim;
	}
	if (tip == 1) {
		Locatie_Stadion* ls;
		ls = new Locatie_Stadion(den, difLocuri, nrZone, vz);
		vLocatie.push_back(ls);
	}
	else {
		Locatie_Cinema* ls;
		ls = new Locatie_Cinema(den, nrZone, vz);
		vLocatie.push_back(ls);
	}
	nrLocatii++;
	cout << "Locatia " << den << " a fost adaugata. \n Apasati o tasta pentru continuare.";
}

void afisareLocatii(vector <Locatie*> vLocatie, int& nrLocatii)
{
	zona* vz;
	if (vLocatie.size() == 0) {
		cout << " Nu sunt locatii inregistrate.";
	}
	else {
		for (int i = 0; i < vLocatie.size(); i++) {
			vLocatie[i]->afiseazaLocatia();
		}
	}


}

void adaugareEveniment(vector <Eveniment*>& vEveniment, vector <Locatie*> vLocatie)
{
	char den[20], status[20];
	Locatie* loc, * auxLoc[10];
	int nrLoc, j = 0;
	string data, ora;
	char stat[20] = "Ocupat";
	cout << "Denumire eveniment:";
	cin >> den;
	cout << "Locatii disponibile:\n";
	for (int i = 0; i < vLocatie.size(); i++)
	{
		if (strcmp(vLocatie[i]->getStatus(), "Disponibil") == 0)
		{
			cout << j + 1 << ". " << vLocatie[i]->getDenumire() << endl;
			auxLoc[j] = vLocatie[i];
			j++;
		}
	}
	do
	{
		cout << "Alege o locatie disponibila(0=fara locatie, 1.." << j << ", ):";
		cin >> nrLoc;
	} while (nrLoc<0 || nrLoc>j);
	if (nrLoc > 0) {
		loc = auxLoc[nrLoc - 1];
		loc->setStatus(stat);
		cout << "Introduceti data evenimentului: ";
		cin >> data;
		cout << "Introduceti ora evenimentului: ";
		cin >> ora;
		Eveniment* ev;
		ev = new Eveniment(den, loc, ora, data);
		vEveniment.push_back(ev);
		cout << "Evenimentul " << den << " a fost adaugat. \n Apasati o tasta pentru continuare.";
	}
}

void afisareEvenimente(vector <Eveniment*>& vEveniment)
{
	if (vEveniment.size() == 0) {
		cout << " Nu sunt evenimente inregistrate.";
	}
	else {
		for (int i = 0; i < vEveniment.size(); i++)
		{
			vEveniment[i]->afisareEveniment();
		}
	}
}


void generareBilete(vector <Bilet*>& vBilet, vector <Eveniment*> vEveniment, set<int> bazaId) {
	int nrEv, nrloc, nrrand, nrzona, id = 0, pret[10];
	char* zon;
	Eveniment* ev;
	set<int>::iterator it;

	for (int i = 0; i < vEveniment.size(); i++) {
		cout << i + 1 << ". " << vEveniment[i]->getDenumire() << endl;
	}
	do {
		cout << "Alege un eveniment(0= renunt):";
		cin >> nrEv;
	} while (nrEv<0 || nrEv>vEveniment.size());
	if (nrEv > 0) {
		ev = vEveniment[nrEv - 1];
		Locatie* loc = ev->getLocatie();
		cout << "Introduceti preturile biletelor pe zone:\n";
		for (int i = 0; i < loc->getNrZone(); i++) {
			cout << "Pret zona " << loc->getZone()[i].den << ":";
			cin >> pret[i];
		}
		for (int i = 0; i < loc->getnrLoc(); ++i) {
			do {
				id = rand() * rand() % 1000000 + 1000000;
				it = bazaId.find(id);
			} while (it != bazaId.end());
			bazaId.insert(id);

			nrloc = loc->getLocuri()[i].nrCol;
			nrrand = loc->getLocuri()[i].nrRand;
			nrzona = loc->getLocuri()[i].nrZona;
			Bilet* bl = new Bilet(id, nrrand, nrloc, loc->getZone()[nrzona].den, pret[nrzona], ev);
			vBilet.push_back(bl);
			//bl->incId();

		}
	}
	cout << "Biletele pentru eveniment au fost generate. Apasati o tasta pentru a continua.";
}
void afisareBilete(vector <Bilet*> vBilet, vector <Eveniment*> vEveniment) {
	int  nrloc, nrrand, nrzona, id, pret, nrEv;
	char* zon;
	Eveniment* ev;
	Locatie* loc;
	cout << "Afisarea biletelor de la un eveniment\n ";

	for (int i = 0; i < vEveniment.size(); i++) {
		cout << i + 1 << ". " << vEveniment[i]->getDenumire() << endl;
	}
	do {
		cout << "Alege un eveniment(0= renunt):";
		cin >> nrEv;
	} while (nrEv<0 || nrEv>vEveniment.size());
	if (nrEv > 0) {
		ev = vEveniment[nrEv - 1];

		for (int i = 0; i < vBilet.size(); ++i) {
			if (strcmp(ev->getDenumire(), vBilet[i]->getEveniment()->getDenumire()) == 0) {
				loc = vBilet[i]->getEveniment()->getLocatie();
				id = vBilet[i]->getId();
				nrloc = vBilet[1]->getNrLoc();
				nrrand = vBilet[1]->getNrRand();
				pret = vBilet[1]->getPret();
				zon = vBilet[i]->getZona();
				cout << id << " loc R" << nrrand << " L" << nrloc << " zona: " << zon << " pret:" << pret << endl;
			}

		}
	}
}

/*
Initializeaza datele din fisierul de intrare date.txt in varianta cu Menu
*/
void InitializareDateFisier(vector <Locatie*>& vLocatie, int& nrLocatii, vector <Eveniment*>& vEveniment) {
	char sir[21];
	while (fin >> sir) {
		if (strcmp(sir, "#locatii") == 0) {
			citireFisierLocatii(vLocatie, nrLocatii);
			afisareLocatii(vLocatie, nrLocatii);
		}
		else
			if (strcmp(sir, "#evenimente") == 0) {
				citireFisierEvenimente(vEveniment, vLocatie);
				afisareLocatii(vLocatie, nrLocatii);
			}
			else
				if (strcmp(sir, "#bilete") == 0) {
					citireFisierLocatii(vLocatie, nrLocatii);  //de modificat
					afisareLocatii(vLocatie, nrLocatii);
				}
	}
}



int main(int argc, char* argv[])
{
	vector <Locatie*> vLocatie;
	int nrLocatii = 0;
	vector <Eveniment*> vEveniment;
	vector <Bilet*> vBilet;
	set <int> bazaId;

	if (argc > 1) {
		cout << "Citire date din fisierul " << argv[1] << endl;
		char sir[21];
		while (fin >> sir) {
			if (strcmp(sir, "#locatii") == 0) {
				citireFisierLocatii(vLocatie, nrLocatii);
				afisareLocatii(vLocatie, nrLocatii);
			}
			else
				if (strcmp(sir, "#evenimente") == 0) {
					citireFisierEvenimente(vEveniment, vLocatie); //de modificat
					afisareEvenimente(vEveniment);
				}
				else
					if (strcmp(sir, "#bilete") == 0) {
						citireFisierLocatii(vLocatie, nrLocatii);  //de modificat
						afisareLocatii(vLocatie, nrLocatii);
					}
		}
	}
	else {
		// Tratare meniu
		char opt;
		do {
			system("cls");
			cout << "Meniu Principal\n";
			cout << "1. Incarcare date aplicatie din fisier\n";
			cout << "2. Adaugare locatie\n";
			cout << "3. Afisare locatii\n";
			cout << "4. Adaugare eveniment\n";
			cout << "5. Afisare evenimente\n";
			cout << "6. Generare bilete pe eveniment\n";
			cout << "7. Afisare bilete pe eveniment\n";
			cout << "8. Vanzare bilet\n";

			cout << "0. Iesire din aplicatie\n";
			cout << "\nAlegeti o optiune:";
			opt = _getch();
			cout << opt << '\n';
			switch (opt) {
			case '1': InitializareDateFisier(vLocatie, nrLocatii, vEveniment);
				break;
			case '2': adaugareLocatie(vLocatie, nrLocatii);
				break;
			case '3': afisareLocatii(vLocatie, nrLocatii);
				break;
			case '4':adaugareEveniment(vEveniment, vLocatie);
				break;
			case '5': afisareEvenimente(vEveniment);
				break;
			case '6': generareBilete(vBilet, vEveniment, bazaId);
				break;
			case '7':afisareBilete(vBilet, vEveniment);
				break;
			case '8':
				break;

			case '0': cout << " Apasati o tasta pentru a iesi din program. ";
				break;
			}
			_getch();
		} while (opt != '0');
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
