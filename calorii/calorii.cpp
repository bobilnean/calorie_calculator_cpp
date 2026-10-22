#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cctype>
#include<ctime>
using namespace std;
struct Aliment
{
	string nume;
	float calorii, proteine, grasimi, grasimi_saturate, grasimi_poli, grasimi_mono, carbohidrati, fibre, zahar, alcool;
};
struct Consumat
{
	Aliment aliment;
	float gramaj;
	int masa;
};
vector<Aliment> citire()
{
	vector<Aliment>alimente; //un vector gol care creste automat
	ifstream f("valori.txt");
	if (!f.is_open()) { cout << "fisierul nu a putut fi deschis\n"; return alimente; }
	string linie;
	getline(f, linie);
	while (getline(f, linie))
	{
		stringstream ss(linie);
		string camp;
		Aliment a;
		getline(ss, camp, ';'); a.nume = camp;
		getline(ss, camp, ';'); a.calorii = stof(camp);
		getline(ss, camp, ';'); a.proteine = stof(camp);
		getline(ss, camp, ';'); a.grasimi = stof(camp);
		getline(ss, camp, ';'); a.grasimi_saturate = stof(camp);
		getline(ss, camp, ';'); a.grasimi_poli = stof(camp);
		getline(ss, camp, ';'); a.grasimi_mono = stof(camp);
		getline(ss, camp, ';'); a.carbohidrati = stof(camp);
		getline(ss, camp, ';'); a.fibre = stof(camp);
		getline(ss, camp, ';'); a.zahar = stof(camp);
		getline(ss, camp, ';'); a.alcool = stof(camp);
		alimente.push_back(a);
	}
	cout << "am incarcat " << alimente.size() << " alimente.\n";
	return alimente;
}
string micute(string text)
{
	for (int i = 0;i < text.size(); i++)text[i] = tolower(text[i]);
	return text;
}
vector<Aliment> sugereaza(vector<Aliment> alimente, string text_cautat)
{
	text_cautat = micute(text_cautat); // transform in litere mici

	vector<Aliment> rezultat; // vector rezultat

	for (int i = 0; i < alimente.size(); i++)
	{
		string nume_normalizat = micute(alimente[i].nume);
		if (nume_normalizat.find(text_cautat) != string::npos) // verific daca textul cautat apare in lista
		{
			rezultat.push_back(alimente[i]); // daca am gasit ce cautam, adaug in vector rezultat
		}
	}

	return rezultat;
}
string data_azi()
{
	time_t acum = time(0);        // secundele scurse de la 1 ianuarie 1970
	tm t;                         // o structura cu an, luna, zi, ora...
	localtime_s(&t, &acum);       // completeaza t cu data locala
	char buf[11];                 // un sir de char, ca in liceu: "2026-10-19" + '\0'
	strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
	return string(buf);
}
void jurnal(Aliment ales, float gramaj, int masa)
{
	ofstream g("JURNAL.txt", ios::app);//asta scrie totul la sfarsit, fara sa imi stearga ce am scris pana acum in fisier
	if (!g.is_open()) { cout << "nu s a putut deschide jurnalul "; return; }
	g <<data_azi() << " | " << masa << " | " << ales.nume << " | " << gramaj << endl;
}
void jurnal_total(float cal, float prot, float gras, float sat, float poli, float mono, float carbo, float fibre, float zahar, float alcool)
{
	ofstream g("JURNAL.txt", ios::app);
	if (!g.is_open()) { cout << "nu s a putut deschide jurnalul "; return; }
	g << data_azi() << " | TOTAL | calorii: " << cal
		<< " | proteine: " << prot
		<< " | grasimi: " << gras
		<< " | grasimi_saturate: " << sat
		<< " | grasimi_poli: " << poli
		<< " | grasimi_mono: " << mono
		<< " | carbohidrati: " << carbo
		<< " | fibre: " << fibre
		<< " | zahar: " << zahar
		<< " | alcool: " << alcool << endl;
}
int main()
{
	//int masa;
	vector<Aliment> alimente = citire();
	vector<Consumat> consumate;
	float caloriiZ=0, proteineZ=0, grasimiZ=0, grasimi_saturateZ=0, grasimi_poliZ=0, grasimi_monoZ=0, carbohidratiZ=0, fibreZ=0, zaharZ=0, alcoolZ=0;
	while (true) {
		cout << "\nce aliment cautati? (tastati 'gata' daca ati terminat sau 'scot' daca doriti sa eliminati un aliment) "; cout << endl;
		string TEXT_CAUTAT; getline(cin, TEXT_CAUTAT);
		if (TEXT_CAUTAT == "gata")break;
		if (TEXT_CAUTAT == "sterge") {
			if (consumate.size() == 0)continue;
			g<<"\nce aliment doriti sa scoateti? tastati numarul din lista"
			for (int i = 0;i < consumate.size();i++) {
				g << i + 1 << consumate[i].nume << "\n";
			}
		}
		vector<Aliment> rezultate = sugereaza(alimente, TEXT_CAUTAT);
		if (rezultate.size() == 0) { cout << "\nnu exista acest aliment"; continue; }
		//else
			for (int i = 0;i < rezultate.size();i++)
			{
				cout << i + 1 << ". " << rezultate[i].nume << "\n";
			}
		int alegere; cout << "\nce aliment doriti? (tastati numarul din lista) "; cin >> alegere;
		if (cin.fail() || alegere < 1 || alegere >(int)rezultate.size())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nnu exista acest numar in lista, alegeti altul\n";
			continue;
		}
		cout << "\nati ales " << rezultate[alegere - 1].nume << " ";
		Aliment ales = rezultate[alegere - 1];
		float gramaj; cout << "\nintroduceti gramajul (grame): "; cin >> gramaj;
		float procent; procent = gramaj / 100;
		cout << "calorii: " << ales.calorii * procent << "| ";	cout << "proteine: " << ales.proteine * procent << "| "; cout << "grasimi: " << ales.grasimi * procent << "| "; 	cout << "grasimi_saturate " << ales.grasimi_saturate * procent << "| ";	cout << "grasimi_poli: " << ales.grasimi_poli * procent << "| ";	cout << "grasimi_mono: " << ales.grasimi_mono * procent << "| ";	cout << "carbohidrati: " << ales.carbohidrati * procent << "| ";	cout << "fibre: " << ales.fibre * procent << "| ";	cout << "zahar: " << ales.zahar * procent << "| ";	cout << "alcool: " << ales.alcool * procent << "| ";
		cout << "\n";
		int masa; cout << "\nintroduceti masa (1-mic dejun; 2 - pranz; 3 - cina; 4 - gustare) "; cin >> masa;
		jurnal(ales, gramaj, masa);
		Consumat c;
		c.aliment = ales;
		c.gramaj = gramaj;
		c.masa = masa;
		consumate.push_back(c);
		cin.ignore(10000, '\n');

		caloriiZ += ales.calorii * procent; proteineZ += ales.proteine * procent; grasimiZ += ales.grasimi* procent; grasimi_saturateZ += ales.grasimi_saturate * procent; grasimi_poliZ += ales.grasimi_poli * procent; grasimi_monoZ += ales.grasimi_mono * procent; carbohidratiZ += ales.carbohidrati * procent; fibreZ += ales.fibre * procent; zaharZ = 0, alcoolZ += ales.alcool * procent;

	}
	if (caloriiZ > 0)
		jurnal_total(caloriiZ, proteineZ, grasimiZ, grasimi_saturateZ, grasimi_poliZ, grasimi_monoZ, carbohidratiZ, fibreZ, zaharZ, alcoolZ);
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
