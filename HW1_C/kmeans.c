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
void updateMean(int indexCluster, Cluster **clusters, Observation *obs);
int addToClosestcluster(int obsNum,Cluster **clusters, Observation **observations);
double calculateDistance(Observation *observation, Cluster *cluster);
void mainLogic (Cluster** cluster);
void changeMean(int indexCluster, Cluster **clusters);

void printCluster(Cluster *cluster)
{
    for (int i=0; i<d; ++i)
    {
        printf("%.2f,",cluster->centroids[i]);
    }
}

void updateMean(int indexCluster, Cluster **clusters, Observation *obs)
{
    for (int i=0; i<d; ++i)
    {
        clusters[indexCluster]->centroids[i] = clusters[indexCluster]->centroids[i] - obs->values[i];
    }
}
void changeMean(int indexCluster, Cluster **clusters)
{
    for (int i=0; i<d; ++i)
    {
        clusters[indexCluster]->prevCentroids[i] = clusters[indexCluster]->centroids[i];
    }
}

double calculateDistance(Observation *observation, Cluster *cluster)
{
    double distance;
    double sum = 0.0f;
        for (int i=0; i<d; ++i)
        {
            distance = (cluster->centroids[i] - observation->values[i]);
            distance = distance * distance;
            sum += distance;
        }
    return sum;
}


int addToClosestcluster(int obsNum,Cluster **clusters, Observation **observations)
{
    /*
changes = False
min = calculateDistance(observations_arr[obsNum], clusters[0], d)
myIndex = 0
for indexCluster in range(1, len(clusters)): # for each cluster
    distance = calculateDistance(observations_arr[obsNum], clusters[indexCluster], d)
    if distance < min: # editing the nearest cluster, saving it's index and sum
        min = distance
        myIndex = indexCluster
prevIndex = observations_arr[obsNum].cluster
if prevIndex is None:
    observations_arr[obsNum].cluster = myIndex
    clusters[myIndex].observations.add(obsNum)
    clusters[myIndex].size += 1
    changes = True
elif prevIndex!= myIndex:
    #if clusters[prevIndex].size() != 1: # if that is the only observation in the cluster we dont want to do anything
    clusters[myIndex].observations.add(obsNum) # add the observation number to the clusters's observation set
    clusters[myIndex].size += 1 # edit the size of the set
    clusters[prevIndex].observations.remove(obsNum) # remove it from its last cluster
    clusters[prevIndex].size -= 1 # remove it from its last cluster
    observations_arr[obsNum].cluster = myIndex # change the pointer in observations_arr to the new cluster's number
    changes = True # we changed at least on observation so we cant exit the loop
return changes
 */
    return 0;
}

 void mainLogic (Cluster** clusters)
{
    Observation* observations_arr[N];
    int counter = 0;
    double n1;
    char c;
    int i = 0;
    while (scanf("%lf%c", &n1, &c) == 2)
    {
        if (i==0)
            observations_arr[counter]->values = (double*) malloc((d+1) * sizeof(double));
        observations_arr[counter]->values[i] = n1;
        if (counter<K) {
            if (i == 0) {
                clusters[counter]->centroids = (double *) malloc((d + 1) * sizeof(double));
                clusters[counter]->prevCentroids = (double *) malloc((d + 1) * sizeof(double));
            }
            clusters[counter]->centroids[i] = n1;
            clusters[counter]->prevCentroids[i] = n1;
        }
        i += 1;
        if (i == d) {
            clusters[counter]->size += 1;
            observations_arr[counter]->cluster = counter;
            i = 0;
            counter += 1;
        }
    }
    for (int j=K; j<N; ++j) {
        addToClosestcluster(j, clusters, observations_arr);
    }
    int iter = 1;
    int changed;
    while (iter < MAX_ITER) {
        int numOfChanges = 0;
        for (int obsNum=0; obsNum<N; ++obsNum) {
            changed = addToClosestcluster(obsNum, clusters, observations_arr);
        }
        if (changed)
            numOfChanges += 1;
        for(int indexCluster=0; indexCluster<K; ++indexCluster)
        {
            changeMean(indexCluster, clusters);
        }
        if (numOfChanges == 0)
            break;
        iter += 1;
    }
}

int main1(int argc, char* argv[])
{
    K = atoi(argv[1]);
    N = atoi(argv[2]);
    d = atoi(argv[3]);
    MAX_ITER = atoi(argv[4]);
    if (K==0 || N==0 || d==0 || MAX_ITER==0)
    {
        printf("Not all required arguments were passed");
        exit(-1);
    }
    else if (K > N) {
        printf("Can\'t have more clusters than observations");;
        exit(-1);
    }

    Cluster* clusters[K];
    mainLogic(clusters);
    for (int i=0; i<K; ++i)
    {
        printCluster(clusters[i]);
        if (i!=K)
            printf("\n");
    }
    return 0;
}