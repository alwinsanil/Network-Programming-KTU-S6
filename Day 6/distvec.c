#include &lt; stdio.h & gt;
struct node
{
    unsigned dist[20];
    unsigned from[20];
} rt[10];
int main()
{
    int costmat[20][20];
    int nodes, i, j, k, count = 0;
    printf(&quot;\nEnter the number of nodes
           : &quot;);
    scanf(&quot; % d & quot;, &amp; nodes); // Enter the nodes
    printf(&quot;\nEnter the cost matrix
           :\n & quot;);
    for (i = 0; i & lt; nodes; i++)
    {
        for (j = 0; j & lt; nodes; j++)
        {
            scanf(&quot; % d & quot;, &amp; costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j]; // initialise the distance equal to cost matrix
            rt[i].from[j] = j;
        }
    }
    do
    {
        count = 0;
        for (i = 0; i & lt; nodes; i++)
            // and add the distance from k to node j
            for (j = 0; j & lt; nodes; j++)
                for (k = 0; k & lt; nodes; k++)
                    if (rt[i].dist[j] & gt; costmat[i][k] + rt[k].dist[j])
                    { // We calculate the minimum distance
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
    } while (count != 0);
    for (i = 0; i & lt; nodes; i++)
    {
        printf(&quot;\n\n For router % d\n & quot;, i + 1);
        for (j = 0; j & lt; nodes; j++)
        {
            printf(&quot;\t\nnode % d via % d Distance % d & quot;, j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }
    printf(&quot;\n\n & quot;);
}