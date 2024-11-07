#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
  
  
           /// CLASA I FUNKCII//
  
  
class smetka
{
	int brsmetka;
	char ime[50];
	int deposit;
	char vid;
public:
	void napravi_smetka();	//funkcija da se dodade korisnik
	void pokazi_smetka() const;	// funkcija da prikaze detali na ekran
	void promeni();	//funkcija da se proemenat detali
	void dep(int);	//funkcija da prifati suma i da ja dodade na smetkata
	void izvadi(int);	//funkcija za vadenje suma na pari od smetka
	void pok_tab() const;	//funkcija da prikazuva detali vo tabelaren izlez
	int vrati_br_smetka() const;	//funkcija da vrati broj na smetka
	int vrati_balans() const;	//funkcija da ni vrate balans na smetka
	char vrati_vid() const;	//funkcija da ni vrate vid na smetka
};        

void smetka::napravi_smetka()
{
	cout<<"\nVnesi broj na smetka :";
	cin>>brsmetka;
	cout<<"\n\nIme na klientot : ";
	cin.ignore();
	cin.getline(ime,50);
	cout<<"\nVnesi vid na smetka (F/K) : ";
	cin>>vid;
	vid=toupper(vid);
	cout<<"\nVnesi suma  ";
	cin>>deposit;
	cout<<"\n\n\nSmetkata e napravena..";
}

void smetka::pokazi_smetka() const
{
	cout<<"\nBroj na smetka : "<<brsmetka;
	cout<<"\nIme na klientot : ";
	cout<<ime;
	cout<<"\nVid na smetka : "<<vid;
	cout<<"\nBalans na smetkata : "<<deposit;
}


void smetka::promeni()
{
	cout<<"\nBroj na smetka : "<<brsmetka;
	cout<<"\nPromeni ime na klientot : ";
	cin.ignore();
	cin.getline(ime,50);
	cout<<"\nPromeni vid na smetka : ";
	cin>>vid;
	vid=toupper(vid);
	cout<<"\nPromeni balans na smetka : ";
	cin>>deposit;
}

void smetka::dep(int x)
{
	deposit+=x;
}
	
void smetka::izvadi(int x)
{
	deposit-=x;
}
	
void smetka::pok_tab() const
{
	cout<<brsmetka<<setw(10)<<" "<<ime<<setw(10)<<" "<<vid<<setw(6)<<deposit<<endl;
}

	
int smetka::vrati_br_smetka() const
{
	return brsmetka;
}

int smetka::vrati_balans() const
{
	return deposit;
}

char smetka::vrati_vid() const
{
	return vid;
}


//KRJA NA KLASA //

//DEKLARACIJA NA FUNKCII

void napisi_smetka();	//funkciaj za zapisuvanje vo binaren fajl
void prikazi_detali(int);	//funkcija za prikazuvanje detali dadeni od korisnikot
void promeni_na_smetka(int);	//funkcija za promenuvanje na zapisanoto vo fajlot
void izbrisi_smetka(int);	//funkcija za brisenje vo fajlot
void prikazi_se();		//funkcija za prikazuvanje na site smetki so detali
void deposit_povlekuvanje(int, int); // funkcija za depozit/povelekuvanje sredstva za dadena smetka 
void intro();	//vovedna funckija na ekran



//Main funkcijata//


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tGLAVNO MENI";
		cout<<"\n\n\t01. NOVA SMETKA";
		cout<<"\n\n\t02. DEPOSIT ";
		cout<<"\n\n\t03. IZVADENA SUMA";
		cout<<"\n\n\t04. BALANS NA SMETKA";
		cout<<"\n\n\t05. IMINJA NA SITE SMETKI";
		cout<<"\n\n\t06. ZATVORI SMETKA";
		cout<<"\n\n\t07. PROMENI NA SMETKA";
		cout<<"\n\n\t08. IZLEZI";
		cout<<"\n\n\tIZBERETE JA VASATA OPCIJA (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			napisi_smetka();
			break;
		case '2':
			cout<<"\n\n\tVnesi broj na smetka : "; cin>>num;
			deposit_povlekuvanje(num, 1);
			break;
		case '3':
			cout<<"\n\n\tVnesi broj na smetka  : "; cin>>num;
			deposit_povlekuvanje(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tVnesi broj na smetka  : "; cin>>num;
			prikazi_detali(num);
			break;
		case '5':
			prikazi_se();
			break;
		case '6':
			cout<<"\n\n\tVnesi broj na smetka  : "; cin>>num;
			izbrisi_smetka(num);
			break;
		 case '7':
			cout<<"\n\n\tVnesi broj na smetka  : "; cin>>num;
			promeni_na_smetka(num);
			break;
		 case '8':
			cout<<"\n\n\tVi blagodarime za korsitenje na nasiot sistem";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}



//FUNKCIJA ZA PISUVANJE VO FAJL


void napisi_smetka()
{
	smetka ac;
	ofstream outFile;
	outFile.open("smetka.dat",ios::binary|ios::app);
	ac.napravi_smetka();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(smetka));
	outFile.close();
}


//funkcija za citanje spec detali od smetka//

void prikazi_detali(int n)
{
	smetka ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("smetka.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fajlot ne moze da bide otvoren !! Pritisni bilo koe kopce...";
		return;
	}
	cout<<"\nBALANS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(smetka)))
	{
		if(ac.vrati_br_smetka()==n)
		{
			ac.pokazi_smetka();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nBrojot na smetka ne postoi";
}


//FUNKCIJA DA PROMENIS VO FAJLOT//

void promeni_na_smetka(int n)
{
	bool found=false;
	smetka ac;
	fstream File;
	File.open("smetka.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Fajlot ne moze da bide otvoren !! Pritismi bilo koe kopce....";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(smetka));
		if(ac.vrati_br_smetka()==n)
		{
			ac.pokazi_smetka();
			cout<<"\n\nVnesi novi detali za smetkata"<<endl;
			ac.promeni();
			int pos=(-1)*static_cast<int>(sizeof(smetka));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(smetka));
			cout<<"\n\n\t Novi detali Vneseni";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Ne e pronajdeno ";
}



//FUNKCIJA ZA BRISENJE DEL OD FAJLO//


void izbrisi_smetka(int n)
{
	smetka ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("smetka.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fajlot ne moze da se otvori !! Pritisni kopce...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(smetka)))
	{
		if(ac.vrati_br_smetka()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(smetka));
		}
	}
	inFile.close();
	outFile.close();
	remove("smetka.dat");
	rename("Temp.dat","smetka.dat");
	cout<<"\n\n\tIzbrisano ..";
}

//Funkcija da se prikazat site smetki//

void prikazi_se()
{
	smetka ac;
	ifstream inFile;
	inFile.open("smetka.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fajlot ne moze da se otvori !! Pritisni kopce...";
		return;
	}
	cout<<"\n\n\t\tLISTA NA SMETKI\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      IME           VID       BALANS\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(smetka)))
	{
		ac.pok_tab();
	}
	inFile.close();
}

//FUNKCIJA ZA DEPOSIT I POVLEKUVANJE NA SUMI//



void deposit_povlekuvanje(int n, int option)
{
	int amt;
	bool found=false;
	smetka ac;
	fstream File;
	File.open("smetka.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Fajlot ne moze da se otvori !! Pritisni kopce...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(smetka));
		if(ac.vrati_br_smetka()==n)
		{
			ac.pokazi_smetka();
			if(option==1)
			{
				cout<<"\n\n\tVNESETE SREDSTVA ";
				cout<<"\n\nVnesete suma na sredstva";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tPOVLEKUVANJE NA SREDSTVA";
				cout<<"\n\nVnesete suma za povlekuvanje";
				cin>>amt;
				int bal=ac.vrati_balans()-amt;
				if((bal<500 && ac.vrati_vid()=='S') || (bal<1000 && ac.vrati_vid()=='C'))
					cout<<"Nemate dovolno sredstva";
				else
					ac.izvadi(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(smetka));
			cout<<"\n\n\t ZAcuveno";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Ne e pronajdeno ";
}

//VOVED//


void intro()
{
	cout<<"\n\n\n\t  BANKA";
	cout<<"\n\n\tMENEGMENT";
	cout<<"\n\n\t  SISTEM";
	cout<<"\n\n\n\nNAPRAVENO OD : NIKOLA KOSTURSKI";
	cout<<"\n\nFAKULTET : FAKULTET ZA INOFRMATIKA GOCE DELCEV STIP";
	cin.get();
}
