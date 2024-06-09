#include <stdio.h>
#include <stdlib.h>

const int seaDimX = 4;
const int seaDimY = 4;
const int numberOfShips = 3;
const int dbg = 1;

struct battleSea
{
    int player;
    int **matrix;
};

// Allocate memory for sea
int initBattleSea(struct battleSea *sea)
{
    if (dbg)
        printf("- DBG: Initializing battleSea for Player %d...\n", (*sea).player);

    (*sea).matrix = malloc(seaDimY * sizeof(int *));
    for (int i = 0; i < seaDimX; i++)
        (*sea).matrix[i] = malloc(seaDimX * sizeof(int));

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

// Shoot at x,y
// returns 1 on hit, zero on miss
int shoot(int targX, int targY, struct battleSea *sea)
{
    if ((*sea).matrix[targX][targY] > 0 && (*sea).matrix[targX][targY] <= numberOfShips)
    {
        if (dbg)
            printf("- DBG: Hitting (%d, %d) = %d\n", targX, targY, (*sea).matrix[targX][targY]);
        (*sea).matrix[targX][targY] = (*sea).matrix[targX][targY] + numberOfShips;
        if (dbg)
            printf("- DBG: Hit (%d, %d) = %d\n", targX, targY, (*sea).matrix[targX][targY]);
        return 1;
    }
    else
    {
        if (dbg)
            printf("- DBG: Missing (%d, %d) = %d\n", targX, targY, (*sea).matrix[targX][targY]);
        (*sea).matrix[targX][targY] = numberOfShips * 2 + 1;
        if (dbg)
            printf("- DBG: Missed (%d, %d) = %d\n", targX, targY, (*sea).matrix[targX][targY]);
        return 0;
    }
}

int checkSea(struct battleSea *sea)
{
    if (dbg)
        printf("Checking Status \n");

    // Create array for shipcount
    int seaStatus[numberOfShips];
    for (int i = 0; i < numberOfShips; i++)
    {
        seaStatus[i] = 0;
    }

    // Check how much is left of each chip
    for (int x = 0; x < seaDimX; x++)
    {
        for (int y = 0; y < seaDimY; y++)
        {
            if ((*sea).matrix[x][y] - 1 < numberOfShips)
            {
                seaStatus[(*sea).matrix[x][y] - 1]++;
            }
            if (dbg)
            {
                for (int i = 0; i < numberOfShips; i++)
                {
                    printf("(%d, %d) \t seaStatus %d=%d\n", x, y, i, seaStatus[i]);
                }
            }
        }
    }

    // Return 1 if there are ships left, else 0;
    for (int i = 0; i < numberOfShips; i++)
    {
        if (seaStatus[i] != 0)
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    printf("Welcome to Battle Sips!\n\n");

    // Create sea for Player1
    struct battleSea seaP1 = {1};
    initBattleSea(&seaP1);
    resetSea(&seaP1);
    printSea(seaP1);

    // Create sea for Player2

    // Place ships for Player1
    //  Place ship 3
    // while(!placeShip(3, 3, 2, 1, &seaP1));
    placeShip(3, 3, 1, 1, &seaP1);
    placeShip(2, 0, 0, 0, &seaP1);
    placeShip(1, 0, 3, 0, &seaP1);
    if (dbg)
        (printSea(seaP1));

    // Place ships for Player2
    shoot(0, 0, &seaP1); // hit
    printSea(seaP1);
    shoot(3, 3, &seaP1); // hit
    printSea(seaP1);
    shoot(3, 0, &seaP1); // hit
    printSea(seaP1);
    // Shoot Player 1
    // Shoot Player 2

    // check sea
    if (!checkSea(&seaP1)){
        printf("Game finished!");
    }

    return 0;
}
