
            

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int izbor;
    cout << "Izberi sto sakas da presmetas:\n";
    cout << "1 - Ednostavna kamata\n";
    cout << "2 - Slozena kamata\n";
    cout << "3 - Renta (naemnina)\n";
    cout << "Izbor: ";
    cin >> izbor;

    if (izbor == 1) {
        // Ednostavna kamata
        double ulog, kamata, vreme;
        cout << "Vnesi ulog: ";
        cin >> ulog;
        cout << "Vnesi godishna kamata (%): ";
        cin >> kamata;
        cout << "Vnesi vreme (vo godini): ";
        cin >> vreme;

        double iznos = ulog * (1 + (kamata / 100) * vreme);
        cout << "Kraen iznos so ednostavna kamata: " << iznos << endl;
    }
    else if (izbor == 2) {
        // Slozena kamata
        double ulog, kamata, vreme;
        cout << "Vnesi ulog: ";
        cin >> ulog;
        cout << "Vnesi godishna kamata (%): ";
        cin >> kamata;
        cout << "Vnesi vreme (vo godini): ";
        cin >> vreme;

        double iznos = ulog * pow(1 + kamata / 100, vreme);
        cout << "Kraen iznos so slozena kamata: " << iznos << endl;
    }
    else if (izbor == 3) {
        // Renta
        double mesecna_renta;
        int meseci;

        cout << "Vnesi mesecna renta: ";
        cin >> mesecna_renta;
        cout << "Vnesi broj na meseci: ";
        cin >> meseci;

        double vkupno = mesecna_renta * meseci;
        cout << "Vkupna renta za " << meseci << " meseci e: " << vkupno << endl;
    }
    else {
        cout << "Nevaliden izbor!" << endl;
    }

    return 0;
}
