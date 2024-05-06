/**********************************************
    File: Movie.cpp
    Project: CMSC 202 Project 5, Spring 2024
    Name: Justin Beverly
    Date: 04/00/24
    Section: 41
    E-Mail: justinb8@gl.umbc.edu
**********************************************/
#include <iostream>
#include <string>
#include "Movie.h"
using namespace std;

  //Name: Movie - Default Constructor
  //Precondition: None
  //Postcondition: Creates a default movie
  Movie::Movie(){

  }
  //Name: Movie - Overloaded Constructor
  //Precondition: Requires title, rating, genre, year, director, star,
  //              budget, gross, studio, and runtime
  //Postcondition: Creates a movie entry based on passed parameters
  Movie::Movie(string title, string rating, string genre, int year, string director,
	string star, long budget, long gross, string studio, int runtime){
        m_title = title;
        m_rating = rating;
        m_genre = genre;
        m_year = year;
        m_director = director;
        m_star = star;
        m_budget = budget;
        m_gross = gross;
        m_studio = studio;
        m_runtime = runtime;
    }
  //Name: Mutators and Accessors
  //Precondition: None
  //Postcondition: Sets and Gets private member variables
  string Movie::GetTitle()const{
    return m_title;
  } // return title
  string Movie::GetRating()const{
    return m_rating;
  } // return rating
  string Movie::GetGenre()const{
    return m_genre;
  } //return genre
  int Movie::GetYear()const{
    return m_year;
  } // return year
  string Movie::GetDirector()const{
    return m_director;
  } // returns director
  string Movie::GetStar() const{
    return m_star;
  } // returns star
  long Movie::GetBudget() const{
    return m_budget;
  } // returns budget
  long Movie::GetGross() const{
    return m_gross;
  } // returns total box office returns (gross)
  string Movie::GetStudio() const{
    return m_studio;
  } // returns studio
  int Movie::GetRuntime() const{
    return m_runtime;
  } //returns runtime of movie (in minutes)
  void Movie::SetTitle(string title){
    m_title = title;
  }
  void Movie::SetRating(string rating){
    m_rating = rating;
  }
  void Movie::SetGenre(string genre){
    m_genre = genre;
  }
  void Movie::SetYear(int year){
    m_year = year;
  }
  void Movie::SetDirector(string director){
    m_director = director;
  }
  void Movie::SetStar(string star){
    m_star = star;
  }
  void Movie::SetBudget(long budget){
    m_budget = budget;
  }
  void Movie::SetGross(long gross){
    m_gross = gross;
  }
  void Movie::SetStudio(string studio){
    m_studio = studio;
  }
  void Movie::SetRuntime(int runtime){
    m_runtime = runtime;
  }
  //Name: Overloaded << operator
  //Precondition: movie available
  //Postcondition: Returns output stream including title by director from year
  ostream& operator<<(ostream& out, Movie& m){
    out << m.m_title << " by " << m.m_director << " from " << m.m_year;
    return out;
  }
  //Name: Overloaded Relational Operator (<)
  //Precondition: Two movie objects required
  //Postcondition: if passed movie's year is less than first,
  //               return true else false
  bool Movie::operator<(const Movie& m){
    if (this->GetYear() < m.GetYear()){return false;}
    else {return true;}
  }
  //Name: Overloaded Relational Operator (>)
  //Precondition: Two movie objects required
  //Postcondition: if passed movie's year is greater than first,
  //               return true else false
  bool Movie::operator>(const Movie& m){
    if (this->GetYear() > m.GetYear()){return false;}
    else {return true;}
  }
