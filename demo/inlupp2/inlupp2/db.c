#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


/*_________uppgift: 6.1________________*/

//STRUKT
struct item
{
    char *namn;
    char *beskrivning;
    int pris;
    char *lagerhylla; //kommer behövas en kontroll så att vi följer korrekt format
};

//TYPALIAS

typedef struct item item_t;

/*_________uppgift: 6.2________________*/

void print_item(item_t *item)
{

    char *namn = item->namn;
    char *beskrivning = item->beskrivning;
    int pris = item->pris;
    int decimal = (pris % 100);
    char *lager = item->lagerhylla;

    printf("\nNamn: %s\nBeskrivning: %s\nPris: %d.%d SEK\nLagerhylla: %s\n\n", namn, beskrivning, pris, decimal, lager);
}

item_t make_item(char *namn, char *beskrivning, int pris, char *lagerhylla)
{

    item_t created_item;

    created_item.namn = namn;
    created_item.beskrivning = beskrivning;
    created_item.pris = pris;
    created_item.lagerhylla = lagerhylla;

    return created_item;
}

//Skriv en funktion make_item() som tar som indata namn,
//beskrivning, pris och lagerhylla. Funktionen make_item kan förutsätta att lagerhyllans format är korrekt.

item_t input_item()
{

    char *namn = ask_question_string("Varunamn: ");
    char *beskrivning = ask_question_string("Beskrivning: ");
    int pris =  ask_question_int("Skriv priset: ");
    char *lagerhylla =  ask_question_shelf("Lagerhylla: ");

    return make_item(namn, beskrivning, pris, lagerhylla);

}

char *magick(char *arr1[], char *arr2[], char *arr3[], int arr_size) //), char *arr2, char *arr3, int arr_size) {
{

    // srandom(time(NULL)); // Initialisera slumpgeneratorn
    int random_word1 = random() % arr_size; // Generate random indices for each array
    int random_word2 = random() % arr_size;
    int random_word3 = random() % arr_size;
    int count = 0;
    int count2 = 0;
    char buf[255];

    while (arr1[random_word1][count] != '\0' && count < 255)
    {
        buf[count] = arr1[random_word1][count];
        count++;
    }

    buf[count] = '-';
    count++;


    // strcat(buf, "-");  //testar lite olika funktioner från string.h biblioteket. ska vara en slags append.

    while (arr2[random_word2][count2] != '\0' && count < 255)
    {
        buf[count] = arr2[random_word2][count2];
        count++;
        count2++;
    }

    buf[count] = ' ';
    count++;

    count2 = 0;

    while (arr3[random_word3][count2] != '\0' && count < 255)
    {
        buf[count] = arr3[random_word3][count2];
        count++;
        count2++;
    }
    buf[count] = '\0';

    return strdup(buf);

}

void list_db(item_t *items, int no_items)
{

    int count = 1;
    printf("\n");
    for(int i = 0; i < no_items; i++)
    {
        printf("%d. %s\n", count++, items[i].namn);
    }
    printf("\n");

}

void edit_db(item_t *items)
{

    int result = 0; //dea'fault värde

    do
    {
        if(0 > result || result > 16 )
        {
            printf("Testa igen, finns ingen vara på den platsen\n");
        }
        result = ask_question_int("Vilken vara vill du editera?\n");
    }
    while(!(0 < result && result < 16));

    char *result_string = ask_question_string("Vad vill du ersätta varan med?\n");

    items[--result].namn = result_string;

    print_item(&items[result]);
}

int print_menu()
{
    printf("1. Lägga till en vara\n2. Ta bort en vara\n3. Redigera en vara\n4. Ångra senaste ändringen\n5. Lista hela varukatalogen\n6. Avsluta\n");
    int choice = ask_question_int("Vad vill du göra? ");

    return choice;

}

void add_item(item_t *items, int size)
{

    if (size > 0 && size <= 16)
    {
        item_t new_item = input_item();
        items[size] = new_item;
        ++size;
        print_menu();

    }
    else
    {
        printf("Du har valt att göra något som inte är möjligt för tillfället\n\n");
    }
}

void remove_item_from_db(item_t *items, int size)
{

    if (size > 0)
    {
        list_db(items, size);
        int choice = ask_question_int("Vilken vara vill du ta bort?");

        while(choice < size)
        {
            items[choice - 1] = items[choice];
            choice++;
        }

        list_db(items, size);
    }
}


int ask_question_menu(item_t *db, int db_siz)
{

    int check_choice = print_menu();

    if(check_choice > 7 ||  0 >= check_choice)
    {
        printf("Ange ett giltigt val \n");
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 1)
    {
        add_item(db, db_siz);
        db_siz++;
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 2)
    {
        remove_item_from_db(db, db_siz);
        db_siz--;
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 3)
    {
        edit_db(db);
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 4)
    {
        printf("Not yet implemented!");
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 5)
    {
        list_db(db, db_siz);
        ask_question_menu(db, db_siz);
    }

    if(check_choice == 6)
    {
        return 0;
    }
    return 0;
}

int event_loop(item_t *arr, int size) //** == *..[]
{
    ask_question_menu(arr, size);
}

int main(int argc, char *argv[])
{
    char *array1[] = { "Fantastisk", "Billig", "Kvalitativ" };
    char *array2[] = { "utomordenlig", "ganska", "vacker" };
    char *array3[] = { "laser", "koala", "flodhäst" };

    if (argc < 2)
    {
        printf("Usage: %s number\n", argv[0]);
    }
    else
    {
        item_t db[16]; // Array med plats för 16 varor
        int db_siz = 0; // Antalet varor i arrayen just nu

        int items = atoi(argv[1]); // Antalet varor som skall skapas

        if (items > 0 && items <= 16)
        {
            for (int i = 0; i < items; ++i)
            {
                // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
                item_t item = input_item();
                db[db_siz] = item;
                ++db_siz;
            }
        }
        else
        {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Avslutar programmet!
        }

        for (int i = db_siz; i < 16; ++i)
        {
            char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
            char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
            int price = random() % 200000;
            char shelf[] = { random() % ('Z'-'A') + 'A',
                             random() % 10 + '0',
                             random() % 10 + '0',
                             '\0'
                           };
            item_t item = make_item(name, desc, price, shelf);

            db[db_siz] = item;
            ++db_siz;
        }
        event_loop(db, db_siz);
    }
    return 0;
}


// int main() {
//     char *array1[] = { "Laser",        "Polka",    "Extra" };
//     char *array2[] = { "förnicklad",   "smakande", "ordinär" };
//     char *array3[] = { "skruvdragare", "kola",     "uppgift" };


//     char *test = magick(array1, array2, array3, 3);

//     printf("Nya strängar: %s\n", test);

//     return 0;
// }