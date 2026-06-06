#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "functii.hpp"

int main()
{
    std::ifstream file("test1.txt"); 
    
    if (!file.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului!" << std::endl;
        return 1;
    }

    Document_El_Tabel** table = init_table();
    
    AVL* avl_arb = 0;
    init_avl(avl_arb);
    bool crescut = false;

    std::string linie;

    if (std::getline(file, linie)) {
        // Antetul a fost sărit
    }

    while (std::getline(file, linie)) {
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string token;
        Document doc;

        for (int i = 0; i < 10; ++i) {
            doc.Cuvinte_Cheie[i] = "";
        }

        if (std::getline(ss, token, ',')) {
            try {
                doc.ID_ARTICOL = std::stoi(trim(token));
            } catch (...) {
                continue; 
            }
        }

        if (std::getline(ss, token, ',')) {
            doc.Titlu_Document = trim(token);
        }

        int indexCuvant = 0;
        while (std::getline(ss, token, ',') && indexCuvant < 10) {
            std::string cuvantCuratat = trim(token);
            if (!cuvantCuratat.empty()) {
                doc.Cuvinte_Cheie[indexCuvant] = cuvantCuratat;
                indexCuvant++;
            }
        }
        insert_table(table,doc);
        crescut = false;
        insert_avl(avl_arb->head,crescut,doc);
    }

    file.close();
    show_table(table);
    return 0;
}