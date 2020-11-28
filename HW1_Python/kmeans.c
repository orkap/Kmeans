#include <assert.h>
#include "stdlib.h"
#include "stdio.h"

typedef struct Cluster {
    int name, size;
    double *centroid;
    double *sum_of_obs;
} Cluster;

typedef struct Observation {
    double *values;
    Cluster *cluster;
} Observation;


void kmeans(int k, int n, int d, int max_iter);

void read_from_file(Observation **observations, int d, int n);

void clean(Observation **observations, int n, Cluster **cluster_array, int k);

void init(Observation **observations, int n, int d);

void find_closest_cluster(Observation *observation, Cluster **clusters_array, int k, int d);

double squared_euclidean_distance(double *observation, double *centroid, int d);

void observation_sum(double *sum_of_obs, double *observation_values, int d);

void observation_sub(double *sum_of_obs, const double *observation_values, int d);

void remove_obs(Observation *observation, Cluster **clusters_array,int d) ;

int update_centroid(Cluster **clusters_array, int k, int d);

void insert_obs(Observation *observation, Cluster *best_cluster, int d);

void create_k_clusters(Observation **observations, Cluster **clusters_array, int k);

void print_clusters(Cluster **clusters_array, int k, int d);

void kmeans(int k, int n, int d, int max_iter) {

    Observation *input_values[n];
    init(input_values, n, d);

    read_from_file(input_values, d, n);

    int is_changed_from_last_run = 1;
    int found_k_clusters = 0;
    int number_of_iter = 1;
    int obs_num = k;
    Cluster *clusters_array[k];
//    int i;
//    for (i = 0; i < n; i++) {
//        printf("%f%c%f\n", input_values[i]->values[0], ',', input_values[i]->values[1]);
//    }

    while (is_changed_from_last_run == 1 && (number_of_iter <= max_iter)) {
        //main loop
        if (found_k_clusters == 1) {
            //k cluster have been initiated
            find_closest_cluster(input_values[obs_num], clusters_array, k, d);
            obs_num+=1;

        } else {
            //initiate k clusters
            create_k_clusters(input_values, clusters_array, k);
            found_k_clusters = 1;
            //print_clusters(clusters_array, k, d);
        }
        if (obs_num == n) {
            //start new iteration
            is_changed_from_last_run=update_centroid(clusters_array,k,d);
            obs_num = 0;
            number_of_iter += 1;
            print_clusters(clusters_array, k, d);
            printf("\n---------------------------------------------------------------------\n");

        }
    }
    print_clusters(clusters_array, k, d);
    clean(input_values, n, clusters_array, k);
}

void print_clusters(Cluster **clusters_array, int k, int d) {
    int i;
    for (i = 0; i < k; i++) {
        int j;
        for (j = 0; j < d; j++) {
            if (j < d - 1) {
                printf("%.2f%s", clusters_array[i]->centroid[j], ",");
            } else {
                printf("%.2f", clusters_array[i]->centroid[j]);
            }
        }
        if (i != k - 1) {
            printf("\n");
        }
    }
}

void create_k_clusters(Observation **observations, Cluster **clusters_array, int k) {
    int index;
    for (index = 0; index < k; index++) {
        clusters_array[index] = malloc(sizeof(Cluster));
        assert(clusters_array[index] != NULL);
        clusters_array[index]->name = index;
        clusters_array[index]->size = 1;
        clusters_array[index]->centroid = observations[index]->values;
        clusters_array[index]->sum_of_obs = observations[index]->values;
    };
}

void init(Observation **observations, int n, int d) {
    int i;
    for (i = 0; i < n; i++) {
        observations[i] = malloc(sizeof(Observation));
        assert(observations[i] != NULL);
        observations[i]->values = (double *) calloc(d, sizeof(double));
        assert(observations[i]->values != NULL);
        observations[i]->cluster = NULL;
    }
}

void clean(Observation **observations, int n, Cluster **cluster_array, int k) {
    int i;
    for (i = 0; i < n; i++) {
        free(observations[i]->values);
        free(observations[i]);
    }
    int j;
    for (j = 0; j < k; j++) {
        free(cluster_array[j]);
    }
}

void read_from_file(Observation **observations, int d, int n) {
    double n1;
    char c;
    int i = 0, obs_num = 0;

    while (scanf("%lf%c", &n1, &c) == 2) {
        if (i < d && i != d - 1) {
            observations[obs_num]->values[i] = n1;
            i++;
        } else {
            observations[obs_num]->values[i] = n1;
//            printf("%f, %f\n", input[obs_num].values[0], input[obs_num].values[1]);
            obs_num++;
            i = 0;
        }
    }
}

void find_closest_cluster(Observation *observation, Cluster **clusters_array, int k, int d) {
    /*find closest cluster for observation (of class Observation)
    size of clusters_array is K, each index is of struct Cluster */

    int index;
    double min_dist;
    double dist;
    Cluster *best_cluster=NULL;

    min_dist = squared_euclidean_distance(observation->values, clusters_array[0]->centroid, d);
    best_cluster = clusters_array[0];

    //if (observation->cluster->size == 1) return;
    for (index=1; index < k; index++) {
        dist = squared_euclidean_distance(observation->values, clusters_array[index]->centroid, d);
        if (dist < min_dist) {
            min_dist = dist;
            printf("\nthe min dist is: %f\n", min_dist);
            best_cluster = clusters_array[index];
        }
    }
    if (observation->cluster != NULL){
        if (observation->cluster->name == best_cluster->name){ return; }
        remove_obs(observation, clusters_array, d);
    }
    insert_obs(observation, best_cluster, d);
}

double squared_euclidean_distance(double *observation, double *centroid, int d){
    /*find cluster’s centroid using squared Euclidean distance
    observation and centroid are lists of size D*/
    int index;
    double dist = 0;
    double temp;

    for (index =0; index < d; index++) {
        temp = (observation[index] - centroid[index]);
        dist += (temp*temp);
    }
    return dist;
}

void observation_sum(double *sum_of_obs, double *observation_values, int d){
    /* sum_of_obs is a list in len D that sums all observations that belongs to the cluster*/
    int index;
    for (index=0; index<d; index++){
        sum_of_obs[index] += observation_values[index];
    }
}

void insert_obs(Observation *observation, Cluster *best_cluster, int d) {
    observation_sum(best_cluster->sum_of_obs, observation->values, d);
    best_cluster->size++;
    observation->cluster = best_cluster;
}

void observation_sub(double *sum_of_obs, const double *observation_values, int d) {
    /*update sum_of_obs sum_of_obs is a list in len D that sums all observations that belongs to the cluster*/
    int index;
    for (index=0; index < d; index++){
        *(sum_of_obs + index) -= *(observation_values + index);
    }
}

void remove_obs(Observation *observation, Cluster **clusters_array,int d) {
    observation->cluster->size -= 1;
    observation_sub(observation->cluster->sum_of_obs, observation->values, d);
}

int update_centroid(Cluster **clusters_array, int k, int d){
    /*update centroid using the sum of observations that belongs to the cluster */
    int dpoint;
    int cluster_index;
    int is_changed = 0;
    double temp_calc = 0;

    for (cluster_index=0; cluster_index<k ;cluster_index++) {
        //iterate over the clusters
        Cluster *current_cluster = clusters_array[cluster_index];
        for (dpoint=0; dpoint<d; dpoint++){
            temp_calc = current_cluster->sum_of_obs[dpoint]/(float)current_cluster->size;
            if (temp_calc != current_cluster->centroid[dpoint]) {
                //check if the centroid in place dpoint should be updated
                current_cluster->centroid[dpoint] = temp_calc;
                is_changed = 1;
            }
        }
    }
    return is_changed;
}

int main(int argc, char *argv[]) {
    assert (argc >= 5);

    const int K = atoi(argv[1]);
    const int N = atoi(argv[2]);
    const int d = atoi(argv[3]);
    const int MAX_ITER = atoi(argv[4]);

    assert(K < N);

    kmeans(K, N, d, MAX_ITER);
    return EXIT_SUCCESS;
}