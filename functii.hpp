#ifndef FUNCTII_HPP_
#define FUNCTII_HPP_
#include <string>
#include <vector>

#define TABLE_SIZE 10000

struct Document{
    int ID_ARTICOL;
    std::string Titlu_Document;
    std::vector<std::string> Cuvinte_Cheie;
};

struct Document_El_Tabel{
    int key;
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

struct Nod{
    int data;
    Nod* next;
};

struct Stack{
    Nod* head;
};

struct Queue{
    Nod* head;
    Nod* tail;
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
int hash_cuv_cheie(std::vector<std::string> chei);
Document_El_Tabel** init_table();
void insert_table(Document_El_Tabel** &table,Document data);

//Stack
void init_stack(Stack* &s);
void push(Stack* &s,int x);
void pull(Stack* &s);
int top(Stack* s);
bool isEmpty(Stack* s);

//Queue
void init_queue(Queue* &q);
void put(Queue* &q,int x);
void pop(Queue* &q);
int get(Queue* q);
bool isEmptyQueue(Queue* q);

//Cerinta I - AVL
void parcurgere_avl_min_max(Nod_AVL* head, int ID_MIN,int ID_MAX);
void cautare_articol(Nod_AVL* head,int ID_CAUTAT,int &pasi);

//Cerinta 2 - Hash Table
void filtrare_multipla(Document_El_Tabel** &table,std::vector<std::string> cuv_cheie);

//Cerinta 3 - BFS/DFS
void BFS(AVL* arb);
void DFS(AVL* arb);

#endif