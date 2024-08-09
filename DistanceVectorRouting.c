// #include <stdio.h>
// #include <stdbool.h>
// #include <limits.h>

// #define MAX_ROUTERS 10
// #define INFINITY INT_MAX

// typedef struct
// {
//     int distance[MAX_ROUTERS];
//     int nextHop[MAX_ROUTERS];
// } DistanceVector;

// void initialize(DistanceVector *dv, int selfRouter, int numRouters)
// {
//     for (int i = 0; i < numRouters; i++)
//     {
//         dv->distance[i] = INFINITY;
//         dv->nextHop[i] = -1;
//     }
//     dv->distance[selfRouter] = 0;
// }

// void updateTable(DistanceVector *dv, int numRouters, int numLinks, int links[][3])
// {
//     bool updated = false;

//     for (int i = 0; i < numRouters; i++)
//     {
//         for (int j = 0; j < numLinks; j++)
//         {
//             int source = links[j][0];
//             int destination = links[j][1];
//             int distance = links[j][2];

//             if (dv->distance[source] != INFINITY && dv->distance[source] + distance < dv->distance[destination])
//             {
//                 dv->distance[destination] = dv->distance[source] + distance;
//                 dv->nextHop[destination] = source;
//                 updated = true;
//             }
//         }
//     }

//     if (updated)
//     {
//         printf("Updated routing table:\n");
//         printf("Node\tNext Hop\tDistance\n");
//         for (int i = 0; i < numRouters; i++)
//         {
//             if (dv->distance[i] == INFINITY)
//             {
//                 printf("%d\t%d\t\tinf\n", i, dv->nextHop[i]);
//             }
//             else
//             {
//                 printf("%d\t%d\t\t%d\n", i, dv->nextHop[i], dv->distance[i]);
//             }
//         }
//         printf("\n");
//     }
// }

// int main()
// {
//     int numRouters, numLinks;

//     printf("Enter the number of routers: ");
//     scanf("%d", &numRouters);

//     printf("Enter the number of links: ");
//     scanf("%d", &numLinks);

//     int links[numLinks][3];

//     printf("Enter the source, destination, and distance for each link:\n");
//     for (int i = 0; i < numLinks; i++)
//     {
//         printf("Link %d: ", i + 1);
//         scanf("%d %d %d", &links[i][0], &links[i][1], &links[i][2]);
//     }

//     DistanceVector dv;
//     initialize(&dv, 0, numRouters); // Assuming self router is router 0
//     updateTable(&dv, numRouters, numLinks, links);

//     return 0;
// }
#include <stdio.h>

struct node
{
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main()
{
    int dmat[20][20], n, i, j, k, count = 0;
    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);
    printf("\nEnter the cost matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dmat[i][j]);
            dmat[i][i] = 0;
            rt[i].dist[j] = dmat[i][j];
            rt[i].from[j] = j;
        }
    }

    do
    {
        count = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    if (rt[i].dist[j] > dmat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    for (i = 0; i < n; i++)
    {
        printf("\n\nState value for router %d is \n", i + 1);
        for (j = 0; j < n; j++)
        {
            printf("\t\nnode %d via %d Distance %d", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }

    return 0;
}
