#include "functii.hpp"
#include <iostream>
#include <string>
#include <vector>

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int hash_cuv_cheie(std::vector<std::string> chei)
{
    int s = 0;
    for(int i = 0;i<chei.size();i++)
        for(int j = 0;j<chei[i].size();j++)
            s = s+chei[i][j];
    return s%TABLE_SIZE;
}
Document_El_Tabel** init_table()
{
    Document_El_Tabel** table = new Document_El_Tabel*[TABLE_SIZE]{nullptr};
    return table;
}
void insert_table(Document_El_Tabel** &table,Document data)
{
    int key = hash_cuv_cheie(data.Cuvinte_Cheie);
    Document_El_Tabel* nou = new Document_El_Tabel{key,data,nullptr};   
    if(table[key] == nullptr)
        table[key] = nou;
    else
    {
        nou->next = table[key];
        table[key] = nou;
    }
}
void filtrare_multipla(Document_El_Tabel** &table,std::vector<std::string> cuv_cheie)
{
    int key = hash_cuv_cheie(cuv_cheie);
    Document_El_Tabel* element = table[key];
    if(element == nullptr)
        std::cout << "Nu a fost gasit niciun element." << std::endl;
    else
    {
        while(element != nullptr)
        {
            std::cout << element->data.ID_ARTICOL << " ";
            element = element->next;
        }
    }
}

//Stack
void init_stack(Stack* &s)
{
    s = new Stack{nullptr};
}
void push(Stack* &s,int x)
{
    Nod* nou = new Nod{x,s->head};
    s->head = nou;
}
void pull(Stack* &s)
{
    if(!isEmpty(s))
    {
        Nod* temp = s->head;
        s->head = s->head->next;
        delete temp;
    }
}
int top(Stack* s)
{
    if(!isEmpty(s))
        return s->head->data;
    else
        return -1;
}
bool isEmpty(Stack* s)
{
    if(s->head == nullptr)
        return true;
    else
        return false;
}

//Queue
void init_queue(Queue* &q)
{
    q = new Queue{nullptr};
}
void put(Queue* &q,int x)
{
    Nod* nou = new Nod{x,nullptr};
    if(isEmptyQueue(q))
    {
        q->head = nou;
        q->tail = nou;
    }
    else
    {
        q->tail->next = nou;
        q->tail = nou;
    }
}
void pop(Queue* &q)
{
    if(!isEmptyQueue(q))
    {
        Nod* temp = q->head;
        q->head = q->head->next;

        if(q->head == nullptr)
            q->tail == nullptr;

        delete temp;
    }
}
int get(Queue* q)
{
    if(!isEmptyQueue(q))
        return q->head->data;
    else
        return -1;
}
bool isEmptyQueue(Queue* q)
{
    if(q->head == nullptr || q->tail == nullptr)
        return true;
    else
        return false;
}

void BFS(AVL* arb)
{
    bool vizitat[TABLE_SIZE] = {0};
    Queue* q = 0;
    init_queue(q);

    Nod_AVL* cnt = arb->head;
    put(q,cnt->data.ID_ARTICOL);
    while(cnt->stg != nullptr)
    {
        while(!isEmptyQueue(q))
        {
            int val = get(q);
            pop(q);

            std::cout << val << " ";
            put(q,cnt->stg->data.ID_ARTICOL);
            put(q,cnt->drt->data.ID_ARTICOL);
        }
    }
}
void DFS(AVL* arb);

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