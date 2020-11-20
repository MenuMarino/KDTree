#include<bits/stdc++.h>

using namespace std;

template<class T>
class Nodo {
public:
    Nodo<T> * m_pSon[2] = {nullptr, nullptr};
    pair<int, int>  coord;
    T dato;
    int d;

    Nodo(pair<int, int> coord, T dato, int d) {
        this->coord = coord;
        this->dato = dato;
        this->d = d;
    }

    void print() {
        cout << dato << " ";
        if(m_pSon[0]) m_pSon[0]->print();
        if(m_pSon[1]) m_pSon[1]->print();
    }
};

template<class T>
class KdTree {
private:
    Nodo<T> * m_pRoot;
public:
    KdTree() {
        m_pRoot =0;
    }

    // cx y cy son los índices del vector de tuplas ordenado por x y luego por y
    Nodo<T> *  Add(int indices[2][100], int Datos[100], int l, int h ) {
        for (int i = 0; i < 100; ++i) {
            insert(Datos[i], indices[0][i], indices[1][i]);
        }
        return m_pRoot;
    }

    void insert(T D, int x, int y) {
        insert(D, m_pRoot, true, {x, y});
    }

    void insert(T D, Nodo<T> * & p, bool d, pair<int, int> coord){
        if(!p) {
            p=new Nodo<T>(coord, D, d);
            return;
        }
        if (p->coord == coord) return;
        if (d) {
            insert(D, p->m_pSon[p->coord.first < coord.first], !d, coord);
        }
        else {
            insert(D, p->m_pSon[p->coord.second < coord.second], !d, coord);
        }
    }

    void print() {
        if(m_pRoot) m_pRoot->print();
        cout << '\n';
    }

    Nodo<T>* find_min_x() {
        return find_min_x_aux(m_pRoot, true, m_pRoot);
    }

    Nodo<T>* find_min_y() {
        return find_min_y_aux(m_pRoot, true, m_pRoot);
    }

    Nodo<T>* find_min_x_aux(Nodo<T>* p, bool d, Nodo<T>* parent) {
        if (p) {
            if (d) {
                auto izq = find_min_x_aux(p->m_pSon[0], !d, p);
                if (!izq) return p;
                return (izq->coord.first < p->coord.first) ? izq : p;
            } else {
                auto izq = find_min_x_aux(p->m_pSon[0], !d, p);
                auto der = find_min_x_aux(p->m_pSon[1], !d, p);
                if (!izq && !der) return p;
                if (!izq) {
                    return (der->coord.first < p->coord.first) ? der : p;
                }
                if (!der) {
                    return (izq->coord.first < p->coord.first) ? izq : p;
                }
                auto hijo = (izq->coord.first < der->coord.first) ? izq : der;
                return (hijo->coord.first < p->coord.first) ? hijo : p;
            }
        }
        return nullptr;
    }

    Nodo<T>* find_min_y_aux(Nodo<T>* p, bool d, Nodo<T>* parent) {
        if (p) {
            if (!d) {
                auto izq = find_min_y_aux(p->m_pSon[0], !d, p);
                if (!izq) return p;
                return (izq->coord.second < p->coord.second) ? izq : p;
            } else {
                auto izq = find_min_y_aux(p->m_pSon[0], !d, p);
                auto der = find_min_y_aux(p->m_pSon[1], !d, p);
                if (!izq && !der) return p;
                if (!izq) {
                    return (der->coord.second < p->coord.second) ? der : p;
                }
                if (!der) {
                    return (izq->coord.second < p->coord.second) ? izq : p;
                }
                auto hijo = (izq->coord.second < der->coord.second) ? izq : der;
                return (hijo->coord.second < p->coord.second) ? hijo : p;
            }
        }
        return nullptr;
    }

    ~KdTree() {
        if (m_pRoot) destroy(m_pRoot);
    }

    void destroy(Nodo<T>* p) {
        if (p) {
            destroy(p->m_pSon[0]);
            destroy(p->m_pSon[1]);
            // cout << "Deleting " << p->dato << '\n';
            delete p;
        }
    }

};


int main() {
    KdTree<char>  A;
    int min_x = INT_MAX, min_y = INT_MAX;
    srand(time(nullptr));
    for (int i = 0; i < 1000; ++i) {
        int x = rand()%20000;
        int y = rand()%20000;
        min_x = min(min_x, x);
        min_y = min(min_y, y);
        A.insert( (char)(i%255), x, y);
    }
    
    auto nodo_x = A.find_min_x();
    auto nodo_y = A.find_min_y();
    
    assert(nodo_x->coord.first == min_x);
    assert(nodo_y->coord.second == min_y);

    return 0;
}
