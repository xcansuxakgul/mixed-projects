## Data Analysis with C

This code provides various options to interact with and display the movie data.The program takes the name of the file to be read as a single argument. An example file (movie.txt) is attached. The program reads this file with labeled columns separated by a semicolon (;). Each line contains information about a movie (separated by semicolons).The program read this text file and parse the given information (separated by semicolons).

You can run this code with like [here](#run).


The program provides the following options:

It hold movies in two dynamic arrays called Budget. Its nodes are named Budget and Name.
Budget contain five components; The arrays name , title, titletype and top250 are stored as strings, while budget and year are stored as integers.

''' C
struct budget {
    int budget; 
    int year;
    char *title; 
    char *titletype; 
    char *top250;
}; 
'''

Name contain seven fields; type and directors are stored as string arrays (note here: this can contain multiple strings and is separated by commas), title, mustsee and url are stored as strings, while score and rating are stored as decimals.

''' C
struct Name {
    char **genre; 
    char *title;
    char **directors; 
    char *mustsee; 
    double rating; 
    double score; 
    char *url;
}; 
'''

Items in the Budget array be added and stored in descending order by year. If the years are the same, they be stored in descending order of the budget. If these two values are the same, they are in an arbitrary order.
The program  store the entire string array (which can be of arbitrary length) in a dynamically allocated string array.

The program  contain 7 different processes.
The program contain a menu like the one below. The program  terminate if and only if the user enters "8". If an invalid entry or previously requested action has been performed, the menu should be displayed repeatedly. There also be an error message when the menu is displayed due to an invalid input. The 7 processes mentioned are listed below:

1. List of Budget series
2. List of Name string
3. List of genera (species)
4. List of Movies by Year
5. List of Movies by Scores
6. All the Information of a Single Movie
7. Frequency of Species
8. Exit

### Running this program
<a name="run">
''' shell
gcc -o project-name main.c
'''

''' shell
./project-name movie.txt
'''
</a>
