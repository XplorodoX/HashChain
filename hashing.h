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
        tab = new Elem* [n] ();
    }
    // Eintrag mit Schlüssel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufügen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put (K k, V& v){
        uint i = hashval(k) % size;
        for (Elem* p = tab[i]; p != nullptr; p = p->next) {
            if(p->key == k){

            }
        }
        ....... hier steht noch was ....
    }

    // Wert zum Schlüssel k über den Referenzparameter v zurückliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unverändert, und der Resultatwert ist false.
    bool get (K k, V& v)

    // Eintrag mit Schlüssel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove (K k)

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schlüssel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plätze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // für die Typen K und V geben.
    void dump ()
};

// Sondierungssequenz mit Schlüsseltyp K für lineare Sondierung.
// An der Stelle, an der LinProb für einen bestimmten Schlüsseltyp K
// verwendet wird, muss wiederum uint hashval (K) bekannt sein.
template <typename K>
struct LinProb {
    // Initialisierung der Sequenz mit Schlüssel k und Tabellengröße n.
    LinProb (K k, uint n)

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
    uint next ()
};

// Sondierungssequenz mit Schlüsseltyp K für quadratische Sondierung,
// analog zu LinProb.
template <typename K>
struct QuadProb {
};

// Sondierungssequenz mit Schlüsseltyp K für doppelte Streuung.
// An der Stelle, an der DblHash für einen bestimmten Schlüsseltyp K
// verwendet wird, muss wiederum uint hashval (K) sowie eine zweite
// Streuwertfunktion uint hashval2 (K, uint n) bekannt sein, die nur
// Werte von 1 bis n - 1 liefert, die teilerfremd zu n sind.
// Ansonsten analog zu LinProb.
template <typename K>
struct DblHash {
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

    HashChain (uint n){
        size = n;
        tab = new Elem* [n] ();
    }
    // Eintrag mit Schlüssel k und Wert v (am Anfang der jeweiligen
    // Liste) hinzufügen (wenn es noch keinen solchen Eintrag gibt)
    // bzw. ersetzen (wenn es bereits einen gibt).
    // Der Resultatwert ist immer true.
    bool put (K k, V& v){
        uint i = hashval(k) % size;
    }

    // Wert zum Schlüssel k über den Referenzparameter v zurückliefern,
    // falls vorhanden; der Resultatwert ist in diesem Fall true.
    // Andernfalls bleibt v unverändert, und der Resultatwert ist false.
    bool get (K k, V& v)

    // Eintrag mit Schlüssel k entfernen, falls vorhanden;
    // der Resultatwert ist in diesem Fall true.
    // Andernfalls wirkungslos, und der Resultatwert ist false.
    bool remove (K k)

    // Inhalt der Tabelle zu Testzwecken ausgeben:
    // Pro Eintrag eine Zeile bestehend aus der Nummer des Platzes,
    // Schlüssel und Wert, jeweils getrennt durch genau ein Leerzeichen.
    // Dieses Ausgabeformat muss exakt eingehalten werden.
    // Leere Plätze werden nicht ausgegeben.
    // Bei Verwendung von dump muss es passende Ausgabeoperatoren (<<)
    // für die Typen K und V geben.
    void dump ()

};