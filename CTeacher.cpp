#include "CTeacher.hpp"
#include <regex>
using namespace std;

CTeacher::CTeacher(string m_Name, string m_Street,
          string m_HouseNr, unsigned m_Zipcode,
          string m_City, int m_Day, int m_Month, int m_Year,
          int m_PersonalNr)
         : CPerson(m_Name,m_Street,m_HouseNr,m_Zipcode,m_City,m_Day,m_Month,m_Year),
           PersonalNr(m_PersonalNr)
 {}
 
 void CTeacher::print()
 {
   cout << Name << " (* ";
   Birthday.print();
   cout << "; ID " << ID << "; PersNr. " << PersonalNr << ")" << endl; 
 }


 void CTeacher::load(ifstream &File)
{
  string Zeile;
  int Len;
  while (getline(File, Zeile))
  {
    Zeile = regex_replace(Zeile, regex("^ +"), ""); //nur führende Leerzeichen entfernen

    if (Zeile == "</teacher>")
    {
      break;
    }

    if (strncmp(Zeile.c_str(), "<name>", 6) == 0)
    {
      Len = Zeile.length() - (6 + 7); // length von "<name>" und </name> -> 6 + 7
      if (strncmp(Zeile.c_str() + 6 + Len, "</name>", 7) == 0)
      {
        Name = Zeile.substr(6, Len);

        LfNr++;
        ID = LfNr;
      }
    }

    if (strncmp(Zeile.c_str(), "<address>", 7) == 0)
    {
      while (getline(File, Zeile))
      {
        Zeile = regex_replace(Zeile, regex("^ +"), ""); //nur führende Leerzeichen entfernen

        if (Zeile == "</address>")
        {
          break;
        }

        if (strncmp(Zeile.c_str(), "<street>", 8) == 0)
        {
          Len = Zeile.length() - (8 + 9);
          if (strncmp(Zeile.c_str() + 8 + Len, "</street>", 9) == 0)
          {
            Address.setStreet(Zeile.substr(8, Len));
          }
        }

        if (strncmp(Zeile.c_str(), "<housenr>", 9) == 0)
        {
          Len = Zeile.length() - (9 + 10);
          if (strncmp(Zeile.c_str() + 9 + Len, "</housenr>", 10) == 0)
          {
            Address.setHouseNr(Zeile.substr(9, Len));
          }
        }

        if (strncmp(Zeile.c_str(), "<zipcode>", 9) == 0)
        {
          Len = Zeile.length() - (9 + 10);
          if (strncmp(Zeile.c_str() + 9 + Len, "</zipcode>", 10) == 0)
          {
            Address.setZipcode(stoi(Zeile.substr(9, Len)));
          }
        }

        if (strncmp(Zeile.c_str(), "<city>", 6) == 0)
        {
          Len = Zeile.length() - (6 + 7);
          if (strncmp(Zeile.c_str() + 6 + Len, "</city>", 7) == 0)
          {
            Address.setCity(Zeile.substr(6, Len));
          }
        }
      }
    }

    if (strncmp(Zeile.c_str(), "<birthday>", 10) == 0)
    {
      while (getline(File, Zeile))
      {
        Zeile = regex_replace(Zeile, regex("^ +"), ""); //nur führende Leerzeichen entfernen

        if (Zeile == "</birthday>")
        {
          break;
        }

        if (strncmp(Zeile.c_str(), "<day>", 5) == 0)
        {
          Len = Zeile.length() - (5 + 6);
          if (strncmp(Zeile.c_str() + 5 + Len, "</day>", 6) == 0)
          {
            Birthday.setDay(stoi(Zeile.substr(5, Len)));
          }
        }

        if (strncmp(Zeile.c_str(), "<month>", 7) == 0)
        {
          Len = Zeile.length() - (7 + 8);
          if (strncmp(Zeile.c_str() + 7 + Len, "</month>", 8) == 0)
          {
            Birthday.setMonth(stoi(Zeile.substr(7, Len)));
          }
        }

        if (strncmp(Zeile.c_str(), "<year>", 6) == 0)
        {
          Len = Zeile.length() - (6 + 7);
          if (strncmp(Zeile.c_str() + 6 + Len, "</year>", 7) == 0)
          {
            Birthday.setYear(stoi(Zeile.substr(6, Len)));
          }
        }
      }
    }

    if (strncmp(Zeile.c_str(), "<personalnr>", 12) == 0)
    {
      Len = Zeile.length() - (12 + 13); 
      if (strncmp(Zeile.c_str() + 12 + Len, "</personalnr>", 13) == 0)
      {
         PersonalNr = stoi(Zeile.substr(12, Len));
      }
    }
    
  }
}