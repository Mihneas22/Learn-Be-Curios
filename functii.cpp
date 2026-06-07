#include "functii.hpp"
#include <iostream>
#include <string>

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

Document_El_Tabel** init_table()
{
    Document_El_Tabel** table = new Document_El_Tabel*[TABLE_SIZE]{nullptr};
    return table;
}
void insert_table(Document_El_Tabel** &table,Document data)
{
    Document_El_Tabel* nou = new Document_El_Tabel{data,nullptr};
    int key = data.ID_ARTICOL % TABLE_SIZE;
    
    if(table[key] == nullptr)
        table[key] = nou;
    else
    {
        nou->next = table[key];
        table[key] = nou;
    }
}
void show_table(Document_El_Tabel** table)
{
    for(int i = 0;i<TABLE_SIZE;i++)
        if(table[i] != nullptr)
            std::cout << table[i]->data.Titlu_Document << std::endl;
}

//AVL
void init_avl(AVL* &arb)
{
    arb = new AVL{nullptr};
}
void insert_avl(Nod_AVL* &head,bool &crescut,Document data)
{
    if(head == nullptr)
    {
        head = new Nod_AVL{data,0,nullptr,nullptr};
        crescut = true;
        return;
    }

    if(data.ID_ARTICOL < head->data.ID_ARTICOL)
    {
        insert_avl(head->stg,crescut,data);

        if(crescut)
        {
            head->bf++;

            if(head->bf == 0)
                crescut = false;
            else if(head->bf == 1)
                crescut = true;
            else if(head->bf == 2)
            {
                if(data.ID_ARTICOL < head->stg->data.ID_ARTICOL)
                    RSD(head);
                else
                    RDD(head);
                crescut = false;
            }
        }
    }else if(data.ID_ARTICOL > head->data.ID_ARTICOL)
    {
        insert_avl(head->drt,crescut,data);

        if(crescut)
        {
            head->bf--;

            if(head->bf == 0)
                crescut = false;
            else if(head->bf == -1)
                crescut = true;
            else if(head->bf == -2)
            {
                if(data.ID_ARTICOL > head->drt->data.ID_ARTICOL)
                    RSS(head);
                else
                    RDS(head);
                crescut = false;
            }
        }
    }
    else
    {
        crescut = false;
        return;
    }
}
void show(Nod_AVL* head)
{
    if(head != nullptr)
    {
        show(head->stg);
        std::cout << head->data.ID_ARTICOL << " ";
        show(head->drt);
    }
}
void RSS(Nod_AVL* &a)
{
    Nod_AVL* b = a->drt;
    a->drt = b->stg;
    b->stg = a;

    a->bf = 0;
    b->bf = 0;

    a = b;
}
void RSD(Nod_AVL* &a)
{
    Nod_AVL* b = a->stg;
    a->stg = b->drt;
    b->drt = a;

    a->bf = 0;
    b->bf = 0;

    a = b;
}
void RDS(Nod_AVL* &a)
{
    Nod_AVL* b = a->drt;
    Nod_AVL* c = b->stg;

    switch (c->bf)
    {
        case 0:
            a->bf = b->bf = 0;
            break;
        
        case 1:
            a->bf = 0;
            b->bf = -1;
            break;

        case -1:
            a->bf = 1;
            b->bf = 0;
            break;

        default:
            break;
    }

    a->drt = c->stg;
    b->stg = c->drt;

    c->bf = 0;
    c->drt = b;
    c->stg = a;

    a = c;
}
void RDD(Nod_AVL* &a)
{
    Nod_AVL* b = a->stg;
    Nod_AVL* c = b->drt;

    switch (c->bf)
    {
        case 0:
            a->bf = b->bf = 0;
            break;
        
        case -1:
            a->bf = 0;
            b->bf = 1;
            break;

        case 1:
            a->bf = -1;
            b->bf = 0;
            break;
    
        default:
            break;
    }

    a->stg = c->drt;
    b->drt = c->stg;

    c->bf = 0;
    c->drt = a;
    c->stg = b;

    a = c;
}
void parcurgere_avl_min_max(Nod_AVL* head, int ID_MIN,int ID_MAX)
{
    if(head != nullptr)
    {
        if (ID_MIN < head->data.ID_ARTICOL)
            parcurgere_avl_min_max(head->stg, ID_MIN, ID_MAX);
        
        if (head->data.ID_ARTICOL >= ID_MIN && head->data.ID_ARTICOL <= ID_MAX)
            std::cout << head->data.ID_ARTICOL << " ";
        
        if (ID_MAX > head->data.ID_ARTICOL)
            parcurgere_avl_min_max(head->drt, ID_MIN, ID_MAX);
    }
}
void cautare_articol(Nod_AVL* head,int ID_CAUTAT,int &pasi)
{
    if (head == nullptr)
        return;
    
    pasi = pasi + 1;

    if(head->data.ID_ARTICOL == ID_CAUTAT)
    {
        std::cout << pasi << std::endl;
        return;
    }

    if(ID_CAUTAT < head->data.ID_ARTICOL)
        cautare_articol(head->stg,ID_CAUTAT,pasi);
    else if(ID_CAUTAT > head->data.ID_ARTICOL)
        cautare_articol(head->drt,ID_CAUTAT,pasi);
}