#include <iostream>
#include <vector>
using namespace std;

struct Uzol {
    int znachenie;   
    Uzol* sleduyushchiy; 
};


void dobavitVUkonets(Uzol*& golova, int znachenie) {
    Uzol* noviyUzol = new Uzol{znachenie, nullptr};
    if (!golova) {
        golova = noviyUzol;
    } else {
        Uzol* tekushchiy = golova;
        while (tekushchiy->sleduyushchiy) {
            tekushchiy = tekushchiy->sleduyushchiy;
        }
        tekushchiy->sleduyushchiy = noviyUzol;
    }
}


void vvestiSpisok(Uzol*& golova) {
    int chislo; 
    cout << "Введите числа для списка (введите -1 для завершения ввода): " << endl;
    
    while (true) {
        cout << "Введите число: ";
        cin >> chislo; 
        
        if (chislo == -1) {
            break;
        }
        
        dobavitVUkonets(golova, chislo);
    }
}


vector<Uzol*> sozdatMassiv(Uzol* golovaL) {
    vector<Uzol*> massiv(10, nullptr);

    while (golovaL) {
        int pervayaTsifra = abs(golovaL->znachenie); 
        while (pervayaTsifra >= 10) {
            pervayaTsifra /= 10; 
        }
        int indeks = (golovaL->znachenie < 10) ? 0 : pervayaTsifra;
        dobavitVUkonets(massiv[indeks], golovaL->znachenie);
        golovaL = golovaL->sleduyushchiy;
    }

    return massiv;
}


void udalitSpisok(Uzol*& golova) {
    while (golova) {
        Uzol* vremennyy = golova;
        golova = golova->sleduyushchiy;
        delete vremennyy;
    }
}

Uzol* sozdatSpisokIzMassiva(const vector<Uzol*>& massiv) {
    Uzol* noviySpisok = nullptr; 
    for (int i = 0; i < 10; ++i) {
        Uzol* tekushchiy = massiv[i];
        while (tekushchiy) {
            dobavitVUkonets(noviySpisok, tekushchiy->znachenie);
            tekushchiy = tekushchiy->sleduyushchiy;
        }
    }
    return noviySpisok;
}

void vyvestiSpisok(Uzol* golova) {
    Uzol* tekushchiy = golova;
    while (tekushchiy) {
        cout << tekushchiy->znachenie << " ";
        tekushchiy = tekushchiy->sleduyushchiy;
    }
    cout << endl; 

int main() {
    Uzol* golovaL = nullptr;
    
    vvestiSpisok(golovaL);
    
    cout << "Введённый список L: ";
    vyvestiSpisok(golovaL);

    vector<Uzol*> massiv = sozdatMassiv(golovaL);

    for (int i = 0; i < 10; ++i) {
        cout << "massiv[" << i << "]: ";
        vyvestiSpisok(massiv[i]); 
    }

    udalitSpisok(golovaL);

    golovaL = sozdatSpisokIzMassiva(massiv);

    cout << "Новый список L: ";
    vyvestiSpisok(golovaL);

    for (int i = 0; i < 10; ++i) {
        udalitSpisok(massiv[i]); 
    }

    udalitSpisok(golovaL);

    return 0; 
}
