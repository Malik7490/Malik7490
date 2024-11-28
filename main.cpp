
/*Bibliothèque de Gestion de Contacts

1 Ajouter un contact avec nom, numéro de téléphone, email, et adresse.
2 Modifier les informations d'un contact.
3 Supprimer un contact de la liste.
4 Rechercher des contacts par nom
5 Trier les contacts par nom
6 Sauvegarder et charger les contacts dans un fichie*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

 //cout << "------------ Structure pour représenter un contact -----------------" << endl;
struct Contact {
    string name;          // Nom du contact
    string phone;         // Numéro de téléphone
    string email;         // Email
    string address;       // Adresse
};
//cout << "-----------------------------" << endl;


 //cout << "-------------Fonction pour afficher un contact----------------" << endl;
void displayContact(const Contact& contact) {
    cout << "Nom: " << contact.name << endl;
    cout << "Téléphone: " << contact.phone << endl;
    cout << "Email: " << contact.email << endl;
    cout << "Adresse: " << contact.address << endl;
    cout << "-----------------------------" << endl;
}

// cout << "-------------Fonction pour ajouter un contact----------------" << endl;
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Entrez le nom: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Entrez le numéro de téléphone: ";
    getline(cin, newContact.phone);
    cout << "Entrez l'email: ";
    getline(cin, newContact.email);
    cout << "Entrez l'adresse: ";
    getline(cin, newContact.address);

    contacts.push_back(newContact); // Ajouter le contact à la liste
    cout << "Contact ajouté avec succès !" << endl;
     cout << "-----------------------------" << endl;
}

  //cout << "--------------Fonction pour modifier un contact---------------" << endl;
void editContact(vector<Contact>& contacts) {
    string searchName;
    cout << "Entrez le nom du contact à modifier: ";
    cin.ignore();
    getline(cin, searchName);

    for (auto& contact : contacts) {
        if (contact.name == searchName) {
            cout << "Modifiez les informations (laissez vide pour conserver l'ancien):" << endl;

            string input;
            cout << "Nom (" << contact.name << "): ";
            getline(cin, input);
            if (!input.empty()) contact.name = input;

            cout << "Téléphone (" << contact.phone << "): ";
            getline(cin, input);
            if (!input.empty()) contact.phone = input;

            cout << "Email (" << contact.email << "): ";
            getline(cin, input);
            if (!input.empty()) contact.email = input;

            cout << "Adresse (" << contact.address << "): ";
            getline(cin, input);
            if (!input.empty()) contact.address = input;

            cout << "Contact modifié avec succès !" << endl;
            return;
        }
    }
    cout << "Contact non trouvé !" << endl;
     cout << "-----------------------------" << endl;

}

//  cout << "--------------Fonction pour supprimer un contact---------------" << endl;
void deleteContact(vector<Contact>& contacts) {
    string searchName;
    cout << "Entrez le nom du contact à supprimer: ";
    cin.ignore();
    getline(cin, searchName);

    auto it = remove_if(contacts.begin(), contacts.end(),
                        [&searchName](const Contact& contact) { return contact.name == searchName; });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        cout << "Contact supprimé avec succès !" << endl;
    } else {
        cout << "Contact non trouvé !" << endl;
         cout << "-----------------------------" << endl;
    }
}

 //cout << "-------------Fonction pour rechercher un contact par nom----------------" << endl;
void searchContact(const vector<Contact>& contacts) {
    string searchName;
    cout << "Entrez le nom du contact à rechercher: ";
    cin.ignore();
    getline(cin, searchName);

    for (const auto& contact : contacts) {
        if (contact.name.find(searchName) != string::npos) {
            displayContact(contact);
        }
    }
}

//  Trier les contacts par nom
void sortContacts(vector<Contact>& contacts) {
    sort(contacts.begin(), contacts.end(),
         [](const Contact& a, const Contact& b) { return a.name < b.name; });
    cout << "Contacts triés par nom !" << endl;
}

//  sauvegarder les contacts dans un fichier
void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);

    if (!file) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << "," << contact.phone << ","
             << contact.email << "," << contact.address << endl;
    }
    file.close();
    cout << "Contacts sauvegardés dans le fichier " << filename << endl;
}

// chargerement des contacts depuis un fichier qu'ont a nommer Filename
void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);

    if (!file) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return;
    }

    contacts.clear(); // cette fonction permet Effacer les anciens contacts avant de charger
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        Contact contact;
        pos = line.find(',');
        contact.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        contact.phone = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        contact.email = line.substr(0, pos);
        line.erase(0, pos + 1);

        contact.address = line;
        contacts.push_back(contact);
    }
    file.close();
    cout << "Contacts chargés depuis le fichier " << filename << endl;
}

// voici le Menu principal auquel l'utlisateur fera les choix
int main() {
    setlocale(LC_ALL, ""); //  paramètres régionaux pour les caractères spéciaux

    vector<Contact> contacts; // Liste de contacts
    string filename = "contacts.txt"; // Nom du fichier dans lesquel les contacte seront sauvegarder
    int choice;

    do {
        cout << "\n**********Menu de Gestion de Contacts********\n";
        cout << "1. Ajouter un contact\n";
        cout << "2. Modifier un contact\n";
        cout << "3. Supprimer un contact\n";
        cout << "4. Rechercher un contact\n";
        cout << "5. Trier les contacts\n";
        cout << "6. Sauvegarder les contacts\n";
        cout << "7. Charger les contacts\n";
        cout << "8. Quitter\n";
        cout << "Choix: ";
        cout << "\n************Cher Utilisateur Veillez faire le choix entre 1 à 8**************\n";
        cin >> choice;
        cout << "\n************Votre choix est approuvé; merci **************\n";
        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: editContact(contacts); break;
            case 3: deleteContact(contacts); break;
            case 4: searchContact(contacts); break;
            case 5: sortContacts(contacts); break;
            case 6: saveContacts(contacts, filename); break;
            case 7: loadContacts(contacts, filename); break;
            case 8: cout << "Au revoir !" << endl; break;
            default: cout << "Choix invalide !" << endl; break;
        }
    } while (choice != 8);

    return 0;
}
