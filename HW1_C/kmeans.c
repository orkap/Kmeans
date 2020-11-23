#include <stdlib.h>
#include <stdio.h>

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
int addToClosestcluster(Cluster *clusters, Observation * obs, int first_insert);
double calculateDistance(Observation *observation, Cluster *cluster);
void mainLogic (Cluster* cluster);
void changeMean(Cluster *cluster);

void printCluster(Cluster *cluster)
{
    for (int i=0; i<d; ++i)
    {
        if (i==d-1)
            printf("%.2f",cluster->prevCentroids[i]);
        else
            printf("%.2f,",cluster->prevCentroids[i]);
    }
}
void addToMean(Cluster *cluster, Observation *obs) {
    double sumObs;
    for (int i=0; i<d; ++i)
    {
        sumObs = (cluster->centroids[i]) * (cluster ->size);
        cluster->centroids[i] = (sumObs + obs->values[i]) / ((cluster->size)+1);
    }
}

void removeFromMean(Cluster *cluster, Observation *obs)
{
    double sumObs;
    for (int i=0; i<d; ++i)
    {
        sumObs = (cluster->centroids[i]) * (cluster ->size);
        cluster->centroids[i] = (sumObs - obs->values[i]) / ((cluster->size)-1);
    }
}
void changeMean(Cluster *cluster)
{
    for (int i=0; i<d; ++i)
    {
        cluster->prevCentroids[i] = cluster->centroids[i];
    }
}

double calculateDistance(Observation *observation, Cluster *cluster)
{
    double distance;
    double sum = 0.0f;
        for (int i=0; i<d; ++i)
        {
            distance = (cluster->prevCentroids[i] - observation->values[i]);
            distance = distance * distance;
            sum += distance;
        }
    return sum;
}


int addToClosestcluster(Cluster *clusters, Observation * obs, int first_insert) {
    int i, myIndex, prevIndex;
    double min, distance;
    min = calculateDistance(obs, clusters);
    myIndex = 0;
    for (i = 1; i < K; ++i) {
        distance = calculateDistance(obs, &clusters[i]);
        if (distance < min) {
            min = distance;
            myIndex = i;
        }
    }
    prevIndex = (*obs).cluster;
    if (first_insert) {
        (*obs).cluster = myIndex;
        addToMean(clusters +myIndex, obs);
        clusters[myIndex].size += 1;
        return 1;
    } else if (prevIndex != myIndex) {
        (*obs).cluster = myIndex;
        addToMean(clusters+myIndex, obs);
        clusters[myIndex].size += 1;
        removeFromMean(clusters+prevIndex, obs);
        clusters[prevIndex].size -= 1;
        return 1;
    }
    return 0;
}

 void mainLogic (Cluster *clusters)
{
    Observation* observations_arr = malloc(N * sizeof(struct Observation));
    int counter = 0;
    double n1;
    char c;
    int i = 0;
    while (scanf("%lf%c", &n1, &c) == 2)
    {
        if (i==0) {
            observations_arr[counter].values = (double*) malloc((d+1)*sizeof(double));
        }
        observations_arr[counter].values[i] = n1;
        if (counter<K) {
            if (i == 0) {
                clusters[counter].size = 1;
                observations_arr[counter].cluster = counter;
                clusters[counter].centroids = (double *) malloc((d + 1) * sizeof(double));
                clusters[counter].prevCentroids = (double *) malloc((d + 1) * sizeof(double));
            }
            clusters[counter].centroids[i] = n1;
            clusters[counter].prevCentroids[i] = n1;
        }
        i += 1;
        if (i == d) {
            i = 0;
            counter += 1;
        }
    }
    for (int j=K; j<N; ++j) {
        addToClosestcluster(clusters, &observations_arr[j], 1);
    }
    for(int indexCluster=0; indexCluster<K; ++indexCluster)
    {
        changeMean(&clusters[indexCluster]);
    }
    int iter = 1;
    int anyoneChanged;
    while (iter < MAX_ITER) {
        anyoneChanged = 0;
        for (int obsNum=0; obsNum<N; ++obsNum) {
            int changed = addToClosestcluster(clusters, &observations_arr[obsNum], 0);
            if (changed)
                anyoneChanged = 1;
        }
        for(int indexCluster=0; indexCluster<K; ++indexCluster)
        {
            changeMean(&clusters[indexCluster]);
        }
        if (!anyoneChanged)
            break;
        iter += 1;
    }
    for (i=0; i<N; ++i)
    {
        free(observations_arr[i].values);
        free(&observations_arr[i]);
    }
}

int main(int argc, char* argv[])
{
    int i;
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

    Cluster clusters[K];
    mainLogic(clusters);
    for (i=0; i<K; ++i)
    {
        printCluster(&clusters[i]);
        if (i!=K)
            printf("\n");
    }
    for (i=0; i<K; ++i)
    {
        free(clusters[i].centroids);
        free(clusters[i].prevCentroids);
        free(&clusters[i]);
    }
    return 0;
}