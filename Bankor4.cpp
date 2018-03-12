#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;
//[],<<,>>,==, (), =
//->, +, -
class Stat{
	public:
		int id;
		int SU;
		int logged=0;
		int decyzja;
		int val;
		string log;
		string pas;		
};
class Users{//dla usera dac konstruktor kopiujacy(z klasy stat) jak sie zaloguje i operowac na tej klasie
	public:
		int id;//nie kosntruktor tylko przypisanie przez przeladowanie
		string log;
		string pas;
		int val;
		int SU;
};
class SUser{
	public:
		int id;
		string log;
		SUser(Stat stat){//konstruktor kopiujacy
			this->id=stat.id;
			this->log=stat.log;
		}
};
class Person{
	public:
		string *nn;
		string *ss;
	Person(){
	}
};
class Wsk{
	public:
		virtual void wypisz()=0;
};
class Pracownik: public Wsk, public Person{
	public:
		int N;
		int *id;
		string *stanowisko;
		
		Pracownik(){

				fstream Login;
				Login.open("pracownicy.txt", ios::in);
				Login >> N;
				
				id=new int[N];
				stanowisko=new string[N];
				nn=new string[N];
				ss=new string[N];
				
				for(int i=0;i<N;i++){
					Login >> id[i];
					Login >> nn[i];
					Login >> ss[i];
					Login >> stanowisko[i];
				}
				Login.close();
				
		}
		void wypisz(){
			cout<< "id		Imie	Nazwisko	Stanowisko"<<endl<<endl;
			for(int i=0;i<N;i++){
				cout << id[i]<<". 		"<<nn[i]<<" 	"<<ss[i]<<" 		"<< stanowisko[i]<<endl;
			}
		}
		~Pracownik(){
				delete [] id;
				delete [] stanowisko;
				delete [] nn;
				delete [] ss;
		}
};
class Bank{
	public:
		int *val;
		int *su;
};
class Uzytkownik: public Wsk, public Person, public Bank{
	public:
		int *id;
		int N;
		
	Uzytkownik(){

				fstream Login;
				Login.open("conf.txt", ios::in);
				Login >> N;
				
				id=new int[N];
				nn=new string[N];
				ss=new string[N];
				val=new int[N];
				su=new int[N];
				
				
				for(int i=0;i<N;i++){
					Login >> id[i];
					Login >> nn[i];
					Login >> ss[i];
					Login >> val[i];
					Login >> su[i];
				}
				Login.close();
				
		}
	
	void wypisz(){
		cout<< "id	Login	Haslo	zl		SU?"<<endl<<endl;
		for(int i=0;i<N;i++){
				cout<< id[i]<<". 	"<<nn[i] <<"	"<<ss[i]<<"	"<<val[i]<<"		";
				if(su[i]==0){
					cout<<"NIE"<<endl;
				}
				else{
					cout<<"TAK"<<endl;
				}
		}
	}
	
			~Uzytkownik(){
				delete [] id;
				delete [] nn;
				delete [] ss;
				delete [] val;
				delete [] su;
			}	
};
class Nadpis{
	public:
		Nadpis(){
			id=0;
			login="";
			password="";
			val=0;
			SU=0;
		}
		
		friend istream & operator>>(istream & is, Nadpis & nad);
		friend ostream & operator<<(ostream & os, Nadpis & nadd);
		

		
		int id;
		string login;
		string password;
		int val;
		int SU;
		
};
class Uzyty{
	public:
		friend void Edycja(Wsk *&wsk, Stat *&stat);
		
		int *id;
		int N;
		string *log;
		string *pas;
		int *val;
		int *SU;
		char path[100];
		
		Uzyty(){

				fstream Login;
				cout<<"Podaj nazwe pliku do skopiowania ktory znajduje sie w katalogu programu"<<endl;
				cin>>path;
				Login.open(path, ios::in);
				Login >> N;
				
				id=new int[N];
				log=new string[N];
				pas=new string[N];
				val=new int[N];
				SU=new int[N];
				
				
				for(int i=0;i<N;i++){
					Login >> id[i];
					Login >> log[i];
					Login >> pas[i];
					Login >> val[i];
					Login >> SU[i];
				}
				Login.close();
				
		}
		
};
class DodOdej{
	public:
	int ktora;
	int ileee;
	
};
class Uzyt{
	public:
		friend void Edycja(Wsk *&wsk, Stat *&stat);
		
		int *id;
		int N;
		string *log;
		string *pas;
		int *val;
		int *SU;
		
		Uzyt & operator[](int i){
			cout<<id[i]<<" "<<log[i]<<" "<<pas[i]<<" "<<val[i]<<" "<<SU[i];
		//	cout<<"elo";
			return *this;
		}
		Uzyt & operator()(){
			int x;
			for(int i=0;i<N;i++){
			if(val[i]>val[i+1]){
				x=i;
			}	
			}
			cout<<"Najbogadszy jest: "<<log[x]<<" "<<pas[x];
			return *this;
		}
		friend void operator==(Uzyt uu, string x);
		
		Uzyt *operator->(){
			return this;
		}
		
		Uzyt operator=( int u){
			val[0]= u;
		}
		Uzyt operator+(DodOdej xs){
			val[xs.ktora]= val[xs.ktora]+xs.ileee;
			return *this;
		}
		Uzyt operator-(DodOdej xs){
			val[xs.ktora]= val[xs.ktora]-xs.ileee;
			return *this;
		}
		
	Uzyt(){

				fstream Login;
				Login.open("conf.txt", ios::in);
				Login >> N;
				
				id=new int[N];
				log=new string[N];
				pas=new string[N];
				val=new int[N];
				SU=new int[N];
				
				
				for(int i=0;i<N;i++){
					Login >> id[i];
					Login >> log[i];
					Login >> pas[i];
					Login >> val[i];
					Login >> SU[i];
				}
				Login.close();
				
		}
	~Uzyt(){
		fstream Login;
				remove("conf.txt");
		Login.open("conf.txt", ios::out);
			Login << N<<endl;
		for(int i=0;i<N;i++){
				Login << id[i] << " " << log[i] << " " << pas[i] <<" "<< val[i]<< " "<< SU[i]<<endl;
		}
		//Login << N << " " << stat->log << " " << stat->pas<<" "<<stat->val;
		Login.close();
	}
	

	
};


istream & operator>>(istream & is, Nadpis & nad){
	cout << "Kolejno......... "<<endl;
	cout << "Login: ";
	is >> nad.login;
	cout << "Haslo: ";
	is >> nad.password;
	cout << "Stan_konta: ";
	is >> nad.val;
	cout << "Czy_SU: ";
	is >> nad.SU;
	return is;
}


		ostream & operator<<(ostream & os, Nadpis & nadd){
			os << nadd.id<<" "<<nadd.login<<" "<<nadd.password<<" "<<nadd.val<<" "<<nadd.SU;
			return os;
		}

void powitanie();
void opcje(Stat *&stat);
void create(Stat *&stat);
void LogIN(Stat *&stat);
void zapisz_val(Stat *&stat);
void wplac(Stat *&stat);
void wyplac(Stat *&stat);
void Edycja(Wsk *&wsk, Stat *&stat);
void Nadpisuje(Nadpis nad);
void uzyje(int I);
void najnaj();
void bogatszy();
void operator==(Uzyt uu, string x);
void szukam();
void dodaj();
void odejmij();
void nowa_baza();
void nad_sup();
void daj_pieniazka_adminowi();

int main(){
	Stat *stat= new Stat;
	powitanie();
	opcje(stat);
	
	return 0;
}
void powitanie(){
	cout << "Witaj w ATS"<<endl;
}
void opcje(Stat *&stat){
	
	/*Super User*/
	if(stat->SU==1){
		Wsk *wsk[4];
		SUser suser(*stat);
		cout<< "Witaj SU ~~"<<suser.log<<"~~"<<endl;
		cout<< "---------------"<<endl;
		cout<< "1. Lista userow"<<endl;
		cout<< "2. Edycja userow"<<endl;
		cout<< "3. Lista pracownikow"<<endl;
		cout<< "5. Wyloguj"<<endl;
		cout<< "Twoja decyzja: ";
		cin >> stat->decyzja;
		
			switch(stat->decyzja){
			case 1:
				system("cls");
				cout<< "Lista Uzytkownikow"<<endl;
				cout<< "_________________________"<<endl<<endl<<endl;
				wsk[0]=new Uzytkownik;
				wsk[0]->wypisz();
				system("pause");
				system("cls");
				opcje(stat);
				break;
			case 2:
				wsk[1]=new Uzytkownik;
				Edycja(wsk[1], stat);
				opcje(stat);
				break;
			case 3:
				system("cls");
				cout<< "Lista Pracownikow"<<endl;
				cout<< "_________________________"<<endl<<endl<<endl;
				wsk[2]=new Pracownik;
				wsk[2]->wypisz();
				system("pause");
				system("cls");
				opcje(stat);
				break;
			case 5:
				zapisz_val(stat);
				stat->logged=0;
				stat->id=999;
				stat->log="0";
				stat->pas="0";
				stat->SU=0;
				cout << "Wylogowano!"<<endl;
				system("pause");
				system("cls");
				opcje(stat);
				break;
			default:
				cout<<"Bledna wartosc"<<endl;
				system("pause");
				system("cls"); 
				opcje(stat);
				break;
			}
		}
	/*koniec Super User*/
	
	if(stat->logged==0){
		cout<< "Niezalogowany!"<<endl;
		cout<< "---------------"<<endl;
		cout<< "1. Zaloguj sie"<<endl;
		cout<< "2. Stworz konto"<<endl;
		cout<< "3. Exit"<<endl;
		cout<< "Twoja decyzja: ";
	}
	else if(stat->logged==1){
		cout<< "Zalogowany!					Posiadasz: "<<stat->val<<"zl. "<<endl;
		cout<< "---------------"<<endl;
		cout << "1. Wyloguj."<<endl;
		cout << "2. Wplac."<<endl;
		cout << "3. Wyplac."<<endl;
		cout << "Twoja decyzja: ";
	}
	else cout<<"Error blad w zmiennej logged";
	
	cin >> stat->decyzja;
	if(stat->logged==0){
		switch(stat->decyzja){
			case 1:
				LogIN(stat);
				break;
			case 2:
				create(stat);
				break;
			case 3:
				exit( 0 );
				break;
			default:
				cout<<"Bledna wartosc"<<endl;
				system("pause");
				system("cls"); 
				opcje(stat);
				break;
		}
	}
	if(stat->logged==1){
		switch(stat->decyzja){
		case 1:
			zapisz_val(stat);
			stat->logged=0;
			stat->id=999;
			stat->log="0";
			stat->pas="0";
			cout << "Wylogowano!"<<endl;
			system("pause");
			system("cls");
			opcje(stat);
			break;
		case 2:
			wplac(stat);
			break;
		case 3:
			wyplac(stat);
			break;
		default:
			cout<<"Bledna wartosc"<<endl;
			system("pause");
			system("cls"); 
			opcje(stat);
			break;
		}

	}
}

void create(Stat *&stat){
			int N;
		fstream Login;
		Login.open("conf.txt", ios::in);
			Login >> N;
			
		Users **users= new Users*[N];
		for(int i=0;i<N;i++){
			users[i]=new Users;
			Login >> users[i]->id;
			Login >> users[i]->log;
			Login >> users[i]->pas;
			Login >> users[i]->val;
			Login >> users[i]->SU;
		}
		Login.close();
	
	system("cls");
	cout << "Tworzenie nowego konta: "<<endl;
	cout<<"Login: ";
	cin >> stat->log;//tu mozna przeciazyc pobranie;
	for(int i=0;i<N;i++){
		if(stat->log==users[i]->log){
			cout<<"Jest juz taki urzytkownik."<<endl;
			system("pause");
			system("cls");
			create(stat);
		}
	}
	cout<<"Haslo: ";
	cin >> stat->pas;
	
	stat->val=0;//poczatkowy stan konta
	stat->SU=0;//wartosc kazdego nowego konat
	//Aby stworzyc SU trzeba recznie nadpisac .txt

		remove("conf.txt");
		Login.open("conf.txt", ios::out);
			Login << (N+1)<<endl;
		for(int i=0;i<N;i++){
			Login << users[i]->id << " " << users[i]->log << " " << users[i]->pas <<" "<< users[i]->val<<" "<<users[i]->SU<< endl;
		}
		Login << N << " " << stat->log << " " << stat->pas<<" "<<stat->val<<" "<< stat->SU;
		Login.close();
		
		for(int i=0;i<N;i++){
			delete users[i];
		}
		delete [] users;
	
	
	
	system("cls");
	cout<<" _______________"<<endl;
	cout<<"|Konto utworzone|"<<endl;
	cout<<" ~~~~~~~~~~~~~~~"<<endl;
	opcje(stat);
}
void LogIN(Stat *&stat){//funkcja logujaca. Pierw pobiera baze danych z pliku conf.txt nastepnie porownuje z loginem i haslem od uzytkownika i porownuje z baza danych.
system("cls");
cout<< "Proces Logowania"<<endl;
cout<< "________________"<<endl;
int N;
	fstream Login;
	Login.open("conf.txt", ios::in);
		Login >> N;
		
	Users **users= new Users*[N];
	for(int i=0;i<N;i++){
		users[i]=new Users;
		Login >> users[i]->id;
		Login >> users[i]->log;
		Login >> users[i]->pas;
		Login >> users[i]->val;
		Login >> users[i]->SU;
	}

	cout << "Login: ";
	cin >> stat->log;
	cout << "Haslo: ";
	cin >> stat->pas;
	
	for(int i=0;i<N;i++){
		if(users[i]->log==stat->log){
			if(users[i]->pas==stat->pas){
			stat->logged=1;
			stat->id=users[i]->id;
			stat->val=users[i]->val;
			stat->SU=users[i]->SU;
			}	
		}
		delete users[i];
	}
	delete [] users;
	Login.close();	
	
	if(stat->logged==0){
		cout<<endl;
		cout<<"________________________________"<<endl;
		cout<<"Bledny login lub haslo"<<endl;
		string str;
		cout<< "Chcesz sprobowac jeszcze raz? [T/N] ";
		cin >> str;
		if((str=="T")||(str=="t")){
			LogIN(stat);
		}
	}
	
	system("cls");
	opcje(stat);
}
void zapisz_val(Stat *&stat){
				int N;
		fstream Login;
		Login.open("conf.txt", ios::in);
			Login >> N;
			
		Users **users= new Users*[N];
		for(int i=0;i<N;i++){
			users[i]=new Users;
			Login >> users[i]->id;
			Login >> users[i]->log;
			Login >> users[i]->pas;
			Login >> users[i]->val;
			Login >> users[i]->SU;
		}
		Login.close();

		remove("conf.txt");
		Login.open("conf.txt", ios::out);
			Login << N<<endl;
		for(int i=0;i<N;i++){
			if(stat->id!=i){
				Login << users[i]->id << " " << users[i]->log << " " << users[i]->pas <<" "<< users[i]->val<< " "<< users[i]->SU<<endl;
			}
			else{
				Login << stat->id<<" "<<stat->log<<" "<<stat->pas<<" "<<stat->val<<" "<<stat->SU<<endl;
			}
		}
		//Login << N << " " << stat->log << " " << stat->pas<<" "<<stat->val;
		Login.close();
		
		for(int i=0;i<N;i++){
			delete users[i];
		}
		delete [] users;
}
void wplac(Stat *&stat){
	system("cls");
	int x;
	cout<<"Ile chcialbys wplacic. 				Posiadasz: "<<stat->val<<"zl."<<endl;
	cin >> x;
	
	if(x>1000000){
		cout<<"Powiedzmy sobie szczerze... nigdy nie bedziesz mial takiej sumy pieniedzy"<<endl;
		system("pause");
		system("cls");
		opcje(stat);
	}
	
	stat->val=stat->val+x;
	system("cls");
	opcje(stat);
}
void wyplac(Stat *&stat){
	system("cls");
	int x;
	cout<<"Ile chcialbys wyplacic. 				Posiadasz: "<<stat->val<<"zl."<<endl;
	cin >> x;
	if(stat->val>=x){
	stat->val=stat->val-x;
	}
	else{
		cout<< "Nie masz tyle pieniedzy"<<endl;
		system("pause");
		wyplac(stat);
	}
	system("cls");
	opcje(stat);
}
void Edycja(Wsk *&wsk, Stat *&stat){
	system("cls");
	int wybur;
	cout<<"Witaj w panelu edycji Userow"<<endl;
	cout<<"_______________________"<<endl<<endl;
	cout<<"1. Nadpisz Usera"<<endl;
	cout<<"2. Szukanie loginem"<<endl;
	cout<<"3. Wyjdz z edycji"<<endl;
	cout<<"4. Szukanie po ID"<<endl;
	cout<<"5. Kto jest najbogadszy"<<endl;
	cout<<"6. Pieniadze dla 1 usera"<<endl;
	cout<<"7. Dodaj Value"<<endl;
	cout<<"8. Odejmij Value"<<endl;
	cout<<"Twoj wybor: ";
	cin >> wybur;

	Nadpis nah;
	switch(wybur){
		case 1:
			system("cls");
			wsk->wypisz();
			cout<<endl<<"Ktorego usera chcesz nadpisac: ";

			cin >> nah.id;
			cin >> nah;
			cout << nah;
			cout<<endl<<"Nadpisac [T/t] ";
			char t;
			cin >> t;
			if((t=='t')or(t='T')){
				Nadpisuje(nah);
			}	
	
			cout<<"Nadpisano";
			wsk=new Uzytkownik;
			system("pause");
			Edycja(wsk, stat);
			break;
		case 2:
			szukam();
			Edycja(wsk, stat);
			break;
		case 3:
			system("cls");
			opcje(stat);
			break;
		case 4:
			system("cls");
			cout<<"Szukanie po ID"<<endl;
			
			cout<<"___________________"<<endl<<endl;
			cout<<"Podaj ID: ";
			int I;
			cin >> I;
			uzyje(I);
			cout<< endl;
			system("pause");
			Edycja(wsk, stat);
			break;
		case 5:
			najnaj();
			Edycja(wsk, stat);
			break;
		case 6:
			system("cls");
			daj_pieniazka_adminowi();
			system("pause");
			Edycja(wsk, stat);
			break;
		case 7:
			system("cls");
			dodaj();
			system("pause");
			Edycja(wsk, stat);
			break;
		case 8:
			system("cls");
			odejmij();
			system("pause");
			Edycja(wsk, stat);
			break;
			
		default:
			cout<<"Bledna wartosc"<<endl;
			system("pause");
			system("cls"); 
			Edycja(wsk, stat);
			break;
	}
	
}
void Nadpisuje(Nadpis nad){
	int N;
		fstream Login;
		Login.open("conf.txt", ios::in);
			Login >> N;
			
		Users **users= new Users*[N];
		for(int i=0;i<N;i++){
			users[i]=new Users;
			Login >> users[i]->id;
			Login >> users[i]->log;
			Login >> users[i]->pas;
			Login >> users[i]->val;
			Login >> users[i]->SU;
		}
		Login.close();

		remove("conf.txt");
		Login.open("conf.txt", ios::out);
			Login << N<<endl;
		for(int i=0;i<N;i++){
			if(nad.id!=i){
				Login << users[i]->id << " " << users[i]->log << " " << users[i]->pas <<" "<< users[i]->val<< " "<< users[i]->SU<<endl;
			}
			else{
				Login << nad.id<<" "<<nad.login<<" "<<nad.password<<" "<<nad.val<<" "<<nad.SU<<endl;
			}
		}
		//Login << N << " " << stat->log << " " << stat->pas<<" "<<stat->val;
		Login.close();
		
		for(int i=0;i<N;i++){
			delete users[i];
		}
		delete [] users;
}
void uzyje(int I){
	Uzyt uu;
	uu[I];
}
void najnaj(){
	system("cls");
	Uzyt uu;
	uu();
	cout<<endl;
	system("pause");
}
void operator==(Uzyt uu, string x){
	for(int i=0;i<uu.N;i++){
		if(x==uu.log[i]){
			cout<<uu.id[i]<<" "<<uu.log[i]<< " "<< uu.pas[i]<<endl;
		}
	}
	cout<<"Wszystko co zostalo znalezione";
}
void szukam(){
	system("cls");
	Uzyt uu;
	cout<<"Szukanie loginem"<<endl;
	cout<<"_______________________"<<endl<<endl;
	cout<<"Podaj login: ";
	string x;
	cin >> x;
	uu==x;
	cout<<endl;
	system("pause");
}
void daj_pieniazka_adminowi(){
	Uzyt sss;
	cout<<"Piedniadze dla 1 uztkownika: ";
	int XYX;
	cin >> XYX;
	sss = XYX;
}
void dodaj(){
	Uzyt uu;
	DodOdej x;	
	cout<<"Komu chcesz dodac pieniedzy? ID: ";
	cin>>x.ktora;
	cout<<"Ile chcesz dodac pieniedzy: ";
	cin>>x.ileee;
	uu= uu+x;
}
void odejmij(){
	Uzyt uu;
	DodOdej x;	
	cout<<"Komu chcesz odjac pieniedze? ID: ";
	cin>>x.ktora;
	cout<<"Ile chcesz odjac pieniedzy: ";
	cin>>x.ileee;
	uu= uu-x;
}
