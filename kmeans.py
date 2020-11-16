import argparse
import sys


class Cluster:
    def __init__(self, dValues):
        self.size = 0
        self.observations = set()
        self.centroids = dValues[:]

    def __repr__(self):
        return ','.join(self.centroids)

class Observation:
    def __init__(self, dValues):
        self.values = dValues[:]


def main(K, N, d, MAX_ITER):
    observations_arr = []
    clusters = []
    counter = 0
    while True:
        try:
            for line in input().split('\n'):
                values = line.split(',')
                observation = Observation(values)
                observations_arr.append([observation, None])
                if counter < K:
                    cluster = Cluster(values)
                    cluster.observations.add(counter)
                    cluster.size += 1
                    clusters.append(cluster)
                    observations_arr[counter][1] = counter
                    counter += 1
        except EOFError:
            break
    iter = 0
    while iter<MAX_ITER:
        changes = false
        for obsNum in range(N):
            changes = addToClosestcluster(obsNum, observations_arr, clusters, changes, d)
        for indexCluster in range(len(clusters)):
            changeMean(indexCluster, clusters, observations_arr, d)
        if changes != true:
            break
        iter += 1

    ##### Mathematical Calculation #####
    exit(0)

def addToClosestcluster(obsNum,observations_arr, clusters, changes, d):
    min = sys.maxint
    myIndex = -1
    for indexCluster in range(len(clusters)): # for each cluster
        sum = 0
        for indexD in range(d): # for each centroid in the cluster we will calculate the distance
            sum += math.pow(abs(clusters[indexCluster].centroids[indexD] - observations_arr[obsNum][indexD]), 2)
        if sum < min: # editing the nearest cluster, saving it's index and sum
            min = sum
            myIndex = indexCluster
    if myIndex > -1:
        if (observations_arr[obsNum] != myIndex):
            if clusters[observations_arr[obsNum]].size() != 1: # if that is the only observation in the cluster we dont want to do anything
                clusters[myIndex].observation.add(obsNum) # add the observation number to the clusters's observation set
                clusters[observations_arr[obsNum]].remove(obsNum) # remove it from its last cluster
                observations_arr[obsNum] = myIndex # change the pointer in observations_arr to the new cluster's number
                clusters[myIndex].size += 1 # edit the size of the set
                changes = true # we changed at least on observation so we cant exit the loop
    return changes


def changeMean(indexCluster, clusters, observations_arr, d):
    for indexD in d:
        sum = 0
        for obs in clusters[indexCluster].observations():
            sum += observations_arr[obs].values[indexD]
        sum /= clusters[indexCluster].size()
        clusters[indexCluster].centroids[indexD] = math.floor(sum, 2)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("K", help="number of clusters")
    parser.add_argument("N", help="number of observations")
    parser.add_argument("d", help="number of values in an observation")
    parser.add_argument("MAX_ITER", help="max iterations")

    args = parser.parse_args()

    if args.K is None or args.N is None or args.d is None or args.MAX_ITER is None:
        sys.exit('Not all required arguments were passed')
    elif args.K > args.N:
        sys.exit('Can\'t have more clusters than observations')
    else:
        main(args.K, args.N, args.d, args.MAX_ITER)