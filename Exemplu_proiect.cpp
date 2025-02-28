#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Rezervor {
	float capacitate;
	string tipCombustibil;
	float pret;
	static float capacitateMax;
public:
	Rezervor() {
		this->capacitate = 0;
		this->tipCombustibil = "-";
		this->pret = 0;
	}
	Rezervor(float _capacitate, string _tipCombustibil, float _pret) {
		if (_capacitate < Rezervor::capacitateMax) {
			this->capacitate = _capacitate;
		}
		else {
			this->capacitate = 0;
		}
		this->tipCombustibil = _tipCombustibil;
		this->pret = _pret;
	}
	Rezervor(const Rezervor& r) {
		this->capacitate = r.capacitate;
		this->tipCombustibil = r.tipCombustibil;
		this->pret = r.pret;
	}
	~Rezervor() {

	}
	Rezervor& operator=(const Rezervor& r) {
		if (this != &r) {
			this->capacitate = r.capacitate;
			this->tipCombustibil = r.tipCombustibil;
			this->pret = r.pret;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Rezervor& r) {
		out << "\n-------------------------------";
		out << "\nCapacitate: " << r.capacitate;
		out << "\nTip combustibil: " << r.tipCombustibil;
		out << "\nPret / litru: " << r.pret;

		return out;
	}

	Rezervor& operator+=(float _alimentare) {
		if (this->capacitate + _alimentare <= Rezervor::capacitateMax) {
			this->capacitate += _alimentare;
			return *this;
		}
		else {
			cout << "\n Capacitate maxima";
			return *this;
		}
	}

	Rezervor& operator-=(float _alimentareMasina) {
		if (this->capacitate - _alimentareMasina >= 0) {
			this->capacitate -= _alimentareMasina;
			return *this;
		}
		else {
			cout << "\n Nu se poate alimenta";
			return *this;
		}
	}

	bool operator!() {
		if (this->capacitate != 0) {
			cout << "\nRezervorul are combustibil";
			return false;
		}
		else {
			cout << "\n Rezervorul este gol ";
			return true;
		}
	}

	friend ofstream& operator<<(ofstream& out, const Rezervor& r) {
		out  << r.capacitate;
		out  << r.tipCombustibil;
		out  << r.pret;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Rezervor& r) {
		in >> r.capacitate;
		in >> r.tipCombustibil;
		in >> r.capacitate;
		return in;
	}

	void writeToFile(fstream& f) {
		f.write((char*)&this->capacitate, sizeof(float));
		int lg = this->tipCombustibil.length()+1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->tipCombustibil.data(), lg);
		f.write((char*)&this->pret, sizeof(float));
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->capacitate, sizeof(float));
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg + 1];
		f.read(buffer, lg);
		this->tipCombustibil = buffer;
		delete[] buffer;
		f.read((char*)&this->pret, sizeof(float));
	}
};
float Rezervor::capacitateMax = 1000;

class Benzinarie {
	string denumire;
	int nrRez;
	Rezervor* listaRezervoare;
public:
	Benzinarie() {
		this->denumire = "-";
		this->nrRez = 0;
		this->listaRezervoare = nullptr;
	}
	Benzinarie(string _denumire, int _nrRez, Rezervor* _listaRezervoare) {
		this->denumire = _denumire;
		if (_nrRez > 0) {
			this->nrRez = _nrRez;
			this->listaRezervoare = new Rezervor[this->nrRez];
			for (int i = 0; i < this->nrRez; i++) {
				this->listaRezervoare[i] = _listaRezervoare[i];
			}
		}
		else {
			this->nrRez = 0;
			this->listaRezervoare = nullptr;
		}
	}
	Benzinarie(const Benzinarie& b) {
		this->denumire = b.denumire;
		if (b.nrRez > 0) {
			this->nrRez = b.nrRez;
			this->listaRezervoare = new Rezervor[this->nrRez];
			for (int i = 0; i < this->nrRez; i++) {
				this->listaRezervoare[i] = b.listaRezervoare[i];
			}
		}
		else {
			this->nrRez = 0;
			this->listaRezervoare = nullptr;
		}
	}
	~Benzinarie() {
		if (this->listaRezervoare != nullptr) {
			delete[] this->listaRezervoare;
			this->listaRezervoare = nullptr;
		}
	}
	Benzinarie& operator=(const Benzinarie& b) {
		if (this != &b) {
			if (this->listaRezervoare != nullptr) {
				delete[] this->listaRezervoare;
				this->listaRezervoare = nullptr;
			}
			this->denumire = b.denumire;
			if (b.nrRez > 0) {
				this->nrRez = b.nrRez;
				this->listaRezervoare = new Rezervor[this->nrRez];
				for (int i = 0; i < this->nrRez; i++) {
					this->listaRezervoare[i] = b.listaRezervoare[i];
				}
			}
			else {
				this->nrRez = 0;
				this->listaRezervoare = nullptr;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Benzinarie& b) {
		out << "\nDenumire: " << b.denumire;
		out << "\nNr rezervoare: " << b.nrRez;
		out << endl;
		for (int i = 0; i < b.nrRez; i++) {
			out << b.listaRezervoare[i];
		}
		return out;
	}

	string getDenumire() {
		return this->denumire;
	}

	void setDenumire(string _denumire) {
		this->denumire = _denumire;
	}
};



int main() {
	Rezervor r1(500, "Benzina", 10);
	Rezervor r2(700, "Motorina", 5);
	Rezervor r3(600, "Benzina", 20);
	Rezervor r4(400, "Combustibil", 20);
	Rezervor r5(900, "Motorina", 35);
	Rezervor lista[] = { r1,r2,r3,r4,r5 };
	Benzinarie b1("Benzinarie 1", 2, lista);
	cout << b1;
	r1 += 100;
	cout << r1;
	cout << endl;
	r2 -= 200;
	cout << r2;
	!r1;

	/*ofstream g("Raport2.txt");
	g << r2;
	g.close();
	ifstream f("Raport2.txt");
	Rezervor r;
	f >> r;
	cout << "\n Fisier TEST";
	cout << r;*/

	/*fstream fileOut("Raport.bin", ios::out | ios::binary);
	r2.writeToFile(fileOut);
	fileOut.close();*/

	/*fstream fileIn("Rapor.bin", ios::in | ios::binary);
	Rezervor r7;
	r7.readFromFile(fileIn);
	cout << endl << "TEST";
	cout << r7;*/

	

	return 0;
}