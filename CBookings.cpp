#include <fstream>
#include <regex>
#include "CStudent.hpp"
#include "CBooking.hpp"
#include "CBookings.hpp"
#include "CList.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

CBookings::CBookings(string str)
{
  ifstream src(str);
  string Zeile;

  if (!src)
  {
    cout << str << " konnte nicht geoffnet werden !" << endl;
    exit(1);
  }
  else
  {
    while (getline(src, Zeile))
    {
      Zeile = regex_replace(Zeile, regex("^ +"), ""); //nur führende Leerzeichen entfernen

      if (Zeile == "</date>")
      {
        break;
      }

      if (Zeile.compare("<room>") == 0)
      {
        CRoom *R = new CRoom();
        R->load(src);
        Rooms.push_back(R);
      }
      if (Zeile.compare("<block>") == 0)
      {
        CBlock *B = new CBlock();
        B->load(src);
        Blocks.push_back(B);
      }
      if (Zeile.compare("<study>") == 0)
      {
        CStudy *S = new CStudy();
        S->load(src);
        Studies.push_back(S);
      }

      if (Zeile.compare("<student>") == 0)
      {
        CStudent *S1 = new CStudent();
        S1->load(src, *this);
        Persons.push_back(S1);
      }

      if (Zeile.compare("<teacher>") == 0)
      {
        CTeacher *T1 = new CTeacher();
        T1->load(src);
        Persons.push_back(T1);
      }

      if (Zeile.compare("<tutor>") == 0)
      {
        CTutor *TU = new CTutor();
        TU->load(src, *this);
        Persons.push_back(TU);
      }

      if (Zeile.compare("<subject>") == 0)
      {
        CSubject *S = new CSubject();
        S->load(src, *this);
        Subjects.push_back(S);
      }

      if (Zeile.compare("<booking>") == 0)
      {
        CBooking *CB = new CBooking();
        CB->load(src, *this);
        Bookings.push_back(CB);
      }
    }
  }
}

CStudy *CBookings::findStudy(string m_Name)
{
  for (int i = 0; i < Studies.size(); i++)
  {
    if (Studies[i]->getStudy() == m_Name)
    {
      return Studies[i];
    }
  }
  return NULL;
}

void CBookings::operator()(Data D)
{
  switch (D)
  {
  case ofPersons:
  {
    printPersons();
    break;
  }
  case ofStudents:
  {
    printStudents();
    break;
  }
  case ofTeachers:
  {
    printTeachers();
    break;
  }
  case ofBookings:
  {
    printBookings();
    break;
  }
  default:
    break;
  }
}

CPerson *CBookings::findTeacher(string m_Name)
{
  for (CList<CPerson *>::iterator it = Persons.begin(); it != Persons.end(); it++)
  {
    if ((*it)->getName() == m_Name)
    {
      return (*it);
      //operator()*it;
    }
    //operator()(it);
  }
  return NULL;
}

CRoom *CBookings::findRoom(string m_Name)
{
  for (int i = 0; i < Rooms.size(); i++)
  {
    if (Rooms[i]->getName() == m_Name)
    {
      return Rooms[i];
    }
  }
  return NULL;
}

CBlock *CBookings::findBlock(short blockNr)
{
  for (int i = 0; i < Blocks.size(); i++)
  {
    if (Blocks[i]->getBlockNr() == blockNr)
    {
      return Blocks[i];
    }
  }
  return NULL;
}

CSubject *CBookings::findSubject(std::string m_Name)
{
  for (int i = 0; i < Subjects.size(); i++)
  {
    if (Subjects[i]->getSubject() == m_Name)
    {
      return Subjects[i];
    }
  }
  return NULL;
}

CStudent *CBookings::findStudent(std::string m_Name)
{

  for (CList<CPerson *>::iterator it = Persons.begin(); it != Persons.end(); it++)
  {
    CStudent *Student = dynamic_cast<CStudent *>((*it));
    if (Student)
    {
      if (Student->getName() == m_Name)
      {
        return Student;
      }
    }
  }
  return NULL;
}

void CBookings::printPersons()
{
  cout << "Datei wurde erfolgreich eingelesen!\n"
       << endl;
  cout << "Personen : " << endl;

  for (CList<CPerson *>::iterator it = Persons.begin(); it != Persons.end(); it++)
  {
     cout << *(*it);
//    (*it)->print();
  }

  cout << endl;
}

void CBookings::printStudents()
{
  cout << "Studenten: " << endl;

  for (CList<CPerson*>::iterator it = Persons.begin(); it != Persons.end() ; it++)
  {
    CStudent *Student = dynamic_cast<CStudent *>((*it));
    if (Student)
      (*it)->print();
  }

  cout << endl;
}

void CBookings::printTeachers()
{
  cout << "Dozenten: " << endl;

  for (CList<CPerson*>::iterator it = Persons.begin(); it != Persons.end() ; it++)
  {
    CTeacher *Dozent = dynamic_cast<CTeacher *>((*it));
    if (Dozent)
      (*it)->print();
  }

  cout << endl;
}

void CBookings::printBookings()
{

  for (int i = 0; i < Bookings.size(); i++)
  {
    Bookings[i]->print();
    cout << endl;
    cout << endl;
  }
}

void CBookings::ClrMemory()
{
  cout << "Bloecke freigeben ..." << endl;
  for (int i = 0; i < Blocks.size(); i++)
  {
    delete Blocks[i];
  }
  cout << "Bloecke freigeben ok" << endl;

  cout << "Raeume freigeben ..." << endl;
  for (int i = 0; i < Blocks.size(); i++)
  {
    delete Rooms[i];
  }
  cout << "Raeume freigeben ok" << endl;

  cout << "Studiengaenge freigeben ..." << endl;
  for (vector<CStudy*>::iterator it = Studies.begin(); it != Studies.end() ; it++)
  {
    delete *it;
  }
  cout << "Studiengaenge freigeben ok" << endl;

  cout << "Personen freigeben ..." << endl;
  for (CList<CPerson*>::iterator it = Persons.begin(); it != Persons.end() ; it++)
  {
    delete *it;
  }
  cout << "Personen freigeben ok" << endl;

  cout << "Faecher freigeben ..." << endl;
  for (int i = 0; i < Subjects.size(); i++)
  {
    delete Subjects[i];
  }
  cout << "Faecher freigeben ok" << endl;

  cout << "Belegungen freigeben ..." << endl;
  for (int i = 0; i < Bookings.size(); i++)
  {
    delete Bookings[i];
  }
  cout << "Belegungen freigeben ok" << endl;
}
