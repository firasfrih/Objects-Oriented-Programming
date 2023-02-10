#include "CStudy.hpp"
#include <regex>   //führende Leerzeichen entfernen
using namespace std;
#include "CBookings.hpp"


CStudy::CStudy(string m_Name, bool m_NC, short m_NrOfTerms)
    : Name(m_Name), NC(m_NC), NrOfTerms(m_NrOfTerms)
{
}

void CStudy::print() const
{
   cout << Name;
}

void CStudy::load(ifstream &File)
{
   string Zeile;
   int Len;
   while (getline(File, Zeile))
   {
      Zeile = regex_replace(Zeile, regex("^ +"), ""); //nur führende Leerzeichen entfernen

      if (Zeile == "</study>")
      {
         break;
      }

      if (strncmp(Zeile.c_str(), "<name>", 6) == 0)
      {
         Len = Zeile.length() - (6 + 7); // length von "<name>" und </name> -> 6 + 7
         if (strncmp(Zeile.c_str() + 6 + Len, "</name>", 7) == 0)
         {
            Name = Zeile.substr(6, Len);
         }
      }

      if (strncmp(Zeile.c_str(), "<nc>", 4) == 0)
      {
         Len = Zeile.length() - (4 + 5);
         if (strncmp(Zeile.c_str() + 4 + Len, "</nc>", 5) == 0)
         {
            if (Zeile.substr(4, Len) == "true")
               NC = 1;
            else
               NC = 0;
         }
      }

      if (strncmp(Zeile.c_str(), "<nrofterms>", 11) == 0)
      {
         Len = Zeile.length() - (11 + 12);
         if (strncmp(Zeile.c_str() + 11 + Len, "</nrofterms>", 12) == 0)
         {
            NrOfTerms = stoi(Zeile.substr(11, Len));
         }
      }
   }
}