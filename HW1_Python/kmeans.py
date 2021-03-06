import argparse

class Cluster:
    def __init__(self, dValues):
        self.size = 0
        self.centroids = [float(value) for value in dValues]
        self.prevCentroids = [float(value) for value in dValues]

    def __repr__(self):
        tmp = ["%.2f" % value for value in self.centroids]
        return ','.join(tmp)

class Observation:
    def __init__(self, dValues, Cluster):
        self.values = [float(value) for value in dValues]
        self.cluster = Cluster

def main(K, N, d, MAX_ITER):
    observations_arr = []
    clusters = []
    counter = 0
    while True:
        try:
            for line in input().split('\n'):
                values = line.split(',')
                # observation = Observation(values, None)
                # observations_arr.append(observation)
                if counter < K:
                    observation = Observation(values, counter)
                    observations_arr.append(observation)
                    cluster = Cluster(values)
                    clusters.append(cluster)
                    cluster.size += 1
                    # observations_arr[counter].cluster = counter
                    counter += 1
                else:
                    observation = Observation(values, None)
                    observations_arr.append(observation)
        except EOFError:
            break
    for i in range(K, N):
        addToClosestcluster(i, observations_arr, clusters, d, K)
    for indexCluster in range(K):
        changeMean(indexCluster, clusters, d)

    iter = 1
    while iter < MAX_ITER:
        is_changed = False
        for obsNum in range(N):
            addToClosestcluster(obsNum, observations_arr, clusters, d, K)
        for indexCluster in range(K):
            changed = changeMean(indexCluster, clusters, d)
            if changed:
                is_changed = True
        if not is_changed:
            break
        iter += 1
    return (clusters)

def calculateDistance(observation, cluster, d):
    sum = 0
    for indexD in range(d):  # for each centroid in the cluster we will calculate the distance
        distance = (cluster.prevCentroids[indexD] - observation.values[indexD])
        distance *= distance
        sum += distance
    return sum

def addToClosestcluster(obsNum,observations_arr, clusters, d, K):
    # changes = False
    min = calculateDistance(observations_arr[obsNum], clusters[0], d)
    myIndex = 0
    for indexCluster in range(1, K): # for each cluster
        distance = calculateDistance(observations_arr[obsNum], clusters[indexCluster], d)
        if distance < min: # editing the nearest cluster, saving it's index and sum
            min = distance
            myIndex = indexCluster
    prevIndex = observations_arr[obsNum].cluster
    if prevIndex is None:
        observations_arr[obsNum].cluster = myIndex
        addToMean(clusters[myIndex], obsNum, observations_arr, d)
        clusters[myIndex].size += 1
    elif prevIndex != myIndex:
        #if clusters[prevIndex].size() != 1: # if that is the only observation in the cluster we dont want to do anything
        addToMean(clusters[myIndex], obsNum, observations_arr, d)
        clusters[myIndex].size += 1 # edit the size of the set
        removeFromMean(clusters[prevIndex], obsNum, observations_arr, d)
        clusters[prevIndex].size -= 1 # remove it from its last cluster
        observations_arr[obsNum].cluster = myIndex # change the pointer in observations_arr to the new cluster's number

def addToMean(cluster, obsNum, observations_arr, d):
    for indexD in range(d):
        sum = cluster.centroids[indexD] * cluster.size
        cluster.centroids[indexD] = (sum+observations_arr[obsNum].values[indexD]) / (cluster.size+1)

def removeFromMean(cluster, obsNum, observations_arr, d):
    for indexD in range(d):
        sum = cluster.centroids[indexD] * cluster.size
        cluster.centroids[indexD] = (sum - observations_arr[obsNum].values[indexD]) / (cluster.size-1)

def changeMean(indexCluster, clusters, d):
    changed = False
    for indexD in range(d):
        if (clusters[indexCluster].prevCentroids[indexD] != clusters[indexCluster].centroids[indexD]):
            changed = True
        clusters[indexCluster].prevCentroids[indexD] = clusters[indexCluster].centroids[indexD]
    return changed

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("K", help="number of clusters")
    parser.add_argument("N", help="number of observations")
    parser.add_argument("d", help="number of values in an observation")
    parser.add_argument("MAX_ITER", help="max iterations")
    args = parser.parse_args()

    if args.K is None or args.N is None or args.d is None or args.MAX_ITER is None:
        print('Not all required arguments were passed')
        quit()
    K = int(args.K)
    N = int(args.N)
    d = int(args.d)
    MAX_ITER = int(args.MAX_ITER)
    if K <= 0 or N <= 0 or d <= 0 or MAX_ITER <= 0:
        print('Not all required arguments are valid')
        exit(1)
    elif K > N:
        print('Can\'t have more clusters than observations')
        exit(1)
    else:
        results = main(int(args.K), int(args.N), int(args.d), int(args.MAX_ITER))

    for cluster in results:
        print(cluster)