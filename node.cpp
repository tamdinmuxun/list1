#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>

using namespace std;
template<typename T>
struct node{
    T val;
    node* next;
    node(T v){
        val = v;
        next = nullptr;
    }
};
template<typename T>
class list{
    node<T> *head, *tail;
public:
    list(){
        head = nullptr;
        tail = nullptr;
    }
    bool empty(){
        if (head == nullptr){
            return true;
        }else{
            return false;
        }
    }
    node<T>* front(){
        return head;
    }
    node<T>* back(){
        return tail;
    }
    void push_front(T x);
    void push_back(T x);
    void push(T x, int k);
    bool pop_front();
    bool pop_back();
    bool pop_ind(int k);
    bool pop_val(T x);
    int find(T x);
    T operator[](int i);
    template<typename Type> friend ostream& operator<<(ostream& out, list<Type>& a);
};

template<typename T>
void list<T>::push_front(T x) {
    auto n = new node<T>(x);
    n->next = head;
    head = n;
    if (tail == nullptr){
        tail = n;
        tail->next = nullptr;
    }
}

template<typename T>
void list<T>::push_back(T x) {
    node<T> *n = new node<T>(x);
    n->next = nullptr;
    if (tail != nullptr) tail->next = n;
    tail = n;
    if (head == nullptr){
        head = n;
    }
}

template<typename T>
void list<T>::push(T x, int k) {
    node<T> *t = new node<T>(x);
    node<T>* pre = head;
    for (int i = 0; i < k - 2; i++){
        pre = pre->next;
    }
    node<T> *nex = pre->next;
    pre->next = t;
    t->next = nex;
}

template<typename T>
bool list<T>::pop_front() {
    if (this->empty()){
        return false;
    }else{
        node<T> *h = head->next;
        delete head;
        head = h;
        return true;
    }
}

template<typename T>
bool list<T>::pop_back() {
    if (this->empty()){
        return false;
    }else{
        node <T> *t = head;
        while (t->next != tail){
            t = t->next;
        }
        t->next = nullptr;
        delete tail;
        tail = t;
        return true;
    }
}

template<typename T>
bool list<T>::pop_ind(int k) {
    if (this->empty()) return false;
    node<T>* pre = head;
    if (k == 0){
        return this->pop_front();
    }
    for (int i = 0; i < k - 1; ++i){
        pre = pre->next;
    }
    node<T> *del = pre->next;
    node<T> *nex = del->next;
    delete del;
    pre->next = nex;
    return true;
}

template<typename T>
bool list<T>::pop_val(T x) {
    if (this->empty()) return false;
    node<T>* pre = head;
    while (pre->next != nullptr && pre->next->val != x){
        pre = pre->next;
    }
    if (pre->next == nullptr){
        return false;
    }
    node<T>* del = pre->next;
    node<T> *nex = del->next;
    delete del;
    pre->next = nex;
    return true;
}

template<typename T>
int list<T>::find(T x) {
    if (this->empty()) return -1;
    node<T>* pre = head;
    int k = 0;
    while (pre->val != x) {
        pre = pre->next;
        k++;
        if (pre->next == nullptr) {
            break;
        }
    }
    if (pre->val != x){
        return -1;
    }
    return k;
}

template<typename T>
T list<T>::operator[](int i) {
    auto it = head;
    for (int k = 0; k < i; k++){
        it = it->next;
    }
    return it->val;
}

template<typename Type>
ostream &operator<<(ostream &out, list<Type> &a) {
    if (a.empty()){
        return out;
    }
    node<Type> *now = a.head;
    while(true){
        out << now->val << ' ';
        if (now->next != nullptr) now = now->next;
        else break;
    }
    return out;
}

template<typename T>
list<T> merge(list<T> &a, list<T> &b){
    list<T> res = list<T>();
    auto it1 = a.front();
    auto it2 = b.front();
    while (it1 != nullptr || it2 != nullptr){
        if (it1 != nullptr && it2 != nullptr && it1->val < it2->val){
            res.push_back(it1->val);
            auto t = it1;
            it1 = it1->next;
            //delete t;
        }else if (it1 != nullptr && it2 != nullptr && it1->val >= it2->val){
            res.push_back(it2->val);
            auto t = it2;
            it2 = it2->next;
            //delete t;
        }else if (it1 != nullptr){
            res.push_back(it1->val);
            auto t = it1;
            it1 = it1->next;
        }else if (it2 != nullptr){
            res.push_back(it2->val);
            auto t = it2;
            it2 = it2->next;
        }
    }
    //cout << res << endl;
    return res;
}
template<typename T>
list<T> sorting(list<T> &a){
    vector<pair<list<T>, int>> st;
    while (true){
        if (st.size() > 1){
            int k = st[st.size() - 2].second, l = st.back().second;
            //cout << k << ' ' << l << endl;
            if (k == l || a.empty()){
                list<T> te1 = st[st.size() - 2].first;
                list<T> te2 = st.back().first;
                //cout << te1 << endl << te2 << endl;
                st.pop_back();
                st.pop_back();
                st.push_back({merge(te1, te2), k + l});
            }
        }
        if (!a.empty()) {
            list<T> t = list<T>();
            t.push_back(a.front()->val);
            a.pop_front();
            st.push_back({t, 1});
        }
        if (st.size() == 1 && a.empty()){
            break;
        }
    }
    a = st.back().first;
    return a;
}
int main(){
    list<int> a = list<int>();
    string ans;
    while (true) {
        cout << "choose command\nempty \npush_front \npush_back \npush_index \npop_front \npop_back \npop_ind\npop_val \nfind_val \n[] \nsort \nprint\nexit\n";
        cin >> ans;
        if (ans == "exit"){
            break;
        }else if (ans == "empty"){
            if (a.empty()){
                cout << "empty\n";
            }else{
                cout << "not empty\n";
            }
        }else if (ans == "push_front"){
            int x;
            cin >> x;
            a.push_front(x);
        }else if (ans == "push_back"){
            int x;
            cin >> x;
            a.push_back(x);
        }else if (ans == "push_index"){
            int x;
            cin >> x;
            int ind;
            cin >> ind;
            a.push(x, ind);
        }else if (ans == "pop_front"){
            a.pop_front();
        }else if (ans == "pop_back"){
            a.pop_back();
        }else if (ans == "pop_ind"){
            int ind;
            cin >> ind;
            a.pop_ind(ind);
        }else if (ans == "pop_val"){
            int x;
            cin >> x;
            a.pop_val(x);
        }else if (ans == "find_val"){
            int x;
            cin >> x;
            cout << a.find(x) << '\n';
        }else if (ans == "[]"){
            int ind;
            cin >> ind;
            cout << a[ind] << '\n';
        }else if (ans == "sort"){
            sorting(a);
        }else if (ans == "print"){
            cout << a << '\n';
        }
    }
}