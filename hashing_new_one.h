// Vorzeichenlose ganze Zahl.
using uint = unsigned int;

// Mit Verkettung implementierte Streuwerttabelle
// mit Schlüsseltyp K und Werttyp V.
// An der Stelle, an der HashChain für einen bestimmten Schlüsseltyp K
// verwendet wird, muss eine Funktion uint hashval (K) zur Berechnung
// von Streuwerten sowie ein passender Gleichheitsoperator (==) für den
// Typ K bekannt sein.
template <typename K, typename V>
struct HashChain {
    struct Elem{
        K key;
        V val;
        Elem* next;
    };

    uint size;
    Elem** tab;

    // Initialisierung mit Größe n.
    HashChain (uint n){
        size = n;
        tab = new Elem* [size] ();
    }

    // Eintrag mit Schlüssel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufügen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put(K k, V v) {
        uint i = hashval(k) % size;
        for (Elem* p = tab[i]; p != nullptr; p = p->next) {
            if(p->key == k) {
                p->val = v;
                return true;
            } else{
                continue;
            }
        }
        Elem* p = new Elem;
        p->key = k;
        p->val = v;
        p->next = tab[i];
        tab[i] = p;
        return true;
    }

    // Wert zum Schlüssel k über den Referenzparameter v zurückliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unverändert, und der Resultatwert ist false.
    bool get (K k, V& v){
        uint i = hashval(k) % size;
        for (Elem* p = tab[i]; p != nullptr; p = p->next) {
            if(p->key == k) {
                v = p->val;
                return true;
            } else{
                continue;
            }
        }
        return false;
    }

    // Eintrag mit Schlüssel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove (K k) {
        uint i = hashval(k) % size;
        for (Elem* p = tab[i]; p != nullptr; p = p->next){
            if(tab[i]->key == k) {
                tab[i] = tab[i]->next;
                return true;
            }

            if ((p->next)->key == k){
                p->next = (p->next)->next;
                return true;
            }
        }
        return false;
    }


        // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schlüssel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plätze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // für die Typen K und V geben.
    void dump(){
        for (uint i = 0; i < size; i++) {
            for (Elem* p = tab[i]; p != nullptr; p = p->next) {
                cout << i << " " << p->key << " " << p->val << endl;
            }
        }
    }
};

// Sondierungssequenz mit Schlüsseltyp K für lineare Sondierung.
// An der Stelle, an der LinProb für einen bestimmten Schlüsseltyp K
// verwendet wird, muss wiederum uint hashval (K) bekannt sein.

template <typename K>
struct LinProb {
    uint size, j, s;
    K key;
    // Initialisierung der Sequenz mit Schlüssel k und Tabellengröße n.
    LinProb (K k, uint n) {
        key = k;
        size = n;
        s = hashval(key) % size;
        j = size;
    }
    // Den ersten bzw. nächsten Wert der Sequenz liefern.
    // Nach einem Aufruf des Konstruktors darf diese Funktion also
    // bis zu n-mal aufgerufen werden.
    // Achtung: Die direkte Verwendung der Formel
    // s[j](k) = (h(k) + j) mod n
    // kann durch arithmetischen Überlauf zu falschen Ergebnissen
    // führen, wenn h(k) sehr groß ist.
    // Deshalb sollte nur der erste Wert s[0](k) = h(k) mod n direkt
    // und alle weiteren Werte jeweils aus dem vorigen Wert berechnet
    // werden: s[j](k) = (s[j-1](k) + 1) mod n für j = 1, ..., n-1.
    // Der vorige Wert kann hierfür in einer Elementvariablen
    // gespeichert werden.
    // Dann kann bei realistischen Tabellengrößen n kein Überlauf
    // auftreten.
    uint next (){
        s = (s + j) % size;
        j++;
        return s;
    }
};

// Sondierungssequenz mit Schlüsseltyp K für quadratische Sondierung,
// analog zu LinProb.
template <typename K>
struct QuadProb {
    uint size, s, j;
    K key;
    QuadProb (K k, uint n){
        key = k;
        size = n;
        s = hashval(key) % size;
        j = size;
    }

    uint next (){
        s = (s + j * j) % size;
        j++;
        return s;
    }
};

// Sondierungssequenz mit Schlüsseltyp K für doppelte Streuung.
// An der Stelle, an der DblHash für einen bestimmten Schlüsseltyp K
// verwendet wird, muss wiederum uint hashval (K) sowie eine zweite
// Streuwertfunktion uint hashval2 (K, uint n) bekannt sein, die nur
// Werte von 1 bis n - 1 liefert, die teilerfremd zu n sind.
// Ansonsten analog zu LinProb.
template <typename K>
struct DblHash {
    uint size, s, j;
    K key;
    DblHash (K k, uint n){
        key = k;
        size = n;
        s = hashval(key) % size;
        j = size;
    }
    uint next (){
        s = (s + hashval2(key, size) * j) % size;
        j++;
        return s;
    }
};

// Mit offener Adressierung implementierte Streuwerttabelle mit
// Schlüsseltyp K, Werttyp V und Sondierungssequenz des Typs S.
// S muss einen Konstruktor S (K, uint) zur Initialisierung der Sequenz
// sowie eine Elementfunktion next () zur Abfrage des ersten bzw.
// nächsten Werts der Sequenz besitzen.
// Bedeutung von Konstruktor und Elementfunktionen wie bei HashChain
// mit folgenden Änderungen:
// put ist bei einer vollen Tabelle wirkungslos und liefert false,
// wenn ein neuer Eintrag hinzugefügt werden müsste.
// dump gibt von Plätzen mit Löschmarkierung nur ihre Nummer aus.
template <typename K, typename V, typename S>
struct HashOpen {
    enum Kind {Empty, Regular, delted};
    struct Elem{
        K key;
        V val;
        Kind kind;
    };

    uint size;
    Elem* tab;

    HashOpen(uint n){
        size = n;
        tab = new Elem[size];
        for (uint i = 0; i < size; i++) {
            tab[i].kind = Empty;
        }
    }


    //Berechne den Index i = sj (k ).
    // Wenn tab[i] leer ist, liefere „nicht vorhanden“ und entweder den gemerkten
    //Index (falls es bereits einen gibt) oder (andernfalls) den Index i zurück.
    // Wenn tab[i] eine Löschmarkierung (siehe unten) enthält
    //und bis jetzt noch kein Index gemerkt wurde,
    // merke den Index i.
    // Wenn tab[i] ein Objekt (k ¢, v ¢) mit k ¢ = k und irgendein
    //Wenn während der Schleife ein Index gemerkt wurde,
    //liefere „nicht vorhanden“ und diesen Index zurück.
    // Andernfalls liefere „Tabelle voll“ zurück.

    uint Hilfsoperation(K k) {
        uint index = 0;
        S s(k, size);
        uint i = s.next();
        for (int j = 0; j < size; ++j) {
            if (tab[i].kind == Empty) {
                if (index > 0) {
                    return index;
                }
                return i;
            } else if (tab[i].kind == delted) {
                if (index == 0) {
                    index = i;
                }
            } else if (tab[i].key == k) {
                return i;
            }
            i = s.next();
        }
        return index;
    }

    //Führe die obige Hilfsoperation aus.
    //Wenn sie einen Index i zurückliefer t, speichere das Objekt (k , v ) in tab[i ].
    //Ander nfalls signalisiere einen Fehler (Tabelle voll).

    bool put(K k, V v){
        uint i = Hilfsoperation(k);
        if (i == 0) {
            return false;
        }
        if (tab[i].kind == Empty) {
            tab[i].key = k;
            tab[i].val = v;
            tab[i].kind = Regular;
            return true;
        }
        return false;
    }

    // Führe die obige Hilfsoperation aus.
    // Wenn sie „vorhanden“ und einen Index i zurückliefer t,
    // liefere den Wer t v ¢ des in tab[i ] gespeicher ten Objekts (k ¢, v ¢) zurück.
    // Ander nfalls liefere ^.
    bool get(K k, V& v){
        uint i = Hilfsoperation(k);
        if (i == 0) {
            return false;
        }
        if (tab[i].kind == Regular) {
            v = tab[i].val;
            return true;
        }
        return false;
    }

    //Führe die obige Hilfsoperation aus.
    // Wenn sie „vorhanden“ und einen Index i zurückliefert,
    // schreibe eine Löschmarkierung in tab[i].

    bool remove(K k){
        uint i = Hilfsoperation(k);
        if (i == 0) {
            return false;
        }
        if (tab[i].kind == Regular) {
            tab[i].kind = delted;
            return true;
        }
        return false;
    }

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schlüssel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plätze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // für die Typen K und V geben.
    void dump (){
        for (uint i = 0; i < size; i++) {
            if (tab[i].kind == Regular) {
                cout << i << " " << tab[i].key << " " << tab[i].val << endl;
            } else if (tab[i].kind == delted) {
                cout << i << endl;
            }
        }
    }
};
