#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class Produs {
	string denumire;
	int cantitate;

public: 
	Produs() {
		this->denumire = "-";
		this->cantitate = 0;
	}

	Produs(string _denumire, int _cantitate) {
		this->denumire = _denumire;
		this->cantitate = _cantitate;
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << endl << p.denumire;
		out << endl << p.cantitate;

		return out;
	}

	int getCantitate() {
		return this->cantitate;
	}

	void setCantitate(int _cantitate) {
		if (_cantitate > 0) {
			this->cantitate = _cantitate;
		}
		else {
			this->cantitate = 0;
		}
	}

	bool operator==(const Produs& p) {
		if (this->denumire == p.denumire && this->cantitate == p.cantitate) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!=(const Produs& p) {
		if (this->denumire != p.denumire && this->cantitate != p.cantitate) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Client {
	const int idC;
	string nume;
	int nrProduseComanda;
	Produs* listaProduse;
public:
	Client() :idC(0) {
		this->nume = "-";
		this->nrProduseComanda = 0;
		this->listaProduse = nullptr;
	}

	Client(int _idC, string _nume, int _nrProduseComanda, Produs* _listaProduse):idC(_idC) {
		this->nume = _nume;
		this->nrProduseComanda = _nrProduseComanda;
		this->listaProduse = new Produs[this->nrProduseComanda];
		for (int i = 0; i < this->nrProduseComanda; i++) {
			this->listaProduse[i] = _listaProduse[i];
		}
	}

	Client(const Client& c) :idC(c.idC) {
		this->nume = c.nume;
		this->nrProduseComanda = c.nrProduseComanda;
		this->listaProduse = new Produs[this->nrProduseComanda];
		for (int i = 0; i < this->nrProduseComanda; i++) {
			this->listaProduse[i] = c.listaProduse[i];
		}
	}

	~Client() {
		if (this->listaProduse != nullptr) {
			delete[] this->listaProduse;
			this->listaProduse = nullptr;
		}
	}

	Client& operator=(const Client& c) {
		if (this != &c) {
			if (this->listaProduse != nullptr) {
				delete[] this->listaProduse;
				this->listaProduse = nullptr;
			}
			this->nume = c.nume;
			this->nrProduseComanda = c.nrProduseComanda;
			this->listaProduse = new Produs[this->nrProduseComanda];
			for (int i = 0; i < this->nrProduseComanda; i++) {
				this->listaProduse[i] = c.listaProduse[i];
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Client& c) {
		out << endl << "ID: " << c.idC;
		out << endl << "nume: " << c.nume;
		out << endl << "nr produse comandate: " << c.nrProduseComanda;
		out << endl << "Lista: ";
		for (int i = 0; i < c.nrProduseComanda; i++) {
			out << c.listaProduse[i];
		}
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Client& c) {
		out << endl << c.idC;
		out << endl <<  c.nume;
		out << endl <<  c.nrProduseComanda;
		out << endl;
		for (int i = 0; i < c.nrProduseComanda; i++) {
			out << c.listaProduse[i];
		}
		return out;
	}

	Produs operator[](int _index) {
		if (_index >= 0 && _index < this->nrProduseComanda) {
			return this->listaProduse[_index];
		}
	}


	Client& operator+=(Produs _produs) {
		for (int i = 0; i < this->nrProduseComanda; i++) {
			if (this->listaProduse[i] == _produs) {
				this->listaProduse[i].setCantitate(this->listaProduse[i].getCantitate() + 1);
				return *this;
			}
			else {
				this->nrProduseComanda += 1;
				Produs* copieLista = new Produs[this->nrProduseComanda];
				for (int i = 0; i < this->nrProduseComanda - 1; i++) {
					copieLista[i] = this->listaProduse[i];
				}
				copieLista[this->nrProduseComanda-1] = _produs;
				delete[] this->listaProduse;
				this->listaProduse = new Produs[this->nrProduseComanda];
				for (int i = 0; i < this->nrProduseComanda; i++) {
					this->listaProduse[i] = copieLista[i];
				}
				delete[] copieLista;
				return *this;
			}
		}
	}



};

class ComandaStatus :public Client {
public:
	string stare_comanda;
	ComandaStatus() {
		this->stare_comanda = "neidentificata";
	}
	ComandaStatus(Client _c, string _stare_comanda) :Client(_c) {
		this->stare_comanda = _stare_comanda;
	}
	ComandaStatus(const ComandaStatus& co) :Client(co) {
		this->stare_comanda = co.stare_comanda;
	}

	friend ofstream& operator<<(ofstream& out, const ComandaStatus& co) {
		if (co.stare_comanda != "neidentificata") {
			out << (Client)co; //upcast prin valoare
			out << co.stare_comanda;

			return out;
		}
		else {
			cout << "Not available";
		}
		
	}


};

int main() {
	Produs p;
	Produs p1("serviciu1", 1);
	Produs p2("serviciu2", 4);
	Produs p3("serviciu3", 3);
	Produs p4("serviciu4", 2);
	Produs p5("serviciu5", 3);
	cout << endl << "----------------------------";
	cout << p4;

	Produs listaP[] = { p1,p2,p3,p4,p5 };
	Client c;
	Client c1(1, "client1", 2, listaP);
	Client c2(2, "client2", 3, listaP);
	Client c3(3, "client3", 4, listaP);
	Client c4(4, "client4", 5, listaP);
	Client c5(5, "client5", 1, listaP);
	Client c6(6, "client6", 2, listaP);
	cout << endl << "----------------------------";
	cout << c5;
	cout << endl << "-------------------------";
	cout<<c4.operator[](4);
	cout << endl << "------------c6 vechi-------------";
	cout << c6;
	cout << endl << "------------c6 nou -------------";
	c6 += p1;
	cout << c6; 


	ComandaStatus co;
	ComandaStatus co1(c2, "delivered");

	ofstream g("StatusComenzi.txt");
	g << co1;
	g << co;
	g.close();

	cout << endl << "lista";

	list<Produs> listaProduse;
	listaProduse.push_back(p1);
	listaProduse.push_back(p2);
	listaProduse.push_front(p3);

	// p3,p1,p2

	cout << endl << "Afisare lista:";
	list<Produs>::iterator it;
	for (it = listaProduse.begin(); it != listaProduse.end(); it++) {
		cout << endl << *it;
	}
	



	return 0;
}