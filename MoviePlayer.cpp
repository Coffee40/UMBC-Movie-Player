/**********************************************
    File: MoviePlayer.cpp
    Project: CMSC 202 Project 5, Spring 2024
    Name: Justin Beverly
    Date: 05/02/24
    Section: 41
    E-Mail: justinb8@gl.umbc.edu
**********************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Movie.h"
#include "Queue.cpp"
#include "MoviePlayer.h"

using namespace std;
  //Name: MoviePlayer - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with m_filename of "proj5_movies.txt"
  MoviePlayer::MoviePlayer(){

  }
  //Name: MoviePlayer - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with passed filename
  MoviePlayer::MoviePlayer(string filename){
    m_filename = filename;
  }
  //Name: ~MoviePlayer - Destructor
  //Precondition: None
  //Postcondition: Deallocates movies from m_movieCatalog
  MoviePlayer::~MoviePlayer(){
    for (int i = 0; i < int(m_movieCatalog.size()); i++){
        delete m_movieCatalog.at(i);
        m_movieCatalog.at(i) = nullptr;
    }

  }
  //Name: LoadCatalog()
  //Precondition: Requires m_filename to be populated
  //Postcondition: Dynamically allocates each movie and inserts into m_movieCatalog
  //Hint:          Allowed to use stoi (string to integer) if needed
  //Hint:          Allowed to use stoul (string to long) if needed
  void MoviePlayer::LoadCatalog(){
    //holder values for reading from file
    string title, rating, genre, year, director, star, budget, gross, studio, runtime;
    int movieCount = 0; //int to keep count of how many movies are loaded

    ifstream catalog(m_filename);
    //opens file and while loop that has condition that 
    //reads until the end of the file
    if (catalog.is_open()){
        while (getline(catalog, title, ';') &&
        getline(catalog, rating, ';') &&
        getline(catalog, genre, ';') &&
        getline(catalog, year, ';') &&
        getline(catalog, director, ';') &&
        getline(catalog, star, ';') &&
        getline(catalog, budget, ';') &&
        getline(catalog, gross, ';') &&
        getline(catalog, studio, ';') &&
        getline(catalog, runtime)){
            //Allocates data to new movie pointer
            Movie *temp = new Movie(title, rating, genre, stoi(year), director,
            star, stoul(budget), stoul(gross), studio, stoi(runtime));
            m_movieCatalog.push_back(temp); // pointer is pushed back to catalog vector
            movieCount++;
        }
    }
    cout << movieCount << " movie files loaded." << endl;
    catalog.close();
  }
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the menu
  void MoviePlayer::MainMenu(){
    int choice = 0; //holder for what menu option user picks 
    int count = 0; //holder for DisplayMovie return value

    //do while that runs until user picks 6
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Display Movue by Type and Year" << endl;
        cout << "2. Add Movie to Playlist" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Sort Playlist by Year" << endl;
        cout << "5. Search for Movie" << endl;
        cout << "6. Quit" << endl;
        cin >> choice;

        switch(choice){
            case 1:
                count = DisplayMovie();
                cout << count << " movies found." << endl;
                break;
            case 2:
                AddMovie();
                break;
            case 3:
                DisplayPlaylist();
                break;;
            case 4:
                SortPlaylist();
                break;
            case 5:
                SearchMovie();
                break;
            case 6:
                cout << "Thank you for using the UMBC Movie Player!" <<  endl;
                break;
            default:
                cout << "Pick a valid option" << endl;
                break;
        }

    }while(choice != 6);
  }
  //Name: DisplayMovie
  //Desc: Asks user for year (between min and max year)
  //      Asks user for genre (no validation)
  //      Displays all movies with year and genre with location in vector
  //Precondition: m_movieCatalog, MIN_YEAR, and MAX_YEAR are all populated
  //Postcondition: Returns count of movies found matching year and genre else 0
  int MoviePlayer::DisplayMovie(){
    int totalMovie = m_movieCatalog.size(); //int for total movie count
    int year = 0; //holder for what year user picks
    string genre = ""; //holder for what genre user picks
    int foundCount = 0; //holder for how many movies mach user selection

    cout << "Enter a search year (1980-2020): " << endl;
    cin >> year;

    //input validation
    while (year < MIN_YEAR || year > MAX_YEAR){
        cout << "Enter a valid year" << endl;
        cin >> year;
    }
    
    cout << "******" << year << "******" << endl;
    cout << "Which genre would you like?" << endl;
    cin >> genre;
    cout << "******" << genre << "******" << endl;
    cout << "MOVIE TOTAL: " << totalMovie << endl;

    //for loop that checks all movies and prints out which
    //movies match criteria 
    for (int i = 0; i < int(m_movieCatalog.size()); i++){
        if (m_movieCatalog.at(i)->GetYear() == year && m_movieCatalog.at(i)->GetGenre() == genre){
            cout << i+1 << " " << *m_movieCatalog.at(i) << endl;
            foundCount++;
        }
    }
    return foundCount;
  }
  //Name: AddMovie
  //Desc: Calls DisplayMovie where user chooses year and genre
  //      User enters index of movie to choose
  //      Validates for number to be between 0 - m_movieCatalog size
  //      Does NOT validate that movie chosen was from year and genre
  //      Uses overloaded << operator to display the example below
  //Example: Airplane! by Jim Abrahams from 1980 added to the playlist
  //Precondition: m_movieCatalog is populated
  //Postcondition: Adds pointer from m_catalog and inserts into m_playList
  void MoviePlayer::AddMovie(){
    int movieChoice; //holder for what movie user wants to add to playlist

    DisplayPlaylist();
    cout << "Choose the movie you would like to add to the playlist" << endl;
    
    int foundCount = DisplayMovie(); //count of how many movies meet criteria

    cout << foundCount << " moveis found." << endl;
    cout << "Enter the number of the movie you would like to add: " << endl;
    cin >> movieChoice;

    //input validation
    while (movieChoice < 1 || movieChoice > int(m_movieCatalog.size())){
        cout << "Enter a valid movie..." << endl;
        cin >> movieChoice;
    }
    
    //based on user input, movie is added to playlist
    Movie *temp = m_movieCatalog.at(movieChoice-1);
    cout << *temp << " added to the playlist." << endl;
    m_playList.PushBack(temp);

  }
  //Name: DisplayPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Displays the playlist using the overloaded << operator
  void MoviePlayer::DisplayPlaylist(){
    if (m_playList.GetSize() == 0){
        cout << "The playlist is currently empty" << endl;
    }else{
        for (int i = 0; i < m_playList.GetSize(); i++){
            cout << i+1 << ". " << *m_playList.At(i) << endl;
        }
    }
  }
  //Name: SortPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Sorts the playlist by year
  void MoviePlayer::SortPlaylist(){
    if (m_playList.GetSize() < 2){
        cout << "Playlist need at least 2 movies to sort" << endl;
    }else{
        m_playList.Sort();
        cout << "Done sorting by year" << endl;
        cout << m_playList.GetSize() << " items sorted." << endl;
    }
  }
  //Name: StartPlayer
  //Precondition: None (file name has already been provided)
  //Postcondition: Loads file and calls main menu
  void MoviePlayer::StartPlayer(){
    LoadCatalog();
    MainMenu();
  }
  //OPTIONAL: EXTRA CREDIT
  //Name: SearchMovie
  //See project document for details - must complete and submit base project first
  void MoviePlayer::SearchMovie(){
    int choice; //holder for what user selects for menu
    int foundCount = 0; //holder for how many movies found
    string name; //name to search for
    int year; //year to search for
    long int earnings; //earnings to search for

    //do while that makes user pick a menu option
    do{
    cout << "What would you like to search by?" << endl;
    cout << "1. Word in Title or Director" << endl;
    cout << "2. Year" << endl;
    cout << "3. Earnings" << endl;
    cin >> choice;
    }while(choice < 1 || choice > 3);

    //if statement that checks how user wants to search
    if (choice == 1){
        cout << "What string would you like to search?" << endl;
        cin >> name;

        //for loop that checks all movies if user input name
        //is in the title/director
        for (int i = 0; i < int(m_movieCatalog.size()); i++){
            if (int(m_movieCatalog.at(i)->GetTitle().find(name)) != -1 || 
            int(m_movieCatalog.at(i)->GetDirector().find(name)) != -1 ){
                foundCount++;
                cout << foundCount << ". " << *m_movieCatalog.at(i) << endl;
            }
        }
    }else if (choice == 2){
        cout << "What year would you like to search?" << endl;
        cin >> year;

        //input validation
        while (year < MIN_YEAR || year > MAX_YEAR){
            cout << "Enter valid year" << endl;
            cin >> year;
        }

        //for loop that checks all movies for matching year
        for (int i = 0; i < int(m_movieCatalog.size()); i++){
            if (m_movieCatalog.at(i)->GetYear() == year){
                foundCount++;
                cout << foundCount << ". " << *m_movieCatalog.at(i) << endl;
            }
        }
    }else if (choice == 3){
        cout << "What is the minimum profit?" << endl;
        cin >> earnings;

        //for loop that checks all movies profit (gross - budget) and compares
        //to user input earnings 
        for (int i = 0; i < int(m_movieCatalog.size()); i++){
            if ((m_movieCatalog.at(i)->GetGross() - m_movieCatalog.at(i)->GetBudget()) > earnings){
                foundCount++;
                cout << foundCount << ". " << *m_movieCatalog.at(i) << endl;
            }
        }
    }else{
        cout << "Not a valid choice..." << endl;
    }
    cout << foundCount << " movies found." << endl;
  }
