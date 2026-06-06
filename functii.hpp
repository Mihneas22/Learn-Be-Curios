#ifndef FUNCTII_HPP_
#define FUNCTII_HPP_
#include <string>

#define TABLE_SIZE 10000

struct Document{
    int ID_ARTICOL;
    std::string Titlu_Document;
    std::string Cuvinte_Cheie[10];
};

struct Document_El_Tabel{
    Document data;
    Document_El_Tabel* next;
};

struct Nod_AVL{
    Document data;
    int bf;
    Nod_AVL *stg,*drt;
};

struct AVL{
    Nod_AVL* head;
};

std::string trim(const std::string& str);

//AVL
void init_avl(AVL* &arb);
void insert_avl(Nod_AVL* &head,bool &crescut,Document data);
void show(Nod_AVL* head);
void RSS(Nod_AVL* &a);
void RSD(Nod_AVL* &a);
void RDS(Nod_AVL* &a);
void RDD(Nod_AVL* &a);

//Hash Table
Document_El_Tabel** init_table();
void insert_table(Document_El_Tabel** &table,Document data);
void show_table(Document_El_Tabel** table);

//Cerinte
void parcurgere_avl_min_max(int ID_MIN,int ID_MAX);

#endif