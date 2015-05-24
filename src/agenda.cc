/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda() {
    // Dia per defecte de l'enunciat
    clock_ = {make_pair(Dia(20,4,15),Hora(0,0)),tasks_.begin()};
}

void Agenda::set_rellotge(Data data) {
    instant it = tasks_.lower_bound(data); //primera tasca del present
    // Actualitzar el conjunt d'etiquetes (esborrar les tasques passades)
    while (clock_.second != it) {
        Tasca::tag_iterator inici = clock_.second->second.begin_etiquetes();
        Tasca::tag_iterator fi = clock_.second->second.end_etiquetes();
        while(inici != fi) {
            tag_map::iterator t = tags_.find(*inici); // cjt associat a l'etiqueta
            t->second.erase(clock_.second); // esborrar l'instant
            if (t->second.empty()) tags_.erase(t); // esborar el cjt si es buit
            ++inici;
        }
        ++clock_.second;
    }
    clock_.first = data;
}

bool Agenda::add_tasca(const Data &data, const Tasca& t) {
    return p_add_tasca(data, t).second;
}

bool Agenda::set_titol(const int id, string titol) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    if (it.second) (*it.first)->second.set_titol(titol);
    return it.second;
}

bool Agenda::set_dia(const int id, Dia d) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    return it.second and ((*it.first)->first.first != d) and
        p_set_data(it.first, make_pair(d, (*it.first)->first.second));
}

bool Agenda::set_hora(const int id, Hora h) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    return it.second and ((*it.first)->first.second != h) and
        p_set_data(it.first, make_pair((*it.first)->first.first, h));
}

bool Agenda::set_data(const int id, Data d) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    return it.second and ((*it.first)->first != d) and p_set_data(it.first, d);
}

bool Agenda::add_etiqueta(const int id, string etiqueta) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    if (it.second) {
        (*it.first)->second.add_etiqueta(etiqueta); //afegir en la tasca
        tags_[etiqueta].insert(*it.first); //afegir en el catàleg
    }
    return it.second;
}

bool Agenda::del_etiqueta(const int id, string etiqueta) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    if (it.second) {
        tag_map::iterator t = tags_.find(etiqueta); //cjt de tasques associat a l'etiqueta
        if (t == tags_.end()) it.second = false;
        else {
            set_instant::iterator el = t->second.find(*it.first); //trobar la tasca
            if (el == t->second.end()) it.second = false;
            else {
                (*it.first)->second.del_etiqueta(etiqueta); // esborrar de la tasca
                t->second.erase(el); // esborrar del cjt
                if (t->second.empty()) tags_.erase(t); //eliminar el cjt si buit
            }
        }
    }
    return it.second;
}

bool Agenda::del_etiquetes(const int id) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    if (it.second) {
        Tasca::tag_iterator inici = (*it.first)->second.begin_etiquetes();
        Tasca::tag_iterator fi = (*it.first)->second.end_etiquetes();
        while(inici != fi) {
            tag_map::iterator t = tags_.find(*inici); //cjt de l'etiqueta
            t->second.erase(*it.first); //eliminar la tasca (segur que hi és)
            if (t->second.empty()) tags_.erase(t); // eliminar cjt si buit
            ++inici;
        }
        (*it.first)->second.del_etiquetes(); //eliminar de la tasca
    }
    return it.second;
}
bool Agenda::del_tasca(const int id) {
    pair<list<instant>::iterator,bool> it = menu_item(id);
    if (it.second) {
        // Eliminar les etiquetes
        Tasca::tag_iterator inici = (*it.first)->second.begin_etiquetes();
        Tasca::tag_iterator fi = (*it.first)->second.end_etiquetes();
        while(inici != fi) {
            tag_map::iterator t = tags_.find(*inici);
            t->second.erase(*it.first);
            if (t->second.empty()) tags_.erase(t);
            ++inici;
        }
        if (*it.first == clock_.second) ++clock_.second; //actualitzar rellotge
        tasks_.erase(*it.first); // esborrar del cjt total
        *it.first = tasks_.end(); // invalidar la tasca en el menú
    }
    return it.second;

}

bool Agenda::is_passat(const Data& data) const {
    return (data < clock_.first);
}

Dia Agenda::get_dia() const {
    return clock_.first.first;
}

Hora Agenda::get_hora() const {
    return clock_.first.second;
}

void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {
    if (dia2 >= dia1 and dia2 >= clock_.first.first) { // interval correcte
        menu_.clear();
        Data d1 = make_pair(dia1, Hora(0,0));// inici de l'interval
        if (d1 < clock_.first) d1 = clock_.first;// anterior al rellotge => rellotge
        Data d2 = make_pair(dia2, Hora(23,59));// final de l'interval (vàlid per l'if)
        instant in1 = tasks_.lower_bound(d1), // instants corresponents
                in2 = tasks_.upper_bound(d2);
        if (expressio.size() == 0) menu_directe(in1, in2);//sense expressio
        else if (expressio[0] == '#') {//amb només una etiqueta
            tag_map::iterator tag = tags_.find(expressio);
            if (tag != tags_.end()) {
            set_instant::iterator it1 = safe_bound(tag,in1),
                                  it2 = safe_bound(tag,in2);
            menu_directe(it1,it2);
            }
        }
        else {//expressió complexa (amb parèntesi)
            istringstream exp(expressio);
            exp_parentitzada(in1, in2, exp, menu_);
            print_menu();
        }
    }
}

void Agenda::consulta(Dia dia, string expressio) {
    consulta(dia, dia, expressio);
}

void Agenda::consulta(string expressio) {
    menu_.clear();
    if (expressio.size() == 0) {
        instant in1 = clock_.second,//còpia per no modificar el rellotge
                in2 = tasks_.end();
        menu_directe(in1, in2);
    }
    else if (expressio[0] == '#'){//una sola etiqueta
        tag_map::iterator tag = tags_.find(expressio);//cjt de l'etiqueta
        if (tag != tags_.end()) {
            set_instant::iterator in1 = tag->second.begin(),//principi
                in2 = tag->second.end();//final
            menu_directe(in1, in2);
        }
    }
    else {//expressió complexa (amb parèntesi)
        instant in1 = clock_.second, //copia per no modificar el rellotge
                in2 = tasks_.end();
        istringstream exp(expressio);
        exp_parentitzada(in1, in2, exp, menu_);
        print_menu();
    }
}

void Agenda::passat() {
    menu_.clear();
    cinstant it = tasks_.begin();
    int i = 1;
    // escriure del principi fins al rellotge
    while (it != clock_.second) {
        print_menu_item(i, it);
        it++, i++;
    }
}

// PRIVATES
bool Agenda::ordre_instant::operator()(const instant& a, const instant& b) const {
    // L'ordre entre instants ve donat per l'ordre entre les dates de les tasques a les
    // que apuntent
    return (a->first < b->first);
}

pair<list<Agenda::instant>::iterator, bool> Agenda::menu_item(const int id) {
    // id dins de les dimensions del menu
    bool ok  = (1 <= id) and (id <= menu_.size());
    list<instant>::iterator it = menu_.begin();
    if (ok) {
        advance(it, id - 1); //avançar fins on toca
        ok = (*it != tasks_.end())
            and not is_passat((*it)->first);//si la tasca és vàlida
    }
    return make_pair(it, ok);
}

pair<Agenda::instant, bool> Agenda::p_add_tasca(const Data& data, const Tasca& t) {
    pair<instant,bool> ins = tasks_.insert(make_pair(data, t));//intenta inserir
    if (ins.second) { //si s'ha pogut inserir
        // afegeix etiquetes i actualitza tags
        Tasca::tag_iterator tag = ins.first->second.begin_etiquetes();
        while (tag != ins.first->second.end_etiquetes()) {
            tags_[*tag].insert(ins.first);
            ++tag;
        }
        // si som la nova primera data no passada
       ++ins.first;
        if (ins.first == clock_.second) --clock_.second;
       --ins.first;
    }
    return ins;
}
bool Agenda::p_set_data(list<instant>::iterator& it, Data data) {
        if (data < clock_.first) return false;//si es passat
        Tasca tem = (*it)->second;//fem còpia de la tasca
        pair<instant,bool> ans = p_add_tasca(data, tem);//l'inserim
        if (ans.second) {//si es pot
            Tasca::tag_iterator inici = (*it)->second.begin_etiquetes();
            Tasca::tag_iterator fi = (*it)->second.end_etiquetes();
            while(inici != fi) {//eliminem els instants associats a l'antiga
                tag_map::iterator t = tags_.find(*inici);
                t->second.erase(*it);
                if (t->second.empty()) tags_.erase(t);
                ++inici;
            }
            if (*it == clock_.second) ++clock_.second;//actualitzar rellotge
            tasks_.erase(*it); //l'esborrem del cjt total
            *it = ans.first;//associem la nova en el menú
        }
        return ans.second;
}

void Agenda::menu_directe(set_instant::iterator& in1, set_instant::iterator& in2) {
    int i = 1;
    // recorrem l'interval escrivint una línia per cada item
    while (in1 != in2) {
        menu_.insert(menu_.end(), *in1);
        print_menu_item(i, *in1);
        ++in1, ++i;
    }
}

void Agenda::menu_directe(instant& in1, instant& in2) {
    int i = 1;
    // recorrem l'interval escrivint una línia per cada item
    while (in1 != in2) {
        menu_.insert(menu_.end(), in1);
        print_menu_item(i, in1);
        ++in1, ++i;
    }
}

template<typename Iterator>
void Agenda::merge_and(Iterator in1, Iterator in2, list<instant>& l){
    list<instant>::iterator it_l = l.begin();
    while (in1 != in2 and it_l != l.end()) {
        if( (*in1)->first < (*it_l)->first ) ++in1;//només en el 1r
        else if((*it_l)->first < (*in1)->first) it_l = l.erase(it_l);//només en el 2n
        else ++it_l, ++in1; //en els 2
    }
    l.erase(it_l, l.end());
}

template<typename Iterator>
void Agenda::merge_or(Iterator in1, Iterator in2, list<instant>& l){
    list<instant>::iterator it_l = l.begin();
    while (in1 != in2 and it_l != l.end()) {
        if ((*in1)->first < (*it_l)->first){ //només en el 1r
            l.insert(it_l, *in1);
            ++in1;
        }
        else if ((*it_l)->first < (*in1)->first) ++it_l;//només en el 2n
        else ++it_l, ++in1;//en ambos
    }
    l.insert(l.end(), in1, in2);
}

string Agenda::extract_tag(istringstream& exp) {
    string ret;
    char c;
    while (c = exp.get(), not exp.eof() and c != '.' and c != ',' and c != ')') {
        ret += c;
    }
    exp.unget();
    return ret;
}

Agenda::set_instant::iterator Agenda::safe_bound(tag_map::iterator &tag, const instant& in) {
    if (in == tasks_.end()) return tag->second.end();
    else return tag->second.lower_bound(in);
}

void Agenda::exp_parentitzada(const instant& in1, const instant& in2, istringstream& exp, list<instant>& l) {
    // ===== 1r operand =====
    char c = exp.get(); //llegir (
    c = exp.peek();//detectar tipus del 1r operand
    if (c == '(') {// expressió delimitada per ()
        // PRE => in1, in2 són vàlids i l és buida
        // IF => exp conté una expressió delimitada per () al principi (1r operand)
        // PRE+IF => PRE de exp_parentitzada
        exp_parentitzada(in1, in2, exp, l);
        // POST exp_parentitzada => HI1
    }
    else {// etiqueta
        tag_map::iterator cjt_tag = tags_.find(extract_tag(exp));// cjt d'instants associat
        if (cjt_tag != tags_.end()) { //si existeix
            l.insert(l.end(), safe_bound(cjt_tag, in1), safe_bound(cjt_tag,in2));
            // => l conté les tasques del cjt de l'etiqueta que estan en [in1,in2)
        }
        // si no existeix => no hi ha tasques que compleixen el 1r operand
        // PRE => l és buit => l conté les tasques del 1r operand (cap)  (1)
        // POST de extract_tag => s'ha consumit el 1r operand            (2)
        // (1) + (2) => HI1
    }
    //HI1: l conté les tasques en [in1, in2) que compleixen el primer operand,
    // i s'ha consumit de exp => queda l'operador, el 2n operand i el parèntesi )
    char op = exp.get(); //operador => queda 2n operand i el parèntesi )
    // ===== 2n operand =====
    c = exp.peek();//detectar el tipus del 2n operand
    if (c == '(') {//expressió delimitada per ()
        list<instant> l2;//nova llista buida => l2 compleix la PRE       (3)
        // PRE => in1, in2 són vàlids
        // IF => exp conté una expressió delimitada per () al principi (2n operand)
        // PRE + IF + (3) => PRE de exp_parentitzada
        exp_parentitzada(in1, in2, exp, l2);
        // POST exp_parentitzada => l conté les tasques en [in2,in2) que compleixen
        // el segon operand i s'ha consumit de exp => queda el parèntesi )
        // l2 declarada => existeix begin i end => PRE merge_{and/or}
        if (op == '.') merge_and(l2.begin(), l2.end(), l);
        else merge_or(l2.begin(), l2.end(), l);
        //POST merge_{and/or} => l conté la {intersecció/unió} de l2 amb l  (4)
        // HI1 + (4) => l conté les tasques en [in1,in2) que compleixen EXP   (8.1)
    }
    else {//etiqueta
        tag_map::iterator cjt_tag = tags_.find(extract_tag(exp)); //cjt associat
        if (cjt_tag != tags_.end()) {//si existeix
            // IF => PRE de safe_bound
            // POST de safe_bound => PRE de merge_{and/or}
            // safe_bound(cjt_tag,in1) i safe_bound(cjt_tag,in2) delimiten les tasques del
            // conjunt de l'etiqueta que estan en [in1,in2)                (5)
            if (op == '.')
                merge_and(safe_bound(cjt_tag,in1), safe_bound(cjt_tag,in2), l);
            else
                merge_or(safe_bound(cjt_tag,in1), safe_bound(cjt_tag,in2), l);
            // POST de merge_{and/or} + (5) => l conté la {intersecció/unió} de les
            // tasques del cjt de l'etiqueta que estan en [in1,in2) amb les de l  (6)
            // HI1 + (6) => l conté les tasques en [in1,in2) que compleixen EXP
        }
        else if (op == '.') l.clear();
        // ELSE => el cjt de l'etiqueta no existeix + INV cjt etiqueta => no hi tasques
        // que tenen l'etiqueta => és un conjunt buit
        // IF (else if) => s'ha de fer la intersecció
        // POST l.clear() => l és buit <=> l conté la intersecció de l amb el cjt
        // d'etiquetes que tenen l'etiqueta (buit)                                  (7.1)

        // ELSE implícit => cjt de l'etiqueta és buit i l'operació és una unió
        // NO OP => l invariat <=> conté la unió de l amb el cjt d'etiquetes (buit) (7.2)
        // HI1 + (7.1 o 7.2) => l conté les tasques en [in1,in2) que compleixen EXP (8.2)
    }
    c = exp.get(); //llegir parèntesi final + (8.1 o 8.2) => POST exp_parentitzada
}

void Agenda::print_menu_item(int i, const cinstant& it) const {
    cout << i << ' ';
    Tasca::print_titol(it->second, cout);
    cout << ' ' << it->first;
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
