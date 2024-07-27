#include <stdio.h>
#include <stdlib.h>

const int seaDimX = 4;
const int seaDimY = 4;
const int numberOfShips = 3;
const int numberOfPlayers = 1;

const int dbg = 1;

struct battleSea
{
    int player;      // Player number
    int **matrix;    // Sea
    int *shipStatus; // Status of ships
};

// Allocate memory for sea
int initBattleSea(struct battleSea *sea)
{
    if (dbg)
        printf("- DBG: Initializing battleSea for Player %d...\n", (*sea).player);

    // Allocate memory for shipStatus
    (*sea).shipStatus = malloc(numberOfShips * sizeof(int *));

    // Reset shipStatus values
    for (int i = 0; i < seaDimY; i++)
    {
        (*sea).shipStatus[i] = 0;
    }

    // Allocate memory for sea
    (*sea).matrix = malloc(seaDimY * sizeof(int *));
    for (int i = 0; i < seaDimX; i++)
        (*sea).matrix[i] = malloc(seaDimX * sizeof(int));

    // Reset sea values
    for (int y = 0; y < seaDimY; y++)
    {
        for (int x = 0; x < seaDimX; x++)
        {
            (*sea).matrix[x][y] = 0;
        }
    }
}

// Reset sea values
int resetSea(struct battleSea *sea)
{
    if (dbg)
        printf("- DBG: Resetting battleSea for Player %d...\n", (*sea).player);

    for (int y = 0; y < seaDimY; y++)
    {
        for (int x = 0; x < seaDimX; x++)
        {
            (*sea).matrix[x][y] = 0;
        }
    }
}

// Prints Sea
int printSea(struct battleSea sea)
{
    printf("Player %d Sea:\n", sea.player);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            printf("%d", sea.matrix[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

// Place ship of size "ship" starting at coordinates "x, y" in orintation 0=x, 1= y, for player "&sea"
int placeShip(int ship, int orgX, int orgY, int orintation, struct battleSea *sea)
{
    printf("Player %d: Place %d-ship\n", (*sea).player, ship);
    printf("Chosen coordinates: %d, %d, orientation: %d\n", orgX, orgY, orintation);

    // Validate position
    if ((!orintation && orgX + ship > seaDimX) || (orintation && orgY + ship > seaDimY))
    {
        printf("ERROR: Placement not allowed!\n");
        return 0;
    }

    // Place ship
    for (int i = 0; i < ship; i++)
    {
        if (orintation)
        {
            (*sea).matrix[orgX][orgY + i] = ship;
        }
        else
        {
            (*sea).matrix[orgX + i][orgY] = ship;
        }
    }
    return 1;
}

// Shoot at x,y, and update matrix and ShipStatus
// Returns hit matrix value
int shoot(int targX, int targY, struct battleSea *sea)
{
    int hit = (*sea).matrix[targX][targY];
    if (dbg)
        printf("Shot: (%d, %d): %d ", targX, targY, hit);
    if (hit > 0 && hit <= numberOfShips)
    {
        (*sea).matrix[targX][targY] = (*sea).matrix[targX][targY] + numberOfShips;
        (*sea).shipStatus[hit - 1]++;
        if (dbg)
            printf("-> hit \n");
    }
    else
    {
        (*sea).matrix[targX][targY] = numberOfShips * 2 + 1;
        if (dbg)
            printf("-> miss \n");
    }
    return hit;
}

// Checks if hit sinks ship
// Returns 1 if sink, else 0;
int checkHit(int hit, struct battleSea *sea)
{
    if ((hit > 0))
    {
        if (((*sea).shipStatus[hit - 1] == hit))
        {
            if (dbg)
                printf("SHIP %d SUNK!\n", hit);
            return 1;
        }
    }
    return 0;
}

// Return 1 if there are ships left, else 0;
int checkShipArray(struct battleSea *sea)
{
    for (int i = 0; i < numberOfShips; i++)
    {
        if ((*sea).shipStatus[i] < i + 1)
        {
            return 1;
        }
    }
    return 0;
}

// int main(void)
{
    printf("Welcome to Battle Sips!\n\n");

    printf("Initializing player 1...");
    // Create sea for Player1
    struct battleSea seaP1 = {1};
    initBattleSea(&seaP1);
    resetSea(&seaP1);
    printf("done!\n");

    // Create sea for Player2
    printf("Initializing player 2...");
    struct battleSea seaP2 = {2};
    initBattleSea(&seaP2);
    resetSea(&seaP2);
    printf("done!\n");

    printf("\n");

    for (int player = 0; player < numberOfPlayers; player++)
    {
        printf("---Player %d--- \n", player + 1);
        for (int i = numberOfShips; i > 0; i--)
        {
            printf("-Place ship %d-\n", i);
            int x, y, o;
            do
            {
                printf("Type orientation: ");
                scanf("%d", &o);
            } while (o < 0 || o > 1);


            do
            {
                printf("Type x: ");
                scanf("%d", &x);
            } while (o == 0 && (x > seaDimX - i || x < 0));

            do
            {
                printf("\nType y:");
                scanf("%d", &y);
            } while (o == 1 && (y > seaDimY - i || y < 0));

            printf("\n");
            // Output the number the user typed
            printf("Coordinates: %d,%d \n", x, y);
            placeShip(i, x, y, o, &seaP1);
        }
        printf("\n");
        printSea(seaP1);
    }

    // Place ships for Player1
    //  Place ship 3
    // while(!placeShip(3, 3, 2, 1, &seaP1));

    // Place ships for Player2
    checkHit(shoot(0, 0, &seaP1), &seaP1); // hit
    printSea(seaP1);
    checkHit(shoot(3, 3, &seaP1), &seaP1); // hit
    printSea(seaP1);
    checkHit(shoot(3, 0, &seaP1), &seaP1); // hit
    printSea(seaP1);
    checkHit(shoot(1, 0, &seaP1), &seaP1); // hit
    printSea(seaP1);
    checkHit(shoot(3, 2, &seaP1), &seaP1); // hit
    printSea(seaP1);
    checkHit(shoot(3, 1, &seaP1), &seaP1); // hit
    printSea(seaP1);
    // Shoot Player 1
    // Shoot Player 2

    // check sea
    if (!checkShipArray(&seaP1))
    {
        printf("Game Over! \n");
    }
    else
    {
        printf("Game continues...\n");
    }

    checkHit(shoot(0, 3, &seaP1), &seaP1); // hit
    printSea(seaP1);
    // check sea
    if (!checkShipArray(&seaP1))
    {
        printf("Game Over! \n");
    }
    else
    {
        printf("Game continues...\n");
    }

    return 0;
}
