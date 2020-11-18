import argparse

class Cluster:
    def __init__(self, dValues):
        self.size = 0
        self.observations = set()
        self.centroids = [float(value) for value in dValues]

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
                observation = Observation(values, None)
                observations_arr.append(observation)
                if counter < K:
                    cluster = Cluster(values)
                    cluster.observations.add(counter)
                    cluster.size += 1
                    clusters.append(cluster)
                    observations_arr[counter].cluster = counter
                    counter += 1
        except EOFError:
            break
    for i in range(K, N):
        addToClosestcluster(i, observations_arr, clusters, d)
        for indexCluster in range(len(clusters)):
            changeMean(indexCluster, clusters, observations_arr, d)
    iter = 1
    while iter < MAX_ITER:
        for cluster in clusters:
            print(cluster, " size: ", cluster.size)
        print ("_______________")
        numOfChanges = 0
        for obsNum in range(N):
            changed = addToClosestcluster(obsNum, observations_arr, clusters, d)
            if changed:
                numOfChanges += 1
        for indexCluster in range(len(clusters)):
            changeMean(indexCluster, clusters, observations_arr, d)
        if numOfChanges == 0:
            break
        iter += 1
    return (clusters)

def calculateDistance(observation, cluster, d):
    sum = 0
    for indexD in range(d):  # for each centroid in the cluster we will calculate the distance
        distance = (abs(cluster.centroids[indexD] - observation.values[indexD])) ** 2
        sum += distance
    return sum

def addToClosestcluster(obsNum,observations_arr, clusters, d):
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


def changeMean(indexCluster, clusters, observations_arr, d):
    for indexD in range(d):
        sum = 0
        for obsNum in clusters[indexCluster].observations:
            sum += observations_arr[obsNum].values[indexD]
        sum /= clusters[indexCluster].size
        clusters[indexCluster].centroids[indexD] = sum


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
        results = main(int(args.K), int(args.N), int(args.d), int(args.MAX_ITER))

    for cluster in results:
        print(cluster)