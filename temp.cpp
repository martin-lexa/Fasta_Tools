#include <fstream>
#include <vector>

class Class
{
};

// to handle writing of a class object to a file
std::ofstream &operator<<(std::ofstream &i_out, Class &i_class)
{
    i_out << i_class.getProperty() << ", " << i_class.getOtherProperty() << '\n';
}

// automatisch befüllen im Constructor mit "g_classList.push_back(this)" - "this" is ein Pointer
// im Destructor der Klasse muss das Objekt aus dieser Liste gelöscht werden "g_classList.erase(this)"
// auch im Destructor:
// for ( auto iter = g_classList.begin(); iter != g_classList.end; iter++)
//      if (*iter == this)
//      {
//          g_classList.erase(iter);
//          return;
//      }
std::vector<Class *> g_classList; // g wie global

// static variableName - heißt, dass eine Variable für die ganze Klasse gilt und nur einmal instanziert wird
// static const std::vector<Class *> &getAllThingies() { return g_classList; }

/*    auto iter = sm_allAcids.find(i_oneLetterName);
    if (iter != sm_allAcids.end())
        return iter->second;
    else
        ; // ERROR */

//////////////////////////////////////////////////////////////////////

/*
class ProteinSequence : public Sequence
{
};

class NucleicAcidSequence : public Sequence
{
public:
    enum class NucleicAcidSequenceType
    {
        DNA,
        RNA
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType;
};

class DNA_Sequence : public NucleicAcidSequence
{
public:
    enum class DNA_Bases // initialized with powers of 2 to enable bitwise OR ( | operator ) linking
    {
        A = 1,
        C = 2,
        G = 4,
        T = 8
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType = NucleicAcidSequenceType::DNA;
};

class RNA_Sequence : public NucleicAcidSequence
{
public:
    enum class DNA_Bases
    {
        A = 1,
        C = 2,
        G = 4,
        U = 8
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType = NucleicAcidSequenceType::RNA;
};*/