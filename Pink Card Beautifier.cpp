#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#define MAX 30000

using namespace std;

int whileSayac = 0;
char transfer[MAX][MAX];

class k {
public:
	char no[MAX][16];
	char ay[MAX][2];
	char yil[MAX][4];
	char cvv[MAX][3];

	ofstream of;
	ifstream ofin;

	void setNo() {
		for (int p = 0; p <= whileSayac; p++) {
			for (int i = 0; i < 16; i++) {
				no[p][i] = transfer[p][i];
			}
		}
	}
	void setAy() {
		for (int p = 0; p <= whileSayac; p++) {
			for (int i = 0; i < 2; i++) {
				ay[p][i] = transfer[p][i + 16];
			}
		}
	}
	void setYil() {
		for (int p = 0; p <= whileSayac; p++) {
			if ((transfer[p][18] == '2') && (transfer[p][19] == '0')) {
				if (((transfer[p][20] == '2') && (transfer[p][21] >= '1')) || ((transfer[p][20] == '3') && (transfer[p][21] >= '0'))) {

					for (int i = 0; i < 4; i++) {
						yil[p][i] = transfer[p][i + 18];
					}
					for (int i = 0; i < 3; i++) {
						cvv[p][i] = transfer[p][i + 22];
					}
				}
			}
			else {
				yil[p][0] = '2';
				yil[p][1] = '0';

				for (int i = 0; i < 2; i++) {
					yil[p][i + 2] = transfer[p][i + 18];

				}
				for (int i = 0; i < 3; i++) {
					cvv[p][i] = transfer[p][i + 20];
				}
			}
		}
	}

	void setCvv() {
		for (int p = 0; p <= whileSayac; p++) {
			for (int i = 0; i < 3; i++) {
				cvv[p][i] = transfer[p][i + 22];
			}
		}
	}
};

int rawSayac = 0;
bool checkIlk = 0;

bool fexists(const char* filename)
{
	ifstream ifile(filename);
	return ifile.good();
}

void d() {
	setlocale(LC_ALL, "Turkish");


	if (!(fexists("txt.txt"))) {
		cout << "Pink Credit Card Beautifier by Raypun" << endl << endl;
		cout << "'txt.txt' isimli dosyaya düzeltilecek kartlarý yapýþtýrýnn  /  Paste the cards into a file named 'txt.txt'" << endl;

	}
	else {

		ifstream in("txt.txt");
		string raw;

		int ilkOlc = 0;
		int r = 0;

		k kart;

		while (getline(in, raw)) {
			rawSayac = 0;
			ilkOlc = 0;
			r = 0;
			while (raw[rawSayac] != '\0') {

				if ((raw[rawSayac] >= '0') && (raw[rawSayac] <= '9')) {

					transfer[whileSayac][r] = raw[rawSayac];
					r++;
				}
				rawSayac++;
			}
			whileSayac++;
		}
		kart.setNo();
		kart.setAy();
		kart.setYil();

		kart.of.open("output.txt");

		for (int p = 0; p <= whileSayac; p++) {
			for (int i = 0; i < 16; i++) {
				kart.of << kart.no[p][i];
			}
			kart.of << "|";
			for (int i = 0; i < 2; i++) {
				kart.of << kart.ay[p][i];
			}
			kart.of << "|";
			for (int i = 0; i < 4; i++) {
				kart.of << kart.yil[p][i];
			}
			kart.of << "|";
			for (int i = 0; i < 3; i++) {
				kart.of << kart.cvv[p][i];
			}
			kart.of << endl;
		}
		kart.of.close();
		ifstream iff;
		string son;

		kart.ofin.open("output.txt");

		ofstream of2("duzeltilenler.txt");

		while (getline(kart.ofin, son)) {
			if (((son[0] == '4') || (son[0] == '5')) && (son[27] != '\0')) {
				of2 << son << endl;
			}
		}
		kart.ofin.close();
		of2.close();
		remove("output.txt");

		cout << "Pink Credit Card Beautifier by Raypun" << endl << endl;
		cout << "'duzeltilenler.txt' içine kaydedildi  /  Saved into 'duzeltilenler.txt'" << endl<<endl<<endl;
	}
}

int main() {
	d();
	system("pause");
}
