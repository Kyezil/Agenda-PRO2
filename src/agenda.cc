/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda() {
    clock_ = {origin,tasks_.begin()};
}

void Agenda::set_rellotge(Data data) {
    clock_ = {data, tasks_.lower_bound(data)};
}

pair<Agenda::instant, bool> Agenda::p_add_tasca(const Data& data, const Tasca& t) {
    pair<instant,bool> ins = tasks_.emplace(make_pair(data, t));
    if (ins.second) { //si s'ha pogut inserir
        // afegeix etiquetes i actualitza tags
        Tasca::tag_iterator tag = ins.first->second.begin_etiquetes();
        while (tag != ins.first->second.end_etiquetes()) {
            tags_[*tag].insert(ins.first);
            ++tag;
        }
        // actualitza rellotge
        if (++ins.first == clock_.second)
            clock_.second = --ins.first;
    }
    return ins;
}

bool Agenda::add_tasca(const Data &data, const Tasca& t) {
    return p_add_tasca(data, t).second;
}

//void Agenda::set_titol(const int id, string titol) {}
//void Agenda::set_data(const int id, Data data) {}
//void Agenda::add_etiqueta(const int id, string etiqueta) {}
//void Agenda::del_etiqueta(const int id, string etiqueta) {}
//void Agenda::del_etiquetes(const int id) {}
//void Agenda::del_tasca(const int id) {}

bool Agenda::is_passat(const Data& data) const {
    return (data < clock_.first);
}

//bool Agenda::is_modificable(const int id) const {}

Dia Agenda::get_dia() const {
    return clock_.first.first;
}

Hora Agenda::get_hora() const {
    return clock_.first.second;
}

void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {
    if (dia2 > dia1 and dia2 > clock_.first.first) {
        menu_.clear();
        //TODO only for test fix and remove
        Data d1 = make_pair(dia1, Hora(0,0));
        if (d1 < clock_.first) d1 = clock_.first;
        Data d2 = make_pair(dia2, Hora(23,59));
        instant in1 = tasks_.lower_bound(d1),
                in2 = tasks_.upper_bound(d2);
        if (expressio.size() == 0) menu_directe(in1, in2);
        else if (expressio[0] == '#') {
            set_instant::iterator it1 = tags_[expressio].lower_bound(in1),
                                  it2 = tags_[expressio].upper_bound(in2);
            menu_directe(it1,it2);
        }
        else {
            istringstream exp(expressio);
            exp_parentitzada(in1, in2, exp, menu_);
            print_menu();
        }
    }
    else cout << "AVIS: NO HA DE FER RES" << endl; //TODO delete al final
}

void Agenda::consulta(Dia dia, string expressio) {
    consulta(dia, dia, expressio);
}

void Agenda::consulta(string expressio) {
    // TODO entendre pq el compilador accepta directament els parametres
    menu_.clear();
    if (expressio.size() == 0) {
        instant in1 = clock_.second, //copia per no modificar el rellotge
                in2 = tasks_.end();
        menu_directe(in1, in2);
    }
    else if (expressio[0] == '#'){
        set_instant::iterator in1 = tags_[expressio].begin(),
                              in2 = tags_[expressio].end();
        menu_directe(in1, in2);
    }
    else {
        instant in1 = clock_.second, //copia per no modificar el rellotge
                in2 = tasks_.end();
        istringstream exp(expressio);
        exp_parentitzada(in1, in2, exp, menu_);
        print_menu();
    }
}

void Agenda::passat() const {
    cinstant it = tasks_.begin();
    int i = 1;
    while (it != clock_.second) {
        print_menu_item(i, it);
        it++, i++;
    }
}

void Agenda::print_map_data_tasca() {
    cinstant it = tasks_.begin();
    cout << "======== MAP PRINCIPAL =======\n";
    while (it != tasks_.end()) {
        cout << it->first << ' ';
        Tasca::print_titol(it->second,cout);
        cout << ' ';
        Tasca::print_etiquetes(it->second, cout);
        cout << '\n';
        ++it;
    }
    cout << endl;
}

void Agenda::print_map_tags() {
    map<string, set<instant, ordre_instant> >::const_iterator it = tags_.begin();
    cout << "======== ETIQUETES =======\n";
    while (it != tags_.end()) {
        cout << "-- " << it->first << " --\n";
        for (auto ins : it->second) {
            cout << ' ';
            Tasca::print_titol(ins->second, cout);
            cout << '\n';
        }
        ++it;
    }
}

void Agenda::print_menu_item(int i, const cinstant& it) const {
    cout << i << ' ';
    Tasca::print_titol(it->second, cout);
    cout << ' ' << it->first << ' ';
    Tasca::print_etiquetes(it->second, cout);
    cout << '\n';
}

void Agenda::print_menu() const {
    list<instant>::const_iterator it = menu_.begin();
    int i = 1;
    while (it != menu_.end()) {
        print_menu_item(i, *it);
        ++it, ++i;
    }
}

template<typename Iterator>
void Agenda::merge_and(Iterator in1, Iterator in2, list<instant>& l){
    list<instant>::iterator it_l = l.begin();
    while (in1 != in2 and it_l != l.end()) {
        if( (*in1)->first < (*it_l)->first ) ++in1;
        else if((*it_l)->first < (*in1)->first) it_l = l.erase(it_l);
        else ++it_l, ++in1;
    }
    while (it_l != l.end()) it_l = l.erase(it_l);
}

template<typename Iterator>
void Agenda::merge_or(Iterator in1, Iterator in2, list<instant>& l){
    list<instant>::iterator it_l = l.begin();
    while (in1 != in2 and it_l != l.end()) {
        if ((*in1)->first < (*it_l)->first){
            l.insert(it_l, *in1);
            ++in1;
        }
        else if ((*it_l)->first < (*in1)->first) ++it_l;
        else ++it_l, ++in1;
    }
    while (in1 != in2) {
        l.insert(l.end(), *in1);
        ++in1;
    }
}

void Agenda::menu_directe(set_instant::iterator& in1, set_instant::iterator& in2) {
    int i = 1;
    while (in1 != in2) {
        menu_.insert(menu_.end(), *in1);
        print_menu_item(i, *in1);
        ++in1, ++i;
    }
}

void Agenda::menu_directe(instant& in1, instant& in2) {
    int i = 1;
    while (in1 != in2) {
        menu_.insert(menu_.end(), in1);
        print_menu_item(i, in1);
        ++in1, ++i;
    }
}

void Agenda::extract_tag(istringstream& exp, string& tag) {
    char c;
    while (c = exp.peek(), not exp.eof() and c != '.' and c != ',' and c != ')')
        tag += exp.get();
}

void Agenda::print_llista(const list<instant>& l) {
    list<instant>::const_iterator it = l.begin();
    while (it != l.end()) {
        cout << (*it)->first << ' ';
        Tasca::print_titol((*it)->second,cout);
        cout << ' ';
        Tasca::print_etiquetes((*it)->second, cout);
        cout << '\n';
        ++it;
    }
}

Agenda::set_instant::iterator Agenda::safe_upper_bound(const string& tag, const instant& in) {
    if (in == tasks_.end()) return tags_[tag].end();
    else return tags_[tag].upper_bound(in);
}

Agenda::set_instant::iterator Agenda::safe_lower_bound(const string& tag, const instant& in) {
    if (in == tasks_.end()) return tags_[tag].end();
    else return tags_[tag].lower_bound(in);
}

void Agenda::exp_parentitzada(const instant& in1, const instant& in2, istringstream& exp, list<instant>& l) {
    // 1r operand
    char c = exp.get(); //llegir (
    c = exp.peek();
    if (c == '(') exp_parentitzada(in1, in2, exp, l);
    else {
        // etiqueta
        string tag;
        extract_tag(exp, tag);
        l.insert(l.end(), safe_lower_bound(tag, in1), safe_upper_bound(tag,in2));
    }
    // operador
    char op = exp.get();
    // 2n operand
    c = exp.peek();
    if (c == '(') {
        list<instant> l2;
        exp_parentitzada(in1, in2, exp, l2);
        if (op == '.') merge_and(l2.begin(), l2.end(), l);
        else merge_or(l2.begin(), l2.end(), l);
    }
    else {
        //etiqueta
        string tag;
        extract_tag(exp, tag);
        if (op == '.')// and
            merge_and(safe_lower_bound(tag,in1), safe_upper_bound(tag,in2), l);
        else merge_or(safe_lower_bound(tag,in1), safe_upper_bound(tag,in2), l);
    }
    // parèntesi final
    c = exp.get();
    if (c != ')') cout << "NO PARENTESI FINAL" << endl; //TODO REMOVE
}

bool Agenda::ordre_instant::operator()(const instant& a, const instant& b) const {
    return (a->first < b->first);
}
