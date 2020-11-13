import argparse
import sys


class Cluster:
    def __init__(self, dValues):
        self.size = 0
        self.centroids = dValues

    def __repr__(self):
        return ','.join(self.centroids)

class Observation:
    def __init__(self, dValues):
        self.values = dValues


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
                    cluster.size += 1
                    clusters.append(cluster)
                    observations_arr[counter][1] = counter
                    counter += 1
        except EOFError:
            break
    ##### Mathematical Calculation #####
    exit(0)


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