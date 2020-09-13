from node import *
import numpy as np
import csv
import pandas
from enum import IntEnum
import math


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath):
        # TODO : read file and implement a data structure you like
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.explored_nodes = []
        # 4, 8, 13, 20
        self.nd_dict = dict()  # key: index, value: the correspond node
        for row in self.raw_data:
            node = Node(int(row[0]))
            for col in range(1,5):
                if math.isnan(row[col]) == False:
                    node.setSuccessor(int(row[col]), col, row[col+4])
            self.nodes.append(node)
            self.nd_dict[row[0]] = node
        self.nowdirection = 1

    def getStartPoint(self, startnd):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        if (startnd not in self.nd_dict):
            print("Error: the start point is not included.")
            return 0        
        return self.nd_dict[startnd]

    def setStartDirection(self, startnd):
        SP = self.getStartPoint(startnd)
        for Successor in SP.getSuccessors():
            self.nowdirection = Successor[1]
            print("StartDirection set")

    def getNowDirection(self):
        return self.nowdirection
    
    def getNodeDict(self):
        return self.nd_dict

    def BFS(self, nd):
        # TODO : design your data structure here for your algorithm
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        self.explored_nodes.append(nd)
        Q = [nd]
        M = [nd]
        P = {}
        destination = -1
        d = {nd:0, destination:10000}
        reversePath = []
        while(len(Q) != 0):
            n = Q.pop(0)
            for Successor in self.nd_dict[n].getSuccessors():
                if Successor[0] not in M:
                    M.append(Successor[0])
                    Q.append(Successor[0])
                    P[Successor[0]] = n
                    d[Successor[0]] = d[n]+Successor[2]
                    if len(self.nd_dict[Successor[0]].getSuccessors()) == 1:
                        if Successor[0] not in self.explored_nodes:
                            if d[Successor[0]] < d[destination]:
                                destination = Successor[0]
                            elif d[Successor[0]] == d[destination]:
                                if Successor[0] < destination:
                                    destination = Successor[0]

        print(destination)
        if destination == -1:
            return [nd]
        self.explored_nodes.append(destination)
        reversePath.append(destination)
        p = P[destination]
        #print(p)
        print(reversePath)
        while(p != nd):
            reversePath.append(p)
            p = P[p]
            #print(p)
            print(reversePath)
            
        reversePath.append(nd)
        print(reversePath)
        reversePath.reverse()
        Path = reversePath[:]
        return Path

    def BFS_2(self, nd_from, nd_to):
        # TODO : similar to BFS but fixed start point and end point
        # Tips : return a sequence of nodes of the shortest path
        self.explored_nodes.append(nd_from)
        Q = [nd_from]
        M = [nd_from]
        P = {}
        destination = -1
        d = {nd_from:0}
        reversePath = []
        while(len(Q) != 0):
            n = Q.pop(0)
            for Successor in self.nd_dict[n].getSuccessors():
                if Successor[0] not in M:
                    M.append(Successor[0])
                    Q.append(Successor[0])
                    P[Successor[0]] = n
                    d[Successor[0]] = d[n]+Successor[2]
                    if Successor[0] == nd_to:
                        destination = Successor[0]
                        print(destination)
                        break

        self.explored_nodes.append(destination)
        reversePath.append(destination)
        p = P[destination]
        #print(p)
        print(reversePath)
        while(p != nd_from):
            reversePath.append(p)
            p = P[p]
            #print(p)
            print(reversePath)
            
        reversePath.append(nd_from)
        print(reversePath)
        reversePath.reverse()
        Path = reversePath[:]
        return Path

    def getAction(self, car_dir, nd_from, nd_to):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car
        action = -1
        for Successor in self.nd_dict[nd_from].getSuccessors():
            if Successor[0] == nd_to:
                direction = Successor[1]
                print("direction = ", Successor[1])

        if direction == car_dir:
            action = Action.ADVANCE
        elif (direction == 1 and car_dir == 2) or (direction == 2 and car_dir == 1) or (direction == 3 and car_dir == 4) or (direction == 4 and car_dir == 3):
            action = Action.U_TURN
        elif (direction == 4 and car_dir == 1) or (direction == 3 and car_dir == 2) or (direction == 1 and car_dir == 3) or (direction == 2 and car_dir == 4):
            action = Action.TURN_RIGHT
        elif (direction == 3 and car_dir == 1) or (direction == 4 and car_dir == 2) or (direction == 2 and car_dir == 3) or (direction == 1 and car_dir == 4):
            action = Action.TURN_LEFT
        self.nowdirection = direction
        return action

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)

if __name__ == '__main__':
    maze = Maze("data/medium_maze.csv")
    maze.setStartDirection()
    print(maze.nowdirection)
    print(maze.BFS(1))
    print(maze.BFS(3))
    print(maze.BFS(7))
    print(maze.BFS(9))
    print(maze.BFS(12))
    print(maze.BFS_2(1, 8))
    print(maze.BFS_2(7, 9))
    print(maze.getAction(maze.nowdirection, 1, 2))
    print(maze.nowdirection)
    print(maze.getAction(maze.nowdirection, 2, 3))
    print(maze.nowdirection)
    print(maze.getAction(maze.nowdirection, 3, 2))
    print(maze.nowdirection)
    print(maze.getAction(maze.nowdirection, 2, 4))
    print(maze.nowdirection)
    print(Direction.EAST == 4)