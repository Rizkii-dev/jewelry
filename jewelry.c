#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function
#include <ctype.h> // For tolower function

#define MAX 100

typedef struct {
    char id[6];
    char name[21];
    char description[51];
    char category[11];
    int price;
    int stock;
} Jewelry;

Jewelry jewelry[MAX];
int jewelryCount = 0;

// Load jewelry data from KaRtier.txt
void loadJewelry()
{
    FILE *file = fopen("KaRtier.txt", "r");
    if (file == NULL)
    {
        jewelryCount = 0; // If file not found, start with empty store
        return;
    }

    while (fscanf(file, "%5s#%20[^#]#%50[^#]#%10[^#]#%d#%d\n",
        jewelry[jewelryCount].id,//%[^\n]
        jewelry[jewelryCount].name,
        jewelry[jewelryCount].description,
        jewelry[jewelryCount].category,
        &jewelry[jewelryCount].price,
        &jewelry[jewelryCount].stock) == 6)
    {
        jewelryCount++;
    }

    fclose(file);
}

// Save jewelry data to KaRtier.txt
void saveJewelry()
{
    FILE *file = fopen("KaRtier.txt", "w");
    for (int i = 0; i < jewelryCount; i++)
    {
        fprintf(file, "%s#%s#%s#%s#%d#%d\n",
                jewelry[i].id,
                jewelry[i].name,
                jewelry[i].description,
                jewelry[i].category,
                jewelry[i].price,
                jewelry[i].stock);
    }
    fclose(file);
}

// Find jewelry by ID
int findJewelryById(char id[])
{
    for (int i = 0; i < jewelryCount; i++)
    {
        if (strcmp(jewelry[i].id, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

// View all jewelry
void viewAllJewelry()
{
    if (jewelryCount == 0)
    {
        printf("No jewelry in the store.\n");
        sleep(3);
        system("cls"); // Clear screen
        return;
    }

    int choice = 0;

    do
    {
        system("cls"); // Clear screen
        for (int i = 0; i < jewelryCount; i++)
        {
            printf("ID: %-5s | Name: %-20s | Description: %-50s | Category: %-10s | Price: %-4d, Stock: %-3d\n",
                jewelry[i].id, jewelry[i].name, jewelry[i].description,
                jewelry[i].category, jewelry[i].price, jewelry[i].stock);
        }

        printf("\nSort by:\n");
        printf("1. ID\n");
        printf("2. Name\n");
        printf("3. Description\n");
        printf("4. Category\n");
        printf("5. Price\n");
        printf("6. Stock\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // sort by character ASCII value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (strcmp(jewelry[i].id, jewelry[j].id) > 0)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 2:
            // sort by character ASCII value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (strcmp(jewelry[i].name, jewelry[j].name) > 0)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 3:
            // sort by character ASCII value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (strcmp(jewelry[i].description, jewelry[j].description) > 0)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 4:
            // sort by character ASCII value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (strcmp(jewelry[i].category, jewelry[j].category) > 0)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 5:
            // sort by integer value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (jewelry[i].price > jewelry[j].price)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 6:
            //sort by integer value
            for (int i = 0; i < jewelryCount - 1; i++)
            {
                for (int j = i + 1; j < jewelryCount; j++)
                {
                    if (jewelry[i].stock > jewelry[j].stock)
                    {
                        Jewelry temp = jewelry[i];
                        jewelry[i] = jewelry[j];
                        jewelry[j] = temp;
                    }
                }
            }
            break;
        case 0:
            printf("Exiting page.\n");
            sleep(3);
            system("cls"); // Clear screen
            break;
        default:
            printf("Invalid choice! Please choose between 0 and 6.\n");
            sleep(3);
            system("cls"); // Clear screen
        }
    } while (choice != 0);
}



// Shop jewelry
void shopJewelry()
{
    if (jewelryCount == 0)
    {
        printf("No jewelry in the store.\n");
        sleep(3);
        system("cls"); // Clear screen
        return;
    }

    int numberOfOutOfStock = 0;
    system("cls"); // Clear screen
    for (int i = 0; i < jewelryCount; i++)
    {
        printf("ID: %-5s | Name: %-20s | Description: %-50s | Category: %-10s | Price: %-4d, Stock: %-3d\n",
            jewelry[i].id, jewelry[i].name, jewelry[i].description,
            jewelry[i].category, jewelry[i].price, jewelry[i].stock);

        if (jewelry[i].stock == 0) {
            numberOfOutOfStock++;
        }
    }

    if (numberOfOutOfStock == jewelryCount) {
        printf("All jewelry out of stock!\n");
        sleep(3);
        system("cls"); // Clear screen
        return;
    }

    char id[6];
    printf("Enter Jewelry ID to purchase: ");
    scanf("%s", id);

    int index = findJewelryById(id);
    if (index != -1)
    {
        if (jewelry[index].stock > 0)
        {
            jewelry[index].stock--;
            saveJewelry();
            printf("Jewelry purchased successfully!\n");
            sleep(3);
            system("cls"); // Clear screen
        }
        else
        {
            printf("Jewelry out of stock!\n");
            sleep(3);
            system("cls"); // Clear screen
        }
    }
    else
    {
        printf("Jewelry not found!\n");
        sleep(3);
        system("cls"); // Clear screen
    }
}


// Add new jewelry
void addJewelry()
{
    Jewelry newJewelry;
    char id[6];

    printf("Enter Jewelry Name (3-20 characters): ");
    scanf(" %[^\n]", newJewelry.name);
    while (strlen(newJewelry.name) < 3 || strlen(newJewelry.name) > 20)
    {
        printf("Invalid name length. Please enter a valid name: ");
        scanf(" %[^\n]", newJewelry.name);
    }
    
    //check if there is a dupelicate
    int isThereDupe = 0;
    int dupeIndex;
    for (int i = 0; i < jewelryCount; i++)
    {
        if (strcmp(jewelry[i].name, newJewelry.name) == 0)
        {
            dupeIndex = i;
            isThereDupe = 1;
        }
    }

    printf("Enter Jewelry Description (10-50 characters): ");
    scanf(" %[^\n]", newJewelry.description);
    while (strlen(newJewelry.description) < 10 || strlen(newJewelry.description) > 50)
    {
        printf("Invalid description length. Please enter a valid description: ");
        scanf(" %[^\n]", newJewelry.description);
    }

    printf("Enter Jewelry Category (Ring/Bracelet/Necklace): ");
    scanf("%s", newJewelry.category);
    int len = strlen(newJewelry.category);

    for (int i = 0; i < len; i++)
    {
        newJewelry.category[i] = tolower((unsigned char)newJewelry.category[i]);
    }

    while (strcmp(newJewelry.category, "ring") != 0 && strcmp(newJewelry.category, "bracelet") != 0 && strcmp(newJewelry.category, "necklace") != 0)
    {
        printf("Invalid category. Please enter 'Ring', 'Bracelet', or 'Necklace': ");
        scanf("%s", newJewelry.category);

        for (int i = 0; i < len; i++)
        {
            newJewelry.category[i] = tolower((unsigned char)newJewelry.category[i]);
        }
    }

    if (strcmp(newJewelry.category, jewelry[dupeIndex].category) != 0) {
        isThereDupe = 0;
    }
    
    //checking the dupe if the type is the same
    while (isThereDupe)
    {
        printf("Invalid category. There is already a similiar name Jewelry that is in this category\n");
        printf("what do you want to do? put it in a different category or cancel\n1. Different category\n2. cancel\nchoose: ");
        int choose;
        scanf ("%d", &choose);
        
        if (choose == 2) {
            return;
		}
		
        printf("Enter Jewelry Category (Ring/Bracelet/Necklace): ");
        scanf("%s", newJewelry.category);

        for (int i = 0; i < len; i++)
        {
            newJewelry.category[i] = tolower((unsigned char)newJewelry.category[i]);
        }

        while (strcmp(newJewelry.category, jewelry[dupeIndex].category) == 0)
        {
            printf("Invalid category. There is already a similiar name Jewelry that is in this category\n");
            printf("Enter Jewelry Category (Ring/Bracelet/Necklace): ");
            scanf("%s", newJewelry.category);

            for (int i = 0; i < len; i++)
            {
                newJewelry.category[i] = tolower((unsigned char)newJewelry.category[i]);
            }
        }
        
        isThereDupe = 0;
    }
    
    for (int i = 0; i < len; i++)
    {
        newJewelry.category[i] = tolower((unsigned char)newJewelry.category[i]);
    }
    
    newJewelry.category[0] = toupper((unsigned char)newJewelry.category[0]);

    printf("Enter Jewelry Price (500-5000): ");
    scanf("%d", &newJewelry.price);
    while (newJewelry.price < 500 || newJewelry.price > 5000)
    {
        printf("Invalid price. Please enter a price between 500 and 5000: ");
        scanf("%d", &newJewelry.price);
    }

    printf("Enter Jewelry Stock (1-100): ");
    scanf("%d", &newJewelry.stock);
    while (newJewelry.stock < 1 || newJewelry.stock > 100)
    {
        printf("Invalid stock. Please enter a stock between 1 and 100: ");
        scanf("%d", &newJewelry.stock);
    }

    // Generate Jewelry ID
    snprintf(newJewelry.id, 6, "J%04d", jewelryCount + 1);

    // Add the new jewelry to the list and save
    jewelry[jewelryCount++] = newJewelry;
    saveJewelry();
    printf("Jewelry added successfully!\n");
    sleep(3);
    system("cls"); // Clear screen
}

// Delete jewelry
void deleteJewelry()
{
    if (jewelryCount == 0)
    {
        printf("No jewelry in the store.\n");
        sleep(3);
        system("cls"); // Clear screen
        return;
    }

    system("cls"); // Clear screen
    for (int i = 0; i < jewelryCount; i++)
    {
        printf("ID: %-5s | Name: %-20s | Description: %-50s | Category: %-10s | Price: %-4d, Stock: %-3d\n",
            jewelry[i].id, jewelry[i].name, jewelry[i].description,
            jewelry[i].category, jewelry[i].price, jewelry[i].stock);
    }

    char id[6];
    printf("Enter Jewelry ID to delete: ");
    scanf("%s", id);

    int index = findJewelryById(id);
    if (index != -1)
    {
        // Shift the array to delete the jewelry
        for (int i = index; i < jewelryCount - 1; i++)
        {
            jewelry[i] = jewelry[i + 1];
        }
        jewelryCount--;
        saveJewelry();
        printf("Jewelry deleted successfully!\n");
        sleep(3);
        system("cls"); // Clear screen
    }
    else
    {
        printf("Jewelry not found!\n");
        sleep(3);
        system("cls"); // Clear screen
    }
}

// Admin page
void adminPage()
{
    int choice;
    system("cls"); // Clear screen
    do
    {
        printf("\nAdmin Menu:\n");
        printf("1. Add New Jewelry\n");
        printf("2. Delete Jewelry\n");
        printf("3. View All Jewelry\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addJewelry();
            system("cls"); // Clear screen
            break;
        case 2:
            deleteJewelry();
            system("cls"); // Clear screen
            break;
        case 3:
            viewAllJewelry();
            break;
        case 0:
            printf("Exiting admin page.\n");
            sleep(3);
            system("cls"); // Clear screen
            break;
        default:
            printf("Invalid choice! Please choose between 0 and 3.\n");
            sleep(3);
            system("cls"); // Clear screen
        }
    } while (choice != 0);
}

// User page
void userPage()
{
    int choice;
    system("cls"); // Clear screen

    do
    {
        printf("\nUser Menu:\n");
        printf("1. Shop Jewelry\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            shopJewelry();
            break;
        case 0:
            printf("Exiting user page.\n");
            sleep(3);
            system("cls"); // Clear screen
            break;
        default:
            printf("Invalid choice! Please choose between 0 and 1.\n");
            sleep(3);
            system("cls"); // Clear screen
        }
    } while (choice != 0);
}

// Display landing page
void landingPage()
{
    system("cls"); // Clear screen

    char role[10];
    printf("Welcome to KaRtier\n");
    printf("Choose your role (Admin/User): ");
    scanf("%s", role);

    int len = strlen(role);

    for (int i = 0; i < len; i++)
    {
        role[i] = tolower((unsigned char)role[i]);
    }

    if (strcmp(role, "admin") == 0)
    {
        adminPage();
    }
    else if (strcmp(role, "user") == 0)
    {
        userPage();
    }
    else
    {
        printf("Invalid role. Please choose either 'Admin' or 'User'.\n");
        sleep(3);
        landingPage();
    }
}

int main() {
    loadJewelry();  // Load jewelry data from file at the start
    landingPage();  // Display landing page
    return 0;
}


