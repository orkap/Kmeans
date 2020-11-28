#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int K, N, d, MAX_ITER;

typedef struct Cluster
{
    int size;
    double *prevCentroids;
    double *centroids;
} Cluster;

typedef struct Observation
{
    int cluster;
    double *values;
} Observation;

void printCluster(Cluster *cluster);
void addToMean(Cluster *cluster, Observation *obs);
void removeFromMean(Cluster *cluster, Observation *obs);
void addToClosestcluster(Cluster *clusters, Observation * obs, int first_insert);
double calculateDistance(Observation *observation, Cluster *cluster);
void mainLogic (Cluster* cluster);
int changeMean(Cluster *cluster);

void printCluster(Cluster *cluster)
{
    int i;
    for (i=0; i<d; ++i)
    {
        if (i==d-1)
            printf("%.2f",cluster->prevCentroids[i]);
        else
            printf("%.2f,",cluster->prevCentroids[i]);
    }
}
void addToMean(Cluster *cluster, Observation *obs) {
    int i;
    double sumObs;
    for (i=0; i<d; ++i)
    {
        sumObs = (cluster->centroids[i]) * (cluster ->size);
        cluster->centroids[i] = (sumObs + obs->values[i]) / ((cluster->size)+1);
    }
}

void removeFromMean(Cluster *cluster, Observation *obs)
{
    int i;
    double sumObs;
    for (i=0; i<d; ++i)
    {
        sumObs = (cluster->centroids[i]) * (cluster ->size);
        cluster->centroids[i] = (sumObs - obs->values[i]) / ((cluster->size)-1);
    }
}
int changeMean(Cluster *cluster)
{
    int changed = 0;
    int i;
    for (i=0; i<d; ++i)
    {
        if (cluster->prevCentroids[i] != cluster->centroids[i])
            changed = 1;
        cluster->prevCentroids[i] = cluster->centroids[i];
    }
    return changed;
}

double calculateDistance(Observation *observation, Cluster *cluster)
{
    int i;
    double distance;
    double sum = 0.0f;
        for (i=0; i<d; ++i)
        {
            distance = (cluster->prevCentroids[i] - observation->values[i]);
            distance = distance * distance;
            sum += distance;
        }
    return sum;
}


void addToClosestcluster(Cluster *clusters_arr, Observation *obs, int first_insert) {
    int i, myIndex, prevIndex;
    double min, distance;
    min = calculateDistance(obs, clusters_arr);
    myIndex = 0;
    for (i = 1; i < K; ++i) {
        distance = calculateDistance(obs, &clusters_arr[i]);
        if (distance < min) {
            min = distance;
            myIndex = i;
        }
    }
    prevIndex = (*obs).cluster;
    if (first_insert) {
        (*obs).cluster = myIndex;
        addToMean(clusters_arr +myIndex, obs);
        clusters_arr[myIndex].size += 1;
    } else if (prevIndex != myIndex) {
        (*obs).cluster = myIndex;
        addToMean(clusters_arr+myIndex, obs);
        clusters_arr[myIndex].size += 1;
        removeFromMean(clusters_arr+prevIndex, obs);
        clusters_arr[prevIndex].size -= 1;
    }
}

 void mainLogic (Cluster *clusters_arr)
{
    int counter = 0;
    double n1;
    char c;
    int i = 0;
    int iter = 1;
    int anyoneChanged;
    int j;
    Observation* observations_arr = malloc(N * sizeof(Observation));
    assert(observations_arr != NULL);
    while (scanf("%lf%c", &n1, &c) == 2)
    {
        if (i==0) {
            observations_arr[counter].values = (double*) malloc(d * sizeof(double));
            assert(observations_arr[counter].values != NULL);
        }
        observations_arr[counter].values[i] = n1;
        if (counter<K) {
            if (i == 0) {
                clusters_arr[counter].size = 1;
                observations_arr[counter].cluster = counter;
                clusters_arr[counter].centroids = (double *) malloc(d * sizeof(double));
                assert(clusters_arr[counter].centroids != NULL);
                clusters_arr[counter].prevCentroids = (double *) malloc(d * sizeof(double));
                assert(clusters_arr[counter].prevCentroids != NULL);
                clusters_arr[counter].size = 1;
            }
            clusters_arr[counter].centroids[i] = n1;
            clusters_arr[counter].prevCentroids[i] = n1;
        }
        i += 1;
        if (i == d) {
            i = 0;
            counter += 1;
        }
    }
    for (j=K; j<N; ++j) {
        addToClosestcluster(clusters_arr, &observations_arr[j], 1);
    }
    for(j=0; j<K; ++j)
    {
        changeMean(&clusters_arr[j]);
    }
    while (iter < MAX_ITER) {
        anyoneChanged = 0;
        for (j=0; j<N; ++j) {
            addToClosestcluster(clusters_arr, &observations_arr[j], 0);
        }
        for(j=0; j<K; ++j)
        {
            int changed = changeMean(&clusters_arr[j]);
            if (changed)
                anyoneChanged = 1;
        }
        if (!anyoneChanged)
            break;
        iter += 1;
    }
    for (i=0; i<N; ++i)
    {
        free(observations_arr[i].values);
    }
    free(observations_arr);
}

int main(int argc, char* argv[])
{
    int i;
    Cluster *clusters_arr;
    assert(argc>=5);
    K = atoi(argv[1]);
    N = atoi(argv[2]);
    d = atoi(argv[3]);
    MAX_ITER = atoi(argv[4]);
    if (K==0 || N==0 || d==0 || MAX_ITER==0)
    {
        printf("Not all required arguments were passed\n");
        exit(-1);
    }
    else if (K > N) {
        printf("Cant have more clusters than observations\n");
        exit(-1);
    }

    clusters_arr = malloc(K * sizeof(Cluster));
    mainLogic(clusters_arr);
    for (i=0; i<K; ++i)
    {
        printCluster(&clusters_arr[i]);
        if (i!=K)
            printf("\n");
    }
    for (i=0; i<K; ++i)
    {
        free(clusters_arr[i].centroids);
        free(clusters_arr[i].prevCentroids);
    }
    free(clusters_arr);
    return 0;
}