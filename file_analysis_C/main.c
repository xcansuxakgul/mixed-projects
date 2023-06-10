#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Budget {
    int budget;
    int year;
    char *title;
    char *titletype;
    char *top250;
};

struct Name {
    char **genre;
    char *title;
    char **directors;
    char *mustsee;
    double rating;
    double score;
    char *url;
};

void readMoviesFile(const char *filename, struct Budget **budgets, struct Name **names, int *numMovies) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    char line[500];
    *numMovies = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        (*numMovies)++;
    }

    rewind(file);

    *budgets = (struct Budget *)malloc((*numMovies) * sizeof(struct Budget));
    *names = (struct Name *)malloc((*numMovies) * sizeof(struct Name));

    for (int i = 0; i < *numMovies; i++) {
        fgets(line, sizeof(line), file);

        char *token = strtok(line, ";");
        (*budgets)[i].budget = atoi(token);

        token = strtok(NULL, ";");
        (*budgets)[i].title = strdup(token);
        (*names)[i].title = (*budgets)[i].title;
        
        token = strtok(NULL, ";");
        (*budgets)[i].titletype = strdup(token);
        
        token = strtok(NULL, ";");
        (*names)[i].directors = (char **)malloc(sizeof(char *));
        (*names)[i].directors[0] = strdup(token);
        
        token = strtok(NULL, ";");
        (*names)[i].rating = atof(token);
        
        token = strtok(NULL, ";");
        
        token = strtok(NULL, ";");
        (*budgets)[i].year = atoi(token);

        token = strtok(NULL, ";");
        (*names)[i].genre = (char **)malloc(sizeof(char *));
        (*names)[i].genre[0] = strdup(token);

        token = strtok(NULL, ";");
        (*names)[i].score = atof(token);        

        token = strtok(NULL, ";");
        (*budgets)[i].top250 = strdup(token);

        token = strtok(NULL, ";");
        (*names)[i].mustsee = strdup(token);

        token = strtok(NULL, ";");
        (*names)[i].url = strdup(token);

    }

    fclose(file);
}


void swapMovies(struct Budget *budgets, struct Name *names, int index1, int index2) {
    struct Budget tempBudget = budgets[index1];
    budgets[index1] = budgets[index2];
    budgets[index2] = tempBudget;

    struct Name tempName = names[index1];
    names[index1] = names[index2];
    names[index2] = tempName;
}

void sortMoviesByYearBudget(struct Budget *budgets, struct Name *names, int numMovies) {
    for (int i = 0; i < numMovies - 1; i++) {
        for (int j = 0; j < numMovies - i - 1; j++) {
            if (budgets[j].year < budgets[j + 1].year || 
                (budgets[j].year == budgets[j + 1].year && budgets[j].budget < budgets[j + 1].budget)) {
                swapMovies(budgets, names, j, j + 1);
            }
        }
    }
}



void printBudgetSeriesList(const struct Budget *budgets, int numMovies) {
    printf("Budget Series List:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Movie %d: Budget: %d, Year: %d\n", i + 1, budgets[i].budget, budgets[i].year);
    }
    printf("\n");
}

void printNameArrayList(const struct Name *names, int numMovies) {
    printf("Name Array List:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Movie %d: Title: %s, Directors: %s\n", i + 1, names[i].title, names[i].directors[0]);
    }
    printf("\n");
}

void printGenreList(const struct Name *names, int numMovies) {
    printf("Genre List:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Movie %d: Genre: %s\n", i + 1, names[i].genre[0]);
    }
    printf("\n");
}

void printMoviesByYear(const struct Budget *budgets, int numMovies) {
    printf("Movies by Year:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Movie %d: Year: %d, Title: %s\n", i + 1, budgets[i].year, budgets[i].title);
    }
    printf("\n");
}

void printMoviesByScores(const struct Name *names, int numMovies) {
    printf("Movies by Scores:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Movie %d: Score: %.2f, Rating: %.2f\n", i + 1, names[i].score, names[i].rating);
    }
    printf("\n");
}

void printMovieInformation(const struct Budget *budgets, const struct Name *names, int numMovies, int movieIndex) {
    if (movieIndex < 1 || movieIndex > numMovies) {
        printf("Invalid movie index.\n");
        return;
    }

    printf("Movie Information:\n");
    printf("Title: %s\n", names[movieIndex - 1].title);
    printf("Budget: %d\n", budgets[movieIndex - 1].budget);
    printf("Year: %d\n", budgets[movieIndex - 1].year);
    printf("Directors: %s\n", names[movieIndex - 1].directors[0]);
    printf("Rating: %.2f\n", names[movieIndex - 1].rating);
    printf("Score: %.2f\n", names[movieIndex - 1].score);
    printf("Genres: %s\n", names[movieIndex - 1].genre[0]);
    printf("Must See: %s\n", names[movieIndex - 1].mustsee);
    printf("URL: %s\n", names[movieIndex - 1].url);
    printf("\n");
}


void printGenreFrequency(const struct Name *names, int numMovies) {
    printf("Genre Frequency:\n");
    struct GenreFrequency {
        char *genre;
        int frequency;
    };

    int totalGenres = 0;
    struct GenreFrequency *genreFreq = (struct GenreFrequency *)malloc(numMovies * sizeof(struct GenreFrequency));

    for (int i = 0; i < numMovies; i++) {
        char *genreStr = strdup(names[i].genre[0]);

        // Tokenize the genre string
        char *token = strtok(genreStr, ",");
        while (token != NULL) {
            bool genreExists = false;
            for (int j = 0; j < totalGenres; j++) {
                if (strcmp(genreFreq[j].genre, token) == 0) {
                    genreFreq[j].frequency++;
                    genreExists = true;
                    break;
                }
            }
            if (!genreExists) {
                genreFreq[totalGenres].genre = strdup(token);
                genreFreq[totalGenres].frequency = 1;
                totalGenres++;
            }
            token = strtok(NULL, ",");
        }

        free(genreStr);
    }

    for (int i = 0; i < totalGenres; i++) {
        printf("%s: %d\n", genreFreq[i].genre, genreFreq[i].frequency);
        free(genreFreq[i].genre);
    }

    free(genreFreq);
    printf("\n");
}

void freeMemory(struct Budget *budgets, struct Name *names, int numMovies) {
    for (int i = 0; i < numMovies; i++) {
        free(budgets[i].title);
        free(budgets[i].titletype);
        free(budgets[i].top250);
        free(names[i].title);
        free(names[i].mustsee);
        free(names[i].url);
        free(names[i].genre[0]);
        free(names[i].directors[0]);
        free(names[i].genre);
        free(names[i].directors);
    }
    free(budgets);
    free(names);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide the filename as an argument.\n");
        return 1;
    }

    struct Budget *budgets;
    struct Name *names;
    int numMovies;

    readMoviesFile(argv[1], &budgets, &names, &numMovies);
    sortMoviesByYearBudget(budgets, names, numMovies);


    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Budget list\n");
        printf("2. Names\n");
        printf("3. Genres\n");
        printf("4. List of movies by year\n");
        printf("5. List of movies by scores\n");
        printf("6. All the Information of a Single Movie\n");
        printf("7. Frequency of genres\n");
        printf("8. Exit\n");
        printf("Enter your choice");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printBudgetSeriesList(budgets, numMovies);
                break;
            case 2:
                printNameArrayList(names, numMovies);
                break;
            case 3:
                printGenreList(names, numMovies);
                break;
            case 4:
                printMoviesByYear(budgets, numMovies);
                break;
            case 5:
                printMoviesByScores(names, numMovies);
                break;
            case 6: {
                int movieIndex;
                printf("Enter an index(1-%d): ", numMovies);
                scanf("%d", &movieIndex);
                printMovieInformation(budgets, names, numMovies, movieIndex);
                break;
            }
            case 7:
                printGenreFrequency(names, numMovies);
                break;
            case 8:
                freeMemory(budgets, names, numMovies);
                return 0;
            default:
                printf("Invalid choice.Try again\n");
        }
    }

    return 0;
}
